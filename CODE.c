		

// https://thingspeak.com/channels/689629 -- PUBLIC VIEW PAGE


#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <LiquidCrystal.h>
#include <String.h>

LiquidCrystal lcd (D0,D1,D2,D3,D4,D5);
 
// WiFi parameters to be configured
const char* ssid = "project12"; // Hoofdlettergevoelig
const char* password = "project123456"; // Hoofdlettergevoelig

const char* http_site = "api.thingspeak.com";
const int http_port = 80;
long duration = 0;
unsigned int distance = 0;

String link = "http://api.thingspeak.com/update?api_key=WXGBY1HU6V57QD3F&field2=";
String iot = "\0";

const int trigPin = 12;  //D6
const int echoPin = 13;  //D7


#define gled 15
#define rled 1

void setup(void) { 
  Serial.begin(9600);
Serial.println("power up");
lcd.begin(16,2);

pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);
pinMode(rled, OUTPUT);
pinMode(gled, OUTPUT);

lcd.clear();
lcdstring(0,0,"   WELCOME TO   ");
lcdstring(0,1,"ADVANCED AIRCRAFT");
delay(2000);
lcd.clear();
lcdstring(0,0," ANTI-COLLISION ");
lcdstring(0,1,"     SYSTEM     ");
delay(1500);



  Serial.print("power up");
  WiFi.begin(ssid, password); // Connect to WiFi
 
  while (WiFi.status() != WL_CONNECTED) {
     delay(500);
     Serial.print(".");
     lcd.clear();
     lcdstring(0,0," CONNECTING  TO ");
lcdstring(0,1,ssid);
delay(1500);
  }
  
  // Verbonden.
  Serial.println("OK!");
  
  // Access Point (SSID).UT
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
  
     lcd.clear();
lcdstring(0,0,"WI-FI CONNECTED");
lcdstring(0,1,"***************");
delay(500);

  // IP adres.
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
 
  // Signaalsterkte.
  long rssi = WiFi.RSSI();
  Serial.print("Signaal sterkte (RSSI): ");
  Serial.print(rssi);
  Serial.println(" dBm");
  Serial.println("");

delay(500);
digitalWrite(gled,HIGH);
digitalWrite(rled,HIGH);
  delay(500);
digitalWrite(gled,LOW);
digitalWrite(rled,LOW);
delay(500);
digitalWrite(gled,HIGH);
digitalWrite(rled,HIGH);
  delay(500);
digitalWrite(gled,LOW);
digitalWrite(rled,LOW);
}
 
void loop() {
  
Serial.println("loop Started");

digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
distance= duration*0.034/2;
Serial.print("Distance: ");
Serial.println(distance);
delay(100);

lcd.clear();
lcdstring(0,0,"DISTANCE = ");
lcdstring(11,0,String(distance));
delay(200);

if (distance <30)
{
  
digitalWrite(gled,LOW);
digitalWrite(rled,HIGH);
delay(50);
 // lcd.clear();
  lcdstring(0,1,"AIRCRAFT DETECTED");
  //lcdstring(0,1,"sending to server");
  delay(1500);
  send_data ();
}
else 
{
  
digitalWrite(rled,LOW);
digitalWrite(gled,HIGH);
delay(50);
}

}

void send_data () {

lcd.clear();
lcdstring(0,0,"AIRCRAFT DETECTED");
lcdstring(0,1,"sending to server");
delay(100);

iot = link + String(distance);

 
 if(WiFi.status()== WL_CONNECTED){ //Check WiFi connection status
  
   HTTPClient http; //Declare an object of class HTTPClient
   // http.begin("http://orangewebtools.com/Irrigation/moisture.php?a=32"); //Specify request destination

 Serial.println(iot);
   http.begin(iot);
    http.begin("\n");
    int httpCode = http.GET(); //Send the request
    if (httpCode > 0) { //Check the returning code
      String payload = http.getString(); //Get the request response payload
      Serial.println(payload); //Print the response payload
    }
    http.end(); //Close connection
  } else {
    Serial.println("Error in WiFi connection");   
  }
  lcd.clear();
lcdstring(0,0,"  DATA SENDING  ");
lcdstring(0,1,"  --COMPLETED--  ");
delay(1);
  delay(3000); //Send a request every 30 seconds

}
void lcdstring (unsigned int a, unsigned int b, String data)
{
  // lcd.clear();
  lcd.setCursor(a, b);
  lcd.print(data);
}



}