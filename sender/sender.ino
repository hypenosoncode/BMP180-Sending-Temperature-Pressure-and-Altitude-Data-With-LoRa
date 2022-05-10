// SENDER

#include <SoftwareSerial.h>
#include <SFE_BMP180.h>
#include <Wire.h>
#include <LoRa_E22.h>

SFE_BMP180 pressure;
int sea_level = 105;
SoftwareSerial mySerial(10, 11); // LoRa RX - TX Pıns

LoRa_E22 e22ttl(&mySerial, 3, 7, 6);
struct veri
{
  byte sicaklik[6];
  byte basinc[5];
  byte irtifa[4];
} datas;

void setup()
{
  Serial.begin(9600);
  e22ttl.begin();
  
  if (pressure.begin())
  Serial.println("Basinc Sensoru Algilandi");
  else
  {
    Serial.println("Basinc Sensoru Algilanamadi\n\n");
  }
}

void loop() 
{
  // Temperature
  double temp, pre, po, alt;
  pressure.startTemperature();
  pressure.getTemperature(temp);
  *(double*)(datas.sicaklik) = temp;
  // Pressure
  pressure.startPressure(3);
  pressure.getPressure(pre, temp);
  *(double*)(datas.basinc) = pre;
  // Altitude
  po = pressure.sealevel(pre, sea_level); // We're at 105 meters (Beylikduzu, Istanbul)
  alt = pressure.altitude(pre, po);
  *(double*)(datas.irtifa) = alt;  
 
  ResponseStatus rs = e22ttl.sendFixedMessage(0, 45, 23, &datas, sizeof(veri)); // Adress: 43 - Channel: 23
  
  Serial.print("Sicaklik: ");
  Serial.print(*(double*)(datas.sicaklik));
  Serial.println(" C");
  Serial.print("Basinc: ");
  Serial.print(*(double*)(datas.basinc));
  Serial.println(" hPa");
  Serial.print("İrtifa: ");
  Serial.print(*(double*)(datas.irtifa));
  Serial.println(" metre");
  Serial.println("-------------------------------");
  delay(1000);
}
