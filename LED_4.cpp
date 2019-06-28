
#define L_Red 13
#define L_Yellow 12
#define L_Green 11
#define L_Blue 10



void setup(){

  pinMode(L_Red, OUTPUT);
  pinMode(L_Yellow, OUTPUT);
  pinMode(L_Green, OUTPUT);
  pinMode(L_Blue, OUTPUT);

}



void loop(){

}



//L_Color의 LED만 키고 나머지 LED는 끈다. delayTime만큼 딜레이한다.
void TurnON(int L_Color, int delayTime){

  for(int i=10; i<=13; i++){

    if(i==L_Color){
      digitalWrite(L_Color, HIGH);
      delay(delayTime);
    }
    else{
      digitalWrite(i, LOW);
    }

  }

}
