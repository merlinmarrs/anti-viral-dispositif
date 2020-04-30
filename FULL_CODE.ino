/*  
 *   
 *   Based on Mel Lester Jr.'s  SevenSegmentLEDdisplay102a.ino 2017-02-20
 *   Fablab Digiscope Display test
 *   Note: F and G on both Displays are switched and there is no decimal point hooked up
 *   
 *   Code to run PCB for this tutorial:
 *   http://www.needlab.org/face-masks-disinfection-device
 *   
*/


#include <Wire.h>
#include <Adafruit_MLX90614.h>

// MLX90614 Temperature Sensor 
Adafruit_MLX90614 mlx = Adafruit_MLX90614();


// GLOBALS

//Piezo
const int piezo = 10; // 

//Photoresistor
const int pResistor = A3; // Photoresistor at Arduino analog pin A3
const int light_threshold = 500; // TEST THIS!

//Shift Register
const int dataPin1 = 3; // left 7 segment display
const int dataPin2 = 6; // right 7 segment display
const int latchPin = 4; // shared between the two shift registers
const int clockPin = 5; // shared between the two shift registers

//LEDs
const int tempLed = 8; // 
const int timeLed = 7; // 
const int errorLed = 9; // 

//Timing
const unsigned long period = 60000;  //the value is a number of milliseconds in a minute

// MLX90614 Temperature Sensor 
const int temp_threshold_min = 70; // 
const int temp_threshold_max = 75; // 

//VARIABLES

//Timing
unsigned long startMillis;  
unsigned long currentMillis;


//Photoresistor
int light;          // Store value from photoresistor (0-1023)

// MLX90614 Temperature Sensor 
int temp;          // Store value from temp sensor



//FUNCTIONS

void myfnUpdateDisplay1(byte eightBits) {

  digitalWrite(latchPin, LOW);  // prepare shift register for data
  shiftOut(dataPin1, clockPin, LSBFIRST, eightBits); // send data
  digitalWrite(latchPin, HIGH); // update display
}

void myfnUpdateDisplay2(byte eightBits) {

  digitalWrite(latchPin, LOW);  // prepare shift register for data
  shiftOut(dataPin2, clockPin, LSBFIRST, eightBits); // send data
  digitalWrite(latchPin, HIGH); // update display
}


byte myfnNumToBits(int someNumber) {
  switch (someNumber) {
    case 0:
      return B11111010;
      break;
    case 1:
      return B01100000;
      break;
    case 2:
      return B11011100;
      break;
    case 3:
      return B11110100;
      break;
    case 4:
      return B01100110;
      break;
    case 5:
      return B10110110;
      break;
    case 6: 
      return B10111110;
      break;
    case 7:
      return B11100000;
      break;
    case 8:
      return B11111110;
      break;
    case 9:
      return B11110110;
      break;
    case 10:
      return B11101110; // Hexidecimal A
      break;
    case 11:
      return B00111110; // Hexidecimal B
      break;
    case 12:
      return B10011010; // Hexidecimal C or use for Centigrade
      break;
    case 13:
      return B01111100; // Hexidecimal D
      break;
    case 14: 
      return B10011110; // Hexidecimal E
      break;
    case 15:
      return B10001110; // Hexidecimal F or use for Fahrenheit
      break;  
    default:
      return B10010100; // Error condition, displays three vertical bars
      break;   
  }
}

void Display(int value) {

//    int trunc_value = (int) value; //truncate to just whole numbers
    
    int j = value / 10; //look at the second number before the decimal point  

    byte bits1 = myfnNumToBits(j);
    myfnUpdateDisplay1(bits1);    // display 2nd alphanumeric digit on left display

    int i = value % 10; //look at the first number before the decimal point

    byte bits2 = myfnNumToBits(i); //
    myfnUpdateDisplay2(bits2);    // display 1st alphanumeric digit on right display
    
    delay(10);                 // pause 
}


void Fin(void){

  for (int i; i++; i<10) // blink temp LED while beeping 10 times
  {
  tone(piezo, 500); // format: pin, hertz, millis
  digitalWrite(errorLed, LOW); // Error LED on
  digitalWrite(tempLed, LOW); // 
  digitalWrite(timeLed, HIGH); // 
  delay(500);
  noTone(piezo);
  digitalWrite(timeLed, LOW); // 
  delay(500);
  }
}

void TempWait(void){

  temp = mlx.readAmbientTempC(); // read temp sensor ambiant. Also possible to read object temp with mlx.readObjectTempC()
    
  while(temp < temp_threshold_min) // while we're below the temp threshold, display the temp
  {
    digitalWrite(tempLed, HIGH); // Temp LED on
    digitalWrite(errorLed, LOW); // 
    digitalWrite(timeLed, LOW); // 
    
    Display(temp);
  }
}


void Count(void)
{
   tone(piezo, 500, 1000); // format: pin, hertz, millis. Buzz one sec to signal start of timing
   
   int Minutes; // Minutes to display
   startMillis = millis();  //initial start time

   temp = mlx.readAmbientTempC(); // read temp sensor ambiant. Also possible to read object temp with mlx.readObjectTempC()
   light = analogRead(pResistor); // read photo resistor
   
   if(temp > temp_threshold_min && temp < temp_threshold_max && light > light_threshold && Minutes < 30) // while in the correct range and light is on
   {
    //display time LED
    digitalWrite(timeLed, HIGH); // Time LED on
    digitalWrite(errorLed, LOW); // 
    digitalWrite(tempLed, LOW); // 

      currentMillis = millis();  //get the current "time" (actually the number of milliseconds since the program started)
      if (currentMillis - startMillis >= period)  //test whether the period has elapsed
      {
        //increment minute counter and display
        Minutes++;
        Display(Minutes);
        startMillis = currentMillis;  //IMPORTANT to save the start time
      }
        
   }

    else if(temp > temp_threshold_min && temp < temp_threshold_max && light > light_threshold && Minutes >= 30) // 30 minutes have elapsed
    {
      Fin();
    }
     
   else
   {
    Error();
   }
}


void Error(void){
  
    for (int i; i++; i<10) // blink temp LED while beeping 10 times
    {
    tone(piezo, 1000, 1000); // format: pin, hertz, millis
    
    digitalWrite(errorLed, HIGH); // Error LED on
    digitalWrite(tempLed, LOW); // 
    digitalWrite(timeLed, LOW); // 
    
    myfnUpdateDisplay2(B10010100);  //three bars = error
    myfnUpdateDisplay1(B10010100);  //three bars = error
    }
}




void setup() {
  // INITS

  //Piezo
  pinMode(piezo, OUTPUT);

  //LEDs
  pinMode(timeLed, OUTPUT);
  pinMode(tempLed, OUTPUT);
  pinMode(errorLed, OUTPUT);
  
  // Shift Register
  pinMode(dataPin1, OUTPUT);
  pinMode(dataPin2, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);

  // Photocell 
  pinMode(pResistor, INPUT);// Set pResistor - A3 pin as an input

  // MLX90614 Temperature Sensor - communicates via I2C
  mlx.begin();  
}

void loop() {

  TempWait(); // wait for temp to hit 70 C
  Count(); // begin 30 minute timer
  Fin(); // 30 minutes has elapsed, sound buzzer
  
}




