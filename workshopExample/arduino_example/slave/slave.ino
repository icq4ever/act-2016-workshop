/*
 * 2016 funpunfolly Site 04 interaction lighting system
 * with I2C master
 * master communicate with p5 via Serial.
 *
 *
 * Firmware by Yi donghoon 
 * icq4ever@gmail.com
 *
 * Hardware by Song yeji
 * songyeji000@gmail.com
 */

/*

  [ ID ]

  gateSlave  : 10
  slave #1   : 11
  slave #2   : 12
  slave #3   : 13
  slave #4   : 14
  slave #5   : 15

*/


#define ID                 11      // <------------------------- ID변경하기 
#include <Wire.h>

bool ledOn = false;
int outPin = 13;

void setup() {
  pinMode(outPin, OUTPUT);

  // I2C 관련 함수
  Wire.begin(ID);                // join i2c bus with own address 
  Wire.onRequest(requestEvent);
  Wire.onReceive(receiveEvent);  // register event


  Serial.begin(9600);           // start serial for output
}

void loop() {
  // 마스터에 의해 설정된 ledOn에 따라 스노우폴 온오프
  if (ledOn)   digitalWrite(outPin, HIGH);
  else         digitalWrite(outPin, LOW);
}


// 마스터의 명령을 수신하면 호출되는 이벤트함수
void receiveEvent(int howMany) {          // <--------------------- howMany가 뭔지는 리서치 해볼것!
  int x = Wire.read();    // receive byte as an integer
  
  if (x == 1) {  
    ledOn = true;
    //    Serial.println("ON");
  }
  else {
    ledOn = false;
    //    Serial.println("OFF");
  }
}

// 마스터에서의 요청이 올 경우 호출되는 이벤트 함수.
void requestEvent(){
  int sendMessage;
  // 뭔가를 날려서 신호를 보내주자
}