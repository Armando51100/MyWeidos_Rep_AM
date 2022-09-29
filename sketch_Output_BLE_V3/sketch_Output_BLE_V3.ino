#include <ArduinoBLE.h>

// This sketch to control the Weidos with a phone, using an App like LightBlue (using value write), or better BluetoothforArduino (using switch with setting On to 1 and Off to 0)
// While connected with the phone pin58 turns on
// When write value is different from 0 it turns pin55, and blink 2 time pin56 & pin57, then pin56 stays on and pin57 stays off

BLEService ledService("19B10000-E8F2-537E-4F6C-D104768A1214"); // Bluetooth® Low Energy LED Service

// Bluetooth® Low Energy LED Switch Characteristic - custom 128-bit UUID, read and writable by central
BLEByteCharacteristic switchCharacteristic("19B10001-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite);


void setup() {

  // begin initialization
  if (!BLE.begin()) {

    while (1);
  }

  // set advertised local name and service UUID:
  BLE.setLocalName("LED");
  BLE.setAdvertisedService(ledService);

  // add the characteristic to the service
  ledService.addCharacteristic(switchCharacteristic);

  // add service
  BLE.addService(ledService);

  // set the initial value for the characeristic:
  switchCharacteristic.writeValue(0);

  // start advertising
  BLE.advertise();

}

void loop() {
  // listen for Bluetooth® Low Energy peripherals to connect:
  BLEDevice central = BLE.central();

  // if a central is connected to peripheral:
   if (central) {

    // while the central is still connected to peripheral:
    while (central.connected()) {
        digitalWrite(pin58, HIGH);
      // if the remote device wrote to the characteristic,
      // use the value to control the LED:
      if (switchCharacteristic.written()) {
        if (switchCharacteristic.value()!=48) {   // any value other than 0
        // will turn the LED on or off
          digitalWrite(pin55, HIGH);
          digitalWrite(pin56, HIGH);
          digitalWrite(pin57, LOW);
          delay(1000);
          digitalWrite(pin56, LOW);
          digitalWrite(pin57, HIGH);
          delay(1000);
          digitalWrite(pin56, HIGH);
          digitalWrite(pin57, LOW);
          delay(1000);
          digitalWrite(pin56, LOW);
          digitalWrite(pin57, HIGH);
          delay(1000);
          digitalWrite(pin56, HIGH);
          digitalWrite(pin57, LOW);
        } else {                              // a 0 value
  
        // will turn the LED off
          digitalWrite(pin55, LOW);
          digitalWrite(pin56, LOW);
          digitalWrite(pin57, LOW);
        }
      }
    }
          digitalWrite(pin58, LOW);

   }
}
