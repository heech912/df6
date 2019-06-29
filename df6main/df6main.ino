//  DF 2019 6팀 orchestra
#include <Wire.h> // gesture 센서의 dependency
#include <SparkFun_APDS9960.h> // gesture 센서를 위한 라이브러리
#include <Adafruit_NeoPixel.h>

#include "SoftwareSerial.h" // mp3 모듈의 dependency
#include "DFRobotDFPlayerMini.h" //mp3 모듈을 위한 라이브러리

#define NUMPIXELS  8 //pixel은 8개 소자로 구성됨
#define DELAYVAL 500 // NeoPixel delay 시간

#define GESTURE_INTERRUPT 2 // gesture 센서의 Interrupt
#define BUTTON 9 // 시작처리를 위한 버튼. 설계에 따라 광센서 사용도 고려할만함
#define NEOPIN1 12
#define NEOPIN2 13

SparkFun_APDS9960 apds = SparkFun_APDS9960(); // gesture 센서의 전역 Instance
DFRobotDFPlayerMini myDFPlayer;
SoftwareSerial mySoftwareSerial(10, 11); // RX, TX
Adafruit_NeoPixel pixels1 (NUMPIXELS, NEOPIN1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels2 (NUMPIXELS, NEOPIN2, NEO_GRB + NEO_KHZ800);

int orchestraON = 0;
int gestureON = 0;




void setup(){

pinMode(GESTURE_INTERRUPT, INPUT);
pinMode(BUTTON, INPUT);


attachInterrupt(0, interruptRoutine, FALLING); // Gesture interrupt initialize
apds.init();
apds.enableGestureSensor(true);
pixels1.begin();
pixels2.begin();

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
    // pixels_TurnOff(5000);

    for(int i=0; i<NUMPIXELS; i++) {
      pixels1.setPixelColor(i, pixels1.Color(150, 150, i * 20));
      pixels1.show();
      delay(DELAYVAL);
    }

    // pixels_TurnOff(5000);

    for(int j=1; j<=250; j++){

      for(int i=0; i<NUMPIXELS; i++) {
        pixels2.setPixelColor(i, pixels2.Color(250-j, 250, 250-i*30));
        pixels2.show();
      }

      delay(100); //dalay 총 25000. 250*100

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

// void pixels_TurnOff(int pixels_delayTime){
//   pixels.clear();
//   pixels.show();
//   delay(pixels_delayTime);
// }
