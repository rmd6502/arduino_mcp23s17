# MCP23S17 library

Drives this useful I/O port expander.  Example is provided for the PiFace,
which is how I tested this library.

## Example
Wire the Arduino up to the PiFace as follows (other boards you're on your own):
![Wiring Diagram](piface%20arduino%20wiring.png)

Note that 5V is connected to pins 1 and 2 on the piface, so the relays and the
chip are powered from 5V.  If using a 3.3V system, connect 3.3V to pin 1 and 5V
to pin 2.

Create an MCP23S17 instance using new() or creating a static instance.

After that, you can use pinMode, digitalRead, and digitalWrite as you would 
normally, only instead of a pin number, you use instance.pin(number) as your pin.

Eventually I'll add support for shiftin, pulsein, etc. with the builtin interrupt
support.  While shiftin and shiftout use digitalRead and digitalWrite behind the
scenes, I'll need to reimplement them to take MCP23S17Pin instead of uint8_t.


## More advanced usage
For those who want more control, I provide setDDRx, readx, writex, and setPUx calls,
as well as sendByte and readByte to directly read and write registers numerically -
I defined the bank=0 register map as a enum for convenience.
