/*

Fablab Digiscope Photocell Test

*/
   

//Constant
const int pResistor = A3; // Photoresistor at Arduino analog pin A3

//Variable
int value;          // Store value from photoresistor (0-1023)

void setup(){
  
  Serial.begin(9600);

  Serial.println("Photocell test");  

  pinMode(pResistor, INPUT);// Set pResistor - A3 pin as an input
}

void loop(){
  
  value = analogRead(pResistor);

  Serial.println(value);  

  Serial.println();
  
  delay(500); //Small delay
}
