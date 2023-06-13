# LED 깜빡이기
import RPi.GPIO as GPIO
import time

signal_pin = 18

# GPIO.setmode(GPIO.BOARD) # 1 ~ 40
GPIO.setmode(GPIO.BCM) # GPIO 18, GROUND
GPIO.setup(signal_pin, GPIO.OUT) # GPIO18핀에다가 출력을 설정

while True:
    GPIO.output(signal_pin, True) # GPIO18핀에 전압시그널 ON
    time.sleep(1) # 2초동안 불을 켬
    GPIO.output(signal_pin, False) # GPIO18핀에 전압시그널 OFF
    time.sleep(0.5) # 1초 동안 불끈상태로 대기