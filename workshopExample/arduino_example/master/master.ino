/*
 * 2016 ACT workshop
 * remote control lighting system with multiple arduinos using I2C communication
 * master arduino communicate with p5 via Serial.
 *
 *
 * Arduino Firmware by Yi donghoon 
 * icq4ever@gmail.com
 *
 * Hardware designed by Song Yeji
 * songyeji000@gmail.com
 */

#define NUMBER_OF_SLAVES  2               // <------------------------- total number of slaves in I2C network

#include <Wire.h>

// LED on/off flag
int ledOn[NUMBER_OF_SLAVES]             = {  0,  0 };
int readFromSlaves[NUMBER_OF_SLAVES]    = {  0,  0 };

// slave ID bank
// const int SLAVE[NUMBER_OF_SLAVES] = { 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};   // SLAVE addresses
const int SLAVE[NUMBER_OF_SLAVES] = { 11, 12 };   // SLAVE addresses
int currentIndex = 0;


// 슬레이브의 갯수만큼 , 를 붙여 메시지 버퍼를 만든다.
// char sendMessageBuffer[NUMBER_OF_SLAVES + (NUMBER_OF_SLAVES - 1)] = { '0', ',', '0', ',', '0', ',', '0', ',', '0', ',', '0' };
char sendMessageBuffer[NUMBER_OF_SLAVES + (NUMBER_OF_SLAVES - 1)] = { '0', ',', '0' };

void setup() {
    pinMode(13, OUTPUT);

    // 프로세싱과 통신 준비하기
    Serial.begin(9600);

    Wire.begin(); // join i2c bus (address optional for master)
}

void loop() {
    if(Serial.available()){     // 플로세싱과의 통신. 

        // read from serial (from processing)
        int incomingValue = Serial.read();
        ledOn[currentIndex] = incomingValue;    // save to LED flag array

        // send on/off flag to each slaves (INT)
        Wire.beginTransmission(SLAVE[currentIndex]);    // beginTransmission(_SLAVE_ADDRESS_)
        Wire.write(ledOn[currentIndex]);                // write(data);
        Wire.endTransmission(SLAVE[currentIndex]);      // endTransmission(_SLAVE_ADDRESS_)

        // request from all slaves
        Wire.requestFrom(SLAVE[currentIndex]);
        while(Wire.available()){ 
            readFromSlaves[currentIndex] = Wire.read(); 
        }


        currentIndex++;     // increase index
        if(currentIndex > NUMBER_OF_SLAVES -1){         // if index is reached 
            currentIndex = 0;                           // set index to 0
        }
    }


}
