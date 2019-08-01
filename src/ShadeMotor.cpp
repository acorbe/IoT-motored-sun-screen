#include <Arduino.h>
#include <AceButton.h>

const int FULLMOVEMENTTIME = 3000;
#include <ShadeMotor.h> 
using namespace ace_button;

const int relay_ctr_pin = 4;
const int btn_pin = 8;



int buttonState = 0;         // variable for reading the pushbutton status
int oldButtonState = 0;
int motor_running = 0;
int extend_screen = 0;

ShadeMotor mymotor(relay_ctr_pin);

ButtonConfig buttonConfig;
AceButton button(&buttonConfig);
void handleEvent(AceButton*, uint8_t, uint8_t);



void setup() {
  // put your setup code here, to run once:
  pinMode(relay_ctr_pin, OUTPUT); 
  pinMode(btn_pin, INPUT_PULLUP);
  button.init(btn_pin);
  button.setEventHandler(handleEvent);
  motor_running = 0;
  Serial.begin(9600); // send and receive at 9600 baud

  buttonConfig.setFeature(ButtonConfig::kFeatureDoubleClick);
  buttonConfig.setFeature(
      ButtonConfig::kFeatureSuppressClickBeforeDoubleClick);
  buttonConfig.setFeature(ButtonConfig::kFeatureSuppressAfterClick);
  buttonConfig.setFeature(ButtonConfig::kFeatureSuppressAfterDoubleClick);
  buttonConfig.setDebounceDelay(40);
  buttonConfig.setClickDelay(400);
  buttonConfig.setDoubleClickDelay(800);
}

void loop() {
  // put your main code here, to run repeatedly:

  //buttonState = digitalRead(btn_pin);
  button.check();
  mymotor.beat();

//  if (buttonState != oldButtonState){
//
//     oldButtonState = buttonState;
//     motor_running = ! motor_running;
//     delay(1000);
//  }
  // if (motor_running){
  //   digitalWrite(relay_ctr_pin, HIGH);
  // } else {
  //   digitalWrite(relay_ctr_pin, LOW);
  // }

  // if (extend_screen){
  //    digitalWrite(relay_ctr_pin, HIGH);
  //    delay(4000);
  //    digitalWrite(relay_ctr_pin, LOW);
  //    extend_screen = 0;
  // }

}

void handleEvent(AceButton* button , uint8_t eventType,
    uint8_t buttonState ) {
      Serial.print("button event: ");
      Serial.print(eventType);
      Serial.print(" ");
  switch (eventType) {
    case AceButton::kEventClicked:
    case AceButton::kEventReleased:
      //digitalWrite(LED_BUILTIN, LED_ON);
      //motor_running = ! motor_running;
      mymotor.stop();
      break;
    case AceButton::kEventDoubleClicked:
      mymotor.do_full_open();
      break;
    
//    /
  }
  Serial.print(motor_running);
  Serial.print("\n");
  
}
