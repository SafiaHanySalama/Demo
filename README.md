# ARM Project

## Description

This project is a comprehensive ARM-based application designed to run on an STM32F401CC microcontroller. It includes several modules and functionalities, such as LCD display, UART communication, clock, and stopwatch.

## Getting Started

### Dependencies

* STM32Cube MCU Package for STM32F4 series
* ARM GCC toolchain
* PlatformIO or other ARM-compatible development environment

### Installing

* Clone the repository: `git clone [url]`
* Navigate to the project directory: `cd [project directory]`
* Open the project in your development environment.

### Building and Running

* Uncomment the application you want to run in `main.c`.
* Build the project using your development environment's build command.
* Upload the built firmware to your STM32F401CC microcontroller.
* Monitor the output using a serial monitor or debugger.
## Applications

This project includes several applications that demonstrate different functionalities of the STM32F401CC microcontroller. To run an application, uncomment the corresponding function call in `main.c`.

* `LCD_Test()`: This function display the date,clock and stopwatch.
* `MCU1_SwitchesTx()`: This function handles the transmission of switch states.
* `MCU1_UARTSignalRx()`: This function handles the reception of UART signals.
* `MCU1_Clock()`: This function implements a digital clock.
* `MCU1_StopWatch()`: This function implements a stopwatch.

## Authors

[Your Name]
[Your Contact Info]

## Version History

* 0.1
    * Initial Release

## License
