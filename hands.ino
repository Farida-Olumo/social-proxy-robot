#include <Servo.h>

// ======================================================
// SERVO PINS
// ======================================================

const byte LEFT_ARM_SERVO_PIN = 10;
const byte RIGHT_ARM_SERVO_PIN = 11;

// ======================================================
// LED PINS
// ======================================================

const byte LEFT_LED_PIN = A0;
const byte RIGHT_LED_PIN = A1;

// Each LED should use a 220–330 ohm resistor.

// ======================================================
// SERVO OBJECTS
// ======================================================

Servo leftArmServo;
Servo rightArmServo;

// ======================================================
// ARM POSITIONS
// ======================================================

// Adjust these angles depending on how your servos are mounted.

const int LEFT_ARM_DOWN = 20;
const int LEFT_ARM_UP = 120;

// The right servo usually moves in the opposite direction.
const int RIGHT_ARM_DOWN = 160;
const int RIGHT_ARM_UP = 60;

// ======================================================
// SETUP
// ======================================================

void setup()
{
  Serial.begin(9600);

  // Attach arm servos.
  leftArmServo.attach(LEFT_ARM_SERVO_PIN);
  rightArmServo.attach(RIGHT_ARM_SERVO_PIN);

  // Configure LEDs.
  pinMode(LEFT_LED_PIN, OUTPUT);
  pinMode(RIGHT_LED_PIN, OUTPUT);

  // Start with LEDs off.
  digitalWrite(LEFT_LED_PIN, LOW);
  digitalWrite(RIGHT_LED_PIN, LOW);

  // Start with both arms lowered.
  leftArmServo.write(LEFT_ARM_DOWN);
  rightArmServo.write(RIGHT_ARM_DOWN);

  delay(500);

  printControls();
}

// ======================================================
// MAIN LOOP
// ======================================================

void loop()
{
  if (Serial.available() > 0)
  {
    char command = Serial.read();

    // Ignore Enter and newline.
    if (command == '\n' || command == '\r')
    {
      return;
    }

    // Convert lowercase letters to uppercase.
    if (command >= 'a' && command <= 'z')
    {
      command = command - 32;
    }

    switch (command)
    {
      case 'Q':
        raiseLeftArm();
        Serial.println("Left hand raised");
        break;

      case 'Z':
        lowerLeftArm();
        Serial.println("Left hand lowered");
        break;

      case 'E':
        raiseRightArm();
        Serial.println("Right hand raised");
        break;

      case 'C':
        lowerRightArm();
        Serial.println("Right hand lowered");
        break;

      case 'R':
        raiseBothArms();
        Serial.println("Both hands raised");
        break;

      case 'F':
        lowerBothArms();
        Serial.println("Both hands lowered");
        break;

      case '?':
        printControls();
        break;

      default:
        Serial.println("Unknown command");
        break;
    }
  }
}

// ======================================================
// LEFT ARM FUNCTIONS
// ======================================================

void raiseLeftArm()
{
  leftArmServo.write(LEFT_ARM_UP);
  digitalWrite(LEFT_LED_PIN, HIGH);
}

void lowerLeftArm()
{
  leftArmServo.write(LEFT_ARM_DOWN);
  digitalWrite(LEFT_LED_PIN, LOW);
}

// ======================================================
// RIGHT ARM FUNCTIONS
// ======================================================

void raiseRightArm()
{
  rightArmServo.write(RIGHT_ARM_UP);
  digitalWrite(RIGHT_LED_PIN, HIGH);
}

void lowerRightArm()
{
  rightArmServo.write(RIGHT_ARM_DOWN);
  digitalWrite(RIGHT_LED_PIN, LOW);
}

// ======================================================
// BOTH ARM FUNCTIONS
// ======================================================

void raiseBothArms()
{
  leftArmServo.write(LEFT_ARM_UP);
  rightArmServo.write(RIGHT_ARM_UP);

  digitalWrite(LEFT_LED_PIN, HIGH);
  digitalWrite(RIGHT_LED_PIN, HIGH);
}

void lowerBothArms()
{
  leftArmServo.write(LEFT_ARM_DOWN);
  rightArmServo.write(RIGHT_ARM_DOWN);

  digitalWrite(LEFT_LED_PIN, LOW);
  digitalWrite(RIGHT_LED_PIN, LOW);
}

// ======================================================
// CONTROL LIST
// ======================================================

void printControls()
{
  Serial.println();
  Serial.println("===========================");
  Serial.println("       HAND CONTROLS");
  Serial.println("===========================");
  Serial.println("Q = Raise left hand");
  Serial.println("Z = Lower left hand");
  Serial.println("E = Raise right hand");
  Serial.println("C = Lower right hand");
  Serial.println("R = Raise both hands");
  Serial.println("F = Lower both hands");
  Serial.println("? = Show controls");
  Serial.println("===========================");
}