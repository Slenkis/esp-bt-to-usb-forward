#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

#define DEBUG_PORT Serial
#define ELM_PORT   SerialBT

String btName = "OBD II";

void setup() {
  DEBUG_PORT.begin(115200);
  ELM_PORT.setPin("1234");
  ELM_PORT.begin("BT", true);

  DEBUG_PORT.println("Connection to " + btName + "...");

  if (ELM_PORT.connect(btName))
    DEBUG_PORT.println("Connected!");
  else
    DEBUG_PORT.println("Couldn't connect to " + btName);
}


void loop() {
  if (ELM_PORT.hasClient()) {
    if (DEBUG_PORT.available()) {
      char c = DEBUG_PORT.read();
      ELM_PORT.write(c);
    }

    if (ELM_PORT.available()) {
      char c = ELM_PORT.read();
      DEBUG_PORT.write(c);
    }
  } else {
    ELM_PORT.connect(btName);
  }
}
