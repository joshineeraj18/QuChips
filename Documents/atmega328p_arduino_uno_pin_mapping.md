
# ATmega328P to Arduino Uno Pin Mapping

This document provides a clear mapping between the ATmega328P microcontroller pins and the corresponding Arduino Uno board pin names and their main functions.

| **ATmega328P Pin** | **Arduino Uno Pin**     | **Function(s)**                    |
|--------------------|-------------------------|------------------------------------|
| 1                  | -                       | PC6 (RESET)                        |
| 2                  | D0 (RX)                 | PD0 (UART RX)                      |
| 3                  | D1 (TX)                 | PD1 (UART TX)                      |
| 4                  | D2                      | PD2 (INT0)                         |
| 5                  | D3 (PWM)                | PD3 (INT1 / OC2B)                  |
| 6                  | D4                      | PD4 (T0 / XCK)                     |
| 7                  | D5 (PWM)                | PD5 (T1 / OC0B)                    |
| 8                  | D6 (PWM)                | PD6 (AIN0 / OC0A)                  |
| 9                  | D7                      | PD7 (AIN1)                         |
| 10                 | D8                      | PB0 (ICP1)                         |
| 11                 | D9 (PWM)                | PB1 (OC1A)                         |
| 12                 | D10 (PWM / SS)          | PB2 (SS / OC1B)                    |
| 13                 | D11 (PWM / MOSI)        | PB3 (MOSI / OC2A)                  |
| 14                 | D12 (MISO)              | PB4 (MISO)                         |
| 15                 | D13 (SCK, LED)          | PB5 (SCK)                          |
| 16                 | AREF                    | Analog Reference                   |
| 17                 | GND                     | Ground                             |
| 18                 | A0                      | PC0 (ADC0)                         |
| 19                 | A1                      | PC1 (ADC1)                         |
| 20                 | A2                      | PC2 (ADC2)                         |
| 21                 | A3                      | PC3 (ADC3)                         |
| 22                 | A4 (SDA)                | PC4 (ADC4 / SDA)                   |
| 23                 | A5 (SCL)                | PC5 (ADC5 / SCL)                   |
| 28                 | -                       | AVCC                               |
| 9, 10              | -                       | XTAL1, XTAL2 (External Crystal)    |

## Notes

- This table is specific to **ATmega328P used on the Arduino Uno**.
- Pins labeled as PWM support analogWrite().
- UART, I2C, and SPI interfaces are identified for reference in communication-based applications.
