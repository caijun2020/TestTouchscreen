# TestTouchscreen
Touchscreen test program based on Qt4.8, support Proface FP3700 touchscreen, read touch data from RS232 COM port.


V2.0 2023-Feb-04
1. Support 2 touchscreen (Proface and MKU)
2. Add touch base class TouchAbs
3. Change config.ini setting, load touchscreen type, 0:proface, 1:MKU
[Touchscreen]
HScreen=1024
VScreen=768
Type=0

4. Update serial widget class SerialDebugWidget, in contructor funtion init the m_title
5. Add UI widget SettingWidget to select touch type
6. In class MainWidow, when create the serial handler, bind to the 2 touchscreen handler, so can support the 2 touchscreen simultaneously



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
