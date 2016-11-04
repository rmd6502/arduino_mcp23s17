#ifndef __MCP23S17_H
#define __MCP23S17_H

#include "Arduino.h"

// IOCON.BANK=0
enum MCP_REGISTERS {
  MCP_DDRA,
  MCP_DDRB,
  MCP_IPOLA,
  MCP_IPOLB,
  MCP_GPINTENA,
  MCP_GPINTENB,
  MCP_DEFVALA,
  MCP_DEFVALB,
  MCP_INTCONA,
  MCP_INTCONB,
  MCP_IOCONA,
  MCP_IOCONB,
  MCP_PUA,
  MCP_PUB,
  MCP_INTFA,
  MCP_INTFB,
  MCP_INTCAPA,
  MCP_INTCAPB,
  MCP_GPIOA,
  MCP_GPIOB,
  MCP_OLATA,
  MCP_OLATB
};

const uint8_t NUM_PINS = 16;
// pin number for invalid pins
const uint8_t DUMMY_PIN = NUM_PINS;

class MCP23S17Pin;

class MCP23S17 {
  friend class MCP23S17Pin;
  public:
    MCP23S17(uint8_t addr=0, uint8_t spics=10);
    void setDDRA(uint8_t ddra);
    void setDDRB(uint8_t ddrb);
    uint8_t readA();
    uint8_t readB();
    void writeA(uint8_t value);
    void writeB(uint8_t value);
    void setPUA(uint8_t pua);
    void setPUB(uint8_t pub);

    void sendByte(uint8_t reg, uint8_t value);
    uint8_t readByte(uint8_t reg);

    // Will return NULL for invalid pin - check before using one of the functions below!
    MCP23S17Pin &pin(uint8_t pinNumber);

  private:
    uint8_t address;
    uint8_t spics;
    MCP23S17Pin *pins[NUM_PINS + 1];
};

class MCP23S17Pin {
  friend class MCP23S17;
  private:
    MCP23S17 *parent;
    uint8_t pin;
  protected:
    MCP23S17Pin(MCP23S17 *parent, uint8_t pinNumber);
  public:
    void setPinMode(uint8_t mode);
    void writePin(uint8_t value);
    uint8_t readPin();
};

// Overloads of existing Arduino functions for convenience
void pinMode(MCP23S17Pin& pin, uint8_t mode);
void digitalWrite(MCP23S17Pin& pin, uint8_t value);
uint8_t digitalRead(MCP23S17Pin& pin);
uint8_t shiftIn(MCP23S17Pin& dataPin, MCP23S17Pin& clockPin, uint8_t bitOrder);
void shiftOut(MCP23S17Pin& dataPin, MCP23S17Pin& clockPin, uint8_t bitOrder, uint8_t val);

#endif // __MCP23S17_H
