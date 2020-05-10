//--------------------------------------------------------------------------------
// 在線検出機と信号機のスケッチ
// [DetSignalino]
// Copyright (c) 2020 Ayanosuke(Maison de DCC)
//
// http://maison-dcc.sblo.jp/ http://dcc.client.jp/ http://ayabu.blog.shinobi.jp/
// https://twitter.com/masashi_214
//
// DCC電子工作連合のメンバーです
// https://desktopstation.net/tmi/ https://desktopstation.net/bb/index.php
//
// This software is released under the MIT License.
// http://opensource.org/licenses/mit-license.php
//--------------------------------------------------------------------------------


#include "PhotoInterrupters.h"
//#include "FourDeceleration.h"
#include "FourVigillance.h"
//
// 1-D12
// 2-D11
// 3-D10
// 4-D9
// 5-GND
// 6-A7
// 7-5V
// 8-D8


unsigned long PreviosTimer = 0;
unsigned char a,b;

PhotoInterrupters PhotoInt(0,8,7,200,200);
//FourDeceleration Signal;
FourVigillance Signal;

void setup() {
  Serial.begin(115200);
  PreviosTimer = millis();
}

void loop()
{
  int ret;
  
  if( (millis() - PreviosTimer ) >= 10 ){  // 1000:1000msec 前回から1000ms経過したかチェック
    PreviosTimer = millis();
    ret = PhotoInt.statechk(LOW);
    Signal.statechk();

    if(ret == HIGH ){
      Signal.Detection();
      PhotoInt.Reset();
    }
  }
}
