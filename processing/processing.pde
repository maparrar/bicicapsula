import processing.video.*;
import processing.serial.*;

Movie mov;

int lf = 10;    // Linefeed in ASCII
String myString = null;
Serial myPort;  // Serial port you are using
float num;

void setup() {
  //size(640, 360);
  size(1920,1080);
  background(0);
  mov = new Movie(this, "earth_night_rotate_1080.mov");
  mov.loop();
  
  myPort = new Serial(this, Serial.list()[0], 9600);
  myPort.clear();
}


void movieEvent(Movie movie) {
  mov.read();  
}


void draw() {
  while (myPort.available() > 0) {
    myString = myPort.readStringUntil(lf);
    if (myString != null) {
      //print(myString);  // Prints String
      num=float(myString);  // Converts and prints float
      println(num);
    }
  }
  myPort.clear();
  
  
  image(mov, 0, 0);
    
  float newSpeed = map(num, 0, 60, 0, 3);
  mov.speed(newSpeed);
  
  fill(255);
  text(nfc(newSpeed, 2) + "X", 10, 30); 
} 
