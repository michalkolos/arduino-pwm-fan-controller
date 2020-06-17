# arduino-pwm-fan-controller

A small script that allows Arduino to separately set the speed of two standard CPU fans. In order to control those fans the Arduino needs to generate a PWM signal at 25 kHz frequency. 

This is significantly more than the default 490 Hz. To achieve that frequency Timer 01 of the chip can be configured to cycle at 25 kHz in phase correct PWM mode since it uses 16bit ICRx register. This affects only two outputs on pins 9 and 10 that are connected to that timer.

Unmodified script will properly work only with boards based on ATmega168 or 328 chips clocked at 16 MHz. 
