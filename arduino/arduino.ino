float start, finished;    //Variables para medir el tiempo entre cada paso del sensor
float elapsed, time;      //Tiempo entre cada paso por el sensor
float elapseds[3];        //Acumula los ultimos tiempos para determinar si la velocidad es cero
int cant_elapseds=3;      //Cantidad de tiempos acumulados
int sensores=3;           //Cantidad de sensores en la rueda
float radio=0.33;         //Distancia del centro de la rueda al sensor (en metros)
float perimetro;          //Permetro de la rueda donde esta el sensor
float velocidad;          //Velocidad en KM/h
float velocidadMax=30;    //Mxima velocidad estimada
 
void setup(){
  pinMode(2, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  float radio=0.33;
  perimetro=(2.0/sensores)*PI*radio;
  //Se ejecuta la interrupcin cada que pasa por el sensor
  // - en Leonardo es el pin 3 => se escribe 0
  // - En Mega es el pin 2 => se escribe 
  // Consultar: http://arduino.cc/en/pmwiki.php?n=Reference/AttachInterrupt
  attachInterrupt(1, calcularVelocidad, RISING); 
  start=millis();
  Serial.begin(9600);
  delay(3000);
}
 
void calcularVelocidad(){
  if(millis()!=start){
    elapsed=millis()-start;
    start=millis();
    velocidad=(3600*perimetro)/elapsed;  //Km/h
    
  }
}

void loop(){
  //Acumula las velocidades para determinar si la rueda est detenida
  for(int i=1;i<cant_elapseds;i++){
    elapseds[i-1]=elapseds[i];
  }
  elapseds[cant_elapseds-1]=elapsed;
  boolean iguales=true;
  for(int i=0;i<cant_elapseds-1;i++){
    if(elapseds[i]!=elapseds[i+1]){
      iguales=false;
    }
  }
  if(iguales&&(millis()-start)>500){
    velocidad=0.0;
  }
  if(velocidad<40){
    Serial.println(velocidad); //Imprime en el puerto serial
    prenderVentilador();
  }
  delay(1000); //Minimiza el parpadeo
}

//Prende leds de acuerdo a la velocidad
void prenderVentilador(){
  float incremento=velocidadMax/4;
  if(velocidad>0.1&&velocidad<=incremento){
    digitalWrite(2, HIGH);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
  }else if(velocidad>incremento&&velocidad<=(incremento*2)){
    digitalWrite(2, LOW);
    digitalWrite(4, HIGH);
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
  }else if(velocidad>(incremento*2)&&velocidad<=(incremento*3)){
    digitalWrite(2, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, HIGH);
    digitalWrite(6, LOW);
  }else if(velocidad>(incremento*3)){
    digitalWrite(2, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    digitalWrite(6, HIGH);
  }else{
    digitalWrite(2, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    digitalWrite(6, LOW); 
  }
}

