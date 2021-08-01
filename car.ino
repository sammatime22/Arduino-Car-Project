/**
 * This class is to be uploaded into the car. It takes input over the serial port, and uses
 * it to run the car.
 *
 * @author sammatime22
 */
#include <SoftwareSerial.h>

// Car constants for all nine pins 
// (eight for transistors that run the motors, one for the Debug LED (builtin))
const int NUM_OF_ACTIVE_PINS = 9;
const int PIN_ARRAY[] = { 12, 11, 10, 9, 8, 7, 6, 5, 13 };

/**
 * Sets up all nine pins and defines the BAUD rate.
 */
void setup() {
  for (int i = 0; i < NUM_OF_ACTIVE_PINS; i++){
    pinMode(PIN_ARRAY[i], OUTPUT);
  }
  Serial.begin(57600);
}

/**
 * This function abstracts the moving of motors.
 * 
 * @param pin_values: The values of that each of the pins are to be set to   
 */
void move_motors(uint8_t pin_values[]) {
  digitalWrite(PIN_ARRAY[8], HIGH); // Blink the LED when you get a signal
  digitalWrite(PIN_ARRAY[0], pin_values[0]); // PNP A
  digitalWrite(PIN_ARRAY[1], pin_values[1]); // NPN A
  digitalWrite(PIN_ARRAY[2], pin_values[2]); // PNP B
  digitalWrite(PIN_ARRAY[3], pin_values[3]); // NPN B
  digitalWrite(PIN_ARRAY[4], pin_values[4]); // PNP C
  digitalWrite(PIN_ARRAY[5], pin_values[5]); // NPN C
  digitalWrite(PIN_ARRAY[6], pin_values[6]); // PNP D
  digitalWrite(PIN_ARRAY[7], pin_values[7]); // NPN D
}

/**
 * The main loop to take in the input from the controller and use that to move the car.
 */
void loop() {
  if(Serial.available() > 0) {
    digitalWrite(PIN_ARRAY[8], HIGH); // Blink the LED when you get a signal
    char recieved_data = Serial.read();
    Serial.print(recieved_data);
    if ('u' == recieved_data) {
      // Controller moved UP, move car Forward
      uint8_t to_motor[] = { LOW, LOW, HIGH, HIGH, HIGH, HIGH, LOW, LOW };
      move_motors(to_motor);
    } else if('d' == recieved_data) {
      // Controller moved DOWN, move car Backward
      uint8_t to_motor[] = { HIGH, HIGH, LOW, LOW, LOW, LOW, HIGH, HIGH };
      move_motors(to_motor);
    } else if('l' == recieved_data) {
      // Controller moved LEFT, turn the car to face Left
      uint8_t to_motor[] = { HIGH, HIGH, LOW, LOW, HIGH, HIGH, LOW, LOW };
      move_motors(to_motor);
    } else if('r' == recieved_data) {
      // Controller moved RIGHT, turn the car to face Right
      uint8_t to_motor[] = { LOW, LOW, HIGH, HIGH, LOW, LOW, HIGH, HIGH };
      move_motors(to_motor);
    } else {
      // 'n' or an unrecognized char has been received, do nothing
      uint8_t to_motor[] = { HIGH, LOW, HIGH, LOW, HIGH, LOW, HIGH, LOW };
      move_motors(to_motor);
    }
    digitalWrite(PIN_ARRAY[8], LOW); // Blink the LED when you get a signal
    Serial.read();
  }
}
