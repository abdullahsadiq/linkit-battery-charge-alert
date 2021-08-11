#include <LBattery.h>
#include <LGSM.h>

int batteryValue;
String startBuffer;
String message = "Your LinkIt ONE's battery is full! Please disconnect it.";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  while (Serial.available() == 0) {}    // Wait until user inputs data and start the program when data is received
  startBuffer = Serial.readString();    // Save the users input in startBuffer variable

  Serial.println("Starting SMS battery charger alert!");  // Start the Send SMS program

  while (!LSMS.ready())  // Wait for the sim to initialize
  {
    delay(1000);   // Wait for a second and then try again
  }
  LSMS.beginSMS("0123456789");

  batteryValue = LBattery.level();
  Serial.println(batteryValue);

  LSMS.print(message);  // Prepare message variable to be sent by LSMS

  if (batteryValue == 100) {
    if (LSMS.endSMS())                  // If so, send the SMS
    {
      Serial.println("Alert SMS sent");    // Print "Alert SMS sent" in serial port if sending is successful
    }
    else
    {
      Serial.println("Alert SMS not sent");// Else print "Alert SMS not sent"
    }
  }
}

void loop() {
  // put your main code here, to run repeatedly:
}
