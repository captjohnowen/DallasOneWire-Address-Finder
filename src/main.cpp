


/*********
 * 
 * This is a utility program to find the addresses of 
 * ds18b20 Temperature Sensors
 * 
 * John Owen
 * April 2022
 *
*********/


#include "Arduino.h"
#include "heltec.h"
#include "OneWire.h"
#include "DallasTemperature.h"

#define I2C_SDA 4
#define I2C_SCL 15

#define BAND    915E6  //you can set band here directly,e.g. 868E6,915E6
String rssi = "RSSI --";
String packSize = "--";
String packet ;
String deviceAddress = "";




// GPIO where the DS18B20 is connected to
OneWire ds(32);

void refreshDisplay(String(deviceAddress)) {  //refreshs the Heltec OLED display
   
   Heltec.display->clear();
   Heltec.display->drawString(0, 0, "ds18b20 Temp Sensor");
   Heltec.display->drawString(0, 13,"Address");
   Heltec.display->drawString(0, 30, deviceAddress);
   Heltec.display->display();
}

void setup() {
  Serial.begin(115200);

  Wire.begin(I2C_SDA, I2C_SCL);

  Heltec.begin(true , true , true, true , BAND );
 
  Heltec.display->init();
  Heltec.display->flipScreenVertically();  
  Heltec.display->setFont(ArialMT_Plain_10);
  delay(1500);
  Heltec.display->clear();
  Heltec.display->drawString(0, 0, "Heltec.LoRa Initial success!");
  Heltec.display->display();
  delay(1000);
}

void loop() {
  byte i;
  byte addr[8];
  
  if (!ds.search(addr)) {
    Serial.println(" No more addresses.");
    Serial.println();
    ds.reset_search();
    delay(1000);
    return;
  }
  Serial.print(" ROM =");
  for (i = 0; i < 8; i++) {
    Serial.write(' ');
    Serial.print(addr[i], HEX);
    deviceAddress = (addr[i]);
  }
  refreshDisplay(deviceAddress);
}