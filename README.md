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

This project is part of the C-DAC PG-DESD (Post Graduate Diploma in Embedded Systems Design) course. It is conducted under the guidance of **Nilesh Ghule**, Technical Director of Sunbeam. The project demonstrates how to create a simple operating system for the ARM Cortex-M STM32F446xx microcontroller without relying on any third-party libraries or RTOS. It includes basic task scheduling, interrupt handling, and synchronization primitives.

## Features

- **Task Scheduling:** Round-robin scheduling with configurable time quanta.
- **Interrupt Handling:** Timer-based interrupts for task switching.
- **Semaphores:** Binary semaphores for task synchronization.
- **Peripheral Control:** Basic control of GPIO and UART peripherals.
- **Assembly Integration:** Critical sections are handled using assembly for optimized performance.

## Prerequisites

- **Hardware:** STM32F446RE Nucleo Board
- **Software:** 
  - STM32CubeIDE
  - ARM GCC Compiler
  - STM32CubeMX (optional for configuration)

## Installation

1. **Clone the Repository:**
    ```bash
    git clone https://github.com/Omkar7637/STM32-BareMetalOS-Crafting-from-Scratch.git
    cd STM32-BareMetalOS-Crafting-from-Scratch
    ```

2. **Import the Project into STM32CubeIDE:**
   - Open **STM32CubeIDE**.
   - Go to **File > Import > Existing Projects into Workspace**.
   - Select the directory where you cloned the project.
   - Click **Finish** to import the project.

3. **Build the Project:**
   - In **STM32CubeIDE**, click on the **Build** icon or press `Ctrl+B` to compile the project.

4. **Flash the Firmware:**
   - Connect your **STM32 Nucleo Board**.
   - Click on the **Run/Debug** button in **STM32CubeIDE** to flash the firmware onto the microcontroller.

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

## Directory Structure

STM32-BareMetalOS-Crafting-from-Scratch/ ├── Inc/ │ ├── led.h │ ├── osKernel.h │ ├── uart.h ├── Src/ │ ├── led.c │ ├── main.c │ ├── osKernel.c ├── STM32F446RETX_FLASH.ld ├── STM32F446RETX_RAM.ld ├── Makefile ├── README.md


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
