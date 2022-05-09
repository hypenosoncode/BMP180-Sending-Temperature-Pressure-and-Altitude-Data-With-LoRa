// RECEIVER

#include <SoftwareSerial.h>
#include <LoRa_E22.h>

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
}

void loop() 
{
  while (e22ttl.available()  > 1) 
  {
    ResponseStructContainer rsc = e22ttl.receiveMessage(sizeof(veri));
    struct veri datas = *(veri*) rsc.data;
    Serial.print("Alinan Sıcaklık: ");
    Serial.println(*(double*)(datas.sicaklik));
    Serial.print("Alinan Basinc: ");
    Serial.println(*(double*)(datas.basinc));
    Serial.print("Alinan İrtifa: ");
    Serial.println(*(double*)(datas.irtifa));
    Serial.println("-------------------------------");
    rsc.close();
  }
}
