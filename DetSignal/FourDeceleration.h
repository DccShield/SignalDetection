//--------------------------------------------------------------------------------
// 4現示減速信号機ドライバ
// [FourDeceleration.h]
// Copyright (c) 2020 Ayanosuke(Maison de DCC)
// https://desktopstation.net/bb/index.php
//
// This software is released under the MIT License.
// http://opensource.org/licenses/mit-license.php
//--------------------------------------------------------------------------------

#ifndef FOURD_H_
#define FOURD_H_

#include <arduino.h>

#define STOPSTIM 1000   // 1000*10ms
#define CAUTIONTIM 300  // 300*10ms
#define DECELEATIONTIM 300  // 50*10ms
#define SUPPRESSTIM 50
#define SUPPRESSCNT 10

class FourDeceleration
{
public:
  FourDeceleration( void );
  void statechk( void ); 
  void Detection( void );
  int nowState(void);
  
private:
  int state = 0;
  int cnt = 0;
  int cycle = 0;
  int detf = 0;
    
  unsigned char onoff;
  
  unsigned long PreviosTimer;

  enum{
    ST_INIT = 0,
    ST_IDLE,
    ST_STOP,            // 停止
    ST_STOPWAIT,        // 停止待ち
    ST_CAUTIONWAIT,     // 注意待ち
    ST_DECELEATIONWAIT, 
    ST_SUPPRESSWAIT,
  };
  

  void advance(void);
  void Deceleration(void);
  void stops(void);
  void caution(void);
  void blank(void);
};

#endif
