#include <Encoder.h>

// Change these pin numbers to the pins connected to your encoder.
//   Best Performance: both pins have interrupt capability
//   Good Performance: only the first pin has interrupt capability
//   Low Performance:  neither pin has interrupt capability
Encoder knob(2,3);

void setup() {
  Serial.begin(9600);
  Serial.println("TwoKnobs Encoder Test:");
}


void loop() {
  int counter = 0;
  while (counter < 1000){
    long newPos;
    newPos = knob.read();
    Serial.println(newPos);
    counter++;
  }
  knob.write(0);
  
}
