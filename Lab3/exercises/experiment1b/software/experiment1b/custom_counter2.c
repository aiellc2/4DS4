#include "define.h"

// ISR when the counter is expired
void handle_counter_expire_interrupts2()
{
	printf("Counter expires\n");

	IOWR(CUSTOM_COUNTER_COMPONENT2_0_BASE, 2, 0);
}

void reset_counter2() {
	printf("Resetting counter value\n");

	IOWR(CUSTOM_COUNTER_COMPONENT2_0_BASE, 1, 1);
	IOWR(CUSTOM_COUNTER_COMPONENT2_0_BASE, 1, 0);

	IOWR(CUSTOM_COUNTER_COMPONENT2_0_BASE, 2, 0);
}

int read_counter2() {
	return IORD(CUSTOM_COUNTER_COMPONENT2_0_BASE, 0);
}

int read_counter_interrupt2() {
	return IORD(CUSTOM_COUNTER_COMPONENT2_0_BASE, 2);
}

void load_counter_config2(int config) {
	printf("Loading counter config %d\n", config);

	IOWR(CUSTOM_COUNTER_COMPONENT2_0_BASE, 3, config);
}

// Function for initializing the ISR of the Counter
void init_counter_irq2() {
	IOWR(CUSTOM_COUNTER_COMPONENT2_0_BASE, 2, 0);

	alt_irq_register(CUSTOM_COUNTER_COMPONENT2_0_IRQ, NULL, (void*)handle_counter_expire_interrupts );
}