
#include"IICCommunicate.h"

void setup(){
  Serial.begin(9600);
  IIC_C *iic=new IIC_C(MSB,A3,A2,HIGH,0x27);
  iic->IICTranByte(0xf7);
}

void loop(){
  
}
