# TestTouchscreen
Touchscreen test program based on Qt4.8, support Proface FP3700 touchscreen, read touch data from RS232 COM port.


V1.0 2022-Mar-19
1. Bugfix for parseTouchData() in class ProfaceTouch, the program can enter loop,
replace comDataBuffer->chop() with comDataBuffer->remove() to fix the bug.
2. Add macro PROFACE_TOUCH_DATA_WITH_HEADER, enable this marco will parse the data with header 0x11,
mask this macro will parse the data without header 0x11.
Currently enable this macro!
3. Bugfix for background image load, replace the background.jpg with background.png.


V1.0 2022-Mar-15
1. Support Proface FP3700 touchscreen, read touch data from serial port(9600/N/8/1)
2. Touchscreen resolution is configed in config.ini
[ProfaceTouch]
HScreen=1024
VScreen=768

[ComSetting]
Port=COM1
BaudRate=9600
StopBits=1
DataBits=8
Parity=None
FlowControl=Off
