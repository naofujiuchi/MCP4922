#include "pins_arduino.h"
#include <SPI.h>
#include <Wire.h>
#include <RTC8564.h>

#define LDAC   9              // ラッチ動作出力ピン
long HOUR[14][4];
long MIN[14][4];
long SEC[14][4];
long TIME[14][4];
double VOLT[14][4];
int v[14][4];
int print[14];
int is;

void setup() {
     int i;
     Serial.begin(9600);
     Rtc.begin();
     // 制御するピンは全て出力に設定する
     pinMode(LDAC,OUTPUT) ;
     // set output pin0-8 as SS0–8 for machine #0-8
     pinMode(2, OUTPUT);
     pinMode(3, OUTPUT);
     pinMode(4, OUTPUT);
     pinMode(5, OUTPUT);
     pinMode(6, OUTPUT);
     pinMode(7, OUTPUT);     
     pinMode(8, OUTPUT);
     // initialize SS0–8
     for(i = 0; i <= 8; i++){
          digitalWrite(i, HIGH);
     }
     // SPIの初期化処理を行う
     SPI.begin() ;                        // ＳＰＩを行う為の初期化
     SPI.setBitOrder(MSBFIRST) ;          // ビットオーダー
     SPI.setClockDivider(SPI_CLOCK_DIV8) ;// クロック(CLK)をシステムクロックの1/8で使用(16MHz/8)
     SPI.setDataMode(SPI_MODE0) ;         // クロック極性０(LOW)　クロック位相０

     // set timecourse of light strength during light term 
     // machine #0
     // set output voltage and beginning time of light term 1 as 24 hour format
     HOUR[0][0] = 0;
     MIN[0][0] = 0;
     SEC[0][0] = 0;
     VOLT[0][0] = 0;
     // set output voltage and beginning time of light term 2 as 24 hour format
     HOUR[0][1] = 0;
     MIN[0][1] = 0;
     SEC[0][1] = 0;
     VOLT[0][1] = 0;
     // set output voltage and beginning time light term 3 as 24 hour format
     HOUR[0][2] = 0;
     MIN[0][2] = 0;
     SEC[0][2] = 0;
     VOLT[0][2] = 0;
     // set output voltage and beginning time light term 4 as 24 hour format
     HOUR[0][3] = 0;
     MIN[0][3] = 0;
     SEC[0][3] = 0;
     VOLT[0][3] = 0;

     // machine #1
     // set output voltage and beginning time of light term 1 as 24 hour format
     HOUR[1][0] = 0;
     MIN[1][0] = 0;
     SEC[1][0] = 0;
     VOLT[1][0] = 0;
     // set output voltage and beginning time of light term 2 as 24 hour format
     HOUR[1][1] = 0;
     MIN[1][1] = 0;
     SEC[1][1] = 0;
     VOLT[1][1] = 0;
     // set output voltage and beginning time light term 3 as 24 hour format
     HOUR[1][2] = 0;
     MIN[1][2] = 0;
     SEC[1][2] = 0;
     VOLT[1][2] = 0;
     // set output voltage and beginning time light term 4 as 24 hour format
     HOUR[1][3] = 0;
     MIN[1][3] = 0;
     SEC[1][3] = 0;
     VOLT[1][3] = 0;

     // machine #2
     // set output voltage and beginning time of light term 1 as 24 hour format
     HOUR[2][0] = 0;
     MIN[2][0] = 0;
     SEC[2][0] = 0;
     VOLT[2][0] = 0;
     // set output voltage and beginning time of light term 2 as 24 hour format
     HOUR[2][1] = 0;
     MIN[2][1] = 0;
     SEC[2][1] = 0;
     VOLT[2][1] = 0;
     // set output voltage and beginning time light term 3 as 24 hour format
     HOUR[2][2] = 0;
     MIN[2][2] = 0;
     SEC[2][2] = 0;
     VOLT[2][2] = 0;
     // set output voltage and beginning time light term 4 as 24 hour format
     HOUR[2][3] = 0;
     MIN[2][3] = 0;
     SEC[2][3] = 0;
     VOLT[2][3] = 0;

     // machine #3
     // set output voltage and beginning time of light term 1 as 24 hour format
     HOUR[3][0] = 0;
     MIN[3][0] = 0;
     SEC[3][0] = 0;
     VOLT[3][0] = 0;
     // set output voltage and beginning time of light term 2 as 24 hour format
     HOUR[3][1] = 0;
     MIN[3][1] = 0;
     SEC[3][1] = 0;
     VOLT[3][1] = 0;
     // set output voltage and beginning time light term 3 as 24 hour format
     HOUR[3][2] = 0;
     MIN[3][2] = 0;
     SEC[3][2] = 0;
     VOLT[3][2] = 0;
     // set output voltage and beginning time light term 4 as 24 hour format
     HOUR[3][3] = 0;
     MIN[3][3] = 0;
     SEC[3][3] = 0;
     VOLT[3][3] = 0;

     // machine #4
     // set output voltage and beginning time of light term 1 as 24 hour format
     HOUR[4][0] = 0;
     MIN[4][0] = 0;
     SEC[4][0] = 0;
     VOLT[4][0] = 0;
     // set output voltage and beginning time of light term 2 as 24 hour format
     HOUR[4][1] = 0;
     MIN[4][1] = 0;
     SEC[4][1] = 0;
     VOLT[4][1] = 0;
     // set output voltage and beginning time light term 3 as 24 hour format
     HOUR[4][2] = 0;
     MIN[4][2] = 0;
     SEC[4][2] = 0;
     VOLT[4][2] = 0;
     // set output voltage and beginning time light term 4 as 24 hour format
     HOUR[4][3] = 0;
     MIN[4][3] = 0;
     SEC[4][3] = 0;
     VOLT[4][3] = 0;

     // machine #5
     // set output voltage and beginning time of light term 1 as 24 hour format
     HOUR[5][0] = 0;
     MIN[5][0] = 0;
     SEC[5][0] = 0;
     VOLT[5][0] = 0;
     // set output voltage and beginning time of light term 2 as 24 hour format
     HOUR[5][1] = 0;
     MIN[5][1] = 0;
     SEC[5][1] = 0;
     VOLT[5][1] = 0;
     // set output voltage and beginning time light term 3 as 24 hour format
     HOUR[5][2] = 0;
     MIN[5][2] = 0;
     SEC[5][2] = 0;
     VOLT[5][2] = 0;
     // set output voltage and beginning time light term 4 as 24 hour format
     HOUR[5][3] = 0;
     MIN[5][3] = 0;
     SEC[5][3] = 0;
     VOLT[5][3] = 0;

     // machine #6
     // set output voltage and beginning time of light term 1 as 24 hour format
     HOUR[6][0] = 0;
     MIN[6][0] = 0;
     SEC[6][0] = 0;
     VOLT[6][0] = 0;
     // set output voltage and beginning time of light term 2 as 24 hour format
     HOUR[6][1] = 0;
     MIN[6][1] = 0;
     SEC[6][1] = 0;
     VOLT[6][1] = 0;
     // set output voltage and beginning time light term 3 as 24 hour format
     HOUR[6][2] = 0;
     MIN[6][2] = 0;
     SEC[6][2] = 0;
     VOLT[6][2] = 0;
     // set output voltage and beginning time light term 4 as 24 hour format
     HOUR[6][3] = 0;
     MIN[6][3] = 0;
     SEC[6][3] = 0;
     VOLT[6][3] = 0;

     // machine #7
     // set output voltage and beginning time of light term 1 as 24 hour format
     HOUR[7][0] = 0;
     MIN[7][0] = 0;
     SEC[7][0] = 0;
     VOLT[7][0] = 0;
     // set output voltage and beginning time of light term 2 as 24 hour format
     HOUR[7][1] = 0;
     MIN[7][1] = 0;
     SEC[7][1] = 0;
     VOLT[7][1] = 0;
     // set output voltage and beginning time light term 3 as 24 hour format
     HOUR[7][2] = 0;
     MIN[7][2] = 0;
     SEC[7][2] = 0;
     VOLT[7][2] = 0;
     // set output voltage and beginning time light term 4 as 24 hour format
     HOUR[7][3] = 0;
     MIN[7][3] = 0;
     SEC[7][3] = 0;
     VOLT[7][3] = 0;

     // machine #8
     // set output voltage and beginning time of light term 1 as 24 hour format
     HOUR[8][0] = 0;
     MIN[8][0] = 0;
     SEC[8][0] = 0;
     VOLT[8][0] = 0;
     // set output voltage and beginning time of light term 2 as 24 hour format
     HOUR[8][1] = 0;
     MIN[8][1] = 0;
     SEC[8][1] = 0;
     VOLT[8][1] = 0;
     // set output voltage and beginning time light term 3 as 24 hour format
     HOUR[8][2] = 0;
     MIN[8][2] = 0;
     SEC[8][2] = 0;
     VOLT[8][2] = 0;
     // set output voltage and beginning time light term 4 as 24 hour format
     HOUR[8][3] = 0;
     MIN[8][3] = 0;
     SEC[8][3] = 0;
     VOLT[8][3] = 0;

     // machine #9
     // set output voltage and beginning time of light term 1 as 24 hour format
     HOUR[9][0] = 0;
     MIN[9][0] = 0;
     SEC[9][0] = 0;
     VOLT[9][0] = 0;
     // set output voltage and beginning time of light term 2 as 24 hour format
     HOUR[9][1] = 0;
     MIN[9][1] = 0;
     SEC[9][1] = 0;
     VOLT[9][1] = 0;
     // set output voltage and beginning time light term 3 as 24 hour format
     HOUR[9][2] = 0;
     MIN[9][2] = 0;
     SEC[9][2] = 0;
     VOLT[9][2] = 0;
     // set output voltage and beginning time light term 4 as 24 hour format
     HOUR[9][3] = 0;
     MIN[9][3] = 0;
     SEC[9][3] = 0;
     VOLT[9][3] = 0;

     // machine #10
     // set output voltage and beginning time of light term 1 as 24 hour format
     HOUR[10][0] = 0;
     MIN[10][0] = 0;
     SEC[10][0] = 0;
     VOLT[10][0] = 0;
     // set output voltage and beginning time of light term 2 as 24 hour format
     HOUR[10][1] = 0;
     MIN[10][1] = 0;
     SEC[10][1] = 0;
     VOLT[10][1] = 0;
     // set output voltage and beginning time light term 3 as 24 hour format
     HOUR[10][2] = 0;
     MIN[10][2] = 0;
     SEC[10][2] = 0;
     VOLT[10][2] = 0;
     // set output voltage and beginning time light term 4 as 24 hour format
     HOUR[10][3] = 0;
     MIN[10][3] = 0;
     SEC[10][3] = 0;
     VOLT[10][3] = 0;

     // machine #11
     // set output voltage and beginning time of light term 1 as 24 hour format
     HOUR[11][0] = 0;
     MIN[11][0] = 0;
     SEC[11][0] = 0;
     VOLT[11][0] = 0;
     // set output voltage and beginning time of light term 2 as 24 hour format
     HOUR[11][1] = 0;
     MIN[11][1] = 0;
     SEC[11][1] = 0;
     VOLT[11][1] = 0;
     // set output voltage and beginning time light term 3 as 24 hour format
     HOUR[11][2] = 0;
     MIN[11][2] = 0;
     SEC[11][2] = 0;
     VOLT[11][2] = 0;
     // set output voltage and beginning time light term 4 as 24 hour format
     HOUR[11][3] = 0;
     MIN[11][3] = 0;
     SEC[11][3] = 0;
     VOLT[11][3] = 0;

     // machine #12
     // set output voltage and beginning time of light term 1 as 24 hour format
     HOUR[12][0] = 0;
     MIN[12][0] = 0;
     SEC[12][0] = 0;
     VOLT[12][0] = 0;
     // set output voltage and beginning time of light term 2 as 24 hour format
     HOUR[12][1] = 0;
     MIN[12][1] = 0;
     SEC[12][1] = 0;
     VOLT[12][1] = 0;
     // set output voltage and beginning time light term 3 as 24 hour format
     HOUR[12][2] = 0;
     MIN[12][2] = 0;
     SEC[12][2] = 0;
     VOLT[12][2] = 0;
     // set output voltage and beginning time light term 4 as 24 hour format
     HOUR[12][3] = 0;
     MIN[12][3] = 0;
     SEC[12][3] = 0;
     VOLT[12][3] = 0;

     // machine #13
     // set output voltage and beginning time of light term 1 as 24 hour format
     HOUR[13][0] = 0;
     MIN[13][0] = 0;
     SEC[13][0] = 0;
     VOLT[13][0] = 0;
     // set output voltage and beginning time of light term 2 as 24 hour format
     HOUR[13][1] = 0;
     MIN[13][1] = 0;
     SEC[13][1] = 0;
     VOLT[13][1] = 0;
     // set output voltage and beginning time light term 3 as 24 hour format
     HOUR[13][2] = 0;
     MIN[13][2] = 0;
     SEC[13][2] = 0;
     VOLT[13][2] = 0;
     // set output voltage and beginning time light term 4 as 24 hour format
     HOUR[13][3] = 0;
     MIN[13][3] = 0;
     SEC[13][3] = 0;
     VOLT[13][3] = 10;

     // get a timecourse of output voltage
     getTimecourse();
}

void loop() {
     int i;    // count for machine number
     int sspin;
     int mask;  // Mask for high byte
     int output;
     for(i = 0; i <= 13; i++){
          if(i & 0x01){
               mask = 0xb0;    // = 10110000 = OUTB/no BUF/1x/no SHD
          }else{
               mask = 0x30;    // = 00110000 = OUTA/no BUF/1x/no SHD
          }
          sspin = (i >> 1) + 2;    // SSpin0–6 = OUTPUTpin2–8
          output = getOutput(i);
          digitalWrite(LDAC,HIGH); // close latch
          digitalWrite(sspin, LOW);  // LOW signal to an interested SS which operates machine #i
          SPI.transfer(((output >> 8) & 0x0f) | mask) ; // High byte
          SPI.transfer(output & 0xff) ;        // Low byte
          digitalWrite(sspin, HIGH) ;     // signal meaning writing data ended
          digitalWrite(LDAC,LOW) ;        // open latch
     }
}

int getOutput(int _i){
     int j;
     int k = 0;
     long h;
     long m;
     long s;
     long now;
     int _output;
     Rtc.available();
     h = Rtc.hours(RTC8564::Decimal);
     m = Rtc.minutes(RTC8564::Decimal);
     s = Rtc.seconds(RTC8564::Decimal);
     now = 3600 * h + 60 * m + s;
     for(j = 0; j <= 3; j++){
          if(now >= TIME[_i][j]){
               k++;
          }
     }
     if((k > 0) && (k < 4)){
          _output = v[_i][k - 1];
     }else{
          _output = v[_i][3];
     }
     print[_i] = _output;
     if(is != s){
          display(h, m, s, now);
     }
     is = s;
     return _output;
}

void getTimecourse(){
     int i;
     int j;
     for(i = 0; i <= 13; i++){
          for(j = 0; j <= 3; j++){
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
     for(i = 0; i <= 13; i++){
          Serial.print("#");
          Serial.print(i);
          Serial.print(": ");
          Serial.print(print[i]);
          Serial.print(", ");
     }
     Serial.println("");
}
