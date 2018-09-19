/**
 * Authors: Thomas van Zonneveld, Leon Klute, Remi Jonkman
 * Group:
 * This sketch is used for the ECA-Project where the goal is to optimize the calculation
 * of C = AB + 2A, where A, B and C are square 13x13 matrices.
 */
 
#include "includes/types.h"
#include "includes/functions.h"
#include "includes/constants.h"

// Create an empty result matrix (all 0 initialized) of 13 by 13 with 16 bit unsigned integers
Matrix<uint32_t, 13, 13> result = {};

void setup() {
  // Begin serial communication at 115.200 baud/s
  Serial.begin(115200);
}

void loop() {
  // Initialize timing variable
  unsigned long timeVariable = 0;

  // To try this out, the const matrix should be stored in Program Memory
  timeVariable = micros();
  // Calculate the multiplication 1000 times
  for (size_t i = 0; i < 1000; i++) {
    multiplyProgMem< >(A, B, result);
  }
  timeVariable = micros() - timeVariable;
  Serial.print("MultiplyProgMem Time: ");
  Serial.println(timeVariable);
  printMatrixToSerial< >(result);

  // To try this out, the const matrix should be stored in Program Memory
  timeVariable = micros();
  // Calculate the multiplication 1000 times
  for (size_t i = 0; i < 1000; i++) {
    multiplyWithTranposeProgMem< >(A, transposed, result);
  }
  timeVariable = micros() - timeVariable;
  Serial.print("MultiplyWithTransposeProgMem Time: ");
  Serial.println(timeVariable);
  printMatrixToSerial< >(result);
}
