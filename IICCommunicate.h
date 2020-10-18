/**
 * Author:sedev_home1896@163.com
 * License:MPL V2.0
*/
#ifndef _IICCOMMUNICATE_H_
#define _IICCOMMUNICATE_H_
//仅支持8bit地址IIC设备
#include"MacroUtills.h"

#define IIC_TIME_OUT 1
#define IIC_TRANS_OK 0



#define SET_CLK setPin(IIC_SCL)
#define CLR_CLK clrPin(IIC_SCL)

#define SET_SDA setPin(IIC_SDA)
#define CLR_SDA clrPin(IIC_SDA)
class IIC_C
{
    public:
        IIC_C(byte TranslateType,PinNum scl,PinNum sda,bool READValue,byte SalveAdd);
        bool IICTranByte(byte data);
        bool IICRecvByte(byte *data);
    private:
        void (IIC_C::*IIC_SendByte)(byte);
        void (IIC_C::*IIC_RecvByte)(byte*);
        bool IIC_Translate(byte data);
        bool IIC_Receive(byte *data);
        PinNum IIC_SCL,IIC_SDA;
        byte IIC_Salve_Address;
        byte READ_INVALID;
        void IIC_Start();
        void IIC_Stop();
        bool IIC_Ack2Slave();
        bool IIC_Ack2Master();
        
        void IIC_Read_MSB(byte *data);
        void IIC_Write_MSB(byte data);

        void IIC_Read_LSB(byte *data);
        void IIC_Write_LSB(byte data);
};

#endif
