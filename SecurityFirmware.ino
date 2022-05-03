
#include <Servo.h>

//defining motors
Servo sensormotor;
Servo doormotor;

//defining modes
int stayawaymode = 0;

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

//defining door scan direction
bool anglegoingup = true;

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
  
//STAY AND AWAY SETTINGS

if (stayawaymode == 0){	// Disarmed Mode
  digitalWrite(7, HIGH); //Green LED is on
  digitalWrite(2, LOW);		//Red LED off
   doormotor.write(90);		//Door open

	if(digitalRead(4)==LOW){   //Away Button Settings
	stayawaymode = 1;
	}
	if(digitalRead(3)==LOW){  //Stay Button Settings
	stayawaymode = 2;
	}
}


if (stayawaymode == 1){	// Away Mode 
    digitalWrite(7, LOW); //Green LED is off
	digitalWrite(2, HIGH);	//Red LED on
	  doormotor.write(0);	//Door Closed
	
	if(digitalRead(4)==LOW && digitalRead(3) == LOW){   //Disarm code
		stayawaymode = 0;
	}
	
	if(anglegoingup == true){
		angle1 += 30;
	}
	else{
		angle1 -= 30;
	}
	
	if(angle1 >=180){  //SensorMotor fluctuates
		angle1=180;
		anglegoingup = false;
	}
	
	if( angle1 <= 0){
		angle1 = 0;
		anglegoingup = true;
	}
	
	sensormotor.write(angle1);			      //between 0 and 180

  
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
   
   //PHOTOCELL AND ALARM
  
  photoresistor= analogRead(A0);

    if (photoresistor <= 100){     		//Door sensor
      
    Serial.println("Door is open");		//Resistor uncovered "Open"
      delay(1000);
      
    tone(10,120,3000);					//Alarm sounded
      delay(2000);
      
      
  }else{
    Serial.println("Door is closed");		//Resistor Covered "Closed"
    delay(1000);
  }
}


if (stayawaymode == 2){ // Stay Mode
  digitalWrite(7, LOW); //Green LED is off
  digitalWrite(2, HIGH);	//Red LED on
	doormotor.write(0);		//Door Closed
	
	if(digitalRead(4)==LOW && digitalRead(3) == LOW){   //Disarm code
	stayawaymode = 0;
	}
	//PHOTOCELL AND ALARM
  
  photoresistor= analogRead(A0);

    if (photoresistor <= 100){     		//Door sensor
      
    Serial.println("Door is open");		//Resistor uncovered "Open"
      delay(1000);
      
    tone(10,120,3000);					//Alarm sounded
      delay(2000);
      
      
  }else{
    Serial.println("Door is closed");		//Resistor Covered "Closed"
    delay(1000);
  }
}
}