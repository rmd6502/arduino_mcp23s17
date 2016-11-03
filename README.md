# MCP23S17 library

Drives this useful I/O port expander.  Example is provided for the PiFace,
which is how I tested this library.

## Example
Wire the Arduino up to the PiFace as follows (other boards you're on your own):
![Wiring Diagram](piface%20arduino%20wiring.png)

Create an MCP23S17 instance using new() or creating a static instance.

After that, you can use pinMode, digitalRead, and digitalWrite as you would 
normally, only instead of a pin number, you use instance.pin(number) as your pin.

Eventually I'll add support for shiftin, pulsein, etc. with the builtin interrupt
support.


## More advanced usage
For those who want more control, I provide setDDRx, readx, writex, and setPUx calls,
as well as sendByte and readByte to directly read and write registers numerically -
I defined the bank=0 register map as a enum for convenience.
