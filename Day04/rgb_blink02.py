# LED RGB 깜빡이기
import RPi.GPIO as GPIO
import time

# isRun = True
red = 17; green = 27; blue = 22 # Ground 역할

GPIO.setmode(GPIO.BCM)
GPIO.setup(red, GPIO.OUT)
GPIO.setup(green, GPIO.OUT)
GPIO.setup(blue, GPIO.OUT)

GPIO.output(red, True)
GPIO.output(green, True)
GPIO.output(blue, True)
# -- 초기화

try:
    while True:
        # red + green ON = yellow / red + blue ON = pink / blue + green ON = sky
        # red + green + blue ON = white

        GPIO.output(red, False) # red ON
        GPIO.output(green, True)
        GPIO.output(blue, True)
        time.sleep(1)
        
        GPIO.output(green, False) # green ON
        GPIO.output(red, True)
        GPIO.output(blue, True)
        time.sleep(1)

        GPIO.output(blue, False) # blue ON
        GPIO.output(red, True)
        GPIO.output(green, True)
        time.sleep(1)

except KeyboardInterrupt:
    GPIO.output(red, GPIO.HIGH)
    GPIO.output(green, GPIO.HIGH)
    GPIO.output(blue, GPIO.HIGH) # LED 꺼짐
    GPIO.cleanup()