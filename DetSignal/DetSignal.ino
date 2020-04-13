#include "PhotoInterrupters.h"
#include "FourDeceleration.h"
//#include "FourVigillance.h"


unsigned long PreviosTimer = 0;
unsigned char a,b;

PhotoInterrupters PhotoInt(0,8,7,200,200);
FourDeceleration Signal;
//FourVigillance Signal;

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
#if 0
//      PhotoInt.Reset();
    }
    if(Signal.nowState() == 1){
        PhotoInt.Reset();
      }
#endif
  }
}
