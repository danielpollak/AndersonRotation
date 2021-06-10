//Pin 18, 19, serial 1
int XMIN = 188;
int XMAX = 252;
int YMIN = 0;
int ZMIN = 70;
//String SPEED = "F350000";

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
}

//int xPos = StrXMIN;
void setup() {
  // initialize both serial ports:
  
  Serial.begin(9600); // 115200);
  Serial2.begin(115200);
  // Go to start position
  delay(1000);
  setPosition(XMIN, YMIN, ZMIN);
//  Serial2.write("G0 X188 Y0 Z70 F350000\n");
}

void loop() {
//    while(true){}

  delay(1500);
//  if (xPos < XMAX){
//    xPos = xPos + 50;
//  } else {
//    xPos = XMIN;
//  }
  setPosition(XMAX, YMIN, ZMIN);
  delay(1500);
  setPosition(int((XMAX+XMIN)/2), YMIN, ZMIN);
  delay(1500);
  setPosition(XMIN, YMIN, ZMIN);
  delay(1500);
  setPosition(int((XMAX+XMIN)/2), YMIN + 20, ZMIN);
  
  

  /*
  digitalWrite(laserPIN, LOW);
  delay(2000);
  //
  int bytesSent = Serial2.write("G0 X252 Y0 Z70 F350000\n");
  Serial2.flush();
  delay(1000);
  bytesSent = Serial2.write("G0 X188 Y0 Z70 F350000\n");
  Serial2.flush();
  delay(1000);
  */

}
