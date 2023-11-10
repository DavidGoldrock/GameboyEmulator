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

void CPU::setZFlag(bool Z) {
	if (Z) {
		this->AF.FLAGS |= 0b10000000;
	}
	else {
		this->AF.FLAGS &= 0b01111111;
	}
}

void CPU::setNFlag(bool N) {
	if (N) {
		this->AF.FLAGS |= 0b01000000;
	}
	else {
		this->AF.FLAGS &= 0b10111111;
	}
}

void CPU::setHFlag(bool H) {
	if (H) {
		this->AF.FLAGS |= 0b00100000;
	}
	else {
		this->AF.FLAGS &= 0b11011111;
	}
}

void CPU::setCFlag(bool C) {
	if (C) {
		this->AF.FLAGS |= 0b00010000;
	}
	else {
		this->AF.FLAGS &= 0b11101111;
	}
}

bool CPU::getZFlag() {
	return this->AF.FLAGS && 0b10000000 != 0;
}

bool CPU::getNFlag() {
	return this->AF.FLAGS && 0b01000000 != 0;
}

bool CPU::getHFlag() {
	return this->AF.FLAGS && 0b00100000 != 0;
}

bool CPU::getCFlag() {
	return this->AF.FLAGS && 0b00010000 != 0;
}