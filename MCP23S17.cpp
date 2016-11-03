#include <SPI.h>

#include "MCP23S17.h"

MCP23S17::MCP23S17(uint8_t addr, uint8_t spics) {
  memset(pins, 0, sizeof(pins));
  SPI.begin();
  SPI.setClockDivider(SPI_CLOCK_DIV2);
  address = addr;
  this->spics = spics;
  digitalWrite(spics, HIGH);
  pinMode(spics, OUTPUT);
}

void MCP23S17::setDDRA(uint8_t ddra) {
  sendByte(MCP_DDRA, ddra);
}

void MCP23S17::setDDRB(uint8_t ddrb) {
  sendByte(MCP_DDRB, ddrb);
}

uint8_t MCP23S17::readA() {
  return readByte(MCP_GPIOA);
}

uint8_t MCP23S17::readB() {
  return readByte(MCP_GPIOB);
}

void MCP23S17::writeA(uint8_t value) {
  sendByte(MCP_GPIOA, value);
}

void MCP23S17::writeB(uint8_t value) {
  sendByte(MCP_GPIOB, value);
}
    
void MCP23S17::setPUA(uint8_t pua) {
  sendByte(MCP_PUA, pua);
}

void MCP23S17::setPUB(uint8_t pub) {
  sendByte(MCP_PUB, pub);
}

void MCP23S17::sendByte(uint8_t reg, uint8_t value) {
  uint8_t control = 0x40 | (address << 1);

  digitalWrite(spics, LOW);
  SPI.transfer(control);
  SPI.transfer(reg);
  SPI.transfer(value);
  digitalWrite(spics, HIGH);
}

uint8_t MCP23S17::readByte(uint8_t reg) {
  uint8_t control = 0x40 | (address << 1) | 1;
  uint8_t result;
  digitalWrite(spics, LOW);
  SPI.transfer(control);
  SPI.transfer(reg);
  result = SPI.transfer(0);
  digitalWrite(spics, HIGH);
  return result;
}

MCP23S17Pin* MCP23S17::pin(uint8_t pinNumber) {
  if (pinNumber < 16) {
    if (pins[pinNumber] == NULL) {
      pins[pinNumber] = new MCP23S17Pin(this, pinNumber);
    }
    return pins[pinNumber];
  } else {
    return NULL;
  }
}

  MCP23S17Pin::MCP23S17Pin(MCP23S17 *parent, uint8_t pinNumber) {
    this->parent = parent;
    this->pin = pinNumber;
  }
  
  void MCP23S17Pin::setPinMode(uint8_t mode) {
    uint8_t modeReg = (pin > 7) ? MCP_DDRB : MCP_DDRA;
    uint8_t pullupReg = (pin > 7) ? MCP_PUB : MCP_PUA;
    uint8_t mask = 1 << (pin & 7);
    uint8_t val = parent->readByte(modeReg);
    uint8_t puVal = parent->readByte(pullupReg);
    if (mode == INPUT || mode == INPUT_PULLUP) {
      val |= mask;
    } else {
      val &= ~mask;
    }
    if (mode == INPUT_PULLUP) {
      puVal |= mask;
    } else {
      puVal &= ~mask;
    }
    parent->sendByte(modeReg, val);
    parent->sendByte(pullupReg, puVal);
  }
  void MCP23S17Pin::writePin(uint8_t value) {
    uint8_t gpioReg = (pin > 7) ? MCP_GPIOB : MCP_GPIOA;
    uint8_t mask = 1 << (pin & 7);
    uint8_t val = parent->readByte(gpioReg);

    if (value == HIGH) {
      val |= mask;
    } else {
      val &= ~mask;
    }
    parent->sendByte(gpioReg, val);
  }
  
  uint8_t MCP23S17Pin::readPin() {
    uint8_t gpioReg = (pin > 7) ? MCP_GPIOB : MCP_GPIOA;
    uint8_t mask = 1 << (pin & 7);
    uint8_t val = parent->readByte(gpioReg) & mask;

    return (val == 0) ? LOW : HIGH;
  }

void pinMode(MCP23S17Pin& pin, uint8_t mode) {
  pin.setPinMode(mode);
}
void digitalWrite(MCP23S17Pin& pin, uint8_t value) {
  pin.writePin(value);
}
uint8_t digitalRead(MCP23S17Pin& pin) {
  return pin.readPin();
}

