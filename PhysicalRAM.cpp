#include "PhysicalRAM.h"
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <stdint.h>
PhysicalRAM::PhysicalRAM() : RAM() {
	this->bootROM = new u8[RAMLocations::cartridgeRAMStart - RAMLocations::bootROMStart];
	// int8_t is explicitly signed
	char* bootROMClone = new char[RAMLocations::cartridgeRAMStart - RAMLocations::bootROMStart];
	std::cout << "[OPENING BOOTROM]" << std::endl;
	std::ifstream selectedFile;
	selectedFile.open("bootrom.gb", std::ios::out | std::ios::binary);
	if (selectedFile.good()) {
			std::cout << "[VALIDATING BOOTROM]" << std::endl;
			selectedFile.read(bootROMClone, RAMLocations::cartridgeRAMStart - RAMLocations::bootROMStart);
			for (int i = 0; i < RAMLocations::cartridgeRAMStart - RAMLocations::bootROMStart; i++)
			{
				this->bootROM[i] = (u8)bootROMClone[i];
				std::cout << (u32) ((u8) this->bootROM[i]) << ", ";
			}
			std::cout << std::endl;
	}
	else {
		std::cout << "[FAILED] ERROR AT OPENING BOOTROM FILE" << std::endl;
	}
	selectedFile.close();
	delete[] bootROMClone;
	this->graphicsRAM = new u8[RAMLocations::extraRAMStart - RAMLocations::graphicsRAMStart];
	this->workingRAM = new u8[RAMLocations::workingRAM2Start - RAMLocations::workingRAMStart];
	this->OAM = new u8[RAMLocations::OIStart - RAMLocations::OAMStart];
	this->HighRAM = new u8[RAMLocations::Interupts - RAMLocations::HighRAMStart];
	this->FFFF_Interrupts = 0;




}
void PhysicalRAM::setValue(u32 location, u8 value) {
	bool no = false;
	if (BETWEEN(location, RAMLocations::bootROMStart, RAMLocations::cartridgeRAMStart)) {
		std::cout << "[FAILED] Tried to write to boot rom at location [" << location << "] value (" << (u32)value << ")" << std::endl;
	}

	else if (BETWEEN(location, RAMLocations::graphicsRAMStart, RAMLocations::extraRAMStart)) {
		this->graphicsRAM[location - RAMLocations::graphicsRAMStart] = value;
	}

	else if (BETWEEN(location, RAMLocations::workingRAMStart, RAMLocations::workingRAM2Start)) {
		this->workingRAM[location - RAMLocations::workingRAMStart] = value;
	}

	else if (BETWEEN(location, RAMLocations::workingRAM2Start, RAMLocations::OAMStart)) {
		this->workingRAM[location - RAMLocations::workingRAM2Start] = value;
	}

	else if (BETWEEN(location, RAMLocations::OAMStart, RAMLocations::OIStart)) {
		this->OAM[location - RAMLocations::OAMStart] = value;
	}

	else if (BETWEEN(location, RAMLocations::HighRAMStart, RAMLocations::Interupts)) {
		this->HighRAM[location - RAMLocations::HighRAMStart] = value;
	}

	else if (location == RAMLocations::Interupts) {
		this->FFFF_Interrupts = value;
	}

	else if (true) {
		no = true;
		std::cout << "[FAILED] GENERAL ACCESSING ERROR FOR PHYSICAL RAM AT LOCATION [" << location << "]" << std::endl;
	}

	if (!no) {
		std::cout << "[SUCCEEDED] SETTING VALUE (" << (u32)value << ") AT LOCATION [" << location << std::endl;
	}
}

u8 PhysicalRAM::getValue(u32 location) {

	if (BETWEEN(location, RAMLocations::bootROMStart, RAMLocations::cartridgeRAMStart)) {
		return this->bootROM[location - RAMLocations::bootROMStart];
	}

	else if (BETWEEN(location, RAMLocations::graphicsRAMStart, RAMLocations::extraRAMStart)) {
		return this->graphicsRAM[location - RAMLocations::graphicsRAMStart];
	}

	else if (BETWEEN(location, RAMLocations::workingRAMStart, RAMLocations::workingRAM2Start)) {
		return this->workingRAM[location - RAMLocations::workingRAMStart];
	}

	else if (BETWEEN(location, RAMLocations::workingRAM2Start, RAMLocations::OAMStart)) {
		return this->workingRAM[location - RAMLocations::workingRAM2Start];
	}

	else if (BETWEEN(location, RAMLocations::OAMStart, RAMLocations::OIStart)) {
		return this->OAM[location - RAMLocations::OAMStart];
	}

	else if (BETWEEN(location, RAMLocations::HighRAMStart, RAMLocations::Interupts)) {
		return this->HighRAM[location - RAMLocations::HighRAMStart];
	}

	else if (location == RAMLocations::Interupts) {
		return this->FFFF_Interrupts;
	}

	else {
		std::cout << "ACCESSING ERROR FOR PHYSICAL RAM AT LOCATION [" << location << "]" << std::endl;
		return -1;
	}

}
bool PhysicalRAM::isInRange(u32 location) {
	return (BETWEEN(location, RAMLocations::bootROMStart, RAMLocations::cartridgeRAMStart) |
		BETWEEN(location, RAMLocations::graphicsRAMStart, RAMLocations::extraRAMStart) |
		BETWEEN(location, RAMLocations::workingRAMStart, RAMLocations::workingRAM2Start) |
		BETWEEN(location, RAMLocations::workingRAM2Start, RAMLocations::OAMStart) |
		BETWEEN(location, RAMLocations::OAMStart, RAMLocations::OIStart) |
		(location >= RAMLocations::HighRAMStart));
	
}
PhysicalRAM::~PhysicalRAM() {
	delete[] this->bootROM;
	delete[] this->graphicsRAM;
	delete[] this->workingRAM;
	delete[] this->OAM;
	delete[] this->HighRAM;
	
	std::cout << "[SUCCEDDED] deleted Physical RAM" << std::endl;
}

