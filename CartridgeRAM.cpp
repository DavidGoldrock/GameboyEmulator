#include "CartridgeRAM.h"
#include <stdlib.h>
#include <iostream>
#include <fstream>


CartridgeRAM::CartridgeRAM() {
	this->gameFileName = "./games/Tetris.gb";

	std::cout << "[OPENING GAME " << gameFileName << "]" << std::endl;
	this->gameFile.open(gameFileName, std::ios::out | std::ios::binary);
	if (this->gameFile.good()) {
		std::cout << "[OPENED GAME " << gameFileName << " SUCCESSFULLY]" << std::endl;
	}
	else {
		std::cout << "[FAILED] ERROR AT OPENING BOOTROM FILE" << std::endl;
	}
	const  u32 chipType = 0x147;
	const  u32 RAMSize = 0x149;

	char data;
	// check if supporting chipset
	this->gameFile.seekg(chipType);
	this->gameFile >> data;
	if (data > 0x03) {
		std::cout << "[FAILED] unsupported chipset" << std::endl;
	}

	this->gameFile.seekg(RAMSize);
	this->gameFile >> data;
	 u32 externalRAMSize;
	
	if (data == 2) {
		externalRAMSize = 0x1000;
	}
	else if (data == 3) {
		externalRAMSize = 0x8000;
	}
	else if (data == 4) {
		externalRAMSize = 0x20000;
	}
	else {
		externalRAMSize = 0;
	}
	std::cout << "[STATUS] intializing ram to be (" << externalRAMSize << ") bytes long" << std::endl;
	this->ExternalRAM = new u8[externalRAMSize];
	this->ROMBank = 1;
	this->RAMBank = 0;
	this->RAMActivated = false;
	this->IsRAMMode = false;
}

CartridgeRAM::~CartridgeRAM() {
	this->gameFile.close();
	delete[] this->ExternalRAM;
	std::cout << "[SUCCEDDED] deleted Physical RAM" << std::endl;
	//std::cout << "[SUCCEDDED] delete" << std::endl;
}

bool CartridgeRAM::isInRange( u32 location) {
	return BETWEEN(location, RAMLocations::cartridgeRAMStart, RAMLocations::additionalBankStart) |
		BETWEEN(location, RAMLocations::additionalBankStart, RAMLocations::cartridgeRAMStart) |
		BETWEEN(location, RAMLocations::extraRAMStart, RAMLocations::workingRAMStart);
}

void CartridgeRAM::setValue( u32 location, u8 value) {
	const u32 RAMEnableStart = 0x0000;
	const u32 ROMBankSelectStart = 0x2000;
	const u32 RAMBankSelectStart = 0x4000;
	const u32 RAM_OR_ROM_SelectStart = 0x6000;

	if (BETWEEN(location, RAMEnableStart, ROMBankSelectStart)) {
		this->RAMActivated = (value == 0x0A);
	}

	else if (BETWEEN(location, ROMBankSelectStart, RAMBankSelectStart)) {
	if (value == 0x00 || value >= 0x20) {
		this->ROMBank = 1;
	}
	else {
		this->ROMBank = value;
	}
}

	else if (BETWEEN(location, RAMBankSelectStart, RAM_OR_ROM_SelectStart)) {
		if (BETWEEN(value, 0x00, 0x03)) {
			this->RAMBank = value;
		}
	}

	else if (BETWEEN(location, RAM_OR_ROM_SelectStart, RAMLocations::graphicsRAMStart)) {
		if (value == 0x00 || value == 0x01) {
			this->IsRAMMode = (value != 0);
		}
}

std::cout << "[FAILED] yet to implement setting value to the cartridge at location [" << location << "]" << std::endl;
}

u8 CartridgeRAM::getValue(u32 location) {
	u8 data;
	if (BETWEEN(location, RAMLocations::cartridgeRAMStart, RAMLocations::additionalBankStart)) {
		this->gameFile.seekg(location);
		this->gameFile >> data;
	}

	else if (BETWEEN(location, RAMLocations::additionalBankStart, RAMLocations::graphicsRAMStart)) {
		if (!this->RAMActivated) {
			u32 locationWithBank = (((int)this->ROMBank - 1) * ((int)RAMLocations::BankSize));
			locationWithBank += location;
			this->gameFile.seekg(locationWithBank);
			this->gameFile >> data;
		}
		else {
			data = (u8)rand();
		}
	}

	else if (BETWEEN(location, RAMLocations::extraRAMStart, RAMLocations::workingRAMStart)) {
		if (this->RAMActivated) {
			location -= RAMLocations::extraRAMStart;
			if (this->IsRAMMode) {
				location += this->RAMBank * (RAMLocations::workingRAMStart - RAMLocations::extraRAMStart);
			}
			data = this->ExternalRAM[location];
		}
		else {
			data = (u8)rand();
		}
	}

	else {
		data = -1;
		std::cout << "ACCESSING ERROR FOR CARTRIDGE RAM AT LOCATION [" << location << "]" << std::endl;
	}
	return data;
}