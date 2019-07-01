#include <Adafruit_NeoPixel.h>
#include "SoftwareSerial.h" // mp3 모듈의 dependency
#include "DFRobotDFPlayerMini.h" //mp3 모듈을 위한 라이브러리

#define NUMPIXELS  8 //pixel은 8개 소자로 구성됨
#define DELAYVAL 500 // NeoPixel delay 시간


#define BUTTON 6 // 시작처리를 위한 버튼. 메인보드의 입력값을 이어옴
#define NEOPIN1 12
#define NEOPIN2 13
#define MAINVOL 10


DFRobotDFPlayerMini myDFPlayerMain;
SoftwareSerial mySoftwareSerialMain(4, 5); // RX, TX
Adafruit_NeoPixel pixels1 (NUMPIXELS, NEOPIN1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels2 (NUMPIXELS, NEOPIN2, NEO_GRB + NEO_KHZ800);

int orchestraON = 0;

// pixels_TurnOff(5000);


void setup(){
  pinMode(BUTTON, INPUT);


  mySoftwareSerialMain.begin(9600);
  myDFPlayerMain.begin(mySoftwareSerialMain);
  myDFPlayerMain.volume(MAINVOL);  //Set volume value. From 0 to 30

  pixels1.begin();
  pixels2.begin();
}


void loop(){
  if(orchestraON){
    myDFPlayerMain.play(1);
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
      Serial.println("Orchestra가 시작되었도다.");
      orchestraON = !orchestraON;
      if(orchestraON) {
        myDFPlayerMain.volume(MAINVOL);
         myDFPlayerMain.play(1);
       }
      else{
        myDFPlayerMain.volume(0);
      }
      delay(3000);


    }
  }





}


// void pixels_TurnOff(int pixels_delayTime){
//   pixels.clear();
//   pixels.show();
//   delay(pixels_delayTime);
// }
