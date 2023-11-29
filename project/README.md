   | **Instruction** | **Operation** | **Description** | **Cycles** |
   | :-- | :-: | :-- | :-: |
   | `add Rd, Rr` |  |  |  |
   | `andi Rd, K` | Rd = Rd and K | Logical AND between register Rd and 8-bit constant K | 1 |
   | `bld Rd, b` |  |  |  |
   | `bst Rd, b` |  |  |  |
   | `com Rd` |  |  |  |
   | `eor Rd, Rr` |  |  |  |
   | `mul Rd, Rr` |  |  |  |
   | `pop Rd` |  |  |  |
   | `push Rr` |  |  |  |
   | `ret` |  |  |  |
   | `rol Rd` |  |  |  |
   | `ror Rd` |  |  |  |

   4. Go through the `main.c` file and make sure you understand each line. Use **AVR® Instruction Set Manual** from Microchip [Online Technical Documentation](https://onlinedocs.microchip.com/), find the description of instructions used in `mac.S`, and complete the table.

   | **Instruction** | **Operation** | **Description** | **Cycles** |
   | :-- | :-: | :-- | :-: |
   | `add Rd, Rr` | Rd ← Rd + Rr | Adds two registers without the C Flag and places the result in the destination register Rd. | 1 |
   | `mul Rd, Rr` | R1:R0 ← Rd × Rr (unsigned ← unsigned × unsigned) | This instruction performs 8-bit × 8-bit → 16-bit unsigned multiplication.| 1 |
   | `ret` | PC(15:0) ← STACK | Returns from subroutine. The return address is loaded from the STACK. The Stack Pointer uses a preincrement scheme during RET | 4 devices with 16-bit PC |

5. Use manual's 16-bit Opcodes and convert used instructions to hexadecimal.

   | **Instruction** | **Binary opcode** | **Hex opcode** | **Compiler Hex opcode** |
   | :-- | :-: | :-: | :-: |
   | `add r24, r0` | `0001_1101_1000_0000` | `0d 80` | `80 0d` |
   | `mul r22, r20` | `1001_1111_0110_0100` | `9f 64` | `64 9f` |
   | `ret` | `1001_0101_0000_1000` | `95 08` | `08 95` |


   1. Consider a 4-bit shift register whose input (LSB bit) is formed by an XNOR gate with taps [4, 3] and the initial value is 0000 [[5]](https://www.edn.com/tutorial-linear-feedback-shift-registers-lfsrs-part-1/). Explore LFSR algorithm within `lfsr4_fibonacci_asm` assembly function, complete Timer1 overflow handler and generate 4-bit pseudo-random sequences for different Tap positions. How many states are generated for every settings?

   ![LFSR generation algo](images/flowchart_lfsr-value_algo.png)

   | **Tap position** | **Generated values** | **Length** |
   | :-: | :-- | :-: |
   | 4, 3 | `0 1 3 7 14 13 11 6 12 9 2 5 10 4 8` | 15 |
   | 4, 2 | `0 1 3 6 12 8` | 6 |
   | 4, 1 | `0 1 2 5 10 4 9 3 6 13 11 7 14 12 8` | 15 |

2. Change [LFSR tap positions](https://courses.cs.washington.edu/courses/cse369/15au/labs/xapp052_LFSRs.pdf) in `lfsr4_fibonacci_asm` function and generate 5-, 6-, and 7-bit versions of pseudorandom sequence. Do not forget to change the binary mask used to clear unused bits in input/output register.

   | **Tap position** | **Length** |
   | :-: | :-: |
   | 5,3 | 31 |
   | 6,5 | 63 |
   | 7,6 | 127 |


   ```c
/**
 * Doxygen will search this block
 */

/* 
 * Classic C block comment; Doxygen will not search it
 */
```