#ifndef FOURD_H_
#define FOURD_H_

#include <arduino.h>

#define STOPSTIM 1000   // 1000*10ms
#define CAUTIONTIM 300  // 300*10ms
#define DECELEATIONTIM 50  // 50*10ms
#define DECELEATIONCNT 10

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
    ST_STOP,
    ST_STOPWAIT,
    ST_CAUTIONWAIT,
    ST_DECELEATIONWAIT,
  };
  

  void advance(void);
  void Deceleration(void);
  void stops(void);
  void caution(void);
  void blank(void);
};

#endif
