#include <cmath>
void setup() {
    // Declaring Pins from D12 — D5 for input
    // These pins are connected to the IR sensors
    pinMode(12, INPUT);  // Connect with IR Sensor 1
    pinMode(8, INPUT);   // Connect with IR Sensor 2
    pinMode(7, INPUT);   // Connect with IR Sensor 3
    pinMode(6, INPUT);   // Connect with IR Sensor 4
    pinMode(5, INPUT);   // Connect with IR Sensor 5
    pinMode(4, INPUT);   // Connect with IR Sensor 6
    pinMode(3, INPUT);   // Connect with IR Sensor 7
    pinMode(2, INPUT);   // Connect with IR Sensor 8

    // Declaring Pins D11, D10, and D9 for PWM Output
    pinMode(11, OUTPUT);  // Connect with Left Motor
    pinMode(10, OUTPUT);  // Connect with Right Motor

    // Speed settings
    int baseSpeed = 255;  // Base speed for the motors

    // Distance from center for error calculation
    int distanceFromCenter1 = 0;  // Sensor 1 (Add Value)
    int distanceFromCenter2 = 0;  // Sensor 2 (Add Value)
    int distanceFromCenter3 = 0;  // Sensor 3 (Add Value)
    int distanceFromCenter4 = 0;  // Sensor 4 (Add Value)
    int distanceFromCenter5 = 0;  // Sensor 5 (Add Value)
    int distanceFromCenter6 = 0;  // Sensor 6 (Add Value)
    int distanceFromCenter7 = 0;  // Sensor 7 (Add Value)
    int distanceFromCenter8 = 0;  // Sensor 8 (Add Value)

    // Car Dimensions
    int length = 0;  // Distance from the sensors and wheel (Add Value)
    int width = 0;   // Distance between the wheels (Add Value)

    // IR pins array
    int leftIRPins[4] = {12, 8, 7, 6};  // <---- Customizable
    int rightIRPins[4] = {5, 4, 3, 2};

    // Realtime variables
    int angle;
    int activeDistance
    int displacement
    int radius;
    int radiusLeft
    int radiusRight;
    char direction;

    void turn(char direction, int correction) {
        if (direction == "left") {
            analogWrite(11, baseSpeed * correction);
            analogWrite(10, baseSpeed);
        }

         else if (direction == "right") {
            analogWrite(11, baseSpeed);
            analogWrite(10, baseSpeed * correction);
        }

    }
}

void loop() {
    // Read the sensor values
    int sensorValue1 = digitalRead(12);  // Read from IR Sensor 1
    int sensorValue2 = digitalRead(8);   // Read from IR Sensor 2
    int sensorValue3 = digitalRead(7);   // Read from IR Sensor 3
    int sensorValue4 = digitalRead(6);   // Read from IR Sensor 4
    int sensorValue5 = digitalRead(5);   // Read from IR Sensor 5
    int sensorValue6 = digitalRead(4);   // Read from IR Sensor 6
    int sensorValue7 = digitalRead(3);   // Read from IR Sensor 7
    int sensorValue8 = digitalRead(2);   // Read from IR Sensor 8

    // Calculate the distance from the center for each sensor
    if (sensorValue8 == HIGH) {
        activeDistance = distanceFromCenter8;
        char = "right";
    }
    else if (sensorValue1 == HIGH) {
        activeDistance = distanceFromCenter1;
        direction = 'left';
    }
    else if (sensorValue7 == HIGH) {
        activeDistance = distanceFromCenter7;
        direction = 'right';
    }
    else if (sensorValue2 == HIGH) {
        activeDistance = distanceFromCenter2;
        direction = 'left';
    }
    else if (sensorValue6 == HIGH) {
        activeDistance = distanceFromCenter6;
        direction = 'right';
    }
    else if (sensorValue3 == HIGH) {
        activeDistance = distanceFromCenter3;
        direction = 'left';
    }
    else if (sensorValue5 == HIGH) {
        activeDistance = distanceFromCenter5;
        direction = 'right';
    }
    else if (sensorValue4 == HIGH) {
        activeDistance = distanceFromCenter4;
        direction = 'left';
    }
    else {
        activeDistance = 0;  // If no sensor is triggered, assume the robot is off the line
    }

    // Calculate the angle of the line relative to the robot
    // atan returns angle in radian
    angle = atan(activeDistance / length);

    // Calculate displacement
    displacement = sqrt(pow(activeDistance, 2) + pow(length, 2));
    radius = displacement / angle;
    
    if (direction == "left") {
        radiusLeft = radius - (width / 2);
        radiusRight = radius + (width / 2);
    }

    else if (direction == "right") {
        radiusLeft = radius + (width / 2);
        radiusRight = radius - (width / 2);
    }

    leftSpeed = baseSpeed * (radiusLeft / radius);
    rightSpeed = baseSpeed * (radiusRight / radius);
    turn(direction, leftSpeed / baseSpeed);
}