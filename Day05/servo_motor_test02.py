# ServoMotor 테스트02
import RPi.GPIO as GPIO
import time

pwm_pin = 18

GPIO.setwarnings(False)
GPIO.setmode(GPIO.BCM)
GPIO.setup(pwm_pin, GPIO.OUT)
pwm = GPIO.PWM(pwm_pin, 50) # 초기화
pwm.start(3)

for i in range(0, 3):
    for high in range(30, 160):
        pwm.ChangeDutyCycle(high/10.0)
        print(f'각도 : {((high/10.0)-3)*10}')
        time.sleep(0.02)

    for low in range(160, 30, -1):
        pwm.ChangeDutyCycle(low/10.0)
        print(f'각도 : {((low/10.0)-3)*10}')
        time.sleep(0.02)

pwm.ChangeDutyCycle(0)
pwm.stop()
GPIO.cleanup()