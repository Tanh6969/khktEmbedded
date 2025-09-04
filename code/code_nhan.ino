#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

const uint64_t pipeIn = 0xE8E8F0F0E1LL; 

RF24 radio(9, 10);

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
  radio.begin();
  lcd.init();
  lcd.home();
  lcd.backlight();
  lcd.clear();
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);
  radio.openReadingPipe(1, pipeIn);
  radio.startListening();
  //lcd.println("Receiver ");
}
void recvData()
{
  if ( radio.available() ) { 
    radio.read(&data, sizeof(MyData));
    }
}
void loop()
{
  recvData();
  //radio.read(&data, sizeof(MyData));

  Serial.println("Humidity: ");
  Serial.println(data.h);
  lcd.setCursor(0,0);
  lcd.print("H:"); 
  lcd.print(data.h);
  lcd.print("%");
  
  
  Serial.println("T: ");
  Serial.println(data.t);
  lcd.setCursor(9,0);
  lcd.print("T:");
  lcd.print(data.t);  
  lcd.print(" C");  

  Serial.println("CO: ");
  Serial.println(data.gas);
  lcd.setCursor(0,1);
  lcd.print("Gas:"); 
  lcd.print(data.gas);

  Serial.println("CO: ");
  Serial.println(data.co);
  lcd.setCursor(9,1);
  lcd.print("CO:"); 
  lcd.print(data.co);
//  lcd.print("%");
  //Serial.print("\n");
//  delay(1000);
}
