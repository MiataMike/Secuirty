
#include <Servo.h>

//defining motors
Servo sensormotor;
Servo doormotor;


//definingbuttons
bool buttonstay = false;
bool buttonaway = false;

//defining photoresistor
int photoresistor = 0;

//defining sensor
//#include <Ultrasonic.h>
int trigPin=8;
int echoPin=9;
long duration;
long distance;

//defining door angle
long angle1=0;


void setup() {

Serial.begin(9600);


sensormotor.attach(5);
doormotor.attach(6);

pinMode(3, INPUT_PULLUP);
pinMode(4, INPUT_PULLUP);
pinMode(7, OUTPUT);
pinMode(2, OUTPUT);
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);
pinMode(10, OUTPUT);


  
}

void loop() {

//PHOTOCELL AND ALARM
  
  photoresistor= analogRead(A0);

    if (photoresistor >= 100){     		//Door sensor
      
    Serial.println("Door is open");		//Resistor uncovered "Open"
      delay(1000);
      
    tone(10,120,3000);					//Alarm sounded
      delay(2000);
      
      
  }else{
    Serial.println("Door is closed");		//Resistor Covered "Closed"
    delay(1000);
  }
  
  
  
//STAY AND AWAY SETTINGS

if (stayawaymode == 0){	// Disarmed Mode
}
if (stayawaymode == 1){	// Away Mode 
}
if (stayawaymode == 2){ // Stay Mode
}
if(digitalRead(4)==LOW){   //Away Button Settings
  buttonaway=!buttonaway;
  delay(2);
 }

if(digitalRead(3)==LOW){  //Stay Button Settings
  buttonstay=!buttonstay;
  delay(2); 
}

 if (buttonstay==true){ //Stay Mode Activated
   
  digitalWrite(7, HIGH); //Green LED is on
  
  doormotor.write(0); //Door shuts
   
   for(angle1 = 1; angle1 <=180; angle1 +=1){  //SensorMotor fluctuates
    sensormotor.write(angle1);			      //between 0 and 180
 
  delay(30);   
   }

    for(angle1 = 180; angle1 >=1; angle1 -=1){
    sensormotor.write(angle1);
  
  delay(30);  
      
   }
  
  digitalWrite(trigPin, LOW);  //Sensor readings
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);   
   
  duration = pulseIn(echoPin, HIGH); //Sensor (cm) conversion
  distance = duration*0.034/2;
   
   
  Serial.print("Location of Intruder (cm): ");  //Print reading
  Serial.println(distance);
   
  }else{					//Green LED off
  digitalWrite(7, LOW);
  sensormotor.write(0); 	//Sensor motor off
  }
  

 if (buttonaway==true){		//Away Mode activated
  digitalWrite(2, HIGH);	//Red LED on
	doormotor.write(0);		//Door Closed
  }else{
  digitalWrite(2, LOW);		//Red LED off
   doormotor.write(90);		//Door open
  }
}