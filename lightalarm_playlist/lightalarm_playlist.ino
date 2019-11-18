#include <ESP8266WiFi.h> //esp8266 library

#include <WiFiClient.h> //http requests to actual playlist location

#include <ESP8266WebServer.h> // fake playlist location serving (to trigger relais on call)
#include <ESP8266mDNS.h>  // support module for server

#include <WiFiManager.h>//no hard-coded wifi credentials

// ---- define D_x - GPIO_y mappings ----
//D0 is already:
//#define LED_BUILTIN 16
#define D1 5
#define D2 4
#define D3 0 //also:flash!!
#define D4 2 //also: TXD1!!
#define D5 14
#define D6 12
#define D7 13
#define D8 15

#define relay1 D1
#define relay2 D2
#define relay3 D5
#define relay4 D6


String String1 = String("[playlist]\n") +
"umberofentries=2\n"+
"File1=http://bbcwssc.ic.llnwd.net/stream/bbcwssc_mp1_ws-eieuk\n" +
"Title1=BBC World Service Online\n" +
"Length1=-1\n" +
"File2=http://bbcwssc.ic.llnwd.net/stream/bbcwssc_mp1_ws-eieuk_backup\n" +
"Title2=BBC World Service Online\n" +
"Length2=-1";


const int led = LED_BUILTIN;

ESP8266WebServer server(80); // global server object for playlist "serving"


// https://github.com/tzapu/WiFiManager
void connectWifi(){
  Serial.print("Connecting using wifiManager");
  WiFiManager wifiManager;
  wifiManager.setConfigPortalTimeout(360); // reboot after 360s if no new wifi entered
  wifiManager.autoConnect("AutoConnectAP"); // opens if previous conf. wifi is unreachable

  // continues only if connected
  Serial.println("Connected");
}//end connect

// setup serial and wifi
void setup() {
  Serial.begin(115200);
  Serial.println("serial set-up");
  connectWifi();

  mysetup();
}


void handleRoot() {
  digitalWrite(led, 1);
  server.send(200, "text/plain", "hello from esp8266!");
  digitalWrite(led, 0);
}

void handleNotFound(){
  digitalWrite(led, 1);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i=0; i<server.args(); i++){
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
  digitalWrite(led, 0);
}

void mysetup(void){

  Serial.println("setting up pins..");
  pinMode(led, OUTPUT);
  digitalWrite(led, 0);

  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);
  pinMode(relay3, OUTPUT);
  
  Serial.println("waiting for wifi to connect (wifi setup complete)");
  
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);


//  Setup the hooks for playlist listening and relais clicking.. 
//---- turnons ----

  server.on("/1.pls", [](){
    server.send(200, "audio/x-scpls", String1);//needed to make alarmclock-app happy
    digitalWrite(relay1, LOW);
    Serial.println("playlist triggered relay1 on");
    delay(1000);                      // Wait for a second
  });

  server.on("/2.pls", [](){
    server.send(200, "audio/x-scpls", String1);
    digitalWrite(relay2, LOW);
    Serial.println("playlist triggered relay2 on");
    delay(1000);                      
  });

  server.on("/3.pls", [](){
    server.send(200, "audio/x-scpls", String1);
    digitalWrite(relay3, LOW);
    Serial.println("playlist triggered relay3 on");
    delay(1000);                      
  });

    server.on("/4.pls", [](){
    server.send(200, "audio/x-scpls", String1);
    digitalWrite(relay4, LOW);
    Serial.println("playlist triggered relay4 on");
    delay(1000);                      
  });

//---- turnoffs ----
    server.on("/1off.pls", [](){
    server.send(200, "audio/x-scpls", String1);
    digitalWrite(relay1, HIGH);
    Serial.println("playlist triggered relay1 off");
    delay(1000);                      
  });

  server.on("/2off.pls", [](){
    server.send(200, "audio/x-scpls", String1);
    digitalWrite(relay2, HIGH);
    Serial.println("playlist triggered relay2 off");
    delay(1000);                      
  });

  server.on("/3off.pls", [](){
    server.send(200, "audio/x-scpls", String1);
    digitalWrite(relay3, HIGH);
    Serial.println("playlist triggered relay3 off");
    delay(1000);                      
  });

    server.on("/4off.pls", [](){
    server.send(200, "audio/x-scpls", String1);
    digitalWrite(relay4, HIGH);
    Serial.println("playlist triggered relay4 off");
    delay(1000);                      
  });

//---- general onoffs ----

   server.on("/on.pls", [](){
    server.send(200, "audio/x-scpls", String1);
    digitalWrite(relay1, LOW);
    digitalWrite(relay2, LOW);
    digitalWrite(relay3, LOW);
    digitalWrite(relay4, LOW);
    Serial.println("playlist triggered ALL-on");
    delay(1000);                      
  });
  
  server.on("/off.pls", [](){
    server.send(200, "audio/x-scpls", String1);
    digitalWrite(relay1, HIGH);
    digitalWrite(relay2, HIGH);
    digitalWrite(relay3, HIGH);
    digitalWrite(relay4, HIGH);
    Serial.println("playlist triggered ALL-off");
    delay(1000);                      
  });
  
  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void){
  server.handleClient();
}
