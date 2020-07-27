#include <IRremote.h>
#include <ir_Lego_PF_BitStreamEncoder.h>

const int receiver = 13;
int maxLeds = 10;
int pins[10] = {11, 10, 9, 8, 7, 6, 5, 4, 3, 2};
bool states[10] = {false, false, false, false, false, false, false, false, false, false};
IRrecv irrecv(receiver);
decode_results results;

void setup()  {
  irrecv.enableIRIn();
  for (int i = 0; i < maxLeds; i++) {
    int pin = pins[i];
    pinMode(pin, OUTPUT);  
  }
}

void loop() {
  int input = translateIR();
  if (irrecv.decode(&results)) {
    if (input != 404) {
      int led = pins[input];
      states[input] = states[input] == true ? false : true;
    }
    irrecv.resume();
  }
  for (int i = 0; i < maxLeds; i++) {
    int pin = pins[i];
    bool state = states[i];
    digitalWrite(pin, state ? HIGH : LOW);
  }
}

int translateIR() {
  switch (results.value) {
    case 0xFF6897:   return 0; break;
    case 0xFF30CF:   return 1; break;
    case 0xFF18E7:   return 2; break;
    case 0xFF7A85:   return 3; break;
    case 0xFF10EF:   return 4; break;
    case 0xFF38C7:   return 5; break;
    case 0xFF5AA5:   return 6; break;
    case 0xFF42BD:   return 7; break;
    case 0xFF4AB5:   return 8; break;
    case 0xFF52AD:   return 9;  break;
    default: return 404;
  }
  delay(1000);
}
