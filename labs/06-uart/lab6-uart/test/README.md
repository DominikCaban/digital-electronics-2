# Lab 6: Dominik Caban

### ASCII

1. Complete the table with selected ASCII codes.

   | **Char** | **Decimal** | **Hexadecimal** | **Binary** |
   | :-: | :-: | :-: | :-: |
   | `a` | 97 | 0x61 | `0b0110_0001` |
   | `b` | 98 | 0x62 | `0b0111_0010` |
   | `c` | 99 | 0x63 | `0b0111_0011` |
   | `0` | 48 | 0x30 | `0b0011_0000` |
   | `1` | 49 | 0x31 | `0b0011_0001` |
   | `2` | 50 | 0x32 | `0b0011_0010` |
   | `Esc` | 27 | 0x1b | `0b0011_1011` |
   | `Space` | 32 | 0x20 | `0b0100_0000` |
   | `Tab` | 9 | 0x9 | `0b0000_1001` |
   | `Backspace` | 127 | 0x7f | `0b0111_1111` |
   | `Enter` | 10 | 0x0a | `0b0000_1010` |

*Notes: 13 (DEC) is for Carriage return not for Enter.*
### UART communication

2. Draw timing diagram of the output from UART/USART when transmitting three character data `De2` in 4800 7O2 mode (7 data bits, odd parity, 2 stop bits, 4800&nbsp;Bd). The image can be drawn on a computer or by hand. Name all parts timing diagram.
###### Calculating bit time duration:
   ![duration](images/duration.png)

###### Converting table and parity calculation:
| **ASCII** | **HEX**  | **BIN** | **Counts of 1-bits** | **Odd parity** |
| :-: | :-: | :-: | :-: | :-: |
| D | 0x44 | 0b0100\_0100 | 2 | 1 |
| e | 0x65 | 0b0110\_0101 | 4 | 1 |
| 2 | 0x32 | 0b0011\_0010 | 3 | 0 |

   ![wavedorm](images/wavedrom2.svg)

     > The figure above was created in [WaveDrom](https://wavedrom.com/) digital timing diagram online tool. The figure source code is as follows (ticks -1, 10, 11 and 12 were manually adjusted afterwards):
  >
  ```javascript
 {
  signal:
  [
    {node: '.AB' },
 	{name: 'ASCII', wave: 'z4..........z4..........z4..........z', "data": "D e 2" },
    {name: 'Template', wave: 'z23333333355z23333333355z23333333355z', "data":"start D0 D1 D2 D3 D4 D5 D6 parity stop stop start D0 D1 D2 D3 D4 D5 D6 parity stop stop start D0 D1 D2 D3 D4 D5 D6 parity stop stop" },
    {name: 'UART 7o2', wave: 'x00010001111x01010011111x00100110011x', data: ["start", "body", "tail", "data"] },
    
  ],
      edge: [
 'A+B 0,2 ms'
  ]
}
  ```

3. Draw a flowchart for function `uint8_t get_parity(uint8_t data, uint8_t type)` which calculates a parity bit of input 8-bit `data` according to parameter `type`. The image can be drawn on a computer or by hand. Use clear descriptions of individual algorithm steps.

   ![FlowChart](images/FlowChart.png)