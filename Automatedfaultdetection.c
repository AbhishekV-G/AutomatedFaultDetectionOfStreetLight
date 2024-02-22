// Automated-Fault-Detection-of-Street-Lights using Two ESP32
//Node mcu 1:
#include <DHT.h>
#define DHTPIN D4
#define DHTTYPE DHT11
DHT dht(D4, DHT11);
#define RELAY_PIN D1
const int ldrPinLED = A0;

void setup() {
Serial.begin(9600);
pinMode(A0, INPUT);
pinMode(D1, OUTPUT);
pinMode(D2,OUTPUT);
dht.begin(); }

void loop() {
int ldrValueLED = analogRead(A0);
float humidity = dht.readHumidity();
digitalWrite(D1, LOW);
digitalWrite(D2, LOW);
float voltage = ldrValueLED * (5.0 / 1023.0);  
Serial.println(voltage);
if (ldrValueLED < 500) {
if (isnan(humidity)) {
Serial.println("Failed to read humidity from DHT sensor");
}
else {
Serial.print("Humidity: ");
Serial.print(humidity);
Serial.println("%");
float humidityThreshold = 60.0;
if (humidity > humidityThreshold) {
  digitalWrite(D1, HIGH);
  digitalWrite(D2, LOW);
} 
else {
  digitalWrite(D1, LOW);
  digitalWrite(D2, HIGH);
}
} }

else{
Serial.println("Failed");
}
delay(10000);
}
//Node mcu 2:
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>
const char* ssid = "Hidden";
const char* password = "12345678";
#define BOTtoken "6726675517:AAGIgM5ZPVMk-g7UXBGGoNXpqf2xnyQBV6c"
#define CHAT_ID "1091317795"
X509List cert(TELEGRAM_CERTIFICATE_ROOT);
WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);
const int ldrPin = A0;
const int threshold = 500;
void setup() {
Serial.begin(115200);
configTime(0, 0, "pool.ntp.org");
client.setTrustAnchors(&cert);
// Attempt to connect to Wifi network:
Serial.print("Connecting Wifi: ");
Serial.println(ssid);
WiFi.mode(WIFI_STA);
WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED) {
Serial.print(".");
delay(500);
}
Serial.println("");
Serial.println("WiFi connected");
Serial.print("IP address: ");
Serial.println(WiFi.localIP());
bot.sendMessage(CHAT_ID, "Bot started up", ""); }
void loop() {
int lightValue = analogRead(A0);
Serial.print("Light Value: ");
Serial.println(lightValue);
if (lightValue < 500) {
bot.sendMessage(CHAT_ID, "Fault Detected at 5th pole of ranganathar street", "");
Serial.println("Fault");
} }