#include "GameBoy.h"
#include "PhysicalRAM.h"
#include <stdlib.h>
#include <iostream>

GameBoy::GameBoy() {
	this->physicalRAM = new PhysicalRAM();
	this->cartridgeRAM = new CartridgeRAM();
	this->cpu = new CPU();
}

GameBoy::~GameBoy() {
	delete this->physicalRAM;
	delete this->cartridgeRAM;
	delete cpu;
}

void GameBoy::setValue(u32 location, u8 value) {
	if (this->physicalRAM->isInRange(location)) {
		this->physicalRAM->setValue(location, value);
	}
	else if (this->cartridgeRAM->isInRange(location)) {
		this->cartridgeRAM->setValue(location, value);
	}
	else {
		std::cout << "[FAILED] ACCESSING ERROR: NO MODULE IN VALUE RANGE" << std::endl;
	}
}

u8 GameBoy::getValue(u32 location) {
	if (this->physicalRAM->isInRange(location)) {
		return this->physicalRAM->getValue(location);
	}
	else if (this->cartridgeRAM->isInRange(location)) {
		return this->cartridgeRAM->getValue(location);
	}
	else {
		std::cout << "[FAILED] ACCESSING ERROR: NO MODULE IN VALUE RANGE" << std::endl;
		return -1;
	}
}

u8 GameBoy::fetch(u32 location) {
	u8 value = this->getValue(location);
	value++;
	return value;
}

void GameBoy::execute(u8 value) {
}