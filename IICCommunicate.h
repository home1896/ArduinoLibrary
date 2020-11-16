/**
 * Author:sedev_home1896@163.com
 * License:MPL V2.0
 * 注：该库只支持7bit的地址
*/


#ifndef _IICCOMMUNICATE_H_
#define _IICCOMMUNICATE_H_
#include"MacroUtills.h"

#define IIC_TIME_OUT 1
#define IIC_TRANS_OK 0

#define IIC_STD_MODE 10
#define IIC_FAST_MODE 3
#define IIC_HS_MODE 1

#define SET_CLK setPin(IIC_SCL)
#define CLR_CLK clrPin(IIC_SCL)

#define SET_SDA setPin(IIC_SDA)
#define CLR_SDA clrPin(IIC_SDA)
class IIC_C
{
    public:
        IIC_C(byte TranslateType,PinNum scl,PinNum sda,bool READValue,byte SlaveAdd,unsigned int freq);
        IIC_C(byte TranslateType,PinNum scl,PinNum sda,bool READValue,byte SlaveAdd);
        IIC_C(PinNum scl,PinNum sda,byte SlaveAdd);
        IIC_C(byte SlaveAdd);
        IIC_C();
        bool virtual IICTranByte(byte data);
        bool virtual IICRecvByte(byte *data);
        void setSlaveAdd(byte address);
        void setIICFreq(unsigned int);
        
    protected://用于开发基于IIC通讯协议进行通讯的其他元件
        PinNum IIC_SCL,IIC_SDA;
        unsigned int delayTime;
        byte IIC_Slave_Address;
        byte READ_INVALID;//设定读取信号是否为高电平
        void IIC_Start();
        void IIC_Stop();
        bool IIC_Ack2Slave();
        bool IIC_NAck2Slave();//在二次开发时需注意，某些IIC器件需要使用NACK信号使从设备停止数据发送，否则会时序混乱
        bool IIC_Ack2Master();


     private://基本操作，私有成员
        void (IIC_C::*IIC_SendByte)(byte);
        void (IIC_C::*IIC_RecvByte)(byte*);
        void IIC_Read_MSB(byte *data);
        void IIC_Write_MSB(byte data);
        void IIC_Read_LSB(byte *data);
        void IIC_Write_LSB(byte data);
};

#endif
