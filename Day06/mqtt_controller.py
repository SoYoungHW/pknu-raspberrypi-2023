# MQTT 패키지 설치 paho-mqtt
# sudo pip install paho-mqtt
## publish(데이터 전송-출판하는쪽) + subscribe(데이터수신-구독하는쪽) 동시에 처리

from threading import Thread, Timer
import time # time.sleep()
import json
import datetime as dt
import paho.mqtt.client as mqtt
import Adafruit_DHT as dht # DHT11 온습도센서
import RPi._GPIO as GPIO # LED

# GPIO, DHT 설정
sensor = dht.DHT11
rcv_pin = 10
green = 27
servo_pin = 18

GPIO.setwarnings(False)

# green led init
GPIO.setmode(GPIO.BCM)
GPIO.setup(green, GPIO.OUT)
GPIO.output(green, True) # = GPIO.HIGH

# servo init
GPIO.setup(servo_pin, GPIO.OUT)
pwm = GPIO.PWM(servo_pin, 100) # 서보모터 최대각도(주파수)
pwm.start(3) # 각도 0 DutyCycle 3 ~ 20

# 여기서 데이터를 보내는 객체
class publisher(Thread):
    def __init__(self):
        Thread.__init__(self) # 스레드 초기화
        self.host = '210.119.12.54' # 본인pc ip주소
        self.port = 1883 # MQTT포트번호(회사에서는 이 번호 그대로 안씀)
        self.clientID = 'IOT54'
        self.count = 0
        print('publisher 스레드 시작')
        self.client = mqtt.Client(client_id = self.clientID) # 설계대로

    def run(self):
        self.client.connect(self.host, self.port)
        # self.client.username_pw_set() 계정으로 로그인할때 필요
        self.publish_data_auto()

    def publish_data_auto(self):
        humid, temp = dht.read_retry(sensor, rcv_pin)
        curr = dt.datetime.now().strftime('%Y-%m-%d %H:%M:%S') # 2023-06-14 10:39:24
        origin_data = { 'DEV_ID' : self.clientID,
                        'CURR_DT' : curr,
                        'TYPE' : 'TEMP | HUMID',
                        'STAT' : f'{temp} | {humid}' } # data(json 형태)
        pub_data = json.dumps(origin_data) # MQTT로 전송할 json데이터로 변환
        self.client.publish(topic='pknu/rpi/control/', payload=pub_data)
        print(f'Data Published #{self.count}')
        self.count += 1
        Timer(2.0, self.publish_data_auto).start() # 2초마다 publish

# 다른곳에서 데이터를 받아오는 객체
class Subscriber(Thread):
    def __init__(self):
        Thread.__init__(self)
        self.host = '210.119.12.54' # 브로커 IP
        # self.host = 'https://'per123.azure.com/....
        self.port = 1883
        self.clientID = 'IOT54_SUB'
        self.topic = 'pknu/monitor/control/'
        print('subscriber 스레드 시작')
        self.client = mqtt.Client(client_id=self.clientID)

    def run(self): # Thread.start() 함수를 실행하면 실행되는 함수
        self.client.on_connect = self.onConnect # 접속성공 시그널 처리
        self.client.on_message = self.onMessage # 접속후 메시지가 수신되면 처리
        self.client.connect(self.host, self.port)
        self.client.subscribe(topic=self.topic)
        self.client.loop_forever() # 무한반복

    def onConnect(self, mqttc, obj, flags, rc):
        print(f'subscriber 연결됨 rc > {rc}')

    def onMessage(self, mqttc, obj, msg):
        rcv_msg = str(msg.payload.decode('utf-8'))
        # print(f'{msg.topic} / {rcv_msg}') //확인완료
        data = json.loads(rcv_msg) # json data로 형변환
        stat = data['STAT']
        print(f'현재 STAT : {stat}')
        if stat == 'OPEN':
            GPIO.output(green, False)
            pwm.ChangeDutyCycle(12) # 90도
        elif stat == 'CLOSE':
            GPIO.output(green, True)
            pwm.ChangeDutyCycle(3) # 0도
        time.sleep(1.0)

if __name__ == '__main__':
    thPub = publisher() # publisher 객체 생성
    thPub.start() # run()이 자동실행
    
    thSub = Subscriber() # subscriber 객체 생성
    thSub.start()