/*
Code Name:ESP32 based 4 channel automation with manual switch (Push Button)
Author: ammarece
Description: This program is used for ESP32 based 4 channel automation with manual switch
License: Remixing or Changing this Thing is allowed. Commercial use is not allowed.
*/
#include "BluetoothSerial.h"
#include <AceButton.h>
using namespace ace_button;

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to enable it.
#endif

BluetoothSerial SerialBT;

// Define the GPIO connected with Relays and push buttons
#define RelayPin1 23 // D23
#define RelayPin2 22 // D22
#define RelayPin3 21 // D21
#define RelayPin4 19 // D19

#define ButtonPin1 13 // D13
#define ButtonPin2 12 // D12
#define ButtonPin3 14 // D14
#define ButtonPin4 27 // D27

int toggleState_1 = 0; // Define integer to remember the toggle state for relay 1
int toggleState_2 = 0; // Define integer to remember the toggle state for relay 2
int toggleState_3 = 0; // Define integer to remember the toggle state for relay 3
int toggleState_4 = 0; // Define integer to remember the toggle state for relay 4

char bt_data; // Variable for storing bluetooth data

ButtonConfig config1;
AceButton button1(&config1);
ButtonConfig config2;
AceButton button2(&config2);
ButtonConfig config3;
AceButton button3(&config3);
ButtonConfig config4;
AceButton button4(&config4);

void all_Switch_OFF()
{
  digitalWrite(RelayPin1, HIGH);
  toggleState_1 = 0;
  digitalWrite(RelayPin2, HIGH);
  toggleState_2 = 0;
  digitalWrite(RelayPin3, HIGH);
  toggleState_3 = 0;
  digitalWrite(RelayPin4, HIGH);
  toggleState_4 = 0;
}

void Bluetooth_handle()
{
  bt_data = SerialBT.read();
  delay(20);

  switch (bt_data)
  {
  case 'A':
    digitalWrite(RelayPin1, LOW);
    toggleState_1 = 1;
    break; // if 'A' received Turn on Relay1
  case 'a':
    digitalWrite(RelayPin1, HIGH);
    toggleState_1 = 0;
    break; // if 'a' received Turn off Relay1
  case 'B':
    digitalWrite(RelayPin2, LOW);
    toggleState_2 = 1;
    break; // if 'B' received Turn on Relay2
  case 'b':
    digitalWrite(RelayPin2, HIGH);
    toggleState_2 = 0;
    break; // if 'b' received Turn off Relay2
  case 'C':
    digitalWrite(RelayPin3, LOW);
    toggleState_3 = 1;
    break; // if 'C' received Turn on Relay3
  case 'c':
    digitalWrite(RelayPin3, HIGH);
    toggleState_3 = 0;
    break; // if 'c' received Turn off Relay3
  case 'D':
    digitalWrite(RelayPin4, LOW);
    toggleState_4 = 1;
    break; // if 'D' received Turn on Relay4
  case 'd':
    digitalWrite(RelayPin4, HIGH);
    toggleState_4 = 0;
    break; // if 'd' received Turn off Relay4
  case 'Z':
    all_Switch_OFF();
    break; // if 'Z' received Turn off all Relays
  default:
    break;
  }
}

void setup()
{
  Serial.begin(9600);

  btStart();

  SerialBT.begin("ESP32_BT"); // Bluetooth device name
  Serial.println("The device started, now you can pair it with Bluetooth!");
  delay(5000);

  pinMode(RelayPin1, OUTPUT);
  pinMode(RelayPin2, OUTPUT);
  pinMode(RelayPin3, OUTPUT);
  pinMode(RelayPin4, OUTPUT);

  pinMode(ButtonPin1, INPUT_PULLUP);
  pinMode(ButtonPin2, INPUT_PULLUP);
  pinMode(ButtonPin3, INPUT_PULLUP);
  pinMode(ButtonPin4, INPUT_PULLUP);

  // During Starting all Relays should TURN OFF
  digitalWrite(RelayPin1, toggleState_1);
  digitalWrite(RelayPin2, toggleState_2);
  digitalWrite(RelayPin3, toggleState_3);
  digitalWrite(RelayPin4, toggleState_4);

  config1.setEventHandler(button1Handler);
  config2.setEventHandler(button2Handler);
  config3.setEventHandler(button3Handler);
  config4.setEventHandler(button4Handler);

  button1.init(ButtonPin1);
  button2.init(ButtonPin2);
  button3.init(ButtonPin3);
  button4.init(ButtonPin4);

  delay(200);
}

void loop()
{
  if (SerialBT.available())
  {
    Bluetooth_handle();
  }

  button1.check();
  button2.check();
  button3.check();
  button4.check();
}

void button1Handler(AceButton *button, uint8_t eventType, uint8_t buttonState)
{
  if (eventType == AceButton::kEventPressed)
  {
    if (toggleState_1 == 0)
    {
      digitalWrite(RelayPin1, LOW);
      toggleState_1 = 1;
    }
    else
    {
      digitalWrite(RelayPin1, HIGH);
      toggleState_1 = 0;
    }
  }
}

void button2Handler(AceButton *button, uint8_t eventType, uint8_t buttonState)
{
  if (eventType == AceButton::kEventPressed)
  {
    if (toggleState_2 == 0)
    {
      digitalWrite(RelayPin2, LOW);
      toggleState_2 = 1;
    }
    else
    {
      digitalWrite(RelayPin2, HIGH);
      toggleState_2 = 0;
    }
  }
}

void button3Handler(AceButton *button, uint8_t eventType, uint8_t buttonState)
{
  if (eventType == AceButton::kEventPressed)
  {
    if (toggleState_3 == 0)
    {
      digitalWrite(RelayPin3, LOW);
      toggleState_3 = 1;
    }
    else
    {
      digitalWrite(RelayPin3, HIGH);
      toggleState_3 = 0;
    }
  }
}

void button4Handler(AceButton *button, uint8_t eventType, uint8_t buttonState)
{
  if (eventType == AceButton::kEventPressed)
  {
    if (toggleState_4 == 0)
    {
      digitalWrite(RelayPin4, LOW);
      toggleState_4 = 1;
    }
    else
    {
      digitalWrite(RelayPin4, HIGH);
      toggleState_4 = 0;
    }
  }
}
