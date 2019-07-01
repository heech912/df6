//  DF 2019 6팀 orchestra
#include <Wire.h> // gesture 센서의 dependency
#include <SparkFun_APDS9960.h> // gesture 센서를 위한 라이브러리

#include "SoftwareSerial.h" // mp3 모듈의 dependency
#include "DFRobotDFPlayerMini.h" //mp3 모듈을 위한 라이브러리

#define GESTURE_INTERRUPT 2 // gesture 센서의 Interrupt
#define BUTTON 9 // 시작처리를 위한 버튼. 설계에 따라 광센서 사용도 고려할만함

SparkFun_APDS9960 apds = SparkFun_APDS9960(); // gesture 센서의 전역 Instance
DFRobotDFPlayerMini myDFPlayer;
SoftwareSerial mySoftwareSerial(10, 11); // RX, TX

int orchestraON = 0;
int gestureON = 0;


void setup(){

pinMode(GESTURE_INTERRUPT, INPUT);
pinMode(BUTTON, INPUT);


attachInterrupt(0, interruptRoutine, FALLING); // Gesture interrupt initialize
apds.init();
apds.enableGestureSensor(true);

Serial.begin(9600);
mySoftwareSerial.begin(9600);
myDFPlayer.begin(mySoftwareSerial);
myDFPlayer.volume(10);  //Set volume value. From 0 to 30
}

void loop(){
  if(orchestraON){
    if( gestureON == 1 ) {
      detachInterrupt(0);
      handleGesture();
      gestureON = 0;
      attachInterrupt(0, interruptRoutine, FALLING);
    }
  }
  else{
    if(!digitalRead(BUTTON)){
      Serial.println("Orchestra가 시작됩니다.");
      orchestraON = 1;
      delay(3000);


    }
  }

}

void handleGesture() {
    if ( apds.isGestureAvailable() ) {
    switch ( apds.readGesture()) {
      case DIR_UP:
        break;
      case DIR_DOWN:
        break;
      case DIR_LEFT:
        myDFPlayer.play(1);
        break;
      case DIR_RIGHT:
        myDFPlayer.play(2);
        break;
      case DIR_NEAR:
        Serial.println("NEAR");
        break;
      case DIR_FAR:
        Serial.println("FAR");
        break;
      default:
        Serial.println("NONE");
    }
  }
}

void interruptRoutine(){
  gestureON = 1;
}
