/*
 */

int sensorPin = A0;    // select the input pin for the potentiometer
int sensorValue = 0;  // variable to store the value coming from the sensor


int rps=0;           //Revoluciones por segundo 

int estado=0;        //1 cuando el iman esta en el sensor, 0 en otro caso
int anterior=0;      //Guarda el estado anterior del sensor para saber si se activa o no
int activado=0;      //Si pasa de 0 a 1

int radio=33;        //Radio de la rueda en centimetros
float velocidad=0;   //Calcula la velocidad en centimetros por segundo
float kmh=0;         //Velocidad en kilmetros por hora

int cant_velocidades=100;
float velocidades[100];
float velocidad_media=0;

void setup() {
  for(int i=0;i<cant_velocidades;i++){
    velocidades[i]=0.0;
  }
}

void loop() {
  //Lee la entrada del sensor anlogo
  sensorValue = analogRead(sensorPin);
  //Mapea el estado del sensor
  estado=map(sensorValue,15,600,0,1);
  //Calcula si cambia a activo o inactivo
  if(anterior==0&&estado==1){
    activado=1;
  }else{
    activado=0;
  }
  anterior=estado;
  //Cuenta las revoluciones por segundo  
  if(activado==1){
    rps++; 
  }
  //Reinicia las rps cada segundo
  if(millis()%1000==0){
    rps=0;
  }
  
  if(millis()%10==0){
    velocidad=rps*2*PI*radio;
    kmh=0.036*velocidad;
    
    for(int i=1;i<cant_velocidades;i++){
      velocidades[i-1]=velocidades[i];
    }
    
    velocidades[cant_velocidades-1]=kmh;
    
    
    float suma_vel=0;
    for(int i=0;i<cant_velocidades;i++){
      suma_vel+=velocidades[i];
    }
    velocidad_media=suma_vel/cant_velocidades;
    Serial.println(velocidad_media);
  }
  
}

