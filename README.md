# pknu-raspberrypi-2023
라즈베리파이 학습 리포지토리

## 1일차 / 2일차
- 라즈베리파이 학습
	- 라즈베리파이 소개
	- 라즈비안 설치
		- Bullseye
	- 라즈비안 설정
		- 기본 업데이트/업그레이드
		- 한글 폰트 및 입력기
		- 스크린세이버, 와이파이 연결 끊김 해제
	- pi-apps 설치
		- Visual Studio Code 설치
		- Github Desktop 설치 및 설정
	- Visual Studio Code
		- Python 플러그인
	- 리눅스 기본
		- 리눅스 명령어 (대표적인 20여가지)

## 3잁차
- 라즈베리파이 학습
	- 통신 설정
		- AnyDesk 실패
	- 리눅스 일반
		- 서비스 실행, 확인, 종료
			- systemctl [start|stop|status] 서비스명
		- MySQL DB
		- WebServer
	- Flask 기본  

## 4일차
- 라즈베리파이 학습
	- PyQt5 설치
	- QtDesigner 설치 및 실행확인
	- 하드웨어 제어 (GPIO)
		- LED / RGB LED 출력

## 5일차
- 라즈베리파이 학습
	- 네트워크 세팅(VNC)
	- RGB LED / Button 클릭
	- 온습도 센서
	- 서보모터

## 6일차
- 라즈베리파이 학습
	- MQTT 통신
		- MQTT Broker IP, port 설정, 계정설정(옵션)
		- RPi <--> WPF
		- RPi 온습도 센서값 MQTT 전송
			- Python paho-mqtt 패키지
		- WPF 모터, LED 제어값 전송
			- C# M2Mqtt 패키지


<온습도 센서값 전송화면>

<img src="https://github.com/SoYoungHW/pknu-raspberrypi-2023/blob/main/images/raspberrypi01.gif" width="700">

<모터, LED 라즈베리파이 테스트 결과>

<img src="https://github.com/SoYoungHW/pknu-raspberrypi-2023/blob/main/images/raspberrypi02.jpg" width="700">

## 7일차
- 라즈베리파이 학습
	- 파이카메라 v1.3 ov5647
	- OpenCV 4.7
	- 카메라 연동 QrCode 