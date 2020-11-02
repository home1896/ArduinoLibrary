/**
 * Author:sedev_home1896@163.com
 * License:MPL V2.0
*/


#include"IICCommunicate.h"




/**
 * Funcation Name:IIC_C
 * Para:
 *      byte            TranslateType 规定传输方式，MSB/LSB
 *      PinNum          scl           规定时钟信号引脚
 *      PinNum          sda           规定数据线引脚
 *      bool            READValue     读命令的电平，写命令则与其相反
 *      byte            slaveAdd      从机地址，除最后一位
 *      unsigned int    freq          总线读取频率，可自定义数值
 * Result:void
 * Funcation description:构造函数
 * 该函数用于初始化IIC通讯标准
*/
IIC_C::IIC_C(byte TranslateType,PinNum scl,PinNum sda,bool READValue,byte SlaveAdd,unsigned int freq)
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
    delayTime=freq;
    
}


/**
 * Funcation Name:IIC_C(overload)
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
    delayTime=IIC_STD_MODE;
    
}


/**
 * Funcation Name:IIC_C(overload)
 * Para:
 *      PinNum scl         规定时钟信号引脚
 *      PinNum sda         规定数据线引脚
 *      byte   slaveAdd    从机地址，除最后一位
 * Result:void
 * Funcation description:构造函数
 * 该函数用于初始化IIC通讯标准
*/
IIC_C::IIC_C(PinNum scl,PinNum sda,byte SlaveAdd)
{
    
    IIC_SendByte=&IIC_Write_MSB;
    IIC_RecvByte=&IIC_Read_MSB;
    
    IIC_SCL=scl;
    IIC_SDA=sda;
    pinModeOut(IIC_SCL);
    pinModeOut(IIC_SDA);
    SET_CLK;
    SET_SDA;
    IIC_Slave_Address=SlaveAdd<<1;
    READ_INVALID=0x01;
    delayTime=IIC_STD_MODE;
    
}

/**
 * Funcation Name:IIC_C(overload)
 * Para:
 *      byte   slaveAdd    从机地址，除最后一位
 * Result:void
 * Funcation description:构造函数
 * 该函数用于初始化IIC通讯标准
*/
IIC_C::IIC_C(byte SlaveAdd)
{
    
    IIC_SendByte=&IIC_Write_MSB;
    IIC_RecvByte=&IIC_Read_MSB;
    
    IIC_SCL=A5;
    IIC_SDA=A4;
    pinModeOut(IIC_SCL);
    pinModeOut(IIC_SDA);
    SET_CLK;
    SET_SDA;
    IIC_Slave_Address=SlaveAdd<<1;
    READ_INVALID=0x01;
    delayTime=IIC_STD_MODE;
    
}

/**
 * Funcation Name:IIC_C(overload)
 * Para:void
 * Result:void
 * Funcation description:构造函数
 * 该函数用于初始化IIC通讯标准
*/
IIC_C::IIC_C()
{
    
    IIC_SendByte=&IIC_Write_MSB;
    IIC_RecvByte=&IIC_Read_MSB;
    
    IIC_SCL=A5;
    IIC_SDA=A4;
    pinModeOut(IIC_SCL);
    pinModeOut(IIC_SDA);
    SET_CLK;
    SET_SDA;
    IIC_Slave_Address=0;
    READ_INVALID=0x01;
    delayTime=IIC_STD_MODE;
    
}



/**
 * Funcation Name:setIICFreq
 * Para:
 *      unsigned int freq 总线频率设置，用于控制延时
 * Result:void
 * Funcation description:设置总线频率
*/
void IIC_C::setIICFreq(unsigned int freq)
{
  this->delayTime=freq;
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
    delayUs(delayTime);
    CLR_SDA;
    delayUs(delayTime);
    CLR_CLK;
    delayUs(delayTime);
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
    delayUs(delayTime);
    SET_CLK;
    delayUs(delayTime);
    SET_SDA;
    delayUs(delayTime);
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
    delayUs(delayTime);
    CLR_CLK;
    return true;
}


/**
 * Funcation Name:IIC_NAck2Slave
 * Para:无
 * Result:true
 * Funcation description:
 * 向从机发送ACK信号
*/
bool IIC_C::IIC_NAck2Slave()
{
    SET_SDA;
    SET_CLK;
    delayUs(delayTime);
    CLR_CLK;
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
    delayUs(delayTime);
    pinModeIN(IIC_SDA);
    SET_CLK;
    delayUs(delayTime);
    byte i=0;
    bool flag=IIC_TIME_OUT;
    while(i!=0xff&&flag==IIC_TIME_OUT)
    {
        i++;
        delayUs(delayTime);
        flag=getPin(IIC_SDA);
    }
    CLR_CLK;
    delayUs(delayTime);
    pinModeOut(IIC_SDA);
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
    delayUs(delayTime);
    pinModeIN(IIC_SDA);
    SET_SDA;
    byte count=8,recv=0,rbit=0;
    while(count!=0)
    {
        count--;
        SET_CLK;
        delayUs(delayTime);
        recv<<=1;
        rbit=getPin(IIC_SDA);
        CLR_CLK;
        recv|=rbit;
    }
    CLR_CLK;
    CLR_SDA;
    *data=recv;
    pinModeOut(IIC_SDA);
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
    byte count=8,sbit=0;
    while (count!=0)
    {
        sbit=(data&0x80)==0x80?1:0;
        if(sbit==1) SET_SDA;
        else CLR_SDA;
        data<<=1;
        delayUs(delayTime);
        SET_CLK;
        delayUs(delayTime*2);
        CLR_CLK;
        delayUs(delayTime);
        count--;
    }
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
    delayUs(50);
    pinModeIN(IIC_SDA);
    SET_SDA;
    byte count=8,recv=0,rbit=0;
    while(count!=0)
    {
        count--;
        recv>>=1;
        SET_CLK;
        delayUs(delayTime);
        rbit=getPin(IIC_SDA);
        CLR_CLK;
        if(rbit==1)
          recv|=(rbit<<7);
        
    }
    *data=recv;
    CLR_SDA;
    CLR_CLK;
    pinModeOut(IIC_SDA);
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
    CLR_CLK;
    byte count=8,sbit=0;
    while (count--)
    {
        sbit=(data&0x01);
        if(sbit==1)    SET_SDA;
        else CLR_SDA;
        data>>=1;
        SET_CLK;
        delayUs(delayTime);
        CLR_CLK;
    }
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

    IIC_Ack2Master();
    
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

    //delayUs(delayTime);
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
