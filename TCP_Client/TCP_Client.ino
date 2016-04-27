#define CCx 1
#include <WiFi.h>
#include <WiFiClient.h>
// variable used
String inData;
char charBuf[20];
char pinnumber[3];
char valuenumber[5];
int command = 0;
int pin = 0;
int i;
int value;

//char ssid[] = "Harigarakumar's iPhone";     //  your network SSID (name)
//char pass[] = "Hariv3131";  // your network password

char ssid[] = "NETGEAR77";     //  your network SSID (name)
char pass[] = "india123";  // your network password


//uint16_t port = 6970;     // port number of the server
//IPAddress server(54, 174, 186, 244);   // IP Address of the server

uint16_t port = 7070;     // port number of the server
IPAddress server(192, 168, 0, 20);   // IP Address of the server


WiFiClient client;
int status = WL_IDLE_STATUS;     // the Wifi radio's status

void setup() {
  ///////////////////////////////////////////////GPS related//////////////////////////////////////////
  while (!Serial);
  Serial.begin(9600);
  Serial1.begin(9600);
  ////////////////////////////////////////////////////////////////////////////////////////////////////
  
  Serial.begin(115200);
  //Initialize serial and wait for port to open:
  Serial.println("********** DEMO PRINT *************");
    Serial.println("***********************************");
    
  // These Pin Modes are specific to each Launchpad and can be reconfigured here. To Use a different Launchpad/Uncomment Relevant Code here and in get/put functions
 //   pinMode(2, INPUT);    //analogread
  //  pinMode(3, INPUT);    //digitalread
  //  pinMode(5, INPUT);    //digitalread
  //  pinMode(6, INPUT);    //analogread
  //  pinMode(7, OUTPUT);   //digitalwrite
   // pinMode(8, OUTPUT);   //digitalwrite
   // pinMode(9, OUTPUT);  //analogwrite
   // pinMode(10, OUTPUT);  //analogwrite
  //  pinMode(29, OUTPUT);   //analogwrite
    
    // attempt to connect to Wifi network:
    Serial.println("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    WiFi.begin(ssid, pass);
    int tries = 0;
    while ( status != WL_CONNECTED) {
      status = WiFi.status();
      // wait .1 seconds for connection:
      delay(100);
      Serial.print(".");
      if (tries++ > 300) {
        Serial.println("Couldn't connect to your wifi network");
        Serial.println("check your ssid and password.");
        while(1);
      }
    }
  
    // you're connected now, so print out the data:
    Serial.println("\nYou're connected to the network");
    IPAddress empty(0,0,0,0);
    while (WiFi.localIP() == empty); //wait for IP assignment
    
    // attempt to connect to the server
    Serial.println("Attempting to connect to server");
    tries = 0;
    while (client.connect(server, port) == false) {
      Serial.print(".");
      if (tries++ > 100) {
        Serial.println("\nThe server isn't responding");
        while(1);
      }
      delay(100);
    }
    Serial.println("\nThe server responded");
    client.print("launcher\n");
//    establishContact(); // send a byte to establish contact until receiver responds 
}

void loop()
{
  // put your main code here, to run repeatedly:
  
  if (Serial.available()) {
    char c = Serial.read();
    if(c == '$'){
      client.print("\0\n$");
    }
    client.print(c);
  }
  
  
  
  if (Serial1.available()) {
    char c = Serial1.read();
    if(c == '$'){
      client.print("\0\n$");
    }
    client.print(c);
  }
  
  
}
