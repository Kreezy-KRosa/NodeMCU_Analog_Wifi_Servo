
#include <ESP8266WiFi.h>

int  Astick;
WiFiServer server(80);

void setup()
{
  Astick = 0;                                       //Analog stick's X Axis Output connected to Pin A0
  Serial.begin(9600);
    WiFi.disconnect();
  delay(3000);
   WiFi.begin("SSID","PASSWORD");                   //Enter your SSID and Password for your network
  while ((!(WiFi.status() == WL_CONNECTED))){
    delay(300);

  }
  Serial.println("Connected");
  Serial.println((WiFi.localIP()));
  server.begin();

}


void loop()
{

    Astick = analogRead(A0);                     //Read the value from the Analog stick
    Astick = map(Astick, 0, 1023, 15, 180);      //Maps the Analog stick value to a range the Servo can work with
    Serial.println(Astick);

    WiFiClient client = server.available();
    if (!client) { return; }
    while(!client.available()){  delay(1); }
    client.flush();
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("");
    client.println("<!DOCTYPE HTML>");
    client.println("<html>");
    client.println(Astick);                       //Analog stick value being sent thru HTML
    client.println("</html>");
    client.stop();
    delay(150);

}
