#include <Statistic.h>

#include <RunningMedian.h>

//100hz sample rate or 100 samples a sec.
//take one reading dealy .01ms then take next reading
//More like a 50hz realtime read because of math in between each reading
int const sampleRate = 100;

int const LED = 13;

//RunningMedian:  used to find the running median/Highest reading
RunningMedian data_1 = RunningMedian(100);
RunningMedian data_2 = RunningMedian(20);
RunningMedian data_3 = RunningMedian(20);
//Statistic library used for standard devivation

float tmp; //temp variable to hold each reading
float thresholdLower;  //standard devivation
float thresholdHigher;
int inputPin = A0;  //input pin

int index = 0;  //keep track of cycles through loop



int lastReading =0;
int currentReading = 0;
bool downward;
bool upward; 
int indexLow = 0;
int indexHigh = 0;

int result;
void setup()
{
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  
  //analogReference(INTERNAL);
  
}

void loop()
{
  tmp = analogRead(inputPin);
  //thresholdHigher = analogRead(A2);
  //thresholdLower = data_1.getHighest();
  data_1.add(tmp);
  //data_2.add(tmp);
  index++;
  lastReading = currentReading;
  currentReading = data_1.getAverage();
  
  if(currentReading < lastReading)
    data_2.add(lastReading);
  
  if(currentReading > lastReading)
    data_3.add(lastReading);
    
  if (currentReading > thresholdHigher)
    digitalWrite(LED, HIGH);
  else
    digitalWrite(LED, LOW);
  

  if (index >= 50)
  {
      thresholdHigher = data_2.getHighest();
      thresholdLower = data_3.getLowest();
      result = thresholdHigher - thresholdLower;

      index = 0;
  }
   
  Serial.print(thresholdHigher);
  Serial.print(",");
  Serial.print(thresholdLower);
  Serial.print(",");
  Serial.print(result);
  Serial.print(",");
  Serial.println(currentReading);
  delay(sampleRate);
  
}




