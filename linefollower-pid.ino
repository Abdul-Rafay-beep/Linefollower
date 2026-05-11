#include <cmath>

// Sensor geometry
float distanceFromCenter1 = 0;  // Sensor 1 (Add Value)
float distanceFromCenter2 = 0;  // Sensor 2 (Add Value)
float distanceFromCenter3 = 0;  // Sensor 3 (Add Value)
float distanceFromCenter4 = 0;  // Sensor 4 (Add Value)
float distanceFromCenter5 = 0;  // Sensor 5 (Add Value)
float distanceFromCenter6 = 0;  // Sensor 6 (Add Value)
float distanceFromCenter7 = 0;  // Sensor 7 (Add Value)
float distanceFromCenter8 = 0;  // Sensor 8 (Add Value)

// Base speed for the motors
int baseSpeed = 180;

// PID Constants
int k1 = 1;  // Proportional constant (Add Value)
int k2 = 0;  // Integral constant (Add Value)
int k3 = 0;  // Derivative constant (Add Value)

// error and time variables for PID control
float previousError = 0;
int previousTime = 0;
float error = 0;
char direction;

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
    float error = 0;
    int sensorCount = 0;

    // Calculate the distance from the center for each sensor
    if (sensorValue8 == HIGH) {
        error += distanceFromCenter8;
        sensorCount++;
    }
    else if (sensorValue1 == HIGH) {
        error += distanceFromCenter1;
        sensorCount++;
    }
    else if (sensorValue7 == HIGH) {
        error += distanceFromCenter7;
        sensorCount++;
    }
    else if (sensorValue2 == HIGH) {
        error += distanceFromCenter2;
        sensorCount++;
    }
    else if (sensorValue6 == HIGH) {
        error += distanceFromCenter6;
        sensorCount++;
    }
    else if (sensorValue3 == HIGH) {
        error += distanceFromCenter3;
        sensorCount++;
    }
    else if (sensorValue5 == HIGH) {
        error += distanceFromCenter5;
        sensorCount++;
    }
    else if (sensorValue4 == HIGH) {
        error += distanceFromCenter4;
        sensorCount++;
    }
    if (sensorCount > 0) {
        error /= sensorCount;  // Average the error if multiple sensors are active
    }

    int time = millis();
    int deltaTime = time - previousTime;
    float proportional = k1 * error;
    float integral = k2 * (error * deltaTime);
    float derivative = k3 * ((error - previousError) / deltaTime);

    int correction = proportional + integral + derivative;
    previousError = error;
    previousTime = time;

    int leftSpeed = constrain(baseSpeed + correction, 0, 255);
    int rightSpeed = constrain(baseSpeed - correction, 0, 255);

    analogWrite(11, leftSpeed);
    analogWrite(10, rightSpeed);
}