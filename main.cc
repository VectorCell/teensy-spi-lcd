#ifdef TESTING_MODE
	#include "test_harness.h"
#else
	#include "WProgram.h"
#endif

#include <vector>
#include <cmath>

using namespace std;

#define P_LED  13

void setup ()
{
	pinMode(P_LED, OUTPUT);
}


int main (void)
{
	setup();
	while (true) {
		
		digitalWriteFast(P_LED, HIGH);
		delay(500);
		digitalWriteFast(P_LED, LOW);
		delay(500);
	}
}
