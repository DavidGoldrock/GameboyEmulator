#include "CPU.h"

CPU::CPU()
{
	this->AF = {0};
	this->BC = {0};
	this->DE = {0};
	this->HL = {0};
	this->SP = 0;
	this->PC = 0;
	this->e8 = 0;
	this->n8 = 0;
	this->a8 = 0;
	this->n16 = 0;
	this->a16 = 0;
	this->im = 0;
	this->isPrefixed = false;
}

void CPU::setZFlag(bool Z)
{
	BIT_SET(this->AF.FLAGS, 8, Z)
}

void CPU::setNFlag(bool N)
{
	BIT_SET(this->AF.FLAGS, 7, N)
}

void CPU::setHFlag(bool H)
{
	BIT_SET(this->AF.FLAGS, 6, H)
}

void CPU::setCFlag(bool C)
{
	BIT_SET(this->AF.FLAGS, 5, C)
}

bool CPU::getZFlag()
{
	return BIT(this->AF.FLAGS, 8)
}

bool CPU::getNFlag()
{
	return BIT(this->AF.FLAGS, 7)
}

bool CPU::getHFlag()
{
	return BIT(this->AF.FLAGS, 6)
}

bool CPU::getCFlag()
{
	return BIT(this->AF.FLAGS, 5)
}