#ifdef TESTING_MODE
	#include "test_harness.h"
#else
	#include "WProgram.h"
	#include "spi4teensy3.h"
#endif

#include <vector>
#include <cmath>

using namespace std;

#define P_LED  14
#define P_BASE 16

void setup ()
{
	pinMode(P_LED, OUTPUT);
	for (int pin = P_BASE; pin < P_BASE + 8; ++pin) {
		pinMode(pin, OUTPUT);
	}
	digitalWriteFast(P_LED, HIGH);
	spi4teensy3::init();
	digitalWriteFast(P_LED, LOW);
}


int main (void)
{
	setup();
	uint8_t led_state = 1;
	uint8_t byte = 0;
	while (true) {
		digitalWriteFast(P_LED, led_state);

		for (int pin = P_BASE; pin < P_BASE + 8; ++pin) {
			uint8_t value = 1 & (byte >> (pin - P_BASE));
			digitalWriteFast(pin, value);
		}

		spi4teensy3::send(byte);
		++byte;
		spi4teensy3::receive();

		delay(10);

		led_state = !led_state;
	}
}
