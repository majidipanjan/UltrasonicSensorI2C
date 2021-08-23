/*
  I2C Ultrasonic 4 Sensors Slave
  All 4 sensors are conected in 1 pin mode and can also connected in 2 pins as well.
  Ultrasonic 4 Sensors Test
*/

#include <NewPing.h>
#include <Wire.h>
#define SLAVE_ADDR 9
#define TRIGGER_PIN_0  8
#define ECHO_PIN_0     8
#define TRIGGER_PIN_1  9
#define ECHO_PIN_1     9
#define TRIGGER_PIN_2  10
#define ECHO_PIN_2     10
#define TRIGGER_PIN_3  11
#define ECHO_PIN_3     11
#define MAX_DISTANCE 400


NewPing sensor0(TRIGGER_PIN_0, ECHO_PIN_0, MAX_DISTANCE);
NewPing sensor1(TRIGGER_PIN_1, ECHO_PIN_1, MAX_DISTANCE);
NewPing sensor2(TRIGGER_PIN_2, ECHO_PIN_2, MAX_DISTANCE);
NewPing sensor3(TRIGGER_PIN_3, ECHO_PIN_3, MAX_DISTANCE);

// Define return data array, one element per sensor
int distance[4];

// Define counter to count bytes in response
int bcount = 0;

void setup() {

  // Initialize I2C communications as Slave
  Wire.begin(SLAVE_ADDR);
 
   // Function to run when data requested from master
  Wire.onRequest(requestEvent); 
  
}

void requestEvent() {
 
  // Define a byte to hold data
  byte bval;
  
  // Cycle through data
  // First response is always 255 to mark beginning
  switch (bcount) {
    case 0:
      bval = 255;
      break;
    case 1:
      bval = distance[0];
      break;
    case 2:
      bval = distance[1];
      break;
    case 3:
      bval = distance[2];
      break;
    case 4:
      bval = distance[3];
      break;
  }
  
  // Send response back to Master
  Wire.write(bval);
  
  // Increment byte counter
  bcount = bcount + 1;
  if (bcount > 4) bcount = 0;

}

void readDistance()
{
  distance[0] = sensor0.ping_cm();
  if (distance[0] > 254 ) {
    distance[0] = 254;
  }
  delay(20);
  
  distance[1] = sensor1.ping_cm();
  if (distance[1] > 254 ) {
    distance[1] = 254;
  }
  delay(20);
  
  distance[2] = sensor2.ping_cm();
  if (distance[2] > 254 ) {
    distance[2] = 254;
  }
  delay(20);
  
  distance[3] = sensor3.ping_cm();
  if (distance[3] > 254 ) {
    distance[3] = 254;
  }
  delay(20);
  
  
}

void loop()
{
  // Refresh readings every 1/10th of a second
  readDistance();
  delay(100);
}
