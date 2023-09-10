#include <ESP8266WiFi.h>
#include <DHT.h>

String apiKey = "2UXZXFQA1RFYO16R";     //  Enter your Write API key from ThingSpeak

const char *ssid =  "Mr.Kr";     // replace with your wifi ssid and wpa2 key
const char *pass =  "";
const char *server = "api.thingspeak.com";

#define DHTPIN D3          //pin where the dht11 is connected
#define MOI A0        //pin where moisture snesor is connected
#define RELAY D2        //pin where relay is connecter

DHT dht(DHTPIN, DHT11);

WiFiClient client;

void setup()
{
  Serial.begin(115200);
  delay(10);
  dht.begin();

  pinMode (MOI,INPUT);
  pinMode (RELAY,OUTPUT);
  

  Serial.println("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

}

void loop()
{

  float h = dht.readHumidity();
  float t = dht.readTemperature();

  float moisture_output = analogRead(MOI) / 1023.00;
  float moisture_percentage = ( 100.00 - (moisture_output) * 100.00 );

if (moisture_percentage < 40){
    digitalWrite(RELAY, HIGH);
    }
    
  if (client.connect(server, 80))  //   "184.106.153.149" or api.thingspeak.com
  {

    String postStr = apiKey;
    postStr += "&field1=";
    postStr += String(t);
    postStr += "&field2=";
    postStr += String(h);
    postStr += "&field3=";
    postStr += String(moisture_percentage);
    postStr += "\r\n\r\n";

    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: " + apiKey + "\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(postStr.length());
    client.print("\n\n");
    client.print(postStr);

    if (moisture_percentage < 45){
    Serial.println("1");
    
}
    
  }
  client.stop();

 

  // thingspeak needs minimum 15 sec delay for updates
  delay(1000);
}
