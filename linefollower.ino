#include <cmath>

// Base speed for the motors
// This is the standard linear speed for combined motion
// of two motors.
int baseSpeed = 255;
int circleTime = 0;  // Add value for one circular motion
float radError = 0;  // Add value for error correction
int startTime = 0;  // Variable to store the start time for delay

// Distance from center for error calculation
float distanceFromCenter1 = 0;  // Sensor 1 (Add Value)
float distanceFromCenter2 = 0;  // Sensor 2 (Add Value)
float distanceFromCenter3 = 0;  // Sensor 3 (Add Value)
float distanceFromCenter4 = 0;  // Sensor 4 (Add Value)
float distanceFromCenter5 = 0;  // Sensor 5 (Add Value)
float distanceFromCenter6 = 0;  // Sensor 6 (Add Value)
float distanceFromCenter7 = 0;  // Sensor 7 (Add Value)
float distanceFromCenter8 = 0;  // Sensor 8 (Add Value)

// Car Dimensions
float length = 1;  // Distance from the sensors and wheel (Add Value)
float width = 0;   // Distance between the wheels (Add Value)

// Realtime variables
float angle;
float activeDistance;
float displacement;
float radius;
float radiusLeft;
float radiusRight;
char direction;
float leftSpeed;
float rightSpeed;

void turn(char direction, int correction) {
    int speed = baseSpeed * correction;
    if (direction == 'L') {
        analogWrite(11, speed);
        analogWrite(10, baseSpeed);
    }

        else if (direction == 'R') {
        analogWrite(11, baseSpeed);
        analogWrite(10, speed);
    }
}

// Setup Function
void setup() {
    // Declaring Pins from D12, and D9 — D6 for input
    // These pins are connected to the IR sensors
    pinMode(12, INPUT);  // Connect with IR Sensor 1
    pinMode(9, INPUT);   // Connect with IR Sensor 2
    pinMode(8, INPUT);   // Connect with IR Sensor 3
    pinMode(7, INPUT);   // Connect with IR Sensor 4
    pinMode(6, INPUT);   // Connect with IR Sensor 5
    pinMode(5, INPUT);   // Connect with IR Sensor 6
    pinMode(4, INPUT);   // Connect with IR Sensor 7
    pinMode(3, INPUT);   // Connect with IR Sensor 8

    // Declaring Pins D11, D10, and D9 for PWM Output
    pinMode(11, OUTPUT);  // Connect with Left Motor
    pinMode(10, OUTPUT);  // Connect with Right Motor

}

void loop() {
    // Read the sensor values
    int sensorValue1 = digitalRead(12);  // Read from IR Sensor 1
    int sensorValue2 = digitalRead(9);   // Read from IR Sensor 2
    int sensorValue3 = digitalRead(8);   // Read from IR Sensor 3
    int sensorValue4 = digitalRead(7);   // Read from IR Sensor 4
    int sensorValue5 = digitalRead(6);   // Read from IR Sensor 5
    int sensorValue6 = digitalRead(5);   // Read from IR Sensor 6
    int sensorValue7 = digitalRead(4);   // Read from IR Sensor 7
    int sensorValue8 = digitalRead(3);   // Read from IR Sensor 8

    // Calculate the distance from the center for each sensor
    if (sensorValue8 == HIGH) {
        activeDistance = distanceFromCenter8;
        direction = 'R';
    }
    else if (sensorValue1 == HIGH) {
        activeDistance = distanceFromCenter1;
        direction = 'L';
    }
    else if (sensorValue7 == HIGH) {
        activeDistance = distanceFromCenter7;
        direction = 'R';
    }
    else if (sensorValue2 == HIGH) {
        activeDistance = distanceFromCenter2;
        direction = 'L';
    }
    else if (sensorValue6 == HIGH) {
        activeDistance = distanceFromCenter6;
        direction = 'R';
    }
    else if (sensorValue3 == HIGH) {
        activeDistance = distanceFromCenter3;
        direction = 'L';
    }
    else if (sensorValue5 == HIGH) {
        activeDistance = distanceFromCenter5;
        direction = 'R';
    }
    else if (sensorValue4 == HIGH) {
        activeDistance = distanceFromCenter4;
        direction = 'L';
    }
    else {
        if (activeDistance != 0) {
            activeDistance = 0;  // If no sensor is triggered, assume the robot is off the line

            if (direction == 'L') {
                direction = 'R';
            }
            else if (direction == 'R') {
                direction = 'L';
            }
            else {
                direction = 'L';  // Default to left if no previous direction is known
            }

            turn(direction, 0);
            startTime = millis();  // Start the timer for delay
        }

        else if (activeDistance == 0 && (millis() - startTime) >= circleTime) {;
            analogWrite(11, 0);
            analogWrite(10, 0);
        }
        return;  // Exit the loop if no sensor is triggered
    }

    // Calculate the angle of the line relative to the robot
    // atan returns angle in radian
    angle = atan(activeDistance / length);

    // Calculate displacement
    displacement = sqrt((activeDistance * activeDistance) + (length * length));
    radius = displacement / angle;

    if (direction == 'L') {
        radiusLeft = radius - (width / 2);
        radiusRight = radius + (width / 2);
    }

    else if (direction == 'R') {
        radiusLeft = radius + (width / 2);
        radiusRight = radius - (width / 2);
    }

    leftSpeed = baseSpeed * (radiusLeft / radius);
    turn(direction, leftSpeed / baseSpeed);
}