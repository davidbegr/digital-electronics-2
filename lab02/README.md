# Pre lab preparations
   | **Data type** | **Number of bits** | **Range** | **Description** |
   | :-: | :-: | :-: | :-- |
   | `uint8_t`  | 8 | 0, 1, ..., 255 | Unsigned 8-bit integer |
   | `int8_t`   | 8 | -128 to +127 | Signed 8-bit integer |
   | `uint16_t` | 16* | 0 to 65535 | Unsigned 16-bit integer |
   | `int16_t`  | 16* | -32768 to 32 767 | Signed 16-bit integer |
   | `float`    | 32 | -3.4e+38, ..., 3.4e+38 | Single-precision floating-point |
   | `void`     | 0 | 0 | Empty value we use in functions, usually takes 1 byte of storage |
> found on [quora](https://www.quora.com/What-is-the-definition-of-the-void-data-type-in-C) and [studytonight](https://www.studytonight.com/c/datatype-in-c.php)
# LAB 02
| **Version** | **Size [B]** |
   | :-- | :-: |
   | Ver. 1: Arduino-style | 508 |
   | Ver. 2: Registers | 182 |
   | Ver. 3: Library functions | 182 |

   | **DDRB** | **PORTB** | **Direction** | **Internal pull-up resistor** | **Description** |
   | :-: | :-: | :-: | :-: | :-- |
   | 0 | 0 | input | no | Tri-state, high-impedance |
   | 0 | 1 | input | yes | Pxn will source current if ext. pulled low |
   | 1 | 0 | output | no | Output low (sink) |
   | 1 | 1 | output | no | Output high (source) |