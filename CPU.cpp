#include "CPU.h"


CPU::CPU() {
	this->AF = {0};
	this->BC = {0};
	this->DE = {0};
	this->HL = {0};
	this->SP = 0;
	this->PC = 0;
	this->isPrefixed = false;
}

u8 CPU::flagsFromData(bool Z, bool S, bool H, bool C) {
	u8 res = 0b00000000;
	if (Z) {
		res |= 0b10000000;
	}
	if (S) {
		res |= 0b01000000;
	}
	if (H) {
		res |= 0b00100000;
	}
	if (C) {
		res |= 0b00010000;
	}
	return res;
}