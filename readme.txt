本工程功能为IIC通讯，可自定义SDA引脚、SCL引脚、选择R/W的有效电平、定义传送方式（MSB/LSB），详情请见构造函数。本工程以Arduino（atmega328p-pu）为基础，在成员函数的指针的用法上与标准的C++略有不同。在测试时可以定义DEBUG宏来显示条件编译下规定的串口返回的辅助信息，需要先使用Serial.begin(baud rate)方法初始化UART传输协议。
License:MPLV2.0协议。
作者:JinYUHuang
e-mail:sedev_home1896@163.com
