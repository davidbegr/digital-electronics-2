## Pre-Lab preparation

1. Use schematic of the [LCD keypad shield](https://oshwlab.com/tomas.fryza/arduino-shields) and find out the connection of LCD display. What data and control signals are used? What is the meaning of these signals?

   | **LCD signal(s)** | **AVR pin(s)** | **Description** |
   | :-: | :-: | :-- |
   | RS | PB0 | Register selection signal. Selection between Instruction register (RS=0) and Data register (RS=1) |
   | R/W | GND | R/W signal is used to specify the direction of data transfer |
   | E | PB1 |  E signal is used to enable data or command transfers to the LCD |
   | D[3:0] | None | These are the data lines for transferring 4-bit data to/from the LCD |
   | D[7:4] | PB[7:4] | These are the data lines for transferring 4-bit data to/from the LCD |
   | K | PB2 | K signal is used for controlling the backlight of the LCD |

2. What is the ASCII table? What are the codes/values for uppercase letters `A` to `E`, lowercase letters `a` to `e`, and numbers `0` to `4` in this table?

   | **Char** | **Decimal** | **Hexadecimal** |
   | :-: | :-: | :-: |
   | `A` | 65 | 0x41 |
   | `B` | 66 | 0x42 |
   | `C` | 67 | 0x43 |
   | `D` | 68 | 0x44 |
   | `E` | 69 | 0x45 |
   | `a` | 97 | 0x61 |
   | `b` | 98 | 0x62 |
   | `c` | 99 | 0x63 |
   | `d` | 100 | 0x64 |
   | `e` | 101 | 0x65 |
   | `0` | 48 | 0x30 |
   | `1` | 49 | 0x31 |
   | `2` | 50 | 0x32 |
   | `3` | 51 | 0x33 |
   | `4` | 52 | 0x34 |
