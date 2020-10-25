/**
 * Author:sedev_home1896@163.com
 * License:MPL V2.0
*/


#include"IICCommunicate.h"




/**
 * Funcation Name:IIC_C
 * Para:byte TranslateType 规定传输方式，MSB/LSB
 *      PinNum scl         规定时钟信号引脚
 *      PinNum sda         规定数据线引脚
 *      bool   READValue   读命令的电平，写命令则与其相反
 *      byte   slaveAdd    从机地址，除最后一位
 * Result:void
 * Funcation description:构造函数
 * 该函数用于初始化IIC通讯标准
*/
IIC_C::IIC_C(byte TranslateType,PinNum scl,PinNum sda,bool READValue,byte SlaveAdd)
{
    if(TranslateType==MSB)
    {
        IIC_SendByte=&IIC_Write_MSB;
        IIC_RecvByte=&IIC_Read_MSB;
    }
    else
    {
        IIC_SendByte=&IIC_Write_LSB;
        IIC_RecvByte=&IIC_Read_LSB;
    }
    IIC_SCL=scl;
    IIC_SDA=sda;
    pinModeOut(IIC_SCL);
    pinModeOut(IIC_SDA);
    SET_CLK;
    SET_SDA;
    IIC_Slave_Address=SlaveAdd<<1;
    READ_INVALID=READValue==true?0x01:0x00;
}


/**
 * Funcation Name:IIC_Start
 * Para:无
 * Result:void
 * Funcation description:
 * 发送起始信号
*/
void IIC_C::IIC_Start()
{  
    SET_SDA;
    SET_CLK;
    delayUs(5);
    CLR_SDA;
    delayUs(5);
    CLR_CLK;
    #ifdef IIC_DEBUG
      Serial.println("IIC infor:Send start signal to slave device.");
    #endif
}

/**
 * Funcation Name:IIC_Stop
 * Para:无
 * Result:无
 * Funcation description:
 * 发送停止信号
*/
void IIC_C::IIC_Stop()
{
    CLR_SDA;
    SET_CLK;
    delayUs(2);
    SET_SDA;
    #ifdef IIC_DEBUG
      Serial.println("IIC infor:Send stop signal to slave device.");
    #endif
}

/**
 * Funcation Name:IIC_Ack2Slave
 * Para:无
 * Result:true
 * Funcation description:
 * 向从机发送ACK信号
*/
bool IIC_C::IIC_Ack2Slave()
{
    CLR_SDA;
    SET_CLK;
    delayUs(25);
    CLR_CLK;
    #ifdef IIC_DEBUG
      Serial.println("IIC infor:Send ACK signal to slave device.");
    #endif
    return true;
}

/**
 * Funcation Name:IIC_Ack2Master
 * Para:无
 * Result:bool 返回从机是否成功接收数据
 * Funcation description:
 * 用于确定从机是否收到数据
*/
bool IIC_C::IIC_Ack2Master()
{
    SET_SDA;
    pinModeIN(IIC_SDA);
    SET_CLK;
    byte i=0;
    bool flag=IIC_TIME_OUT;
    while(i!=0xff&&flag==IIC_TIME_OUT)
    {
        i++;
        delayUs(2);
        flag=getPin(IIC_SDA);
    }
    CLR_CLK;
    pinModeOut(IIC_SDA);
    #ifdef IIC_DEBUG
    if(flag==IIC_TIME_OUT) Serial.println("IIC infor:Slave device timed Out!");
    else Serial.println("IIC infor:Slave device operate successed!");
    #endif
    return flag;
}


/**
 * Funcation Name:IIC_Read_MSB
 * Para:byte* data 用于返回读取的数据
 * Result:void
 * Funcation description:
 * 用于IIC总线的MSB方式读取一个字节
*/
void IIC_C::IIC_Read_MSB(byte *data)
{
    #ifdef IIC_DEBUG
        Serial.println("IIC infor:MSB_READ_START");
    #endif
    CLR_CLK;
    pinModeIN(IIC_SDA);
    byte count=8,recv=0,rbit=0;
    while(count!=0)
    {
        count--;
        SET_CLK;
        delayUs(1);
        rbit=getPin(IIC_SDA);
        recv=(recv<<1)|rbit;
        CLR_CLK;
        #ifdef IIC_DEBUG
          if(count==7)
            Serial.print("IIC data:");
          Serial.print(rbit);
          if(count==0)
            Serial.println();
        #endif
    }
    *data=recv;
    pinModeOut(IIC_SDA);
    #ifdef IIC_DEBUG
        Serial.println("IIC infor:MSB_READ_END");
    #endif
    return;
}

/**
 * Funcation Name:IIC_Read_MSB
 * Para:byte data 用于写入的数据
 * Result:void
 * Funcation description:
 * 用于IIC总线的MSB方式写入一个字节
*/
void IIC_C::IIC_Write_MSB(byte data)
{
    #ifdef IIC_DEBUG
    Serial.println("IIC infor:MSB_WRITE_START");
    #endif
    CLR_CLK;
    byte count=8,sbit=0;
    while (count--)
    {
        sbit=(data&0x80)>>7;
        if(sbit==1)    SET_SDA;
        else CLR_SDA;
        data<<=1;
        SET_CLK;
        delayUs(2);
        CLR_CLK;
        #ifdef IIC_DEBUG
        if(count==7)
          Serial.print("IIC data:");
        Serial.print(sbit);
        if(count==0)
          Serial.println();
        #endif
    }
    #ifdef IIC_DEBUG
       Serial.println("IIC infor:MSB_WRITE_END");
    #endif
    return;
}


/**
 * Funcation Name:IIC_Read_LSB
 * Para:byte* data 用于返回读取的数据
 * Result:void
 * Funcation description:
 * 用于IIC总线的LSB方式读取一个字节
*/
void IIC_C::IIC_Read_LSB(byte *data)
{
    #ifdef IIC_DEBUG
        Serial.println("IIC infor:LSB_REDA");
    #endif
    CLR_CLK;
    pinModeIN(IIC_SDA);
    byte count=8,recv=0,rbit=0;
    while(count!=0)
    {
        count--;
        SET_CLK;
        delayUs(1);
        rbit=getPin(IIC_SDA);
        recv|=(rbit<<7);
        recv>>=1;
        CLR_CLK;
        #ifdef IIC_DEBUG
        if(count==7)
          Serial.print("IIC data:");
        Serial.print(rbit);
        if(count==0)
          Serial.println();
        #endif
    }
    *data=recv;
    pinModeOut(IIC_SDA);
    #ifdef IIC_DEBUG
        Serial.println("IIC infor:LSB_READ_END");
    #endif
    return;
}

/**
 * Funcation Name:IIC_Read_LSB
 * Para:byte data 用于写入的数据
 * Result:void
 * Funcation description:
 * 用于IIC总线的MSB方式写入一个字节
*/
void IIC_C::IIC_Write_LSB(byte data)
{
    #ifdef IIC_DEBUG
        Serial.println("IIC infor:LSB_WRITE_START");
    #endif
    CLR_CLK;
    byte count=8,sbit=0;
    while (count--)
    {
        sbit=(data&0x01);
        if(sbit==1)    SET_SDA;
        else CLR_SDA;
        data>>=1;
        SET_CLK;
        delayUs(2);
        CLR_CLK;
        #ifdef IIC_DEBUG
        if(count==7)
          Serial.print("IIC data:");
        Serial.print(sbit);
        if(count==0)
          Serial.println();
        #endif
    }
    #ifdef IIC_DEBUG
        Serial.println("IIC infor:LSB_WRITE_END");
    #endif
    return;
}

/**
 * Funcation Name:IICRecvByte
 * Para:byte* data 用于返回读取到的数据
 * 
 * Result:bool 读取是否成功
 * Funcation description:
 * 从IIC设备读取一个字节数据
*/
bool IIC_C::IICRecvByte(byte *data)
{
    bool flag=false;
    IIC_Start();
    (this->*IIC_C::IIC_SendByte)(this->IIC_Slave_Address|(READ_INVALID==0x01?1:0));
    flag=IIC_Ack2Master();
    if(flag==IIC_TIME_OUT)
    {
        IIC_Stop();
        return flag;
    }

    (this->*IIC_C::IIC_RecvByte)(data);
    IIC_Ack2Slave();
    IIC_Stop();
    return flag;
}

/**
 * Funcation Name:IICTranByte
 * Para:byte* data 用于返回读取到的数据
 * 
 * Result:bool 读取是否成功
 * Funcation description:
 * 向IIC设备写入1Byte数据
*/
bool IIC_C::IICTranByte(byte data)
{
    bool flag=false;
    IIC_Start();
    (this->*IIC_C::IIC_SendByte)((byte)(this->IIC_Slave_Address|(READ_INVALID==0x01?0:1)));
    flag=IIC_Ack2Master();
    if(flag==IIC_TIME_OUT)
    {
        IIC_Stop();
        return flag;
    }

    (this->*IIC_C::IIC_SendByte)(data);
    flag=IIC_Ack2Master();

    IIC_Stop();
    return flag;
}


/**
 * Funcation Name:setSlaveAdd
 * Para:
 *      byte    slaveAdd    从机地址
 * Result:void
 * Funcation description:
 * 更改通讯从机地址
*/
void IIC_C::setSlaveAdd(byte slaveAdd)
{
    this->IIC_Slave_Address=slaveAdd<<1;
}
