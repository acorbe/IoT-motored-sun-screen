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
  pinMode(btn_pin, INPUT_PULLUP); //_PULLDOWN
  button.init(btn_pin);
  button.setEventHandler(handleEvent);
  motor_running = 0;
  Serial.begin(9600); // send and receive at 9600 baud

  buttonConfig.setFeature(ButtonConfig::kFeatureDoubleClick);
  buttonConfig.setFeature(
      ButtonConfig::kFeatureSuppressClickBeforeDoubleClick);
  buttonConfig.setFeature(ButtonConfig::kFeatureSuppressAfterClick);
  buttonConfig.setFeature(ButtonConfig::kFeatureSuppressAfterDoubleClick);
  buttonConfig.setDebounceDelay(20);
  buttonConfig.setClickDelay(200);
  buttonConfig.setDoubleClickDelay(400);
  buttonConfig.setFeature(ButtonConfig::kFeatureLongPress);
  buttonConfig.setLongPressDelay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:

  //buttonState = digitalRead(btn_pin);
  button.check();  
  mymotor.beat();
  

}

void handleEvent(AceButton* button , uint8_t eventType,
    uint8_t buttonState ) {
      Serial.print("button event: ");
      Serial.print(eventType);
      Serial.print(" ");
  switch (eventType) {
    case AceButton::kEventDoubleClicked:
      mymotor.do_full_open();
      break;
    case AceButton::kEventClicked:
    case AceButton::kEventReleased:
      //digitalWrite(LED_BUILTIN, LED_ON);
      //motor_running = ! motor_running;
      mymotor.stop();
      break;
    case AceButton::kEventLongPressed:
      mymotor.open();
      break;
  }
  Serial.print(motor_running);
  Serial.print("\n");
  
}
