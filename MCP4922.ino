#include "pins_arduino.h"
#include <SPI.h>
#define LDAC   9              // ラッチ動作出力ピン

// set timecourse of light strength during light term


void setup() {
     Serial.begin(9600);
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
     double dt1;
     double dt2;
     int v1;
     int v2;
     t = millis() / 1000 % CYCLE;
     dt1 = CYCLE * DUTY1 / 100;
     dt2 = dt1 + CYCLE * DUTY2 / 100;
     v1 = VOLT1 * 4095 / 10;
     v2 = VOLT2 * 4095 / 10;

//     test(v1, v2);

     digitalWrite(LDAC,HIGH) ;
     digitalWrite(SS,LOW) ;
     if(t <= dt1){
          SPI.transfer(((v1 >> 8) & 0x0f) | 0x30) ; // Highバイト(0x30=OUTA/BUFなし/1x/シャットダウンなし)
          SPI.transfer(v1 & 0xff) ;        // Lowバイトの出力
     }else if(t <= dt2){
          SPI.transfer((v2 >> 8) | 0x30) ; // Highバイト(0x30=OUTA/BUFなし/1x/シャットダウンなし)
          SPI.transfer(v2 & 0xff) ;        // Lowバイトの出力
     }else{ 
          SPI.transfer(0x30) ; // Highバイト(0x30=OUTA/BUFなし/1x/シャットダウンなし)
          SPI.transfer(0x00) ;        // Lowバイトの出力
     }
     digitalWrite(SS,HIGH) ;
     digitalWrite(LDAC,LOW) ;        // ラッチ信号を出す
}

void test(int _v1, int _v2){
     int b;
     int c;
     b = (_v1 >> 8) | 0x30;
     c = _v1 & 0xff;
     Serial.println(_v1);
     Serial.print(b, BIN);
     Serial.println("");
     Serial.print(c, BIN);
     Serial.println("");
     delay(5000);
}