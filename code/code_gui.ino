#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include "DHT.h"
const uint64_t pipeOut = 0xE8E8F0F0E1LL; 
#define DHTPIN 7  
#define DHTTYPE DHT22 
DHT dht(DHTPIN, DHTTYPE);

RF24 radio(9, 10); //  CN and CSN  pins of nrf
struct MyData {
  byte h;
  byte t;
  byte co;
  byte gas;
};
MyData data;
void setup()
{
  Serial.begin(9600); 
  dht.begin();
  pinMode(6, OUTPUT);
  radio.begin();
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);
  radio.openWritingPipe(pipeOut);
}
void loop()
{
  data.co = analogRead(A1);
  data.gas = analogRead(A2);
//  data.co = analogRead(A0);

  
  data.h = dht.readHumidity();
  data.t = dht.readTemperature();
  if (isnan(data.h) || isnan(data.t)){
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  Serial.println("Humidity: ");
  Serial.println(data.h);
  Serial.println("Temperature: ");
  Serial.println(data.t);

  Serial.println("Gas: ");
  Serial.println(data.gas);

  Serial.println("KK: ");
  Serial.println(data.co);
  
  //if(data.gas >= 150 || data.co >= 150){
   // digitalWrite(6, HIGH);
   // }
  radio.write(&data, sizeof(MyData));

  Serial.println("Da Gui");
  
}
