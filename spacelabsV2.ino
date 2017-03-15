#include <string.h>
#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>

String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

//Global Variables
#define MAX_TOKENS 10
#define BUFFER_SIZE 200
String result[MAX_TOKENS];
char received_data[BUFFER_SIZE]; 

//Bluemix -----------------------------------------------------------------------------------------------------------------
// Local Network Settings
byte mac[] = { 0xD4, 0x28, 0xB2, 0xFF, 0xA0, 0xA1 }; // Must be unique on local network
EthernetClient ethClient;

char orgName[] = "aemm5s";      // Your org name, found under the "Credentials" area in your Bluemix dashboard.
char macstr[] = "d428b2ffa0a1";
//char type[] = "d428b2ffa0a1";    // Type of device you have registered in the IBM Bluemix Devices area.
//char token[] = "2br@fN5NZy+o(PR-9@"; // Token issued when you first register your IoT device (only appears once)
int  port = 1883;

char servername[]="quickstart.messaging.internetofthings.ibmcloud.com";
String clientName = String("d:quickstart:iotsample-arduino:")+macstr;
String topicName = String("iot-2/evt/status/fmt/json");

PubSubClient client(servername, port, 0, ethClient);
//-----------------------------------------------------------------------------------------------------------------
//Thingpseak-------------------------------------------------------------------------------------------------------
char thingSpeakAddress[] = "api.thingspeak.com";
byte thingserver[]  = { 184, 106, 153, 149 }; // ThingSpeak IP Address: 184.106.153.149
IPAddress thingip(184, 106, 153, 149);

String writeAPIKey = "7RHG463K2JQHPDE1";
const int updateThingSpeakInterval = 16 * 1000;      // Time interval in milliseconds to update ThingSpeak (number of seconds * 1000 = interval)

long lastConnectionTime = 0; 
boolean lastConnected = false;
int failedCounter = 0;
//-----------------------------------------------------------------------------------------------------------------
void setup() {
  // initialize serial
  Serial.begin(57600);
  Serial3.begin(9600);
  Serial.println("Initiating Setup MDI - Spacelabs Monitor @ CloudStat");
  startEthernet();
  delay(1000);
  inputString.reserve(BUFFER_SIZE); 
  Serial.println("Setup READY \n Waiting for serial monitor..."); 
  Serial3.flush();
}
void loop() {
  serialEvent(); //call the function
  int received_tokens =0;
  if (stringComplete) {
    Serial.println(inputString);
    //----------------Procesamiento de tokens------------------------
    inputString.toCharArray(received_data,inputString.length()) ;
    //Serial.println(received_data);
    received_tokens = tokenizeString(received_data);
    Serial.println("Tokens: "+String(received_tokens)+" Data: << "+inputString+" >>");
    if (detectarHora()){
       //Serial.println("HORA!");
       printTokens(received_tokens);
       if(received_tokens==7){
         Serial.println("Posting...");
         Serial.println(buildJson());         
         String thingpost="field1="+String(result[5])+"&field2="+String(result[6]);
         Serial.println(thingpost);
         postBluemix();
         //updateThingSpeak(thingpost);
       }
    }
    //---------------------------------------------------------------    
    inputString = "";
    stringComplete = false;
  }
}
