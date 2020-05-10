//--------------------------------------------------------------------------------
// フォトインタラプタドライバ
// [PhotoInterrupters.h]
// Copyright (c) 2020 Ayanosuke(Maison de DCC)
// https://desktopstation.net/bb/index.php
//
// This software is released under the MIT License.
// http://opensource.org/licenses/mit-license.php
//--------------------------------------------------------------------------------
#ifndef PHOTO_H_
#define PHOTO_H_

#include <stdio.h>

// 状態基底クラス
class PhotoInterrupters
{
public:
  PhotoInterrupters(char ch , char chIR , char chAI , int LTh, int HTh);
  char statechk( char range );
  void Reset( void );

private:
  int LThreshold;
  int HThreshold;
  int adf;        // A/D first
  int ads;        // A/D second
  int dif;        // A/D dif
  int cnt;
  int cntup;
  char IRport;
  char AIport;
  char state;
  char detres;
  
  static unsigned long PreviosTimer;
  enum{
      ST_INIT = 0,
      ST_IRON,
      ST_WAIT,
      ST_MEAS1,
      ST_MEAS2,
      ST_DETECTION,
      ST_DETWAIT,
      ST_DETRES
  };
};

#endif
