#include "osKernel.h"

uint32_t MILLIS_PRESCALER;
uint32_t period_tick;

struct tcb {
    int32_t *stackPt;
    struct tcb *nextPt;
};

typedef struct tcb tcbType;

tcbType tcbs[NUM_OF_THREADS];
tcbType *currentPt;

int32_t TCB_STACK[NUM_OF_THREADS][STACKSIZE];

void osKernelStackInit(int i) {
    tcbs[i].stackPt = &TCB_STACK[i][STACKSIZE - 16];
    TCB_STACK[i][STACKSIZE - 1] = (1U << 24); // Set bit 21 (T-bit) in PSR to 1, to operate in Thumb mode
}

uint8_t osKernelAddThread(TaskFunction task) {
    static int thread_index = 0;
    if (thread_index >= NUM_OF_THREADS) {
        // No more space for new threads
        return 0;
    }
    osKernelStackInit(thread_index);
    TCB_STACK[thread_index][STACKSIZE - 2] = (int32_t)(task); // Initial PC
    if (thread_index == 0) {
        // Start from thread0
        currentPt = &tcbs[0];
    }
    else {
        // Link the threads
        tcbs[thread_index - 1].nextPt = &tcbs[thread_index];
    }
    thread_index++;
    return 1;
}

void osKernelInit(void) {
    MILLIS_PRESCALER = (BUS_FREQ / 1000);
}

void osKernelLaunch(uint32_t quanta) {
    SysTick->CTRL = SYSTICK_RST; // Reset systick
    SysTick->VAL = 0; // Clear systick current value register
    SysTick->LOAD = (quanta * MILLIS_PRESCALER) - 1; // Load quanta
    NVIC_SetPriority(SysTick_IRQn, 15); // Set systick to low priority
    SysTick->CTRL = CTRL_CLCKSRC | CTRL_ENABLE; // Enable systick, select internal clock
    SysTick->CTRL |= CTRL_TICKINT; // Enable systick interrupt
    osSchedulerLaunch(); // Launch scheduler
}

__attribute__((naked)) void SysTick_Handler(void) {
    // SUSPEND CURRENT THREAD
    __asm("CPSID I"); // Disable global interrupts
    __asm("PUSH {R4-R11}"); // Save r4-r11
    __asm("LDR R0, =currentPt"); // Load address of currentPt into r0
    __asm("LDR R1,[R0]"); // Load r1 from address equals r0
    __asm("STR SP,[R1]"); // Store Cortex-M SP at address equals r1
    // CHOOSE NEXT THREAD
    __asm("PUSH {R0,LR}");
    __asm("BL osSchedulerRoundRobin");
    __asm("POP {R0,LR}");
    __asm("LDR R1,[R0]"); // R1 = currentPt i.e. New Thread
    __asm("LDR SP,[R1]"); // SP = currentPt->StackPt
    __asm("POP {R4-R11}"); // Restore r4-r11
    __asm("CPSIE I"); // Enable global interrupts
    // Return from exception and restore r0-r3, r12, lr, pc, psr
    __asm("BX LR");
}

void osSchedulerLaunch(void) {
    __asm("LDR R0, =currentPt"); // Load address of currentPt into R0
    __asm("LDR R2,[R0]"); // Load r2 from address equals r0
    __asm("LDR SP,[R2]"); // Load Cortex-M SP from address equals R2
    __asm("POP {R4-R11}"); // Restore r4-r11
    __asm("POP {R12}"); // Restore r12
    __asm("POP {R0-R3}"); // Restore r0-r3
    __asm("ADD SP, SP, #4"); // Skip LR
    __asm("POP {LR}"); // Create a new start location by popping LR
    __asm("ADD SP, SP, #4"); // Skip PSR
    __asm("CPSIE I"); // Enable global interrupts
    __asm("BX LR"); // Return from exception
}

void osThreadYield(void) {
    SysTick->VAL = 0; // Clear Systick Current Value register
    INTCTRL = PENDSTSET; // Trigger SysTick
}

void osSchedulerRoundRobin(void) {
    if ((++period_tick) == PERIOD) {
        // Do something
        period_tick = 0;
    }
    currentPt = currentPt->nextPt;
}

void tim2_1hz_interrupt_init(void) {
    RCC->APB1ENR |= TIM2EN; // Enable clock access to tim2
    TIM2->PSC = 1600 - 1; // Set timer prescaler
    TIM2->ARR = 10000 - 1; // Set auto-reload value
    TIM2->DIER |= DIER_UIE; // Enable update interrupt
    NVIC_SetPriority(TIM2_IRQn, 5); // Set interrupt priority
    NVIC_EnableIRQ(TIM2_IRQn); // Enable interrupt
    TIM2->CR1 |= CR1_CEN; // Enable timer
}
