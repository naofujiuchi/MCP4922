#include "pins_arduino.h"
#include <SPI.h>

#define LDAC   9              // ラッチ動作出力ピン
#define CYCLE 10    // work cycle [sec]
#define DUTY1 30     // first duty ratio [%]
#define DUTY2 30     // second duty ratio [%]
// #define VOLTAGEA 10       // set voltage during DUTY1
// #define VOLTAGEB 5      // set voltage during DUTY2

int voltage1 = 10;
int voltage2 = 5;

void setup() {
     // 制御するピンは全て出力に設定する
     pinMode(LDAC,OUTPUT) ;
     // SPIの初期化処理を行う
     SPI.begin() ;                        // ＳＰＩを行う為の初期化
     SPI.setBitOrder(MSBFIRST) ;          // ビットオーダー
     SPI.setClockDivider(SPI_CLOCK_DIV8) ;// クロック(CLK)をシステムクロックの1/8で使用(16MHz/8)
     SPI.setDataMode(SPI_MODE0) ;         // クロック極性０(LOW)　クロック位相０
}
void loop() {
     int t;
     int dt1;
     int dt2;
     int v1;
     int v2;
     t = millis() / 1000 % CYCLE;
     dt1 = CYCLE * DUTY1 / 100;
     dt2 = dt1 + CYCLE * DUTY2 / 100;
//     v1 = VOLTAGE1;
     v1 = voltage1 * 4095 / 10;
     v2 = voltage2 * 4095 / 10;

     int i;
     int b;
     int c;
//     int b1;
//     int c1;
     b = (v1 >> 8) | 0x30;
     c = v1 & 0xff;
     Serial.print(b, BIN);
     Serial.println("");
     Serial.print(c, BIN);
     Serial.println("");
     Serial.println("1");
     delay(1000);

/*
     if(t <= dt1){

          digitalWrite(LDAC,HIGH) ;
          digitalWrite(SS,LOW) ;
          SPI.transfer(((v1 >> 8) & 0x0f) | 0x30) ; // Highバイト(0x30=OUTA/BUFなし/1x/シャットダウンなし)
          SPI.transfer(v1 & 0xff) ;        // Lowバイトの出力
          digitalWrite(SS,HIGH) ;
          digitalWrite(LDAC,LOW) ;        // ラッチ信号を出す
     }else if(t <= dt2){
          digitalWrite(LDAC,HIGH) ;
          digitalWrite(SS,LOW) ;
          SPI.transfer((v2 >> 8) | 0x30) ; // Highバイト(0x30=OUTA/BUFなし/1x/シャットダウンなし)
          SPI.transfer(v2 & 0xff) ;        // Lowバイトの出力
          digitalWrite(SS,HIGH) ;
          digitalWrite(LDAC,LOW) ;        // ラッチ信号を出す
     }else{ 
          digitalWrite(LDAC,HIGH) ;
          digitalWrite(SS,LOW) ;
          SPI.transfer(0x30) ; // Highバイト(0x30=OUTA/BUFなし/1x/シャットダウンなし)
          SPI.transfer(0x00) ;        // Lowバイトの出力
          digitalWrite(SS,HIGH) ;
          digitalWrite(LDAC,LOW) ;        // ラッチ信号を出す
     }
*/
}