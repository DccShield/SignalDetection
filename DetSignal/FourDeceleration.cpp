//--------------------------------------------------------------------------------
// 4現示減速信号機ドライバ
// [FourDeceleration.cpp]
// Copyright (c) 2020 Ayanosuke(Maison de DCC)
// https://desktopstation.net/bb/index.php
//
// This software is released under the MIT License.
// http://opensource.org/licenses/mit-license.php
//--------------------------------------------------------------------------------

#include <arduino.h>
#include "FourDeceleration.h"

FourDeceleration::FourDeceleration(void)
{
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
}

void FourDeceleration::Detection(void)
{
  detf = HIGH;
}

int FourDeceleration::nowState()
{
  return state; 
}

void FourDeceleration::statechk( void ) 
{
static int prestate = 0;
if(prestate != state ){
  Serial.println(state);
  prestate = state;
}
  switch(state){
      case ST_INIT:
              advance();
              state = ST_IDLE;
              break;

      case ST_IDLE:     //1
              if(detf == HIGH){
                detf = LOW;
                state = ST_STOP;
              }
              break;

      case ST_STOP:     //2
              stops();
              cnt = 0;
              state = ST_STOPWAIT;
              break;
      
      case ST_STOPWAIT: //3
              cnt++;
              if( cnt > STOPSTIM ) {
                cnt = 0;
                caution();
                state = ST_CAUTIONWAIT;
              }
              break;
      
      case ST_CAUTIONWAIT://4
              cnt++;
              if( cnt > CAUTIONTIM) {
                cnt = 0;
                cycle = 0;
                Deceleration();
                state = ST_DECELEATIONWAIT;
              }
              break;

      case ST_DECELEATIONWAIT:  //5
              cnt++;
              if( cnt > DECELEATIONTIM) {
                cnt = 0;
                cycle = 0;
                Deceleration();
                state = ST_SUPPRESSWAIT;
              }
              break;

      case ST_SUPPRESSWAIT:  //5
              cnt++;
              if( cnt > SUPPRESSTIM) {
                cnt = 0;
                if(onoff == 0) {
                  blank();
                  onoff = 1;
                } else {
                  Deceleration();
                  onoff = 0;
                  cycle++;
                }
                if( cycle >= SUPPRESSCNT ){
                  advance();
                  state = ST_IDLE;
                }
              }
              break;
      default:
              break;
    }
}



void FourDeceleration::advance(void) // 進行
{
   digitalWrite(9, LOW);
   digitalWrite(10, LOW);
   digitalWrite(11, HIGH);
   digitalWrite(12, LOW);
}


void FourDeceleration::Deceleration(void) // 減速
{
   digitalWrite(9, HIGH);
   digitalWrite(10, LOW);
   digitalWrite(11, HIGH);
   digitalWrite(12, LOW);
}


void FourDeceleration::caution(void) // 注意
{
   digitalWrite(9, HIGH);
   digitalWrite(10, LOW);
   digitalWrite(11, HIGH);
   digitalWrite(12, HIGH);
}


void FourDeceleration::stops(void) // 停止
{
   digitalWrite(9, LOW);
   digitalWrite(10, HIGH);
   digitalWrite(11, HIGH);
   digitalWrite(12, HIGH);
}

void FourDeceleration::blank(void) // 消灯
{
   digitalWrite(9, LOW);
   digitalWrite(10, LOW);
   digitalWrite(11, LOW);
   digitalWrite(12, LOW);
}
