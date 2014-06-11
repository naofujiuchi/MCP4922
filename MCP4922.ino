#include "pins_arduino.h"
#include <SPI.h>
#include <Wire.h>
#include <RTC8564.h>

#define LDAC   9              // ラッチ動作出力ピン
long HOUR[8][3];
long MIN[8][3];
long SEC[8][3];
long TIME[8][3];
double VOLT[8][3];
int v[8][3];
int print[8];
int is;

void setup() {
     Serial.begin(9600);
     Rtc.begin();
     // 制御するピンは全て出力に設定する
     pinMode(LDAC,OUTPUT) ;
     // SPIの初期化処理を行う
     SPI.begin() ;                        // ＳＰＩを行う為の初期化
     SPI.setBitOrder(MSBFIRST) ;          // ビットオーダー
     SPI.setClockDivider(SPI_CLOCK_DIV8) ;// クロック(CLK)をシステムクロックの1/8で使用(16MHz/8)
     SPI.setDataMode(SPI_MODE0) ;         // クロック極性０(LOW)　クロック位相０

     // set timecourse of light strength during light term 
     // machine #0
     // set output voltage and beginning time of light term 1 as 24 hour format
     HOUR[0][0] = 19;
     MIN[0][0] = 21;
     SEC[0][0] = 0;
     VOLT[0][0] = 10;
     // set output voltage and beginning time of light term 2 as 24 hour format
     HOUR[0][1] = 19;
     MIN[0][1] = 21;
     SEC[0][1] = 10;
     VOLT[0][1] = 5;
     // set output voltage and beginning time light term 3 as 24 hour format
     HOUR[0][2] = 19;
     MIN[0][2] = 21;
     SEC[0][2] = 20;
     VOLT[0][2] = 0;

     // machine #1
     // set output voltage and beginning time of light term 1 as 24 hour format
     HOUR[1][0] = 19;
     MIN[1][0] = 21;
     SEC[1][0] = 0;
     VOLT[1][0] = 1;
     // set output voltage and beginning time of light term 2 as 24 hour format
     HOUR[1][1] = 19;
     MIN[1][1] = 21;
     SEC[1][1] = 10;
     VOLT[1][1] = 2;
     // set output voltage and beginning time light term 3 as 24 hour format
     HOUR[1][2] = 19;
     MIN[1][2] = 21;
     SEC[1][2] = 20;
     VOLT[1][2] = 1;

     // machine #2
     // set output voltage and beginning time of light term 1 as 24 hour format
     HOUR[2][0] = 19;
     MIN[2][0] = 21;
     SEC[2][0] = 0;
     VOLT[2][0] = 10;
     // set output voltage and beginning time of light term 2 as 24 hour format
     HOUR[2][1] = 19;
     MIN[2][1] = 21;
     SEC[2][1] = 10;
     VOLT[2][1] = 5;
     // set output voltage and beginning time light term 3 as 24 hour format
     HOUR[2][2] = 19;
     MIN[2][2] = 21;
     SEC[2][2] = 20;
     VOLT[2][2] = 2;

     // machine #3
     // set output voltage and beginning time of light term 1 as 24 hour format
     HOUR[3][0] = 19;
     MIN[3][0] = 21;
     SEC[3][0] = 0;
     VOLT[3][0] = 10;
     // set output voltage and beginning time of light term 2 as 24 hour format
     HOUR[3][1] = 19;
     MIN[3][1] = 21;
     SEC[3][1] = 10;
     VOLT[3][1] = 5;
     // set output voltage and beginning time light term 3 as 24 hour format
     HOUR[3][2] = 19;
     MIN[3][2] = 21;
     SEC[3][2] = 20;
     VOLT[3][2] = 3;

     // machine #4
     // set output voltage and beginning time of light term 1 as 24 hour format
     HOUR[4][0] = 19;
     MIN[4][0] = 21;
     SEC[4][0] = 0;
     VOLT[4][0] = 10;
     // set output voltage and beginning time of light term 2 as 24 hour format
     HOUR[4][1] = 19;
     MIN[4][1] = 21;
     SEC[4][1] = 10;
     VOLT[4][1] = 5;
     // set output voltage and beginning time light term 3 as 24 hour format
     HOUR[4][2] = 19;
     MIN[4][2] = 21;
     SEC[4][2] = 20;
     VOLT[4][2] = 4;

     // machine #5
     // set output voltage and beginning time of light term 1 as 24 hour format
     HOUR[5][0] = 19;
     MIN[5][0] = 21;
     SEC[5][0] = 0;
     VOLT[5][0] = 1;
     // set output voltage and beginning time of light term 2 as 24 hour format
     HOUR[5][1] = 19;
     MIN[5][1] = 21;
     SEC[5][1] = 10;
     VOLT[5][1] = 5;
     // set output voltage and beginning time light term 3 as 24 hour format
     HOUR[5][2] = 19;
     MIN[5][2] = 21;
     SEC[5][2] = 20;
     VOLT[5][2] = 5;

     // machine #6
     // set output voltage and beginning time of light term 1 as 24 hour format
     HOUR[6][0] = 19;
     MIN[6][0] = 21;
     SEC[6][0] = 0;
     VOLT[6][0] = 0;
     // set output voltage and beginning time of light term 2 as 24 hour format
     HOUR[6][1] = 19;
     MIN[6][1] = 21;
     SEC[6][1] = 10;
     VOLT[6][1] = 5;
     // set output voltage and beginning time light term 3 as 24 hour format
     HOUR[6][2] = 19;
     MIN[6][2] = 21;
     SEC[6][2] = 20;
     VOLT[6][2] = 6;

     // machine #7
     // set output voltage and beginning time of light term 1 as 24 hour format
     HOUR[7][0] = 19;
     MIN[7][0] = 21;
     SEC[7][0] = 0;
     VOLT[7][0] = 10;
     // set output voltage and beginning time of light term 2 as 24 hour format
     HOUR[7][1] = 19;
     MIN[7][1] = 21;
     SEC[7][1] = 10;
     VOLT[7][1] = 5;
     // set output voltage and beginning time light term 3 as 24 hour format
     HOUR[7][2] = 19;
     MIN[7][2] = 21;
     SEC[7][2] = 20;
     VOLT[7][2] = 7.5;

     // get a timecourse of output voltage
     getTimecourse();
}

void loop() {
     int i;
     int output;
     for(i = 0; i <= 7; i++){
          output = getOutput(i);
          digitalWrite(LDAC,HIGH) ;
          digitalWrite(SS,LOW) ;
          SPI.transfer(((output >> 8) & 0x0f) | 0x30) ; // Highバイト(0x30=OUTA/BUFなし/1x/シャットダウンなし)
          SPI.transfer(output & 0xff) ;        // Lowバイトの出力
          digitalWrite(SS,HIGH) ;
          digitalWrite(LDAC,LOW) ;        // ラッチ信号を出す
     }
}

int getOutput(int _i){
     int j;
     int k = 0;
     long h;
     long m;
     long s;
     long now;
     int out;
     Rtc.available();
     h = Rtc.hours(RTC8564::Decimal);
     m = Rtc.minutes(RTC8564::Decimal);
     s = Rtc.seconds(RTC8564::Decimal);
     now = 3600 * h + 60 * m + s;
     for(j = 0; j <= 2; j++){
          if(now >= TIME[_i][j]){
               k++;
          }
     }
     if((k > 0) && (k < 3)){
          out = v[_i][k - 1];
     }else{
          out = v[_i][2];
     }
     print[_i] = out;
     if(is != s){
          display(h, m, s, now);
     }
     is = s;
     return out;
}

void getTimecourse(){
     int i;
     int j;
     for(i = 0; i <= 7; i++){
          for(j = 0; j <= 2; j++){
               TIME[i][j] = 3600 * HOUR[i][j] + 60 * MIN[i][j] + SEC[i][j];
               v[i][j] = VOLT[i][j] * 4095 / 10;
          }
     }
}

void display(int _h, int _m, int _s, long _now){
     int i;
     Serial.print("CLOCK ");
     Serial.print(_h);
     Serial.print(":");
     Serial.print(_m);
     Serial.print(":");
     Serial.print(_s);
     Serial.print(", ");
     Serial.print(_now);
     Serial.print(", ");
     for(i = 0; i <= 7; i++){
          Serial.print(i);
          Serial.print(": ");
          Serial.print(print[i]);
          Serial.print(", ");
     }
     Serial.println("");
}
