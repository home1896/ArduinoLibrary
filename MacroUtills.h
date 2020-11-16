#ifndef _MACROUTILLS_H_
#define _MACROUTILLS_H_

/**
 * 本文件定义了宏常量和宏函数
 * Author:sedev_home1896@163.com
 * License:MPL V2.0
*/

#include"Arduino.h"




//自定义变量类型
#define PinNum unsigned char
#define byte unsigned char

#define MSB 0
#define LSB 1


//宏函数
#define pinModeOut(PIN) pinMode(PIN,OUTPUT)
#define pinModeIN(PIN) pinMode(PIN,INPUT)

#define setPin(PIN) digitalWrite(PIN,HIGH)
#define clrPin(PIN) digitalWrite(PIN,LOW)

#define getPin(PIN) digitalRead(PIN)

#define delayUs(us) delayMicroseconds(us)

#endif
