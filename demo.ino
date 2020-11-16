
#include"IICCommunicate.h"

IIC_C *iic;
byte rc=0;
void setup(){
  iic=new IIC_C(MSB,A0,A1,HIGH,0x27);
  iic->setIICFreq(IIC_HS_MODE);
}

void loop(){
  while(digitalRead(A2)==0){
    iic->setSlaveAdd(0x20);
    iic->IICRecvByte(&rc);
    
    iic->setSlaveAdd(0x27);
    iic->IICTranByte(rc);
  }
  
}
