#include "MCP23S17.h"

MCP23S17 mcp23s17;

void setup() {
  /*
  mcp23s17.setDDRA(0);
  mcp23s17.setDDRB(0xff);
  mcp23s17.writeA(0);
  mcp23s17.setPUB(0xff);
  */
  Serial.begin(115200);
  int i;
  for (i=0; i < 8; ++i) {
    pinMode(*mcp23s17.pin(i), OUTPUT);
  }

  for (i=8; i < 12; ++i) {
    pinMode(*mcp23s17.pin(i), INPUT_PULLUP);
  }

  Serial.println("ready");
}

void loop() {
  static uint8_t v[4] = {1,1,1,1};
  uint8_t v2;
  uint8_t i;
  for (i=8; i < 12; ++i) {
    v2 = digitalRead(*mcp23s17.pin(i));
    if (v[i-8] != v2) {
      Serial.print("pin "); Serial.print(i); Serial.print(" = "); Serial.println(v2);
      v[i-8] = v2;
    }
  }
  digitalWrite(*mcp23s17.pin(2), HIGH);
  
  digitalWrite(*mcp23s17.pin(2), LOW);
  
}
