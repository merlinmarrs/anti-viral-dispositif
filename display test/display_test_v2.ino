/*  
 *   
 *   Based on Mel Lester Jr.'s  SevenSegmentLEDdisplay102a.ino 2017-02-20
 *   Fablab Digiscope Display test
 *   Note: F and G on both Displays are switched and there is no decimal point hooked up
 *   
*/

// Globals
const int dataPin1 = 6; // 
const int dataPin2 = 3; // 
const int latchPin = 4; // 
const int clockPin = 5; // 

void setup() {
  // initialize I/O pins
  pinMode(dataPin1, OUTPUT);
  pinMode(dataPin2, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
}

void loop() {



    // generate characters to display 2 for hexidecimal numbers 0 to F
  for (int i = 0; i <= 9; i++) {
    byte bits = myfnNumToBits1(i) ;
    myfnUpdateDisplay2(bits);    // display alphanumeric digit
    delay(500);                 // pause for 1/2 second
  }

  myfnUpdateDisplay2(0);    // display alphanumeric digit
  
  // generate characters to display 1 for hexidecimal numbers 0 to F
  for (int i = 0; i <= 9; i++) {
    byte bits = myfnNumToBits2(i) ; // THESE ARE REVERSED BECAUSE THE DISPLAY IS UPSIDE DOWN
    myfnUpdateDisplay1(bits);    // display alphanumeric digit
    delay(500);                 // pause for 1/2 second
  }
  

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


byte myfnNumToBits2(int someNumber) { // THESE ARE REVERSED BECAUSE THE DISPLAY IS UPSIDE DOWN
  switch (someNumber) {
    case 0:
      return B11111010; ///
      break;
    case 1:
      return B00001010; ///
      break;
    case 2:
      return B11011100; /// ??
      break;
    case 3:
      return B10011110; //
      break;
    case 4:
      return B00101110; //
      break;
    case 5:
      return B10110110; //
      break;
    case 6: 
      return B11110110; //
      break;
    case 7:
      return B00011010; ///
      break;
    case 8:
      return B11111110; //
      break;
    case 9:
      return B00111110; // 
      break;
//    case 10:
//      return B01111110; // Hexidecimal A //
//      break;
//    case 11:
//      return B11100110; // Hexidecimal B //
//      break;
//    case 12:
//      return B11110000; // Hexidecimal C or use for Centigrade //
//      break;
//    case 13:
//      return B11001000; // Hexidecimal D /// ?? WRONG
//      break;
//    case 14: 
//      return B11110100; // Hexidecimal E ///
//      break;
//    case 15:
//      return B01110100; // Hexidecimal F or use for Fahrenheit ///
//      break;  
    default:
      return B10010100; // Error condition, displays three vertical bars
      break;   
  }
}

byte myfnNumToBits1(int someNumber) {
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
//    case 10:
//      return B11101110; // Hexidecimal A
//      break;
//    case 11:
//      return B00111110; // Hexidecimal B
//      break;
//    case 12:
//      return B10011010; // Hexidecimal C or use for Centigrade
//      break;
//    case 13:
//      return B01111100; // Hexidecimal D
//      break;
//    case 14: 
//      return B10011110; // Hexidecimal E
//      break;
//    case 15:
//      return B10001110; // Hexidecimal F or use for Fahrenheit
//      break;  
    default:
      return B10010100; // Error condition, displays three vertical bars
      break;   
  }
}

