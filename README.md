# STM32 Bare Metal OS

This project involves crafting a bare-metal operating system from scratch for the ARM Cortex-M STM32F446xx microcontroller. The OS supports basic task management and semaphore-based synchronization.

## Table of Contents

- [Introduction](#introduction)
- [Features](#features)
- [Prerequisites](#prerequisites)
- [Installation](#installation)
- [Usage](#usage)
- [Directory Structure](#directory-structure)
- [Contributing](#contributing)
- [License](#license)
- [Contact](#contact)

## Introduction

This project is part of the C-DAC PG-DESD (Post Graduate Diploma in Embedded Systems Design) course, which I am pursuing at Sunbeam Institute. The project is conducted under the guidance of Nilesh Ghule, the Technical Director of Sunbeam. It demonstrates how to create a simple operating system for the ARM Cortex-M STM32F446xx microcontroller without relying on any third-party libraries or RTOS. It includes basic task scheduling, interrupt handling, and synchronization primitives.

## Features

- **Task Scheduling:** Round-robin scheduling with configurable time quanta.
- **Interrupt Handling:** Timer-based interrupts for task switching.
- **Semaphores:** Binary semaphores for task synchronization.
- **Peripheral Control:** Basic control of GPIO and UART peripherals.

## Prerequisites

- **Hardware:** STM32F446RE Nucleo Board
- **Software:** 
  - ARM GCC Compiler
  - STM32CubeMX (optional for configuration)
  - OpenOCD (for flashing and debugging)

## Installation

1. **Clone the Repository:**
    ```bash
    git clone https://github.com/Omkar7637/STM32-BareMetalOS-Crafting-from-Scratch.git
    cd STM32-BareMetalOS-Crafting-from-Scratch
    ```

2. **Build the Project:**
    ```bash
    make
    ```

3. **Flash the Firmware:**
    ```bash
    openocd -f interface/stlink.cfg -f target/stm32f4x.cfg -c "program build/STM32-BareMetalOS.elf verify reset exit"
    ```

## Usage

1. **Initialize and Configure UART:**
    ```c
    uart_tx_init();
    ```

2. **Initialize the Hardware Timer:**
    ```c
    tim2_1hz_interrupt_init();
    ```

3. **Initialize Semaphores:**
    ```c
    initializeSemaphores();
    ```

4. **Initialize the Kernel and Add Tasks:**
    ```c
    osKernelInit();
    osKernelAddThreads(&task0, &task1, &task2);
    osKernelAddThread(&task7);
    osKernelAddThread(&task4);
    osKernelAddThread(&task5);
    osKernelAddThread(&task6);
    ```

5. **Launch the Kernel:**
    ```c
    osKernelLaunch(QUANTA);
    ```
    
## Contributing

Contributions are welcome! Please follow these steps:

1. Fork the repository.
2. Create a new branch (`git checkout -b feature-branch`).
3. Make your changes.
4. Commit your changes (`git commit -m 'Add some feature'`).
5. Push to the branch (`git push origin feature-branch`).
6. Open a pull request.

## License

## Contact

Created by [Omkar7637](https://github.com/Omkar7637). This project is part of the C-DAC PG-DESD course under the guidance of Nilesh Ghule, Technical Director of Sunbeam. Feel free to contact me for any queries.
