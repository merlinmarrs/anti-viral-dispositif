/*  
 *   
 *   Based on Mel Lester Jr.'s  SevenSegmentLEDdisplay102a.ino 2017-02-20
 *   Fablab Digiscope Display test
 *   Note: F and G on both Displays are switched and there is no decimal point hooked up
 *   
 *   Reads ambiant value of IR temperature sensor and displays the 1st and 2nd digits of the value on a pair of 7 segment displays.
 *   
*/


#include <Wire.h>
#include <Adafruit_MLX90614.h>

// MLX90614 Temperature Sensor 
Adafruit_MLX90614 mlx = Adafruit_MLX90614();


// GLOBALS

//Photoresistor
const int pResistor = A3; // Photoresistor at Arduino analog pin A3

//Shift Register
const int dataPin1 = 3; // left 7 segment display
const int dataPin2 = 6; // right 7 segment display
const int latchPin = 4; // shared between the two shift registers
const int clockPin = 5; // shared between the two shift registers

//LEDs
const int tempLed = 8; // 
const int timeLed = 7; // 
const int errorLed = 9; // 

//VARIABLES

//Photoresistor
//int light;          // Store value from photoresistor (0-1023)

// MLX90614 Temperature Sensor 
int temp;          // Store value from temp sensor (0-1023)

void setup() {
  // INITS

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

  // MLX90614 Temperature Sensor 
  mlx.begin();  
}

void loop() {

 // light = analogRead(pResistor); // read photocell

  digitalWrite(timeLed, LOW);
  digitalWrite(errorLed, LOW);
  digitalWrite(tempLed, HIGH);
    

    temp = (int) mlx.readAmbientTempC(); // read temp sensor ambiant and truncate what comes after decimal point. Also possible to read object temp with mlx.readObjectTempC()

    int j = temp / 10; //look at the second number before the decimal point  

    byte bits1 = myfnNumToBits(j);
    myfnUpdateDisplay1(bits1);    // display 2nd alphanumeric digit

    int i = temp % 10; //look at the first number before the decimal point

    byte bits2 = myfnNumToBits(i); //
    myfnUpdateDisplay2(bits2);    // display 1st alphanumeric digit
    
    delay(500);                 // pause for 1/2 second
}

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
