#include <Servo.h>
#define MOV_FREQ 50

Servo middle,ring,pinky,thumb;  // create servo object to control a servo
unsigned long lastMove = millis(); 
// twelve servo objects can be created on most boards
int pos = 0;    // variable to store the servo position
int mean = 0, n = 0;

void setup() {
  Serial.begin(115200);
  middle.attach(5);  // attaches the servo on pin 9 to the servo object
  ring.attach(4);
  pinky.attach(0);
  thumb.attach(2);
}

void loop() {
  int adcValue = analogRead(A0); // Read analog value from ADC0 pin
  unsigned long currentTime = millis();
  mean+=adcValue; ++n;
  if(currentTime - lastMove >= MOV_FREQ){
    mean = mean/n; // sampling
    pos = map(mean, 200, 600, 0, 180);  
    middle.write(pos); pinky.write(pos);
    ring.write(180-pos); thumb.write(180-pos);  

    mean = 0; n = 0;
  }
  Serial.print("ADC0 Value: ");
  Serial.println(adcValue); // Print ADC value to serial monitor
}
