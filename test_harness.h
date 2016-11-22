#pragma once

#include <vector>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <csignal>

using namespace std;


#define PI M_PI

#define INPUT  0
#define OUTPUT 1

#define LOW    0
#define HIGH 255


class TestEnvironment
{

private:

	typedef struct pin_struct {
		int id;
		int state;
		int mode;
		pin_struct(int i, int s, int mode) : id(i), state(s), mode(s) {}
	} pin_type;

	vector<pin_type> pins;


public:

	TestEnvironment() {}

	void setPinMode (int id, int mode)
	{
		int index = -1;
		for (int k = 0; k < (int)pins.size(); ++k) {
			if (pins[k].id == id) {
				index = k;
				break;
			}
		}
		if (index == -1) {
			index = (int)pins.size();
			pins.push_back(pin_type(id, LOW, mode));
		} else {
			pins[index].mode = mode;
		}
	}

	int& getPinState (int id)
	{
		int index = -1;
		for (int k = 0; k < (int)pins.size(); ++k) {
			if (pins[k].id == id) {
				index = k;
				break;
			}
		}
		return pins[index].state;
	}

	void setPinState (int id, int state)
	{
		getPinState(id) = state;
	}
};


class SerialEmulator
{

public:

	void begin (int baud)
	{
		printf("initializing Serial with baud rate: %d\n", baud);
	}

	void println ()
	{
		printf("\n");
	}

	void println (const char *str)
	{
		printf("%s\n", str);
	}

	void println (int n)
	{
		printf("%d\n", n);
	}
};


TestEnvironment env;
SerialEmulator Serial;


void analogWrite (int pin, int state)
{
	//printf("analogWrite(%d, %d)\n", pin, state);
	env.setPinState(pin, state);
}

int analogRead (int pin)
{
	//printf("analogRead(%d)\n", pin);
	return rand() % 1024;
	//return env.getPinState(pin);
}

void pinMode (int pin, int mode)
{
	//printf("pinMode(%d)\n", pin);
	env.setPinMode(pin, mode);
}

void digitalWrite (int pin, int state)
{
	//printf("digitalWrite(%d, %s)\n", pin, state ? "HIGH" : "LOW");
	env.setPinState(pin, state ? HIGH : LOW);
}

void digitalWriteFast (int pin, int state)
{
	digitalWrite(pin, state);
}

int digitalRead (int pin)
{
	//printf("digitalRead(%d)\n", pin);
	return env.getPinState(pin) ? 0 : 1;
}

void delay (int ms)
{
	this_thread::sleep_for(chrono::milliseconds(ms));
}

static void signal_handler (int signo)
{
	if (signo == SIGINT) {
		printf("exiting due to received SIGINT\n");
		exit(0);
	}
	if (signo == SIGTERM) {
		printf("exiting due to received SIGTERM\n");
		exit(0);
	}
}

void set_signal_handlers ()
{
	signal(SIGINT, signal_handler);
	signal(SIGTERM, signal_handler);
}
