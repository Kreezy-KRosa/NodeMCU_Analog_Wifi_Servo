//Analog Controlled Wifi Servo Example Code
//By Kreezy(KRosa) 1.15.2018

//Upload this to the Client NodeMCU

#include <ESP8266WiFi.h>
#include <Servo.h>
#include <ESP8266HTTPClient.h>

Servo myservo;

String  i;
int  ServoPos;
String  httpurl;
String  TheHiddenAnswerOfClient;
HTTPClient http;

String SendWithAnswer(String IPcache, String monmessagecache) {
httpurl = "http://";
httpurl+=IPcache;
httpurl+="/";
httpurl+=monmessagecache;
http.begin(httpurl);
http.GET();
TheHiddenAnswerOfClient = (http.getString());
http.end();
return TheHiddenAnswerOfClient;
}

void setup()
{
  myservo.attach(D1);                              //Servo connected to Pin D1
  
  i = "";

  ServoPos = 0;
  Serial.begin(9600);
    WiFi.disconnect();
  delay(3000);
   WiFi.begin("SSID","PASSWORD");                   //Enter your SSID and Password for your network 
  while ((!(WiFi.status() == WL_CONNECTED))){
    delay(300);

  }
  Serial.println("Connected");

}
void loop()
{

    i = (SendWithAnswer("192.168.0.114","Yes"));
    i.remove(0, 25);
    i.remove(i.length()-11,11);
    ServoPos = i.toInt();                             //Taking the Analog stick data and making it an INT
    Serial.println(ServoPos);
    myservo.write(ServoPos);                          //Writing the Analog Stick position to the Servo
    delay(150);

}
