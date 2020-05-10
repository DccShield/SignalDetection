//--------------------------------------------------------------------------------
// 4現示抑速信号機ドライバ
// [FourVigillance.h]
// Copyright (c) 2020 Ayanosuke(Maison de DCC)
// https://desktopstation.net/bb/index.php
//
// This software is released under the MIT License.
// http://opensource.org/licenses/mit-license.php
//--------------------------------------------------------------------------------

#ifndef FOURV_H_
#define FOURV_H_

#define STOPSTIM 1000   // 1000*10ms
#define CAUTIONTIM 300  // 300*10ms
#define DECELEATIONTIM 50  // 50*10ms
#define DECELEATIONCNT 10
#define VIGILANCETIM 300


class FourVigillance
{
public:
  FourVigillance( void );
  void statechk( void ); 
  void Detection( void );
  int nowState(void);
  
private:
  int state = 0;
  int cnt = 0;
    int detf = 0;
  unsigned long PreviosTimer;

  enum{
    ST_INIT = 0,
    ST_IDLE,
    ST_STOP,
    ST_STOPWAIT,
    ST_VIGILANCEWAIT,
    ST_CAUTIONWAIT,
    ST_DECELEATIONWAIT,
  };

  void advance(void);
  void stops(void);
  void vigilance(void);
  void caution(void);
  void blank(void);
};

#endif
