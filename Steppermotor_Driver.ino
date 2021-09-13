/*Example sketch to control a stepper motor with A4988 stepper motor driver and Arduino without a library. More info: https://www.makerguides.com */
// Define stepper motor connections and steps per revolution:
#define dirPin 22
#define stepPin 23
#define stepsPerRevolution 200
#define FORCE_SENSOR_PIN A0 // the FSR and 10K pulldown are connected to A0
int RST=4, EN=18;      //Fro aduino uno 7 for esp32 18
char receivedChar;

void setup() {
  // Declare pins as output:
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(EN, OUTPUT);  

  Serial.begin(115200);
  Serial.flush();
}

void loop() {
  
   int j=0;
   int distance=50;  //value in mm
   recvOneChar();
   
  //delay(1000);
  //go_forward(distance);
  //delay(1000);
  //go_backward(distance);
}

void recvOneChar() {
 if (Serial.available() > 0) {
  int serialCommandIn = Serial.parseInt(); 
  if (Serial.read() == '\n')  {
 receivedChar = Serial.read();
 //Serial.println(serialCommandIn); // print the raw analog reading
 if (serialCommandIn>0){
   go_forward(serialCommandIn);
 }
 else{
   go_backward(abs(serialCommandIn));
 }
 
 }
 }
}

void go_forward(int distance) {
  // Set the spinning direction clockwise:
    int j=0;
  digitalWrite(dirPin, HIGH);
  digitalWrite(EN, LOW);
  //Spin the stepper motor 5 revolutions fast:
  for (int i = 0; i < distance * 4 * stepsPerRevolution; i++) {
    // These four lines result in 1 step:
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(100);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(100);
    j++;
    if (j==80) {
    int analogReading = analogRead(FORCE_SENSOR_PIN);
    Serial.print(i); // print the raw analog reading
    Serial.print(",");  
    Serial.println(analogReading); // print the raw analog reading
    //Serial.println(";");  
    j=0;
    }
  digitalWrite(EN, HIGH);
  }
}

void go_backward(int distance) {
  // Set the spinning direction counterclockwise:
    int j=0;
  digitalWrite(dirPin, LOW);
  digitalWrite(EN, LOW);
  //Spin the stepper motor 5 revolutions fast:
  for (int i = 0; i < distance * 4 * stepsPerRevolution; i++) {
    // These four lines result in 1 step:
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(100);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(100);
    j++;
    if (j==80) {
    int analogReading = analogRead(FORCE_SENSOR_PIN);
    Serial.print(i); // print the raw analog reading
    Serial.print(",");  
    Serial.println(analogReading); // print the raw analog reading
    //Serial.println(";");  
    j=0;
    }
  digitalWrite(EN, HIGH);
  }
}
