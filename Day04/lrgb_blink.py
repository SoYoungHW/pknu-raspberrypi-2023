# LED RGB 깜빡이기
import RPi.GPIO as GPIO
import time

# isRun = True
red = 17
green = 27
blue = 22

GPIO.setmode(GPIO.BCM)
GPIO.setup(red, GPIO.OUT)
GPIO.setup(green, GPIO.OUT)
GPIO.setup(blue, GPIO.OUT)

try:
    while True:
        GPIO.output(red, True)
        GPIO.output(blue, False)
        GPIO.output(green, False)
        time.sleep(1)

        GPIO.output(green, True)
        GPIO.output(red, False)
        GPIO.output(blue, False)
        time.sleep(1)

        GPIO.output(blue, True)
        GPIO.output(green, False)
        GPIO.output(red, False)
        time.sleep(1)
        



except KeyboardInterrupt:
    GPIO.cleanup()