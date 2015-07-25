
#include <RunningMedian.h>
int timer1_counter;  

//RunningMedian:  used to find the running median/Highest reading
//Sample rate is 50hz so the running Median is 3 samples or
//Running Median over three secs
RunningMedian data_1 = RunningMedian(150);

//Setup to receive data from GSR sensor circuit
int inputPin = A0;  //input pin

//used to control the LED bar graph (10 LEDs)
float display = 0;
int result = 0;

void setup()
{
  Serial.begin(9600);  //setup serial port for graphic display
  //configure pins 2-11 for LED bar graph
  pinMode(11,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(2,OUTPUT);
  
 //initialize timer1
 noInterrupts();  //disable all interrupts
 TCCR1A = 0;
 TCCR1B = 0;
 
 //Set timer1_counter to the correct value interrupt interval
 timer1_counter = 64286;  // preload timer 65536-16MHz/256/50Hz
 
 TCNT1 = timer1_counter;  //preload timer
 TCCR1B |= (1 << CS12);  //256 prescaler
 TIMSK1 |= (1 << TOIE1); //enable timer overflow interrupt
 interrupts();           //enable all interrupts
 
}

ISR(TIMER1_OVF_vect)
{
  TCNT1 = timer1_counter;  //load timer 
  //Using RunningMedian.h to store 150 values or 3 seconds of data
  data_1.add(analogRead(inputPin));  //add samples at 50hz
}

float skinConductance(void)
{
  //!******************************************************************************
  //!		Name:	getSkinConductance()											
  //!		Description: Returns the value of skin conductance.						
  //!		Param : void															
  //!		Returns: float with the value of skin conductance						
  //!						
  //!******************************************************************************
  //Local variable declaration
  float resistance;
  float conductance;
  delay(1);
  //Read Running average from runningMedian.h sample group
  float sensorValue = data_1.getAverage();
  float voltage = sensorValue * 5 / 1023;
  
  conductance = 2 * ((voltage - .05) / 1000000);
  
  //Conductance calculation
  resistance = 1 / conductance;
  conductance = conductance * 1000000;
  delay(1);
  
  if(conductance > 1.0) return conductance;
  else return -1.0;
}

void loop()
{
  //setup to update LED bar graph
  display = skinConductance();  //get average conductance
  display = round(display);  //round to whole number
  result = (int) display;  //convert to int
  
  switch (result)
  {
    case 1:  //Turn 1 LED on
      digitalWrite(11,HIGH);
      digitalWrite(10,LOW);
      digitalWrite(9,LOW);
      digitalWrite(8,LOW);
      digitalWrite(7,LOW);
      digitalWrite(6,LOW);
      digitalWrite(5,LOW);
      digitalWrite(4,LOW);
      digitalWrite(3,LOW);
      digitalWrite(2,LOW);
      break;
    case 2:   //Turn 2 LEDs on 
      digitalWrite(11,HIGH);
      digitalWrite(10,HIGH);
      digitalWrite(9,LOW);
      digitalWrite(8,LOW);
      digitalWrite(7,LOW);
      digitalWrite(6,LOW);
      digitalWrite(5,LOW);
      digitalWrite(4,LOW);
      digitalWrite(3,LOW);
      digitalWrite(2,LOW);
      break;
    case 3:  //Turn 3 LEDs on
      digitalWrite(11,HIGH);
      digitalWrite(10,HIGH);
      digitalWrite(9,HIGH);
      digitalWrite(8,LOW);
      digitalWrite(7,LOW);
      digitalWrite(6,LOW);
      digitalWrite(5,LOW);
      digitalWrite(4,LOW);
      digitalWrite(3,LOW);
      digitalWrite(2,LOW);
      break;
    case 4:  //Turn 4 LEDs on
      digitalWrite(11,HIGH);
      digitalWrite(10,HIGH);
      digitalWrite(9,HIGH);
      digitalWrite(8,HIGH);
      digitalWrite(7,LOW);
      digitalWrite(6,LOW);
      digitalWrite(5,LOW);
      digitalWrite(4,LOW);
      digitalWrite(3,LOW);
      digitalWrite(2,LOW);
      break;
   case 5:  //Turn 5 LEDs on
      digitalWrite(11,HIGH);
      digitalWrite(10,HIGH);
      digitalWrite(9,HIGH);
      digitalWrite(8,HIGH);
      digitalWrite(7,HIGH);
      digitalWrite(6,LOW);
      digitalWrite(5,LOW);
      digitalWrite(4,LOW);
      digitalWrite(3,LOW);
      digitalWrite(2,LOW);
      break;
   case 6:  //Turn 6 LEDs on
      digitalWrite(11,HIGH);
      digitalWrite(10,HIGH);
      digitalWrite(9,HIGH);
      digitalWrite(8,HIGH);
      digitalWrite(7,HIGH);
      digitalWrite(6,HIGH);
      digitalWrite(5,LOW);
      digitalWrite(4,LOW);
      digitalWrite(3,LOW);
      digitalWrite(2,LOW);
      break;
   case 7:  //Turn 7 LEDs on
      digitalWrite(11,HIGH);
      digitalWrite(10,HIGH);
      digitalWrite(9,HIGH);
      digitalWrite(8,HIGH);
      digitalWrite(7,HIGH);
      digitalWrite(6,HIGH);
      digitalWrite(5,HIGH);
      digitalWrite(4,LOW);
      digitalWrite(3,LOW);
      digitalWrite(2,LOW);
      break;
  case 8:  //Turn 8 LEDs on
     digitalWrite(11,HIGH);
      digitalWrite(10,HIGH);
      digitalWrite(9,HIGH);
      digitalWrite(8,HIGH);
      digitalWrite(7,HIGH);
      digitalWrite(6,HIGH);
      digitalWrite(5,HIGH);
      digitalWrite(4,HIGH);
      digitalWrite(3,LOW);
      digitalWrite(2,LOW);
      break;
  case 9:  //Turn 9 LEDs on
     digitalWrite(11,HIGH);
      digitalWrite(10,HIGH);
      digitalWrite(9,HIGH);
      digitalWrite(8,HIGH);
      digitalWrite(7,HIGH);
      digitalWrite(6,HIGH);
      digitalWrite(5,HIGH);
      digitalWrite(4,HIGH);
      digitalWrite(3,HIGH);
      digitalWrite(2,LOW);
      break;
  case 10:  //Turn 10 LEDs on
    digitalWrite(11,HIGH);
      digitalWrite(10,HIGH);
      digitalWrite(9,HIGH);
      digitalWrite(8,HIGH);
      digitalWrite(7,HIGH);
      digitalWrite(6,HIGH);
      digitalWrite(5,HIGH);
      digitalWrite(4,HIGH);
      digitalWrite(3,HIGH);
      digitalWrite(2,HIGH);
      break;
  }
  delay(10);
//used to display graph when hooked up to serial port      
  Serial.println(skinConductance());
 
}






