/**
 * This class is to be uploaded into the controller. It takes user input and transmits it
 * over bluetooth.
 *
 * @author sammatime22
 */
#include <SoftwareSerial.h>

// Controller Constants
int LEFT = 2;
int RIGHT = 3;
int UP = 4;
int DOWN = 5;
int LIGHT = 13;

/**
 * Sets up the Controller's LEFT, RIGHT, UP, and DOWN directions.
 *
 * Additionally, an LED for debugging as well as the BAUD rate are both set here.
 */
void setup() {
  pinMode(LEFT, INPUT);
  pinMode(RIGHT, INPUT);
  pinMode(UP, INPUT);
  pinMode(DOWN, INPUT);
  pinMode(LIGHT, OUTPUT);
  Serial.begin(57600);
}

/**
 * The main loop to read in the desired direction from the Joystick.
 */
void loop() {
  if(!digitalRead(UP)) {
    // Write the UP command
    Serial.write('u');
    digitalWrite(LIGHT, HIGH); // LED debug up
  } else if(!digitalRead(DOWN)) {
    // Write the DOWN command
    Serial.write('d');
    digitalWrite(LIGHT, HIGH); // LED debug up
  } else if(!digitalRead(LEFT)) {
    // Write the LEFT command
    Serial.write('l');
    digitalWrite(LIGHT, HIGH); // LED debug up
  } else if(!digitalRead(RIGHT)) {
    // Write the RIGHT command
    Serial.write('r');
    digitalWrite(LIGHT, HIGH); // LED debug up
  } else {
    // Send the info that no command is being sent over the connection
    Serial.write('n');
  }
  digitalWrite(LIGHT, LOW); // Bring the LED debug down
  Serial.flush(); // Flush the output
}
