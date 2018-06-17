# An example from https://sourceforge.net/p/raspberry-gpio-python/wiki/PWM/

import RPi.GPIO as GPIO

j_pin = 12 # Note! This is the number of the phisical pin that correspond to GPIO 18

GPIO.setmode(GPIO.BOARD)
GPIO.setup(j_pin, GPIO.OUT)

p = GPIO.PWM(j_pin, 500) # Frequency in Hz
p.start(30) # 30% PWM

input('Press ENTER to stop')
p.stop()
GPIO.cleanup()