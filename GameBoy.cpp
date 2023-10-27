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

u8 GameBoy::fetch() {
	u8 value = this->getValue(this->cpu->PC);
	this->cpu->PC++;
	return value;
}

void GameBoy::execute(u8 value) {
	u8 opcode = fetch();
	if (this->cpu->isPrefixed) {
		switch (opcode)
		{
		case 0x00: // NOP
			//operand 1: , operand 2:  , length: 1 flags: ['-', '-', '-', '-'] cycles [4]
			break;
		case 0x01: // LD
			//operand 1: BC, operand 2: d16 , length: 3 flags: ['-', '-', '-', '-'] cycles [12]
			u16 operand = fetch();
			operand << 8;
			operand += fetch();
			this->cpu->BC.BC = operand;
			break;
		case 0x02: // LD
			//operand 1: (BC), operand 2: A , length: 1 flags: ['-', '-', '-', '-'] cycles [8]
			this->cpu->BC.BC = this->cpu->AF.A;
			break;
		case 0x03: // INC
			//operand 1: BC, operand 2:  , length: 1 flags: ['-', '-', '-', '-'] cycles [8]
			this->cpu->BC.BC++;
			break;
		case 0x04: // INC
			//operand 1: B, operand 2:  , length: 1 flags: ['Z', '0', 'H', '-'] cycles [4]
			this->cpu->BC.B++;
			if (!this->cpu->BC.B) {
				this->cpu->AF.FLAGS = this->cpu->flagsFromData(this->cpu->BC.B == 0, false, this->cpu->BC.B == 0, this->cpu->AF.FLAGS && 0b00010000);
			}
			break;
		case 0x05: // DEC
			//operand 1: B, operand 2:  , length: 1 flags: ['Z', '1', 'H', '-'] cycles [4]
			this->cpu->BC.B--;
			if (!this->cpu->BC.B) {
				this->cpu->AF.FLAGS = this->cpu->flagsFromData(this->cpu->BC.B == 0, true, this->cpu->BC.B == 0xff, this->cpu->AF.FLAGS && 0b00010000);
			}
			break;
		case 0x06: // LD
			//operand 1: B, operand 2: d8 , length: 2 flags: ['-', '-', '-', '-'] cycles [8]
			u8 operand = fetch();
			this->cpu->BC.B = operand;
			break;
		case 0x07: // RLCA
			//operand 1: , operand 2:  , length: 1 flags: ['0', '0', '0', 'C'] cycles [4]
			break;
		case 0x08: // LD
			//operand 1: (a16), operand 2: SP , length: 3 flags: ['-', '-', '-', '-'] cycles [20]
			break;
		case 0x09: // ADD
			//operand 1: HL, operand 2: BC , length: 1 flags: ['-', '0', 'H', 'C'] cycles [8]
			break;
		case 0x0a: // LD
			//operand 1: A, operand 2: (BC) , length: 1 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0x0b: // DEC
			//operand 1: BC, operand 2:  , length: 1 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0x0c: // INC
			//operand 1: C, operand 2:  , length: 1 flags: ['Z', '0', 'H', '-'] cycles [4]
			break;
		case 0x0d: // DEC
			//operand 1: C, operand 2:  , length: 1 flags: ['Z', '1', 'H', '-'] cycles [4]
			break;
		case 0x0e: // LD
			//operand 1: C, operand 2: d8 , length: 2 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0x0f: // RRCA
			//operand 1: , operand 2:  , length: 1 flags: ['0', '0', '0', 'C'] cycles [4]
			break;
		case 0x10: // STOP
			//operand 1: 0, operand 2:  , length: 1 flags: ['-', '-', '-', '-'] cycles [4]
			break;
		case 0x11: // LD
			//operand 1: DE, operand 2: d16 , length: 3 flags: ['-', '-', '-', '-'] cycles [12]
			break;
		case 0x12: // LD
			//operand 1: (DE), operand 2: A , length: 1 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0x13: // INC
			//operand 1: DE, operand 2:  , length: 1 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0x14: // INC
			//operand 1: D, operand 2:  , length: 1 flags: ['Z', '0', 'H', '-'] cycles [4]
			break;
		case 0x15: // DEC
			//operand 1: D, operand 2:  , length: 1 flags: ['Z', '1', 'H', '-'] cycles [4]
			break;
		case 0x16: // LD
			//operand 1: D, operand 2: d8 , length: 2 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0x17: // RLA
			//operand 1: , operand 2:  , length: 1 flags: ['0', '0', '0', 'C'] cycles [4]
			break;
		case 0x18: // JR
			//operand 1: r8, operand 2:  , length: 2 flags: ['-', '-', '-', '-'] cycles [12]
			break;
		case 0x19: // ADD
			//operand 1: HL, operand 2: DE , length: 1 flags: ['-', '0', 'H', 'C'] cycles [8]
			break;
		case 0x1a: // LD
			//operand 1: A, operand 2: (DE) , length: 1 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0x1b: // DEC
			//operand 1: DE, operand 2:  , length: 1 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0x1c: // INC
			//operand 1: E, operand 2:  , length: 1 flags: ['Z', '0', 'H', '-'] cycles [4]
			break;
		case 0x1d: // DEC
			//operand 1: E, operand 2:  , length: 1 flags: ['Z', '1', 'H', '-'] cycles [4]
			break;
		case 0x1e: // LD
			//operand 1: E, operand 2: d8 , length: 2 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0x1f: // RRA
			//operand 1: , operand 2:  , length: 1 flags: ['0', '0', '0', 'C'] cycles [4]
			break;
		case 0x20: // JR
			//operand 1: NZ, operand 2: r8 , length: 2 flags: ['-', '-', '-', '-'] cycles [12, 8]
			break;
		case 0x21: // LD
			//operand 1: HL, operand 2: d16 , length: 3 flags: ['-', '-', '-', '-'] cycles [12]
			break;
		case 0x22: // LD
			//operand 1: (HL+), operand 2: A , length: 1 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0x23: // INC
			//operand 1: HL, operand 2:  , length: 1 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0x24: // INC
			//operand 1: H, operand 2:  , length: 1 flags: ['Z', '0', 'H', '-'] cycles [4]
			break;
		case 0x25: // DEC
			//operand 1: H, operand 2:  , length: 1 flags: ['Z', '1', 'H', '-'] cycles [4]
			break;
		case 0x26: // LD
			//operand 1: H, operand 2: d8 , length: 2 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0x27: // DAA
			//operand 1: , operand 2:  , length: 1 flags: ['Z', '-', '0', 'C'] cycles [4]
			break;
		case 0x28: // JR
			//operand 1: Z, operand 2: r8 , length: 2 flags: ['-', '-', '-', '-'] cycles [12, 8]
			break;
		case 0x29: // ADD
			//operand 1: HL, operand 2: HL , length: 1 flags: ['-', '0', 'H', 'C'] cycles [8]
			break;
		case 0x2a: // LD
			//operand 1: A, operand 2: (HL+) , length: 1 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0x2b: // DEC
			//operand 1: HL, operand 2:  , length: 1 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0x2c: // INC
			//operand 1: L, operand 2:  , length: 1 flags: ['Z', '0', 'H', '-'] cycles [4]
			break;
		case 0x2d: // DEC
			//operand 1: L, operand 2:  , length: 1 flags: ['Z', '1', 'H', '-'] cycles [4]
			break;
		case 0x2e: // LD
			//operand 1: L, operand 2: d8 , length: 2 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0x2f: // CPL
			//operand 1: , operand 2:  , length: 1 flags: ['-', '1', '1', '-'] cycles [4]
			break;
		case 0x30: // JR
			//operand 1: NC, operand 2: r8 , length: 2 flags: ['-', '-', '-', '-'] cycles [12, 8]
			break;
		case 0x31: // LD
			//operand 1: SP, operand 2: d16 , length: 3 flags: ['-', '-', '-', '-'] cycles [12]
			break;
		case 0x32: // LD
			//operand 1: (HL-), operand 2: A , length: 1 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0x33: // INC
			//operand 1: SP, operand 2:  , length: 1 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0x34: // INC
			//operand 1: (HL), operand 2:  , length: 1 flags: ['Z', '0', 'H', '-'] cycles [12]
			break;
		case 0x35: // DEC
			//operand 1: (HL), operand 2:  , length: 1 flags: ['Z', '1', 'H', '-'] cycles [12]
			break;
		case 0x36: // LD
			//operand 1: (HL), operand 2: d8 , length: 2 flags: ['-', '-', '-', '-'] cycles [12]
			break;
		case 0x37: // SCF
			//operand 1: , operand 2:  , length: 1 flags: ['-', '0', '0', '1'] cycles [4]
			break;
		case 0x38: // JR
			//operand 1: C, operand 2: r8 , length: 2 flags: ['-', '-', '-', '-'] cycles [12, 8]
			break;
		case 0x39: // ADD
			//operand 1: HL, operand 2: SP , length: 1 flags: ['-', '0', 'H', 'C'] cycles [8]
			break;
		case 0x3a: // LD
			//operand 1: A, operand 2: (HL-) , length: 1 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0x3b: // DEC
			//operand 1: SP, operand 2:  , length: 1 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0x3c: // INC
			//operand 1: A, operand 2:  , length: 1 flags: ['Z', '0', 'H', '-'] cycles [4]
			break;
		case 0x3d: // DEC
			//operand 1: A, operand 2:  , length: 1 flags: ['Z', '1', 'H', '-'] cycles [4]
			break;
		case 0x3e: // LD
			//operand 1: A, operand 2: d8 , length: 2 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0x3f: // CCF
			//operand 1: , operand 2:  , length: 1 flags: ['-', '0', '0', 'C'] cycles [4]
			break;
		case 0x40: // LD
			//operand 1: B, operand 2: B , length: 1 flags: ['-', '-', '-', '-'] cycles [4]
			break;
		case 0x41: // LD
			//operand 1: B, operand 2: C , length: 1 flags: ['-', '-', '-', '-'] cycles [4]
			break;
		case 0x42: // LD
			//operand 1: B, operand 2: D , length: 1 flags: ['-', '-', '-', '-'] cycles [4]
			break;
		case 0x43: // LD
			//operand 1: B, operand 2: E , length: 1 flags: ['-', '-', '-', '-'] cycles [4]
			break;
		case 0x44: // LD
			//operand 1: B, operand 2: H , length: 1 flags: ['-', '-', '-', '-'] cycles [4]
			break;
		case 0x45: // LD
			//operand 1: B, operand 2: L , length: 1 flags: ['-', '-', '-', '-'] cycles [4]
			break;
		case 0x46: // LD
			//operand 1: B, operand 2: (HL) , length: 1 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0x47: // LD
			//operand 1: B, operand 2: A , length: 1 flags: ['-', '-', '-', '-'] cycles [4]
			break;
		case 0x48: // LD
			//operand 1: C, operand 2: B , length: 1 flags: ['-', '-', '-', '-'] cycles [4]
			break;
		case 0x49: // LD
			//operand 1: C, operand 2: C , length: 1 flags: ['-', '-', '-', '-'] cycles [4]
			break;
		case 0x4a: // LD
			//operand 1: C, operand 2: D , length: 1 flags: ['-', '-', '-', '-'] cycles [4]
			break;
		case 0x4b: // LD
			//operand 1: C, operand 2: E , length: 1 flags: ['-', '-', '-', '-'] cycles [4]
			break;
		case 0x4c: // LD
			//operand 1: C, operand 2: H , length: 1 flags: ['-', '-', '-', '-'] cycles [4]
			break;
		case 0x4d: // LD
			//operand 1: C, operand 2: L , length: 1 flags: ['-', '-', '-', '-'] cycles [4]
			break;
		case 0x4e: // LD
			//operand 1: C, operand 2: (HL) , length: 1 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0x4f: // LD
			//operand 1: C, operand 2: A , length: 1 flags: ['-', '-', '-', '-'] cycles [4]
			break;
		case 0x50: // LD
			//operand 1: D, operand 2: B , length: 1 flags: ['-', '-', '-', '-'] cycles [4]
			break;
		case 0x51: // LD
			//operand 1: D, operand 2: C , length: 1 flags: ['-', '-', '-', '-'] cycles [4]
			break;
		case 0x52: // LD
			//operand 1: D, operand 2: D , length: 1 flags: ['-', '-', '-', '-'] cycles [4]
			break;
		case 0x53: // LD
			//operand 1: D, operand 2: E , length: 1 flags: ['-', '-', '-', '-'] cycles [4]
			break;
		case 0x54: // LD
			//operand 1: D, operand 2: H , length: 1 flags: ['-', '-', '-', '-'] cycles [4]
			break;
		case 0x55: // LD
			//operand 1: D, operand 2: L , length: 1 flags: ['-', '-', '-', '-'] cycles [4]
			break;
		case 0x56: // LD
			//operand 1: D, operand 2: (HL) , length: 1 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0x57: // LD
			//operand 1: D, operand 2: A , length: 1 flags: ['-', '-', '-', '-'] cycles [4]
			break;
		case 0x58: // LD
			//operand 1: E, operand 2: B , length: 1 flags: ['-', '-', '-', '-'] cycles [4]
			break;
		case 0x59: // LD
			//operand 1: E, operand 2: C , length: 1 flags: ['-', '-', '-', '-'] cycles [4]
			break;
		case 0x5a: // LD
			//operand 1: E, operand 2: D , length: 1 flags: ['-', '-', '-', '-'] cycles [4]
			break;
		case 0x5b: // LD
			//operand 1: E, operand 2: E , length: 1 flags: ['-', '-', '-', '-'] cycles [4]
			break;
		case 0x5c: // LD
			//operand 1: E, operand 2: H , length: 1 flags: ['-', '-', '-', '-'] cycles [4]
			break;
		case 0x5d: // LD
			//operand 1: E, operand 2: L , length: 1 flags: ['-', '-', '-', '-'] cycles [4]
			break;
		case 0x5e: // LD
			//operand 1: E, operand 2: (HL) , length: 1 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0x5f: // LD
			//operand 1: E, operand 2: A , length: 1 flags: ['-', '-', '-', '-'] cycles [4]
			break;
		case 0x60: // LD
			//operand 1: H, operand 2: B , length: 1 flags: ['-', '-', '-', '-'] cycles [4]
			break;
		case 0x61: // LD
			//operand 1: H, operand 2: C , length: 1 flags: ['-', '-', '-', '-'] cycles [4]
			break;
		case 0x62: // LD
			//operand 1: H, operand 2: D , length: 1 flags: ['-', '-', '-', '-'] cycles [4]
			break;
		case 0x63: // LD
			//operand 1: H, operand 2: E , length: 1 flags: ['-', '-', '-', '-'] cycles [4]
			break;
		case 0x64: // LD
			//operand 1: H, operand 2: H , length: 1 flags: ['-', '-', '-', '-'] cycles [4]
			break;
		case 0x65: // LD
			//operand 1: H, operand 2: L , length: 1 flags: ['-', '-', '-', '-'] cycles [4]
			break;
		case 0x66: // LD
			//operand 1: H, operand 2: (HL) , length: 1 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0x67: // LD
			//operand 1: H, operand 2: A , length: 1 flags: ['-', '-', '-', '-'] cycles [4]
			break;
		case 0x68: // LD
			//operand 1: L, operand 2: B , length: 1 flags: ['-', '-', '-', '-'] cycles [4]
			break;
		case 0x69: // LD
			//operand 1: L, operand 2: C , length: 1 flags: ['-', '-', '-', '-'] cycles [4]
			break;
		case 0x6a: // LD
			//operand 1: L, operand 2: D , length: 1 flags: ['-', '-', '-', '-'] cycles [4]
			break;
		case 0x6b: // LD
			//operand 1: L, operand 2: E , length: 1 flags: ['-', '-', '-', '-'] cycles [4]
			break;
		case 0x6c: // LD
			//operand 1: L, operand 2: H , length: 1 flags: ['-', '-', '-', '-'] cycles [4]
			break;
		case 0x6d: // LD
			//operand 1: L, operand 2: L , length: 1 flags: ['-', '-', '-', '-'] cycles [4]
			break;
		case 0x6e: // LD
			//operand 1: L, operand 2: (HL) , length: 1 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0x6f: // LD
			//operand 1: L, operand 2: A , length: 1 flags: ['-', '-', '-', '-'] cycles [4]
			break;
		case 0x70: // LD
			//operand 1: (HL), operand 2: B , length: 1 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0x71: // LD
			//operand 1: (HL), operand 2: C , length: 1 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0x72: // LD
			//operand 1: (HL), operand 2: D , length: 1 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0x73: // LD
			//operand 1: (HL), operand 2: E , length: 1 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0x74: // LD
			//operand 1: (HL), operand 2: H , length: 1 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0x75: // LD
			//operand 1: (HL), operand 2: L , length: 1 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0x76: // HALT
			//operand 1: , operand 2:  , length: 1 flags: ['-', '-', '-', '-'] cycles [4]
			break;
		case 0x77: // LD
			//operand 1: (HL), operand 2: A , length: 1 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0x78: // LD
			//operand 1: A, operand 2: B , length: 1 flags: ['-', '-', '-', '-'] cycles [4]
			break;
		case 0x79: // LD
			//operand 1: A, operand 2: C , length: 1 flags: ['-', '-', '-', '-'] cycles [4]
			break;
		case 0x7a: // LD
			//operand 1: A, operand 2: D , length: 1 flags: ['-', '-', '-', '-'] cycles [4]
			break;
		case 0x7b: // LD
			//operand 1: A, operand 2: E , length: 1 flags: ['-', '-', '-', '-'] cycles [4]
			break;
		case 0x7c: // LD
			//operand 1: A, operand 2: H , length: 1 flags: ['-', '-', '-', '-'] cycles [4]
			break;
		case 0x7d: // LD
			//operand 1: A, operand 2: L , length: 1 flags: ['-', '-', '-', '-'] cycles [4]
			break;
		case 0x7e: // LD
			//operand 1: A, operand 2: (HL) , length: 1 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0x7f: // LD
			//operand 1: A, operand 2: A , length: 1 flags: ['-', '-', '-', '-'] cycles [4]
			break;
		case 0x80: // ADD
			//operand 1: A, operand 2: B , length: 1 flags: ['Z', '0', 'H', 'C'] cycles [4]
			break;
		case 0x81: // ADD
			//operand 1: A, operand 2: C , length: 1 flags: ['Z', '0', 'H', 'C'] cycles [4]
			break;
		case 0x82: // ADD
			//operand 1: A, operand 2: D , length: 1 flags: ['Z', '0', 'H', 'C'] cycles [4]
			break;
		case 0x83: // ADD
			//operand 1: A, operand 2: E , length: 1 flags: ['Z', '0', 'H', 'C'] cycles [4]
			break;
		case 0x84: // ADD
			//operand 1: A, operand 2: H , length: 1 flags: ['Z', '0', 'H', 'C'] cycles [4]
			break;
		case 0x85: // ADD
			//operand 1: A, operand 2: L , length: 1 flags: ['Z', '0', 'H', 'C'] cycles [4]
			break;
		case 0x86: // ADD
			//operand 1: A, operand 2: (HL) , length: 1 flags: ['Z', '0', 'H', 'C'] cycles [8]
			break;
		case 0x87: // ADD
			//operand 1: A, operand 2: A , length: 1 flags: ['Z', '0', 'H', 'C'] cycles [4]
			break;
		case 0x88: // ADC
			//operand 1: A, operand 2: B , length: 1 flags: ['Z', '0', 'H', 'C'] cycles [4]
			break;
		case 0x89: // ADC
			//operand 1: A, operand 2: C , length: 1 flags: ['Z', '0', 'H', 'C'] cycles [4]
			break;
		case 0x8a: // ADC
			//operand 1: A, operand 2: D , length: 1 flags: ['Z', '0', 'H', 'C'] cycles [4]
			break;
		case 0x8b: // ADC
			//operand 1: A, operand 2: E , length: 1 flags: ['Z', '0', 'H', 'C'] cycles [4]
			break;
		case 0x8c: // ADC
			//operand 1: A, operand 2: H , length: 1 flags: ['Z', '0', 'H', 'C'] cycles [4]
			break;
		case 0x8d: // ADC
			//operand 1: A, operand 2: L , length: 1 flags: ['Z', '0', 'H', 'C'] cycles [4]
			break;
		case 0x8e: // ADC
			//operand 1: A, operand 2: (HL) , length: 1 flags: ['Z', '0', 'H', 'C'] cycles [8]
			break;
		case 0x8f: // ADC
			//operand 1: A, operand 2: A , length: 1 flags: ['Z', '0', 'H', 'C'] cycles [4]
			break;
		case 0x90: // SUB
			//operand 1: B, operand 2:  , length: 1 flags: ['Z', '1', 'H', 'C'] cycles [4]
			break;
		case 0x91: // SUB
			//operand 1: C, operand 2:  , length: 1 flags: ['Z', '1', 'H', 'C'] cycles [4]
			break;
		case 0x92: // SUB
			//operand 1: D, operand 2:  , length: 1 flags: ['Z', '1', 'H', 'C'] cycles [4]
			break;
		case 0x93: // SUB
			//operand 1: E, operand 2:  , length: 1 flags: ['Z', '1', 'H', 'C'] cycles [4]
			break;
		case 0x94: // SUB
			//operand 1: H, operand 2:  , length: 1 flags: ['Z', '1', 'H', 'C'] cycles [4]
			break;
		case 0x95: // SUB
			//operand 1: L, operand 2:  , length: 1 flags: ['Z', '1', 'H', 'C'] cycles [4]
			break;
		case 0x96: // SUB
			//operand 1: (HL), operand 2:  , length: 1 flags: ['Z', '1', 'H', 'C'] cycles [8]
			break;
		case 0x97: // SUB
			//operand 1: A, operand 2:  , length: 1 flags: ['Z', '1', 'H', 'C'] cycles [4]
			break;
		case 0x98: // SBC
			//operand 1: A, operand 2: B , length: 1 flags: ['Z', '1', 'H', 'C'] cycles [4]
			break;
		case 0x99: // SBC
			//operand 1: A, operand 2: C , length: 1 flags: ['Z', '1', 'H', 'C'] cycles [4]
			break;
		case 0x9a: // SBC
			//operand 1: A, operand 2: D , length: 1 flags: ['Z', '1', 'H', 'C'] cycles [4]
			break;
		case 0x9b: // SBC
			//operand 1: A, operand 2: E , length: 1 flags: ['Z', '1', 'H', 'C'] cycles [4]
			break;
		case 0x9c: // SBC
			//operand 1: A, operand 2: H , length: 1 flags: ['Z', '1', 'H', 'C'] cycles [4]
			break;
		case 0x9d: // SBC
			//operand 1: A, operand 2: L , length: 1 flags: ['Z', '1', 'H', 'C'] cycles [4]
			break;
		case 0x9e: // SBC
			//operand 1: A, operand 2: (HL) , length: 1 flags: ['Z', '1', 'H', 'C'] cycles [8]
			break;
		case 0x9f: // SBC
			//operand 1: A, operand 2: A , length: 1 flags: ['Z', '1', 'H', 'C'] cycles [4]
			break;
		case 0xa0: // AND
			//operand 1: B, operand 2:  , length: 1 flags: ['Z', '0', '1', '0'] cycles [4]
			break;
		case 0xa1: // AND
			//operand 1: C, operand 2:  , length: 1 flags: ['Z', '0', '1', '0'] cycles [4]
			break;
		case 0xa2: // AND
			//operand 1: D, operand 2:  , length: 1 flags: ['Z', '0', '1', '0'] cycles [4]
			break;
		case 0xa3: // AND
			//operand 1: E, operand 2:  , length: 1 flags: ['Z', '0', '1', '0'] cycles [4]
			break;
		case 0xa4: // AND
			//operand 1: H, operand 2:  , length: 1 flags: ['Z', '0', '1', '0'] cycles [4]
			break;
		case 0xa5: // AND
			//operand 1: L, operand 2:  , length: 1 flags: ['Z', '0', '1', '0'] cycles [4]
			break;
		case 0xa6: // AND
			//operand 1: (HL), operand 2:  , length: 1 flags: ['Z', '0', '1', '0'] cycles [8]
			break;
		case 0xa7: // AND
			//operand 1: A, operand 2:  , length: 1 flags: ['Z', '0', '1', '0'] cycles [4]
			break;
		case 0xa8: // XOR
			//operand 1: B, operand 2:  , length: 1 flags: ['Z', '0', '0', '0'] cycles [4]
			break;
		case 0xa9: // XOR
			//operand 1: C, operand 2:  , length: 1 flags: ['Z', '0', '0', '0'] cycles [4]
			break;
		case 0xaa: // XOR
			//operand 1: D, operand 2:  , length: 1 flags: ['Z', '0', '0', '0'] cycles [4]
			break;
		case 0xab: // XOR
			//operand 1: E, operand 2:  , length: 1 flags: ['Z', '0', '0', '0'] cycles [4]
			break;
		case 0xac: // XOR
			//operand 1: H, operand 2:  , length: 1 flags: ['Z', '0', '0', '0'] cycles [4]
			break;
		case 0xad: // XOR
			//operand 1: L, operand 2:  , length: 1 flags: ['Z', '0', '0', '0'] cycles [4]
			break;
		case 0xae: // XOR
			//operand 1: (HL), operand 2:  , length: 1 flags: ['Z', '0', '0', '0'] cycles [8]
			break;
		case 0xaf: // XOR
			//operand 1: A, operand 2:  , length: 1 flags: ['Z', '0', '0', '0'] cycles [4]
			break;
		case 0xb0: // OR
			//operand 1: B, operand 2:  , length: 1 flags: ['Z', '0', '0', '0'] cycles [4]
			break;
		case 0xb1: // OR
			//operand 1: C, operand 2:  , length: 1 flags: ['Z', '0', '0', '0'] cycles [4]
			break;
		case 0xb2: // OR
			//operand 1: D, operand 2:  , length: 1 flags: ['Z', '0', '0', '0'] cycles [4]
			break;
		case 0xb3: // OR
			//operand 1: E, operand 2:  , length: 1 flags: ['Z', '0', '0', '0'] cycles [4]
			break;
		case 0xb4: // OR
			//operand 1: H, operand 2:  , length: 1 flags: ['Z', '0', '0', '0'] cycles [4]
			break;
		case 0xb5: // OR
			//operand 1: L, operand 2:  , length: 1 flags: ['Z', '0', '0', '0'] cycles [4]
			break;
		case 0xb6: // OR
			//operand 1: (HL), operand 2:  , length: 1 flags: ['Z', '0', '0', '0'] cycles [8]
			break;
		case 0xb7: // OR
			//operand 1: A, operand 2:  , length: 1 flags: ['Z', '0', '0', '0'] cycles [4]
			break;
		case 0xb8: // CP
			//operand 1: B, operand 2:  , length: 1 flags: ['Z', '1', 'H', 'C'] cycles [4]
			break;
		case 0xb9: // CP
			//operand 1: C, operand 2:  , length: 1 flags: ['Z', '1', 'H', 'C'] cycles [4]
			break;
		case 0xba: // CP
			//operand 1: D, operand 2:  , length: 1 flags: ['Z', '1', 'H', 'C'] cycles [4]
			break;
		case 0xbb: // CP
			//operand 1: E, operand 2:  , length: 1 flags: ['Z', '1', 'H', 'C'] cycles [4]
			break;
		case 0xbc: // CP
			//operand 1: H, operand 2:  , length: 1 flags: ['Z', '1', 'H', 'C'] cycles [4]
			break;
		case 0xbd: // CP
			//operand 1: L, operand 2:  , length: 1 flags: ['Z', '1', 'H', 'C'] cycles [4]
			break;
		case 0xbe: // CP
			//operand 1: (HL), operand 2:  , length: 1 flags: ['Z', '1', 'H', 'C'] cycles [8]
			break;
		case 0xbf: // CP
			//operand 1: A, operand 2:  , length: 1 flags: ['Z', '1', 'H', 'C'] cycles [4]
			break;
		case 0xc0: // RET
			//operand 1: NZ, operand 2:  , length: 1 flags: ['-', '-', '-', '-'] cycles [20, 8]
			break;
		case 0xc1: // POP
			//operand 1: BC, operand 2:  , length: 1 flags: ['-', '-', '-', '-'] cycles [12]
			break;
		case 0xc2: // JP
			//operand 1: NZ, operand 2: a16 , length: 3 flags: ['-', '-', '-', '-'] cycles [16, 12]
			break;
		case 0xc3: // JP
			//operand 1: a16, operand 2:  , length: 3 flags: ['-', '-', '-', '-'] cycles [16]
			break;
		case 0xc4: // CALL
			//operand 1: NZ, operand 2: a16 , length: 3 flags: ['-', '-', '-', '-'] cycles [24, 12]
			break;
		case 0xc5: // PUSH
			//operand 1: BC, operand 2:  , length: 1 flags: ['-', '-', '-', '-'] cycles [16]
			break;
		case 0xc6: // ADD
			//operand 1: A, operand 2: d8 , length: 2 flags: ['Z', '0', 'H', 'C'] cycles [8]
			break;
		case 0xc7: // RST
			//operand 1: 00H, operand 2:  , length: 1 flags: ['-', '-', '-', '-'] cycles [16]
			break;
		case 0xc8: // RET
			//operand 1: Z, operand 2:  , length: 1 flags: ['-', '-', '-', '-'] cycles [20, 8]
			break;
		case 0xc9: // RET
			//operand 1: , operand 2:  , length: 1 flags: ['-', '-', '-', '-'] cycles [16]
			break;
		case 0xca: // JP
			//operand 1: Z, operand 2: a16 , length: 3 flags: ['-', '-', '-', '-'] cycles [16, 12]
			break;
		case 0xcb: // PREFIX
			//operand 1: CB, operand 2:  , length: 1 flags: ['-', '-', '-', '-'] cycles [4]
			this->cpu->isPrefixed = true;
			break;
		case 0xcc: // CALL
			//operand 1: Z, operand 2: a16 , length: 3 flags: ['-', '-', '-', '-'] cycles [24, 12]
			break;
		case 0xcd: // CALL
			//operand 1: a16, operand 2:  , length: 3 flags: ['-', '-', '-', '-'] cycles [24]
			break;
		case 0xce: // ADC
			//operand 1: A, operand 2: d8 , length: 2 flags: ['Z', '0', 'H', 'C'] cycles [8]
			break;
		case 0xcf: // RST
			//operand 1: 08H, operand 2:  , length: 1 flags: ['-', '-', '-', '-'] cycles [16]
			break;
		case 0xd0: // RET
			//operand 1: NC, operand 2:  , length: 1 flags: ['-', '-', '-', '-'] cycles [20, 8]
			break;
		case 0xd1: // POP
			//operand 1: DE, operand 2:  , length: 1 flags: ['-', '-', '-', '-'] cycles [12]
			break;
		case 0xd2: // JP
			//operand 1: NC, operand 2: a16 , length: 3 flags: ['-', '-', '-', '-'] cycles [16, 12]
			break;
		case 0xd4: // CALL
			//operand 1: NC, operand 2: a16 , length: 3 flags: ['-', '-', '-', '-'] cycles [24, 12]
			break;
		case 0xd5: // PUSH
			//operand 1: DE, operand 2:  , length: 1 flags: ['-', '-', '-', '-'] cycles [16]
			break;
		case 0xd6: // SUB
			//operand 1: d8, operand 2:  , length: 2 flags: ['Z', '1', 'H', 'C'] cycles [8]
			break;
		case 0xd7: // RST
			//operand 1: 10H, operand 2:  , length: 1 flags: ['-', '-', '-', '-'] cycles [16]
			break;
		case 0xd8: // RET
			//operand 1: C, operand 2:  , length: 1 flags: ['-', '-', '-', '-'] cycles [20, 8]
			break;
		case 0xd9: // RETI
			//operand 1: , operand 2:  , length: 1 flags: ['-', '-', '-', '-'] cycles [16]
			break;
		case 0xda: // JP
			//operand 1: C, operand 2: a16 , length: 3 flags: ['-', '-', '-', '-'] cycles [16, 12]
			break;
		case 0xdc: // CALL
			//operand 1: C, operand 2: a16 , length: 3 flags: ['-', '-', '-', '-'] cycles [24, 12]
			break;
		case 0xde: // SBC
			//operand 1: A, operand 2: d8 , length: 2 flags: ['Z', '1', 'H', 'C'] cycles [8]
			break;
		case 0xdf: // RST
			//operand 1: 18H, operand 2:  , length: 1 flags: ['-', '-', '-', '-'] cycles [16]
			break;
		case 0xe0: // LDH
			//operand 1: (a8), operand 2: A , length: 2 flags: ['-', '-', '-', '-'] cycles [12]
			break;
		case 0xe1: // POP
			//operand 1: HL, operand 2:  , length: 1 flags: ['-', '-', '-', '-'] cycles [12]
			break;
		case 0xe2: // LD
			//operand 1: (C), operand 2: A , length: 1 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0xe5: // PUSH
			//operand 1: HL, operand 2:  , length: 1 flags: ['-', '-', '-', '-'] cycles [16]
			break;
		case 0xe6: // AND
			//operand 1: d8, operand 2:  , length: 2 flags: ['Z', '0', '1', '0'] cycles [8]
			break;
		case 0xe7: // RST
			//operand 1: 20H, operand 2:  , length: 1 flags: ['-', '-', '-', '-'] cycles [16]
			break;
		case 0xe8: // ADD
			//operand 1: SP, operand 2: r8 , length: 2 flags: ['0', '0', 'H', 'C'] cycles [16]
			break;
		case 0xe9: // JP
			//operand 1: (HL), operand 2:  , length: 1 flags: ['-', '-', '-', '-'] cycles [4]
			break;
		case 0xea: // LD
			//operand 1: (a16), operand 2: A , length: 3 flags: ['-', '-', '-', '-'] cycles [16]
			break;
		case 0xee: // XOR
			//operand 1: d8, operand 2:  , length: 2 flags: ['Z', '0', '0', '0'] cycles [8]
			break;
		case 0xef: // RST
			//operand 1: 28H, operand 2:  , length: 1 flags: ['-', '-', '-', '-'] cycles [16]
			break;
		case 0xf0: // LDH
			//operand 1: A, operand 2: (a8) , length: 2 flags: ['-', '-', '-', '-'] cycles [12]
			break;
		case 0xf1: // POP
			//operand 1: AF, operand 2:  , length: 1 flags: ['Z', 'N', 'H', 'C'] cycles [12]
			break;
		case 0xf2: // LD
			//operand 1: A, operand 2: (C) , length: 1 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0xf3: // DI
			//operand 1: , operand 2:  , length: 1 flags: ['-', '-', '-', '-'] cycles [4]
			break;
		case 0xf5: // PUSH
			//operand 1: AF, operand 2:  , length: 1 flags: ['-', '-', '-', '-'] cycles [16]
			break;
		case 0xf6: // OR
			//operand 1: d8, operand 2:  , length: 2 flags: ['Z', '0', '0', '0'] cycles [8]
			break;
		case 0xf7: // RST
			//operand 1: 30H, operand 2:  , length: 1 flags: ['-', '-', '-', '-'] cycles [16]
			break;
		case 0xf8: // LD
			//operand 1: HL, operand 2: SP+r8 , length: 2 flags: ['0', '0', 'H', 'C'] cycles [12]
			break;
		case 0xf9: // LD
			//operand 1: SP, operand 2: HL , length: 1 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0xfa: // LD
			//operand 1: A, operand 2: (a16) , length: 3 flags: ['-', '-', '-', '-'] cycles [16]
			break;
		case 0xfb: // EI
			//operand 1: , operand 2:  , length: 1 flags: ['-', '-', '-', '-'] cycles [4]
			break;
		case 0xfe: // CP
			//operand 1: d8, operand 2:  , length: 2 flags: ['Z', '1', 'H', 'C'] cycles [8]
			break;
		case 0xff: // RST
			//operand 1: 38H, operand 2:  , length: 1 flags: ['-', '-', '-', '-'] cycles [16]
			break;
		}
	}
	else {
		switch (opcode) {
		case 0x00: // RLC
			//operand 1: B, operand 2:  , length: 2 flags: ['Z', '0', '0', 'C'] cycles [8]
			break;
		case 0x01: // RLC
			//operand 1: C, operand 2:  , length: 2 flags: ['Z', '0', '0', 'C'] cycles [8]
			break;
		case 0x02: // RLC
			//operand 1: D, operand 2:  , length: 2 flags: ['Z', '0', '0', 'C'] cycles [8]
			break;
		case 0x03: // RLC
			//operand 1: E, operand 2:  , length: 2 flags: ['Z', '0', '0', 'C'] cycles [8]
			break;
		case 0x04: // RLC
			//operand 1: H, operand 2:  , length: 2 flags: ['Z', '0', '0', 'C'] cycles [8]
			break;
		case 0x05: // RLC
			//operand 1: L, operand 2:  , length: 2 flags: ['Z', '0', '0', 'C'] cycles [8]
			break;
		case 0x06: // RLC
			//operand 1: (HL), operand 2:  , length: 2 flags: ['Z', '0', '0', 'C'] cycles [16]
			break;
		case 0x07: // RLC
			//operand 1: A, operand 2:  , length: 2 flags: ['Z', '0', '0', 'C'] cycles [8]
			break;
		case 0x08: // RRC
			//operand 1: B, operand 2:  , length: 2 flags: ['Z', '0', '0', 'C'] cycles [8]
			break;
		case 0x09: // RRC
			//operand 1: C, operand 2:  , length: 2 flags: ['Z', '0', '0', 'C'] cycles [8]
			break;
		case 0x0a: // RRC
			//operand 1: D, operand 2:  , length: 2 flags: ['Z', '0', '0', 'C'] cycles [8]
			break;
		case 0x0b: // RRC
			//operand 1: E, operand 2:  , length: 2 flags: ['Z', '0', '0', 'C'] cycles [8]
			break;
		case 0x0c: // RRC
			//operand 1: H, operand 2:  , length: 2 flags: ['Z', '0', '0', 'C'] cycles [8]
			break;
		case 0x0d: // RRC
			//operand 1: L, operand 2:  , length: 2 flags: ['Z', '0', '0', 'C'] cycles [8]
			break;
		case 0x0e: // RRC
			//operand 1: (HL), operand 2:  , length: 2 flags: ['Z', '0', '0', 'C'] cycles [16]
			break;
		case 0x0f: // RRC
			//operand 1: A, operand 2:  , length: 2 flags: ['Z', '0', '0', 'C'] cycles [8]
			break;
		case 0x10: // RL
			//operand 1: B, operand 2:  , length: 2 flags: ['Z', '0', '0', 'C'] cycles [8]
			break;
		case 0x11: // RL
			//operand 1: C, operand 2:  , length: 2 flags: ['Z', '0', '0', 'C'] cycles [8]
			break;
		case 0x12: // RL
			//operand 1: D, operand 2:  , length: 2 flags: ['Z', '0', '0', 'C'] cycles [8]
			break;
		case 0x13: // RL
			//operand 1: E, operand 2:  , length: 2 flags: ['Z', '0', '0', 'C'] cycles [8]
			break;
		case 0x14: // RL
			//operand 1: H, operand 2:  , length: 2 flags: ['Z', '0', '0', 'C'] cycles [8]
			break;
		case 0x15: // RL
			//operand 1: L, operand 2:  , length: 2 flags: ['Z', '0', '0', 'C'] cycles [8]
			break;
		case 0x16: // RL
			//operand 1: (HL), operand 2:  , length: 2 flags: ['Z', '0', '0', 'C'] cycles [16]
			break;
		case 0x17: // RL
			//operand 1: A, operand 2:  , length: 2 flags: ['Z', '0', '0', 'C'] cycles [8]
			break;
		case 0x18: // RR
			//operand 1: B, operand 2:  , length: 2 flags: ['Z', '0', '0', 'C'] cycles [8]
			break;
		case 0x19: // RR
			//operand 1: C, operand 2:  , length: 2 flags: ['Z', '0', '0', 'C'] cycles [8]
			break;
		case 0x1a: // RR
			//operand 1: D, operand 2:  , length: 2 flags: ['Z', '0', '0', 'C'] cycles [8]
			break;
		case 0x1b: // RR
			//operand 1: E, operand 2:  , length: 2 flags: ['Z', '0', '0', 'C'] cycles [8]
			break;
		case 0x1c: // RR
			//operand 1: H, operand 2:  , length: 2 flags: ['Z', '0', '0', 'C'] cycles [8]
			break;
		case 0x1d: // RR
			//operand 1: L, operand 2:  , length: 2 flags: ['Z', '0', '0', 'C'] cycles [8]
			break;
		case 0x1e: // RR
			//operand 1: (HL), operand 2:  , length: 2 flags: ['Z', '0', '0', 'C'] cycles [16]
			break;
		case 0x1f: // RR
			//operand 1: A, operand 2:  , length: 2 flags: ['Z', '0', '0', 'C'] cycles [8]
			break;
		case 0x20: // SLA
			//operand 1: B, operand 2:  , length: 2 flags: ['Z', '0', '0', 'C'] cycles [8]
			break;
		case 0x21: // SLA
			//operand 1: C, operand 2:  , length: 2 flags: ['Z', '0', '0', 'C'] cycles [8]
			break;
		case 0x22: // SLA
			//operand 1: D, operand 2:  , length: 2 flags: ['Z', '0', '0', 'C'] cycles [8]
			break;
		case 0x23: // SLA
			//operand 1: E, operand 2:  , length: 2 flags: ['Z', '0', '0', 'C'] cycles [8]
			break;
		case 0x24: // SLA
			//operand 1: H, operand 2:  , length: 2 flags: ['Z', '0', '0', 'C'] cycles [8]
			break;
		case 0x25: // SLA
			//operand 1: L, operand 2:  , length: 2 flags: ['Z', '0', '0', 'C'] cycles [8]
			break;
		case 0x26: // SLA
			//operand 1: (HL), operand 2:  , length: 2 flags: ['Z', '0', '0', 'C'] cycles [16]
			break;
		case 0x27: // SLA
			//operand 1: A, operand 2:  , length: 2 flags: ['Z', '0', '0', 'C'] cycles [8]
			break;
		case 0x28: // SRA
			//operand 1: B, operand 2:  , length: 2 flags: ['Z', '0', '0', '0'] cycles [8]
			break;
		case 0x29: // SRA
			//operand 1: C, operand 2:  , length: 2 flags: ['Z', '0', '0', '0'] cycles [8]
			break;
		case 0x2a: // SRA
			//operand 1: D, operand 2:  , length: 2 flags: ['Z', '0', '0', '0'] cycles [8]
			break;
		case 0x2b: // SRA
			//operand 1: E, operand 2:  , length: 2 flags: ['Z', '0', '0', '0'] cycles [8]
			break;
		case 0x2c: // SRA
			//operand 1: H, operand 2:  , length: 2 flags: ['Z', '0', '0', '0'] cycles [8]
			break;
		case 0x2d: // SRA
			//operand 1: L, operand 2:  , length: 2 flags: ['Z', '0', '0', '0'] cycles [8]
			break;
		case 0x2e: // SRA
			//operand 1: (HL), operand 2:  , length: 2 flags: ['Z', '0', '0', '0'] cycles [16]
			break;
		case 0x2f: // SRA
			//operand 1: A, operand 2:  , length: 2 flags: ['Z', '0', '0', '0'] cycles [8]
			break;
		case 0x30: // SWAP
			//operand 1: B, operand 2:  , length: 2 flags: ['Z', '0', '0', '0'] cycles [8]
			break;
		case 0x31: // SWAP
			//operand 1: C, operand 2:  , length: 2 flags: ['Z', '0', '0', '0'] cycles [8]
			break;
		case 0x32: // SWAP
			//operand 1: D, operand 2:  , length: 2 flags: ['Z', '0', '0', '0'] cycles [8]
			break;
		case 0x33: // SWAP
			//operand 1: E, operand 2:  , length: 2 flags: ['Z', '0', '0', '0'] cycles [8]
			break;
		case 0x34: // SWAP
			//operand 1: H, operand 2:  , length: 2 flags: ['Z', '0', '0', '0'] cycles [8]
			break;
		case 0x35: // SWAP
			//operand 1: L, operand 2:  , length: 2 flags: ['Z', '0', '0', '0'] cycles [8]
			break;
		case 0x36: // SWAP
			//operand 1: (HL), operand 2:  , length: 2 flags: ['Z', '0', '0', '0'] cycles [16]
			break;
		case 0x37: // SWAP
			//operand 1: A, operand 2:  , length: 2 flags: ['Z', '0', '0', '0'] cycles [8]
			break;
		case 0x38: // SRL
			//operand 1: B, operand 2:  , length: 2 flags: ['Z', '0', '0', 'C'] cycles [8]
			break;
		case 0x39: // SRL
			//operand 1: C, operand 2:  , length: 2 flags: ['Z', '0', '0', 'C'] cycles [8]
			break;
		case 0x3a: // SRL
			//operand 1: D, operand 2:  , length: 2 flags: ['Z', '0', '0', 'C'] cycles [8]
			break;
		case 0x3b: // SRL
			//operand 1: E, operand 2:  , length: 2 flags: ['Z', '0', '0', 'C'] cycles [8]
			break;
		case 0x3c: // SRL
			//operand 1: H, operand 2:  , length: 2 flags: ['Z', '0', '0', 'C'] cycles [8]
			break;
		case 0x3d: // SRL
			//operand 1: L, operand 2:  , length: 2 flags: ['Z', '0', '0', 'C'] cycles [8]
			break;
		case 0x3e: // SRL
			//operand 1: (HL), operand 2:  , length: 2 flags: ['Z', '0', '0', 'C'] cycles [16]
			break;
		case 0x3f: // SRL
			//operand 1: A, operand 2:  , length: 2 flags: ['Z', '0', '0', 'C'] cycles [8]
			break;
		case 0x40: // BIT
			//operand 1: 0, operand 2: B , length: 2 flags: ['Z', '0', '1', '-'] cycles [8]
			break;
		case 0x41: // BIT
			//operand 1: 0, operand 2: C , length: 2 flags: ['Z', '0', '1', '-'] cycles [8]
			break;
		case 0x42: // BIT
			//operand 1: 0, operand 2: D , length: 2 flags: ['Z', '0', '1', '-'] cycles [8]
			break;
		case 0x43: // BIT
			//operand 1: 0, operand 2: E , length: 2 flags: ['Z', '0', '1', '-'] cycles [8]
			break;
		case 0x44: // BIT
			//operand 1: 0, operand 2: H , length: 2 flags: ['Z', '0', '1', '-'] cycles [8]
			break;
		case 0x45: // BIT
			//operand 1: 0, operand 2: L , length: 2 flags: ['Z', '0', '1', '-'] cycles [8]
			break;
		case 0x46: // BIT
			//operand 1: 0, operand 2: (HL) , length: 2 flags: ['Z', '0', '1', '-'] cycles [16]
			break;
		case 0x47: // BIT
			//operand 1: 0, operand 2: A , length: 2 flags: ['Z', '0', '1', '-'] cycles [8]
			break;
		case 0x48: // BIT
			//operand 1: 1, operand 2: B , length: 2 flags: ['Z', '0', '1', '-'] cycles [8]
			break;
		case 0x49: // BIT
			//operand 1: 1, operand 2: C , length: 2 flags: ['Z', '0', '1', '-'] cycles [8]
			break;
		case 0x4a: // BIT
			//operand 1: 1, operand 2: D , length: 2 flags: ['Z', '0', '1', '-'] cycles [8]
			break;
		case 0x4b: // BIT
			//operand 1: 1, operand 2: E , length: 2 flags: ['Z', '0', '1', '-'] cycles [8]
			break;
		case 0x4c: // BIT
			//operand 1: 1, operand 2: H , length: 2 flags: ['Z', '0', '1', '-'] cycles [8]
			break;
		case 0x4d: // BIT
			//operand 1: 1, operand 2: L , length: 2 flags: ['Z', '0', '1', '-'] cycles [8]
			break;
		case 0x4e: // BIT
			//operand 1: 1, operand 2: (HL) , length: 2 flags: ['Z', '0', '1', '-'] cycles [16]
			break;
		case 0x4f: // BIT
			//operand 1: 1, operand 2: A , length: 2 flags: ['Z', '0', '1', '-'] cycles [8]
			break;
		case 0x50: // BIT
			//operand 1: 2, operand 2: B , length: 2 flags: ['Z', '0', '1', '-'] cycles [8]
			break;
		case 0x51: // BIT
			//operand 1: 2, operand 2: C , length: 2 flags: ['Z', '0', '1', '-'] cycles [8]
			break;
		case 0x52: // BIT
			//operand 1: 2, operand 2: D , length: 2 flags: ['Z', '0', '1', '-'] cycles [8]
			break;
		case 0x53: // BIT
			//operand 1: 2, operand 2: E , length: 2 flags: ['Z', '0', '1', '-'] cycles [8]
			break;
		case 0x54: // BIT
			//operand 1: 2, operand 2: H , length: 2 flags: ['Z', '0', '1', '-'] cycles [8]
			break;
		case 0x55: // BIT
			//operand 1: 2, operand 2: L , length: 2 flags: ['Z', '0', '1', '-'] cycles [8]
			break;
		case 0x56: // BIT
			//operand 1: 2, operand 2: (HL) , length: 2 flags: ['Z', '0', '1', '-'] cycles [16]
			break;
		case 0x57: // BIT
			//operand 1: 2, operand 2: A , length: 2 flags: ['Z', '0', '1', '-'] cycles [8]
			break;
		case 0x58: // BIT
			//operand 1: 3, operand 2: B , length: 2 flags: ['Z', '0', '1', '-'] cycles [8]
			break;
		case 0x59: // BIT
			//operand 1: 3, operand 2: C , length: 2 flags: ['Z', '0', '1', '-'] cycles [8]
			break;
		case 0x5a: // BIT
			//operand 1: 3, operand 2: D , length: 2 flags: ['Z', '0', '1', '-'] cycles [8]
			break;
		case 0x5b: // BIT
			//operand 1: 3, operand 2: E , length: 2 flags: ['Z', '0', '1', '-'] cycles [8]
			break;
		case 0x5c: // BIT
			//operand 1: 3, operand 2: H , length: 2 flags: ['Z', '0', '1', '-'] cycles [8]
			break;
		case 0x5d: // BIT
			//operand 1: 3, operand 2: L , length: 2 flags: ['Z', '0', '1', '-'] cycles [8]
			break;
		case 0x5e: // BIT
			//operand 1: 3, operand 2: (HL) , length: 2 flags: ['Z', '0', '1', '-'] cycles [16]
			break;
		case 0x5f: // BIT
			//operand 1: 3, operand 2: A , length: 2 flags: ['Z', '0', '1', '-'] cycles [8]
			break;
		case 0x60: // BIT
			//operand 1: 4, operand 2: B , length: 2 flags: ['Z', '0', '1', '-'] cycles [8]
			break;
		case 0x61: // BIT
			//operand 1: 4, operand 2: C , length: 2 flags: ['Z', '0', '1', '-'] cycles [8]
			break;
		case 0x62: // BIT
			//operand 1: 4, operand 2: D , length: 2 flags: ['Z', '0', '1', '-'] cycles [8]
			break;
		case 0x63: // BIT
			//operand 1: 4, operand 2: E , length: 2 flags: ['Z', '0', '1', '-'] cycles [8]
			break;
		case 0x64: // BIT
			//operand 1: 4, operand 2: H , length: 2 flags: ['Z', '0', '1', '-'] cycles [8]
			break;
		case 0x65: // BIT
			//operand 1: 4, operand 2: L , length: 2 flags: ['Z', '0', '1', '-'] cycles [8]
			break;
		case 0x66: // BIT
			//operand 1: 4, operand 2: (HL) , length: 2 flags: ['Z', '0', '1', '-'] cycles [16]
			break;
		case 0x67: // BIT
			//operand 1: 4, operand 2: A , length: 2 flags: ['Z', '0', '1', '-'] cycles [8]
			break;
		case 0x68: // BIT
			//operand 1: 5, operand 2: B , length: 2 flags: ['Z', '0', '1', '-'] cycles [8]
			break;
		case 0x69: // BIT
			//operand 1: 5, operand 2: C , length: 2 flags: ['Z', '0', '1', '-'] cycles [8]
			break;
		case 0x6a: // BIT
			//operand 1: 5, operand 2: D , length: 2 flags: ['Z', '0', '1', '-'] cycles [8]
			break;
		case 0x6b: // BIT
			//operand 1: 5, operand 2: E , length: 2 flags: ['Z', '0', '1', '-'] cycles [8]
			break;
		case 0x6c: // BIT
			//operand 1: 5, operand 2: H , length: 2 flags: ['Z', '0', '1', '-'] cycles [8]
			break;
		case 0x6d: // BIT
			//operand 1: 5, operand 2: L , length: 2 flags: ['Z', '0', '1', '-'] cycles [8]
			break;
		case 0x6e: // BIT
			//operand 1: 5, operand 2: (HL) , length: 2 flags: ['Z', '0', '1', '-'] cycles [16]
			break;
		case 0x6f: // BIT
			//operand 1: 5, operand 2: A , length: 2 flags: ['Z', '0', '1', '-'] cycles [8]
			break;
		case 0x70: // BIT
			//operand 1: 6, operand 2: B , length: 2 flags: ['Z', '0', '1', '-'] cycles [8]
			break;
		case 0x71: // BIT
			//operand 1: 6, operand 2: C , length: 2 flags: ['Z', '0', '1', '-'] cycles [8]
			break;
		case 0x72: // BIT
			//operand 1: 6, operand 2: D , length: 2 flags: ['Z', '0', '1', '-'] cycles [8]
			break;
		case 0x73: // BIT
			//operand 1: 6, operand 2: E , length: 2 flags: ['Z', '0', '1', '-'] cycles [8]
			break;
		case 0x74: // BIT
			//operand 1: 6, operand 2: H , length: 2 flags: ['Z', '0', '1', '-'] cycles [8]
			break;
		case 0x75: // BIT
			//operand 1: 6, operand 2: L , length: 2 flags: ['Z', '0', '1', '-'] cycles [8]
			break;
		case 0x76: // BIT
			//operand 1: 6, operand 2: (HL) , length: 2 flags: ['Z', '0', '1', '-'] cycles [16]
			break;
		case 0x77: // BIT
			//operand 1: 6, operand 2: A , length: 2 flags: ['Z', '0', '1', '-'] cycles [8]
			break;
		case 0x78: // BIT
			//operand 1: 7, operand 2: B , length: 2 flags: ['Z', '0', '1', '-'] cycles [8]
			break;
		case 0x79: // BIT
			//operand 1: 7, operand 2: C , length: 2 flags: ['Z', '0', '1', '-'] cycles [8]
			break;
		case 0x7a: // BIT
			//operand 1: 7, operand 2: D , length: 2 flags: ['Z', '0', '1', '-'] cycles [8]
			break;
		case 0x7b: // BIT
			//operand 1: 7, operand 2: E , length: 2 flags: ['Z', '0', '1', '-'] cycles [8]
			break;
		case 0x7c: // BIT
			//operand 1: 7, operand 2: H , length: 2 flags: ['Z', '0', '1', '-'] cycles [8]
			break;
		case 0x7d: // BIT
			//operand 1: 7, operand 2: L , length: 2 flags: ['Z', '0', '1', '-'] cycles [8]
			break;
		case 0x7e: // BIT
			//operand 1: 7, operand 2: (HL) , length: 2 flags: ['Z', '0', '1', '-'] cycles [16]
			break;
		case 0x7f: // BIT
			//operand 1: 7, operand 2: A , length: 2 flags: ['Z', '0', '1', '-'] cycles [8]
			break;
		case 0x80: // RES
			//operand 1: 0, operand 2: B , length: 2 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0x81: // RES
			//operand 1: 0, operand 2: C , length: 2 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0x82: // RES
			//operand 1: 0, operand 2: D , length: 2 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0x83: // RES
			//operand 1: 0, operand 2: E , length: 2 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0x84: // RES
			//operand 1: 0, operand 2: H , length: 2 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0x85: // RES
			//operand 1: 0, operand 2: L , length: 2 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0x86: // RES
			//operand 1: 0, operand 2: (HL) , length: 2 flags: ['-', '-', '-', '-'] cycles [16]
			break;
		case 0x87: // RES
			//operand 1: 0, operand 2: A , length: 2 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0x88: // RES
			//operand 1: 1, operand 2: B , length: 2 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0x89: // RES
			//operand 1: 1, operand 2: C , length: 2 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0x8a: // RES
			//operand 1: 1, operand 2: D , length: 2 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0x8b: // RES
			//operand 1: 1, operand 2: E , length: 2 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0x8c: // RES
			//operand 1: 1, operand 2: H , length: 2 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0x8d: // RES
			//operand 1: 1, operand 2: L , length: 2 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0x8e: // RES
			//operand 1: 1, operand 2: (HL) , length: 2 flags: ['-', '-', '-', '-'] cycles [16]
			break;
		case 0x8f: // RES
			//operand 1: 1, operand 2: A , length: 2 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0x90: // RES
			//operand 1: 2, operand 2: B , length: 2 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0x91: // RES
			//operand 1: 2, operand 2: C , length: 2 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0x92: // RES
			//operand 1: 2, operand 2: D , length: 2 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0x93: // RES
			//operand 1: 2, operand 2: E , length: 2 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0x94: // RES
			//operand 1: 2, operand 2: H , length: 2 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0x95: // RES
			//operand 1: 2, operand 2: L , length: 2 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0x96: // RES
			//operand 1: 2, operand 2: (HL) , length: 2 flags: ['-', '-', '-', '-'] cycles [16]
			break;
		case 0x97: // RES
			//operand 1: 2, operand 2: A , length: 2 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0x98: // RES
			//operand 1: 3, operand 2: B , length: 2 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0x99: // RES
			//operand 1: 3, operand 2: C , length: 2 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0x9a: // RES
			//operand 1: 3, operand 2: D , length: 2 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0x9b: // RES
			//operand 1: 3, operand 2: E , length: 2 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0x9c: // RES
			//operand 1: 3, operand 2: H , length: 2 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0x9d: // RES
			//operand 1: 3, operand 2: L , length: 2 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0x9e: // RES
			//operand 1: 3, operand 2: (HL) , length: 2 flags: ['-', '-', '-', '-'] cycles [16]
			break;
		case 0x9f: // RES
			//operand 1: 3, operand 2: A , length: 2 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0xa0: // RES
			//operand 1: 4, operand 2: B , length: 2 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0xa1: // RES
			//operand 1: 4, operand 2: C , length: 2 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0xa2: // RES
			//operand 1: 4, operand 2: D , length: 2 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0xa3: // RES
			//operand 1: 4, operand 2: E , length: 2 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0xa4: // RES
			//operand 1: 4, operand 2: H , length: 2 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0xa5: // RES
			//operand 1: 4, operand 2: L , length: 2 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0xa6: // RES
			//operand 1: 4, operand 2: (HL) , length: 2 flags: ['-', '-', '-', '-'] cycles [16]
			break;
		case 0xa7: // RES
			//operand 1: 4, operand 2: A , length: 2 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0xa8: // RES
			//operand 1: 5, operand 2: B , length: 2 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0xa9: // RES
			//operand 1: 5, operand 2: C , length: 2 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0xaa: // RES
			//operand 1: 5, operand 2: D , length: 2 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0xab: // RES
			//operand 1: 5, operand 2: E , length: 2 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0xac: // RES
			//operand 1: 5, operand 2: H , length: 2 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0xad: // RES
			//operand 1: 5, operand 2: L , length: 2 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0xae: // RES
			//operand 1: 5, operand 2: (HL) , length: 2 flags: ['-', '-', '-', '-'] cycles [16]
			break;
		case 0xaf: // RES
			//operand 1: 5, operand 2: A , length: 2 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0xb0: // RES
			//operand 1: 6, operand 2: B , length: 2 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0xb1: // RES
			//operand 1: 6, operand 2: C , length: 2 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0xb2: // RES
			//operand 1: 6, operand 2: D , length: 2 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0xb3: // RES
			//operand 1: 6, operand 2: E , length: 2 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0xb4: // RES
			//operand 1: 6, operand 2: H , length: 2 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0xb5: // RES
			//operand 1: 6, operand 2: L , length: 2 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0xb6: // RES
			//operand 1: 6, operand 2: (HL) , length: 2 flags: ['-', '-', '-', '-'] cycles [16]
			break;
		case 0xb7: // RES
			//operand 1: 6, operand 2: A , length: 2 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0xb8: // RES
			//operand 1: 7, operand 2: B , length: 2 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0xb9: // RES
			//operand 1: 7, operand 2: C , length: 2 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0xba: // RES
			//operand 1: 7, operand 2: D , length: 2 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0xbb: // RES
			//operand 1: 7, operand 2: E , length: 2 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0xbc: // RES
			//operand 1: 7, operand 2: H , length: 2 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0xbd: // RES
			//operand 1: 7, operand 2: L , length: 2 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0xbe: // RES
			//operand 1: 7, operand 2: (HL) , length: 2 flags: ['-', '-', '-', '-'] cycles [16]
			break;
		case 0xbf: // RES
			//operand 1: 7, operand 2: A , length: 2 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0xc0: // SET
			//operand 1: 0, operand 2: B , length: 2 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0xc1: // SET
			//operand 1: 0, operand 2: C , length: 2 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0xc2: // SET
			//operand 1: 0, operand 2: D , length: 2 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0xc3: // SET
			//operand 1: 0, operand 2: E , length: 2 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0xc4: // SET
			//operand 1: 0, operand 2: H , length: 2 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0xc5: // SET
			//operand 1: 0, operand 2: L , length: 2 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0xc6: // SET
			//operand 1: 0, operand 2: (HL) , length: 2 flags: ['-', '-', '-', '-'] cycles [16]
			break;
		case 0xc7: // SET
			//operand 1: 0, operand 2: A , length: 2 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0xc8: // SET
			//operand 1: 1, operand 2: B , length: 2 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0xc9: // SET
			//operand 1: 1, operand 2: C , length: 2 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0xca: // SET
			//operand 1: 1, operand 2: D , length: 2 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0xcb: // SET
			//operand 1: 1, operand 2: E , length: 2 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0xcc: // SET
			//operand 1: 1, operand 2: H , length: 2 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0xcd: // SET
			//operand 1: 1, operand 2: L , length: 2 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0xce: // SET
			//operand 1: 1, operand 2: (HL) , length: 2 flags: ['-', '-', '-', '-'] cycles [16]
			break;
		case 0xcf: // SET
			//operand 1: 1, operand 2: A , length: 2 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0xd0: // SET
			//operand 1: 2, operand 2: B , length: 2 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0xd1: // SET
			//operand 1: 2, operand 2: C , length: 2 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0xd2: // SET
			//operand 1: 2, operand 2: D , length: 2 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0xd3: // SET
			//operand 1: 2, operand 2: E , length: 2 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0xd4: // SET
			//operand 1: 2, operand 2: H , length: 2 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0xd5: // SET
			//operand 1: 2, operand 2: L , length: 2 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0xd6: // SET
			//operand 1: 2, operand 2: (HL) , length: 2 flags: ['-', '-', '-', '-'] cycles [16]
			break;
		case 0xd7: // SET
			//operand 1: 2, operand 2: A , length: 2 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0xd8: // SET
			//operand 1: 3, operand 2: B , length: 2 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0xd9: // SET
			//operand 1: 3, operand 2: C , length: 2 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0xda: // SET
			//operand 1: 3, operand 2: D , length: 2 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0xdb: // SET
			//operand 1: 3, operand 2: E , length: 2 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0xdc: // SET
			//operand 1: 3, operand 2: H , length: 2 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0xdd: // SET
			//operand 1: 3, operand 2: L , length: 2 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0xde: // SET
			//operand 1: 3, operand 2: (HL) , length: 2 flags: ['-', '-', '-', '-'] cycles [16]
			break;
		case 0xdf: // SET
			//operand 1: 3, operand 2: A , length: 2 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0xe0: // SET
			//operand 1: 4, operand 2: B , length: 2 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0xe1: // SET
			//operand 1: 4, operand 2: C , length: 2 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0xe2: // SET
			//operand 1: 4, operand 2: D , length: 2 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0xe3: // SET
			//operand 1: 4, operand 2: E , length: 2 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0xe4: // SET
			//operand 1: 4, operand 2: H , length: 2 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0xe5: // SET
			//operand 1: 4, operand 2: L , length: 2 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0xe6: // SET
			//operand 1: 4, operand 2: (HL) , length: 2 flags: ['-', '-', '-', '-'] cycles [16]
			break;
		case 0xe7: // SET
			//operand 1: 4, operand 2: A , length: 2 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0xe8: // SET
			//operand 1: 5, operand 2: B , length: 2 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0xe9: // SET
			//operand 1: 5, operand 2: C , length: 2 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0xea: // SET
			//operand 1: 5, operand 2: D , length: 2 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0xeb: // SET
			//operand 1: 5, operand 2: E , length: 2 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0xec: // SET
			//operand 1: 5, operand 2: H , length: 2 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0xed: // SET
			//operand 1: 5, operand 2: L , length: 2 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0xee: // SET
			//operand 1: 5, operand 2: (HL) , length: 2 flags: ['-', '-', '-', '-'] cycles [16]
			break;
		case 0xef: // SET
			//operand 1: 5, operand 2: A , length: 2 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0xf0: // SET
			//operand 1: 6, operand 2: B , length: 2 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0xf1: // SET
			//operand 1: 6, operand 2: C , length: 2 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0xf2: // SET
			//operand 1: 6, operand 2: D , length: 2 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0xf3: // SET
			//operand 1: 6, operand 2: E , length: 2 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0xf4: // SET
			//operand 1: 6, operand 2: H , length: 2 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0xf5: // SET
			//operand 1: 6, operand 2: L , length: 2 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0xf6: // SET
			//operand 1: 6, operand 2: (HL) , length: 2 flags: ['-', '-', '-', '-'] cycles [16]
			break;
		case 0xf7: // SET
			//operand 1: 6, operand 2: A , length: 2 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0xf8: // SET
			//operand 1: 7, operand 2: B , length: 2 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0xf9: // SET
			//operand 1: 7, operand 2: C , length: 2 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0xfa: // SET
			//operand 1: 7, operand 2: D , length: 2 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0xfb: // SET
			//operand 1: 7, operand 2: E , length: 2 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0xfc: // SET
			//operand 1: 7, operand 2: H , length: 2 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0xfd: // SET
			//operand 1: 7, operand 2: L , length: 2 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		case 0xfe: // SET
			//operand 1: 7, operand 2: (HL) , length: 2 flags: ['-', '-', '-', '-'] cycles [16]
			break;
		case 0xff: // SET
			//operand 1: 7, operand 2: A , length: 2 flags: ['-', '-', '-', '-'] cycles [8]
			break;
		}
	}
}