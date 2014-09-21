import processing.video.*;
import processing.serial.*;

Movie mov;

int lf = 10;    // Linefeed in ASCII
String myString = null;
Serial myPort;  // Serial port you are using


int tasaDeLectura=60; //Lee el puerto cada tasaDeLectura veces del draw()
int tasaContador=0;

float velocidadReproduccion=0;      //Velocidad del video

float velocidad=0;      //Velocidad de la bicicleta en Km/h
float velocidadMax=20;  //Mxima velocidad estimada en la bicicleta
float velocidadNormal=15;  //Velocidad en KM/h a la que el video se reproduce a 1x

void setup() {
  //size(1640, 360,P2D);
  size(1280,720);    //HD
  //size(1920,1080);  //Full HD
  background(0);
  //mov = new Movie(this, "tarbena.mp4");
  //mov = new Movie(this, "earth_night_rotate_1080.mov");
  mov = new Movie(this, "xvid_480p_as_l5_1mbps_he-aac_foreign_subs_matrix.mkv");
  mov.loop();
  myPort = new Serial(this, Serial.list()[0], 9600);
  myPort.clear();
}

void movieEvent(Movie movie) {
  mov.read();  
}

void draw() {
  if(tasaContador==tasaDeLectura){
    //Con el puerto
    while (myPort.available() > 0) {
      myString = myPort.readStringUntil(lf);
      if (myString != null) {
        //print(myString);  // Prints String
        velocidad=float(myString);  // Converts and prints float
      }
    }
    myPort.clear();
    if(velocidad<=velocidadNormal){
      velocidadReproduccion = map(velocidad, 0, velocidadNormal, 0, 1);
    }else{
      velocidadReproduccion = map(velocidad, velocidadNormal,velocidadMax,1,4);
    }
    tasaContador=0;
  }
  image(mov, 0, 0);
  velocidadVideo();
  tasaContador++;
  
  fill(255);
  text(nfc(velocidadReproduccion, 2) + "X", 10, 30);
  text(nfc(velocidad, 2) + " Km/h", 10, 50); 
}

//Especifica la velocidad del video de acuerdo a la velocidad de entrada
void velocidadVideo(){
  float incremento=velocidadMax/4;
  if(velocidadReproduccion==0){
    mov.pause();
  }else{/* if(velocidad>incremento&&velocidad<=(incremento*2)){*/
    mov.play();
    mov.speed(velocidadReproduccion);
  }
}
