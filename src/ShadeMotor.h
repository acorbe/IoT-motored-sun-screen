enum CurrentAction{
		   ACTION_STEADY,
		   ACTION_ROLL,
		   ACTION_UNROLL,		     
};

class ShadeMotor {

private:
  char current_action;
  unsigned long  until_time;
  char myMotorRelayPin;
  int fullmovementtime;
  unsigned long getClock(){ return millis(); }
  
public:
  ShadeMotor(char myMotorRelayPin
	     , int fullmovementtime = FULLMOVEMENTTIME):
    myMotorRelayPin(myMotorRelayPin)
    , fullmovementtime(fullmovementtime)
  {
    this->current_action = ACTION_STEADY;
    this->until_time = -1;
    
  }
  
  int beat(){
    unsigned long cur_clock = getClock();
    if (until_time > 0){
      if (cur_clock > until_time){
	stop(); 
      } else {
	
      }      
    }    
  }
  
  int do_full_open(){
    until_time = getClock() + fullmovementtime;
    open();
    return until_time;
  }

  int open(){
    current_action = ACTION_UNROLL;
    digitalWrite( myMotorRelayPin, HIGH);
  }
  
  int stop(){
    this->current_action = ACTION_STEADY;
    this->until_time = -1;
    digitalWrite( myMotorRelayPin, LOW);
  }
  
};
