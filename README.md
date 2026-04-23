# STM32 Bare-Metal OS - Crafting from Scratch

![Platform](https://img.shields.io/badge/Platform-STM32F446RE-blue)
![Core](https://img.shields.io/badge/Core-ARM%20Cortex--M4-informational)
![Toolchain](https://img.shields.io/badge/Toolchain-arm--none--eabi--gcc-success)
![IDE](https://img.shields.io/badge/IDE-STM32CubeIDE-orange)
![Style](https://img.shields.io/badge/Project%20Type-Bare%20Metal%20Kernel-important)

An educational bare-metal OS project for STM32 that builds RTOS fundamentals from first principles: startup flow, context switching, scheduler design, periodic tasks, and semaphore-based synchronization.

The repository is intentionally organized as milestone versions so anyone reviewing it can see technical growth over time.

---

## Why This Project Stands Out

- Designed and implemented without FreeRTOS or third-party scheduler middleware.
- Demonstrates low-level Cortex-M exception and stack-frame behavior.
- Shows progression from manual context switching to dynamic thread creation.
- Combines C + inline assembly where performance/control matters.
- Uses STM32CubeIDE-compatible project layout so it can be built and debugged immediately.

---

## Demo Snapshot

![Project Snapshot](./Screenshot%20from%202024-08-09%2014-27-43_1.png)

---

## Milestone Timeline

| Version | Focus Area | Key Outcome |
|---|---|---|
| `V1` | Baseline setup | Initial project scaffolding |
| `V1_1_Manual_Context_Switching` | Manual task switching | Understand stack/register restore path |
| `V1_2_Round_Robin` | Preemptive scheduler | Core round-robin task rotation |
| `V1_3_CooperativeScheduler` | Cooperative model | Explicit thread yielding (`osThreadYield`) |
| `V1_4_PeriodicScheduler_v1` | Periodic execution | Fixed-rate periodic work integration |
| `V1_5_PeriodicScheduler_v2` | Timer-driven refinement | Improved periodic scheduling behavior |
| `V1_6_SpinlockSemaphore` | Synchronization | Semaphore wait/set usage in task flow |
| `V1_7_DYANMIC_TASK_CREATION` | Dynamic threads | Runtime thread creation with allocated stacks |

---

## Repository Structure

```text
STM32-BareMetalOS-Crafting-from-Scratch/
|- Chip_headers/                      # CMSIS + STM32 device headers
|- V1/
|- V1_1_Manual_Context_Switching/
|- V1_2_Round_Robin/
|- V1_3_CooperativeScheduler/
|- V1_4_PeriodicScheduler_v1/
|- V1_5_PeriodicScheduler_v2/
|- V1_6_SpinlockSemaphore/
|- V1_7_DYANMIC_TASK_CREATION/       # Latest milestone
|  |- Inc/
|  |- Src/
|  |- Startup/
|  |- STM32F446RETX_FLASH.ld
|  `- STM32F446RETX_RAM.ld
`- README.md
```

---

## Hardware and Toolchain

- **Board:** STM32 NUCLEO-F446RE
- **MCU:** STM32F446RETx (ARM Cortex-M4)
- **IDE:** STM32CubeIDE
- **Compiler:** `arm-none-eabi-gcc`
- **Debugger/Programmer:** ST-LINK (GDB server via CubeIDE)

---

## Build and Flash

1. Clone:
   ```bash
   git clone https://github.com/Omkar7637/STM32-BareMetalOS-Crafting-from-Scratch.git
   cd STM32-BareMetalOS-Crafting-from-Scratch
   ```
2. Open STM32CubeIDE.
3. Import any milestone folder as an existing project.
4. Build (`Ctrl+B`).
5. Connect NUCLEO board and run/debug using ST-LINK.

Recommended starting point: **`V1_2_Round_Robin`**, then continue in milestone order.

---

## Latest Architecture (`V1_7_DYANMIC_TASK_CREATION`)

### Core Components

- **Startup + Vector Table:** `Startup/startup_stm32f446retx.s`
- **Kernel API:** `Inc/osKernel.h`
- **Kernel implementation:** `Src/osKernel.c`
- **Application tasks:** `Src/main.c`
- **Memory layout:** `STM32F446RETX_FLASH.ld`

### Execution Flow

```text
Reset_Handler
   -> C runtime init (.data/.bss)
   -> main()
      -> uart_tx_init()
      -> tim2_1hz_interrupt_init()
      -> initializeSemaphores()
      -> osKernelInit()
      -> osKernelAddThreads(...) + osKernelAddThread(...)
      -> osKernelLaunch(QUANTA)
         -> SysTick configured
         -> first task launched
         -> SysTick_Handler performs context switch continuously
```

### Context Switching (High Level)

- SysTick interrupt triggers `SysTick_Handler`.
- Current thread state is preserved (`R4-R11`, stack pointer).
- Scheduler selects next TCB in round-robin order.
- Next thread state is restored and execution resumes.

---

## Kernel API (Current Milestone)

From `V1_7_DYANMIC_TASK_CREATION/Inc/osKernel.h`:

- `osKernelInit()`
- `osKernelLaunch(uint32_t quanta)`
- `osKernelAddThreads(void(*task0)(void), void(*task1)(void), void(*task2)(void))`
- `osKernelAddThread(void(*task)(void))`
- `osThreadYield()`
- `osSemaphoreInit(int32_t *semaphore, int32_t value)`
- `osSemaphoreSet(int32_t *semaphore)`
- `osSemaphoreWait(int32_t *semaphore)`

---

## Example Runtime Setup

The latest `main.c` initializes peripherals, kernel, semaphores, and launches multiple threads:

```c
uart_tx_init();
tim2_1hz_interrupt_init();
initializeSemaphores();

osKernelInit();
osKernelAddThreads(&task0, &task1, &task2);
osKernelAddThread(&task7);
osKernelAddThread(&task4);
osKernelAddThread(&task5);
osKernelAddThread(&task6);
osKernelLaunch(QUANTA);
```

---

## Professional Talking Points (For Recruiters/Interviewers)

- Implemented a thread scheduler and context-switch path at register/stack level.
- Built synchronization primitives and demonstrated producer/consumer-like flow.
- Worked directly with Cortex-M exceptions (`SysTick`, timer IRQs).
- Used linker/startup fundamentals and memory-map aware development.
- Structured work as versioned milestones to show engineering progression.

---

## Limitations and Improvement Opportunities

- Educational design; not yet production-hardened RTOS.
- Semaphore wait uses busy waiting (can be replaced with blocked/wakeup scheduling).
- Dynamic thread creation allocates stacks but currently lacks delete/reclaim APIs.
- No automated CI/test harness yet (manual hardware validation flow).

---

## Recommended Learning Path

1. `V1_1_Manual_Context_Switching`
2. `V1_2_Round_Robin`
3. `V1_3_CooperativeScheduler`
4. `V1_4_PeriodicScheduler_v1`
5. `V1_5_PeriodicScheduler_v2`
6. `V1_6_SpinlockSemaphore`
7. `V1_7_DYANMIC_TASK_CREATION`

---

## Contribution Guide

Contributions are welcome.

1. Fork the repo
2. Create a branch (`feature/<name>`)
3. Make focused changes with clear commit messages
4. Validate build and flash on target board
5. Open a pull request

---

## Contact

Created by [Omkar7637](https://github.com/Omkar7637) as part of the C-DAC PG-DESD learning journey under the guidance of Nilesh Ghule.
