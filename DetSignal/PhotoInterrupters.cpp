#include "PhotoInterrupters.h"
#include  <arduino.h>

PhotoInterrupters::PhotoInterrupters(char ch , char chIR , char chAI, int LTh, int HTh){
  AIport = chAI;
  IRport = chIR;
//  cntup = ct;
  LThreshold = LTh;
  HThreshold = HTh;
  
  pinMode(chIR,OUTPUT);
  digitalWrite(chIR,LOW);

}

void PhotoInterrupters::Reset( void ){
  detres = HIGH;
}

char PhotoInterrupters::statechk( char range ){
  static int nextTimer = 0;
  char temp[30];
//  sprintf(temp,"state:%d:",state);
//  Serial.println(temp);
    
  switch(state){
    case ST_INIT:
              state = ST_IRON;
              break;
    case ST_IRON:
              digitalWrite(IRport, HIGH);   // 赤外LEDをon
              nextTimer = 1;
              state = ST_WAIT;
              break;
    case ST_WAIT:
              nextTimer --;
              if(nextTimer <=0 ){
                state = ST_MEAS1;
              }
              break;          
    case ST_MEAS1:
              adf = analogRead( AIport );              
              digitalWrite(IRport, LOW);   // 赤外LEDをoff
              state = ST_MEAS2;
              break;
    case ST_MEAS2:
              ads = analogRead( AIport );       
//sprintf(temp,"adf:%d , ads:%d , dif:%d",adf,ads,adf-ads);
//Serial.println(temp);
              if( adf - ads >= 200 ) {
Serial.println("DETECTION");
                state = ST_DETECTION;            //車両検知
              } else {
                state = ST_IRON;            //ノイズかな
              }
            break;
    case ST_DETECTION:
              nextTimer = 500;
              state = ST_DETWAIT;
              return HIGH;
              break;
    case ST_DETWAIT:
              nextTimer --;
              if(nextTimer <=0 ){
                state = ST_DETRES;
              }
              break;   
    case ST_DETRES:
              if(detres == HIGH){
                detres = LOW;
                state = ST_INIT;
              }
              break;
    default:
              break;
  }
  return LOW;
}
