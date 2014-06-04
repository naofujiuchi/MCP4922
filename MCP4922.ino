#include "pins_arduino.h"
#include <SPI.h>
#include <Wire.h>
#include <RTC8564.h>

#define LDAC   9              // ラッチ動作出力ピン
long HOUR[4];
long MIN[4];
long SEC[4];
long TIME[4];
double VOLT[4];
int v[4];
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
     // set beginning time of light term 1 as 24 hour
     HOUR[0] = 19;
     MIN[0] = 21;
     SEC[0] = 0;
     VOLT[0] = 10;
     // set beginning time of light term 2 as 24 hour
     HOUR[1] = 19;
     MIN[1] = 21;
     SEC[1] = 10;
     VOLT[1] = 5;
     // set beginning time of light term 3 as 24 hour
     HOUR[2] = 19;
     MIN[2] = 21;
     SEC[2] = 20;
     VOLT[2] = 2.5;
     // set beginning time of light term 4 as 24 hour
     HOUR[3] = 19;
     MIN[3] = 21;
     SEC[3] = 30;
     VOLT[3] = 0;

     // get a timecourse of output voltage
     getTimecourse();
}

void loop() {
     int output;
     output = getOutput();
     digitalWrite(LDAC,HIGH) ;
     digitalWrite(SS,LOW) ;
     Rtc.available();
     SPI.transfer(((output >> 8) & 0x0f) | 0x30) ; // Highバイト(0x30=OUTA/BUFなし/1x/シャットダウンなし)
     SPI.transfer(output & 0xff) ;        // Lowバイトの出力
     digitalWrite(SS,HIGH) ;
     digitalWrite(LDAC,LOW) ;        // ラッチ信号を出す
}

int getOutput(){
     int i;
     int j = 0;
     long h;
     long m;
     long s;
     long now;
     int out;
     h = Rtc.hours(RTC8564::Decimal);
     m = Rtc.minutes(RTC8564::Decimal);
     s = Rtc.seconds(RTC8564::Decimal);
     now = 3600 * h + 60 * m + s;
     for(i = 0; i <= 3; i++){
          if(now >= TIME[i]){
               j++;
          }
     }
     if((j > 0) && (j < 4)){
          out = v[j - 1];
     }else{
          out = v[3];
     }
     display(h, m, s, now, out);
     is = s;
     return out;
}

void getTimecourse(){
     int i;
     for(i = 0; i <= 3; i++){
          TIME[i] = 3600 * HOUR[i] + 60 * MIN[i] + SEC[i];
          v[i] = VOLT[i] * 4095 / 10;
     }
}

void display(int _h, int _m, int _s, long _now, long _out){
     if(is != _s){
          Serial.print("CLOCK ");
          Serial.print(_h);
          Serial.print(":");
          Serial.print(_m);
          Serial.print(":");
          Serial.print(_s);
          Serial.print(", ");
          Serial.print(_now);
          Serial.print(", ");
          Serial.println(_out);
     }
}