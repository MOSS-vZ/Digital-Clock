# 基于MCU的数字钟设计
## 开发平台
- 单片机：德州仪器（TI）的MSPM0L1306开发板；
- 开发环境：Keil，集成了SysConfig图形化配置工具。
## 主要功能
1. 秒定时功能。利用定时器中断实现 1s 的精确定时功能，通过 IO 口输出并驱动 LED 灯每 1S 闪烁一次。
2. 24 小时制时钟功能。通过 OLED 屏显示当前时间的时、分、秒，能够正确走时和进位。
3. 万年历功能。通过 OLED 屏显示日期（年、月、日、星期）。
4. 时间、日期设置功能。可通过矩阵按键设置当前时间和日期。
5. 12 小时制。在 12 小时制时显示 AM/PM，通过按键切换 12/24 时制。
6. 闹钟功能。可独立设置 3 个闹钟，可查看闹钟时间并修改，可设置闹钟开关，各个闹钟可独立工作。
7. 计时器功能。计时器显示单位为 s，能通过按键开启、暂停、关闭和清零计时器。
## 按键说明
从左到右，从上到下按键依次映射为1,2,3,u,4,5,6,d,7,8,9,l,q,0,y,r（也可以到[main.c](https://github.com/MOSS-vZ/Digital-Clock/blob/main/Core/src/main.c)里面的keyboard函数模块查看）。

>[!tip] 
>1. 这个项目是在空工程基础上设计的，主要由本人编写的是[main.c](https://github.com/MOSS-vZ/Digital-Clock/blob/main/Core/src/main.c)，[DIGITAL_CLOCK.syscfg](DIGITAL_CLOCK.syscfg)（通过SysConfig配置的）；
>2. 闹钟功能在设置时间过程会出现乱码，但不影响设置结果；
>3. 计时器功能偶尔会出现乱码，清零后再开启就正常了；
>4. 第一次进行开发设计，所有的代码都写在[main.c](https://github.com/MOSS-vZ/Digital-Clock/blob/main/Core/src/main.c)一个文件里面了，可读性比较差。
