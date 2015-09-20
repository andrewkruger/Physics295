// Shows how to run three Steppers at once with varying speeds
//
// Requires the Adafruit_Motorshield v2 library 
//   https://github.com/adafruit/Adafruit_Motor_Shield_V2_Library
// And AccelStepper with AFMotor support 
//   https://github.com/adafruit/AccelStepper

// Coded for protoAHCS

// This tutorial is for Adafruit Motorshield v2 only!
#include <AccelStepper.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_PWMServoDriver.h"

Adafruit_MotorShield AFMStop(0x60); // Default address, no jumpers

// Connect stepper with 513 steps per revolution to the shield
Adafruit_StepperMotor *myStepper = AFMStop.getStepper(513, 2);

// you can change these to DOUBLE or INTERLEAVE or MICROSTEP!
void forwardstep() {  
  myStepper->onestep(FORWARD, DOUBLE);
}
void backwardstep() {  
  myStepper->onestep(BACKWARD, DOUBLE);
}

// Wrap the 3 steppers in an AccelStepper object
AccelStepper stepper(forwardstep, backwardstep);

// Set up variables for angles
float gammaPos;     //Input heading from gamma
int gammaPosSteps;  // Convert units to motor steps
int heading;        //Desired heading
const float DegToSteps = 1.425;  //Degree to Motor steps conversion 
                                 //(#steps/360deg)

void setup()
{  
  AFMStop.begin();                // Start the top shield
  Serial.begin(38400);            // Gamma using 38400 baud
  stepper.setMaxSpeed(5000.0);    //steps/sec, high value is limited by time
                                  //taken to call run()
  stepper.setAcceleration(200.0); //steps/sec^2
  heading= 0 * DegToSteps;        // In units of motor steps
}

void loop()
{
    if (Serial.available() > 0) {

        gammaPos = Serial.parseFloat();      //Read in gamma heading in deg
 
 /*-------Comment out if moving in another way---------*/
 //This example will rotate the protoAHCS until the gamma is facing 
 //the desired heading
        gammaPosSteps = -gammaPos * DegToSteps;  //Convert to steps
        stepper.move(gammaPosSteps - heading);   //Tells steps to move
 /*-------End Comment out for changing movement-------*/
 
 /*-------Code here if moving in another way---------*/






 /*-------End coding for changing movement-------*/
 
        stepper.run();                          //Move
        serialFlush();                          //Clear serial memory
      }    
    
    stepper.run();                              //Keep moving until new gammaPos
}


void serialFlush() {
  while(Serial.available() > 0) {
    char t = Serial.read();
  }
}

