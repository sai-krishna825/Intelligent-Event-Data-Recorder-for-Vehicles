#include <Wire.h> 
#include <Adafruit_GFX.h> 
#include <Adafruit_SSD1306.h> 
#include "DHT.h" 
#define SCREEN_WIDTH 128 // OLED display width, in pixels 
#define SCREEN_HEIGHT 64 // OLED display height, in pixels 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1); 
//SoftwareSerial = Serial2(8, 9); 
#define DHTPIN 2     
#define DHTTYPE DHT11 
DHT dht(DHTPIN, DHTTYPE); 
#define vib 5 
#define fire 6
#define speaker0 A0 
#define speaker1 A1 
#define speaker2 A2 
#define speaker3 A3 
#define led 8 
#define buzz 7 
const int vib_State = 0; 
const int fire_State = 0; 
void setup(){ 
  // put your setup code here, to run once: 
 Serial.begin(9600); 
 dht.begin(); 
 // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally 
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    //Serial.println(F("SSD1306 allocation failed")); 
    while (true) 
    ; // Don't proceed, loop forever 
  } 
  pinMode(vib,INPUT); 
  pinMode(fire, INPUT); 
  pinMode(speaker0, OUTPUT); 
  pinMode(speaker1, OUTPUT); 
  pinMode(speaker2, OUTPUT); 
  pinMode(speaker3, OUTPUT); 
  pinMode(led,OUTPUT);
  pinMode(buzz,OUTPUT); 
  // wait for initializing 
  display.clearDisplay(); 
  display.setTextSize(1); 
  display.setTextColor(WHITE); 
  display.setCursor(0, 0); 
  display.println("INTELLIGENT EVENT DATA RECORDER FOR VEHICLES"); 
  display.display(); 
  delay(2000); 
     
} 
 void loop() { 
  // put your main code here, to run repeatedly: 
 float h = dht.readHumidity(); 
 float t = dht.readTemperature(); 
 float f = dht.readTemperature(true); 
 
  float hif = dht.computeHeatIndex(f, h); 
  float hic = dht.computeHeatIndex(t, h, false); 
   
 display.clearDisplay(); 
 display.setTextSize(1); 
 display.setTextColor(WHITE); 
 display.setCursor(0,0); 
 display.print("Temperature :");
 display.setTextSize(2);          // text size 
 display.setTextColor(WHITE);     // text color 
  display.setCursor(0, 10); 
  display.print(t); 
  display.display(); 
  delay(500); 
  if (t >= 45) { 
    digitalWrite(buzz, HIGH); 
    digitalWrite(speaker0,LOW); 
    digitalWrite(speaker1,LOW); 
    digitalWrite(speaker2,LOW); 
    digitalWrite(speaker3,LOW); 
    display.clearDisplay();       // clear display 
    display.setTextSize(1);       // text size 
    display.setTextColor(WHITE);  // text color 
    display.setCursor(0, 0);      // position to display 
    display.print("Temperature Abnormal!!!!"); 
    display.display(); 
    delay(800); 
    digitalWrite(buzz, LOW); 
   } 
 
  display.setTextSize(1);       // text size 
  display.setTextColor(WHITE);  // text color 
  display.setCursor(0, 30);     // position to display
  display.print("Humidity :");  // text to display 
  display.setTextSize(2);       // text size 
  display.setTextColor(WHITE);  // text color 
  display.setCursor(0, 40); 
  display.print(h); 
  display.display(); 
  delay(1500); 
  if (h >= 80) { 
    digitalWrite(buzz, HIGH); 
    digitalWrite(speaker0,LOW); 
    digitalWrite(speaker1,LOW); 
    digitalWrite(speaker2,LOW); 
    digitalWrite(speaker3,LOW); 
    display.clearDisplay();       // clear display 
    display.setTextSize(1);       // text size 
    display.setTextColor(WHITE);  // text color 
    display.setCursor(0, 0);      // position to display 
    display.print("Humidity is Abnormal!!!"); 
    display.display(); 
    delay(800); 
    digitalWrite(buzz, LOW); 
    display.clearDisplay(); 
} 
  display.clearDisplay(); 
  int vib_State = digitalRead(vib);
  if (vib_State == HIGH) 
  { 
    digitalWrite(buzz,HIGH); 
    digitalWrite(speaker0,LOW); 
    digitalWrite(speaker1,LOW); 
    digitalWrite(speaker2,LOW); 
    digitalWrite(speaker3,LOW); 
    digitalWrite(led,HIGH); 
    display.clearDisplay(); 
    display.setCursor(0, 20); 
    display.setTextColor(WHITE); 
    display.setTextSize(1); 
    display.println("vibration Abnormal"); 
    display.display(); 
    delay(1000); 
    } 
  else 
  { 
    digitalWrite(buzz,LOW); 
    digitalWrite(speaker0,HIGH); 
    digitalWrite(speaker1,HIGH); 
    digitalWrite(speaker2,HIGH); 
    digitalWrite(speaker3,HIGH); 
    digitalWrite(led,LOW);
    display.setCursor(0, 10); 
    display.setTextColor(WHITE); 
    display.setTextSize(1); 
    display.println("vibration Normal"); 
    display.display(); 
    delay(1000); 
    display.clearDisplay(); 
   } 
   
  int fire_State = digitalRead(fire); 
 
  if (fire_State == LOW) 
  { 
    digitalWrite(buzz,HIGH); 
    digitalWrite(speaker0,LOW); 
    digitalWrite(speaker1,LOW); 
   digitalWrite(speaker2,LOW); 
    digitalWrite(speaker3,LOW); 
    digitalWrite(led,HIGH); 
    display.setCursor(0, 20); 
    display.setTextColor(WHITE); 
    display.setTextSize(1); 
    display.println("fire Abnormal"); 
    display.display(); 
    delay(1000);
    } 
  else 
  { 
    digitalWrite(buzz,LOW); 
    digitalWrite(speaker0,HIGH); 
    digitalWrite(speaker1,HIGH); 
    digitalWrite(speaker2,HIGH); 
    digitalWrite(speaker3,HIGH); 
    digitalWrite(led,LOW); 
    display.setCursor(0, 10); 
    display.setTextColor(WHITE); 
    display.setTextSize(1); 
    display.println("fire Normal"); 
    display.display(); 
    delay(1000); 
   }  
}