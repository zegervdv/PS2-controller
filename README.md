# PS2 Controller

Sample joystick positions with STM32F072B and send over serial to
[STM-Quadcopter](http://github.com/zegervdv/STM-Quadcopter)

## Wiring
| PS2 colour | Button | Pin | HID byte |
| ---------- | ------ | --- | -------- |
| Yellow     | RX     | PA1 | 1        |
| Blue       | RY     | PA0 | 0        |
| Brown      | RZ     | PC5 | 4 [0]    |
| Green      | LX     | PA5 | 3        |
| Purple     | LY     | PA4 | 2        |
| Orange     | LZ     | PC4 | 4 [1]    |
