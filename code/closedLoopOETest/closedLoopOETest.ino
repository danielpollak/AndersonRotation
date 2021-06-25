// Sending the rotary encoder data and arm position data
/*
 * Initialize Rotary encoder
 */
#include <Encoder.h>

Encoder knob(2,3);

/*
 * Initialize Robot parameters
*/
//Pin 18, 19, serial 1

//  // Go to start position
//  setPosition(XMIN, YMIN, ZMAX);

int XMIN = 178; // decrease to bring start back
int XMAX = 252;

int YMIN = 0;

int ZMAX = 100; // increase to bring start up
int ZMIN = 70;

int xPos = XMIN;
int oldxPos = xPos;
int zPos = ZMAX;

// Send efferent copy of arm position to the OE board
int armPosEfferentPin = 5;

int inByte = 0,//serial buf
    num = 0;//buf counter
void wait_for_finish_moving()
{
  inByte=0;//clear the buffer
  while(inByte==0){
     if (Serial2.available() > 0) {
        inByte = Serial2.read();
     }
  }
}

void setPosition(int x, int y, int z){
  //"G0 X188 Y0 Z70 F350000\n"
  char str[27];
  
  String commands = "G0 X";
  commands.concat(x);
  commands += " Y";
  commands.concat(y);
  commands += " Z";
  commands.concat(z);
  commands += " F350000\n"; // " F350000\n"
  commands.toCharArray(str, 27);
  Serial2.write(str);
  wait_for_finish_moving();

  // Send efferent copy to the board
  int copyVal = map(x, XMIN, XMAX, 0, 254/2);
  analogWrite(armPosEfferentPin, copyVal);
}

//
void setup() {
  // Initialize both serial ports
  // NOTE: THERE MAY BE A BUG IF YOU USE SERIAL   
  Serial.begin(9600); // 115200);
  Serial2.begin(115200);
  // Go to start position
  setPosition(XMIN, YMIN, ZMAX);

  // Initialize robotic arm position efferent as output
  pinMode(armPosEfferentPin, OUTPUT);
  digitalWrite(armPosEfferentPin, LOW);
}

float alpha = 0.050;
int leak = 5;
long oldRotPos = 0;
long newRotPos;
void loop() {
  oldRotPos = newRotPos;
  newRotPos = knob.read();
  
  oldxPos = xPos;
  xPos += alpha * (newRotPos - oldRotPos) - leak;
  zPos = map(xPos, XMIN, XMAX, ZMAX, ZMIN);
  // Account for going backward
  if (xPos >= XMAX){
    // "Burst" for seven seconds
    setPosition(XMAX, YMIN, ZMIN);
    delay(7000);

    // Then let it repolarize
    xPos = XMIN;
    oldxPos = xPos;
    setPosition(xPos, YMIN, ZMAX);
    
    // reset knob
    knob.write(0);
  } else if (xPos  < XMIN){
    xPos = XMIN;
    oldxPos = xPos;
  }
  
  Serial.println(xPos);
  
  // Set to xPos 
  if (oldxPos != xPos){
    setPosition(xPos, YMIN, zPos);
  }
  
  // Interval between adjustments
  delay(100);
  
}
