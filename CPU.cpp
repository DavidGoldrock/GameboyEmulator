#include "CPU.h"


CPU::CPU() {
	this->AF = {0};
	this->BC = {0};
	this->DE = {0};
	this->HL = {0};
	this->SP = 0;
	this->PC = 0;
}