#ifndef _MACROUTILLS_H_
#define _MACROUTILLS_H_

#include"Arduino.h"

#define DEBUG

//data type define by self
#define PinNum unsigned char
#define byte unsigned char

#define MSB 0
#define LSB 1


//Macro funcation
#define pinModeOut(PIN) pinMode(PIN,OUTPUT)
#define pinModeIN(PIN) pinMode(PIN,INPUT)

#define setPin(PIN) digitalWrite(PIN,HIGH)
#define clrPin(PIN) digitalWrite(PIN,LOW)

#define getPin(PIN) digitalRead(PIN)

#define delayUs(us) delayMicroseconds(us)

#endif
