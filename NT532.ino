#include <SPI.h>
#include <Wire.h>
#include "DHT.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32

#define DHTPIN 2
#define LED_G 3
#define LED_R 4
#define LED_R1 5
#define DHTTYPE DHT11

#define OLED_RESET -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
    float lux;
    DHT dht(DHTPIN, DHTTYPE, 6);

    // Light sensor (0-1024)
    void temp_6000(){
    float volts = analogRead(A0) * 5.0 / 1024.0;
    float amps = volts / 10000.0; // across 10,000 Ohms
    float microamps = amps * 1000000;
    lux = microamps * 2.0;
}

// mang hinh oled i2c
void SSD_1306(){
    if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    }
      delay(2000);
      display.clearDisplay();
    }

void temp_humi(){
    float h = dht.readHumidity();
    float t = dht.readTemperature();

    Serial.print(String(t)+" "+String(h)+" "+String(lux));
    if ( lux > 70 )
    {
      digitalWrite(LED_G, HIGH);
      digitalWrite(LED_R, LOW);
    }
    else
    {
      digitalWrite(LED_G, LOW);
      digitalWrite(LED_R, HIGH);
    }

    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 10);

    // Display static text
    display.clearDisplay();
    display.print("Humidity: ");
    display.print(h);
    display.println("%");

    display.setCursor(0, 0);
    display.print("Temperature: ");
    display.print(t);
    display.println("C");

    display.setCursor(0, 20);
    display.print("Light: ");
    display.print(lux);

    display.display();

}

void setup() {
    // put your setup code here, to run once:
    Serial.begin(9600);
    SSD_1306();
    // Serial.println(F("DHTxx test!"));
    dht.begin();

    pinMode(LED_G, OUTPUT);
    pinMode(LED_R, OUTPUT);
    pinMode(LED_R1, OUTPUT);
}

void loop() {
    temp_6000();

    temp_humi();

    if (Serial.available() > 0 ){
        String data = Serial.readString();
        if(data == "ON"){
          digitalWrite(LED_R1, HIGH);
        } else if (data == "OFF"){
          digitalWrite(LED_R1, LOW);
        } else;
    }

    delay(2000);
}