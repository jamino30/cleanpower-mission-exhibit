#include <LiquidCrystal.h> // include LCD library

const int BUTTON[] = {13, 12}; // {on, off} ports
const int MOTOR[] = {9, 10, 11}; // {1&2, 1, 2} ports
const int LED = 8; // led town port
const int POTENT = A0; // potentiometer port
LiquidCrystal lcd(7, 6, 5, 4, 3, 2); // LCD Display ports

int onButton, offButton, potentValue, sensorValue, speed; // declare empty variables

void turbineSpeed() { // wind turbine speed changer using potentiometer
 if (sensorValue == 1024) {lcd.print ("NONE");
 }
 if (sensorValue <= 340) { // if potentiometer is in first 1/3 range
   speed = 100; // set speed to HIGH: 100

   lcd.setCursor(12, 0); lcd.print("HIGH"); // print HIGH for wind speed
 }
 if ((sensorValue > 340) && (sensorValue <= 680)) { // if potentiometer is in middle 1/3 range
   speed = 30; // set speed to MEDIUM: 30

   lcd.setCursor(12, 0); lcd.print("MED "); // print MED for wind speed
 }
 if (sensorValue > 680) { // if potentiometer is in last 1/3 range
   speed = 20; // set speed to LOW: 20

   lcd.setCursor(12, 0); lcd.print("LOW "); // print LOW for wind speed
 }

}

void motorState(int value) { // motor control function
 turbineSpeed(); // run turbine speed function
 analogWrite(MOTOR[0], speed); // determine speed of motor based on turbinespeed()
 digitalWrite(MOTOR[1], value); // turn motor forwards HIGH/LOW
 digitalWrite(MOTOR[2], 0); // motor backwards always off
}

void LEDState(int value) { // controls LED state
 digitalWrite(LED, value); // sets LEDS either HIGH or LOW
}

void motorWithButtons() { // controls exhibit controls
 if (onButton) { // if "on" button is pressed
   motorState(1); // turn motor on
   LEDState(1); // turn all LEDs on

   lcd.setCursor(12, 1); lcd.print("ON "); // print that town power state is ON
 }
 if (offButton) { // if "off" button is pressed
   motorState(0); // turn motor off
   LEDState(0); // turn all LEDs off

   lcd.setCursor(12, 0); lcd.print("NONE"); // print that there is NO wind speed
   lcd.setCursor(12, 1); lcd.print("OFF"); // print that town power state is OFF
 }
}

void setup() {
 for (int x = 0; x < 2; x++) pinMode(BUTTON[x], INPUT); // setup on/off buttons
 pinMode(POTENT, INPUT); // setup potentiometer
 pinMode(LED, OUTPUT); // setup LEDs
 for (int x = 0; x < 3; x++) pinMode(MOTOR[x], OUTPUT); // setup motor for windmill
 lcd.begin(16, 2); // setup LCD display
 lcd.setCursor(0, 0); lcd.print("WIND SPEED:"); // print "wind speed:" in row 1
 lcd.setCursor(0, 1); lcd.print("TOWN POWER:"); // print "town power:" in row 2
 Serial.begin(9600);
}

void loop() {
 Serial.println(potentValue);

 onButton = digitalRead(BUTTON[0]); // read on button (green)
 offButton = digitalRead(BUTTON[1]); // read off button (red)
 potentValue = analogRead(POTENT); // read potentiometer value
 sensorValue = potentValue;
 turbineSpeed();
 analogWrite(MOTOR[0], speed);
 motorWithButtons(); // turn on/off motor
}
