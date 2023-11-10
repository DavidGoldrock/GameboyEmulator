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

#define ADC(operand1,operand2) operand1 += operand2 + this->cpu->getCFlag()
#define ADD(operand1,operand2)
#define AND(operand1,operand2)
#define BIT(operand1,operand2)
#define CALL(operand1)
#define CALL(operand1,operand2)
#define CCF()
#define CP(operand1,operand2)
#define CPL()
#define DAA()
#define DEC(operand1)
#define DI()
#define EI()
#define HALT()
#define ILLEGAL()
#define INC(operand1)
#define JP(operand1)
#define JP(operand1,operand2)
#define JR(operand1)
#define JR(operand1,operand2)
#define LD(operand1,operand2)
#define LD(operand1,operand2,operand3)
#define LDH(operand1,operand2)
#define NOP()
#define OR(operand1,operand2)
#define POP(operand1)
#define PREFIX()
#define PUSH(operand1)
#define RES(operand1,operand2)
#define RET()
#define RET(operand1)
#define RETI()
#define RL(operand1)
#define RLA()
#define RLC(operand1)
#define RLCA()
#define RR(operand1)
#define RRA()
#define RRC(operand1)
#define RRCA()
#define RST(operand1)
#define SBC(operand1,operand2)
#define SCF()
#define SET(operand1,operand2)
#define SLA(operand1)
#define SRA(operand1)
#define SRL(operand1)
#define STOP(operand1)
#define SUB(operand1,operand2)
#define SWAP(operand1)
#define XOR(operand1,operand2)

void GameBoy::execute(u8 value) {
	u8 opcode = fetch();
    if (this->cpu->isPrefixed) {
        switch (opcode) {
        case 0x88:
            ADC(this->cpu->AF.A, this->cpu->BC.B);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            // calculate H  this->cpu->setHFlag();
            // calculate C  this->cpu->setCFlag();
            this->delayCycles(4);
            break;
        case 0x89:
            ADC(this->cpu->AF.A, this->cpu->BC.C);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            // calculate H  this->cpu->setHFlag();
            // calculate C  this->cpu->setCFlag();
            this->delayCycles(4);
            break;
        case 0x8A:
            ADC(this->cpu->AF.A, this->cpu->DE.D);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            // calculate H  this->cpu->setHFlag();
            // calculate C  this->cpu->setCFlag();
            this->delayCycles(4);
            break;
        case 0x8B:
            ADC(this->cpu->AF.A, this->cpu->DE.E);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            // calculate H  this->cpu->setHFlag();
            // calculate C  this->cpu->setCFlag();
            this->delayCycles(4);
            break;
        case 0x8C:
            ADC(this->cpu->AF.A, this->cpu->HL.H);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            // calculate H  this->cpu->setHFlag();
            // calculate C  this->cpu->setCFlag();
            this->delayCycles(4);
            break;
        case 0x8D:
            ADC(this->cpu->AF.A, this->cpu->HL.L);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            // calculate H  this->cpu->setHFlag();
            // calculate C  this->cpu->setCFlag();
            this->delayCycles(4);
            break;
        case 0x8E:
            ADC(this->cpu->AF.A, this->cpu->HL.HL);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            // calculate H  this->cpu->setHFlag();
            // calculate C  this->cpu->setCFlag();
            this->delayCycles(8);
            break;
        case 0x8F:
            ADC(this->cpu->AF.A, this->cpu->AF.A);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            // calculate H  this->cpu->setHFlag();
            // calculate C  this->cpu->setCFlag();
            this->delayCycles(4);
            break;
        case 0xCE:
            ADC(this->cpu->AF.A, fetch());
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            // calculate H  this->cpu->setHFlag();
            // calculate C  this->cpu->setCFlag();
            this->delayCycles(8);
            break;
        case 0x09:
            ADD(this->cpu->HL.HL, this->cpu->BC.BC);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            // calculate H  this->cpu->setHFlag();
            // calculate C  this->cpu->setCFlag();
            this->delayCycles(8);
            break;
        case 0x19:
            ADD(this->cpu->HL.HL, this->cpu->DE.DE);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            // calculate H  this->cpu->setHFlag();
            // calculate C  this->cpu->setCFlag();
            this->delayCycles(8);
            break;
        case 0x29:
            ADD(this->cpu->HL.HL, this->cpu->HL.HL);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            // calculate H  this->cpu->setHFlag();
            // calculate C  this->cpu->setCFlag();
            this->delayCycles(8);
            break;
        case 0x39:
            ADD(this->cpu->HL.HL, this->cpu->SP);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            // calculate H  this->cpu->setHFlag();
            // calculate C  this->cpu->setCFlag();
            this->delayCycles(8);
            break;
        case 0x80:
            ADD(this->cpu->AF.A, this->cpu->BC.B);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            // calculate H  this->cpu->setHFlag();
            // calculate C  this->cpu->setCFlag();
            this->delayCycles(4);
            break;
        case 0x81:
            ADD(this->cpu->AF.A, this->cpu->BC.C);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            // calculate H  this->cpu->setHFlag();
            // calculate C  this->cpu->setCFlag();
            this->delayCycles(4);
            break;
        case 0x82:
            ADD(this->cpu->AF.A, this->cpu->DE.D);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            // calculate H  this->cpu->setHFlag();
            // calculate C  this->cpu->setCFlag();
            this->delayCycles(4);
            break;
        case 0x83:
            ADD(this->cpu->AF.A, this->cpu->DE.E);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            // calculate H  this->cpu->setHFlag();
            // calculate C  this->cpu->setCFlag();
            this->delayCycles(4);
            break;
        case 0x84:
            ADD(this->cpu->AF.A, this->cpu->HL.H);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            // calculate H  this->cpu->setHFlag();
            // calculate C  this->cpu->setCFlag();
            this->delayCycles(4);
            break;
        case 0x85:
            ADD(this->cpu->AF.A, this->cpu->HL.L);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            // calculate H  this->cpu->setHFlag();
            // calculate C  this->cpu->setCFlag();
            this->delayCycles(4);
            break;
        case 0x86:
            ADD(this->cpu->AF.A, this->cpu->HL.HL);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            // calculate H  this->cpu->setHFlag();
            // calculate C  this->cpu->setCFlag();
            this->delayCycles(8);
            break;
        case 0x87:
            ADD(this->cpu->AF.A, this->cpu->AF.A);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            // calculate H  this->cpu->setHFlag();
            // calculate C  this->cpu->setCFlag();
            this->delayCycles(4);
            break;
        case 0xC6:
            ADD(this->cpu->AF.A, fetch());
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            // calculate H  this->cpu->setHFlag();
            // calculate C  this->cpu->setCFlag();
            this->delayCycles(8);
            break;
        case 0xE8:
            ADD(this->cpu->SP, fetch());
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            // calculate H  this->cpu->setHFlag();
            // calculate C  this->cpu->setCFlag();
            this->delayCycles(16);
            break;
        case 0xA0:
            AND(this->cpu->AF.A, this->cpu->BC.B);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(true);
            this->cpu->setCFlag(false);
            this->delayCycles(4);
            break;
        case 0xA1:
            AND(this->cpu->AF.A, this->cpu->BC.C);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(true);
            this->cpu->setCFlag(false);
            this->delayCycles(4);
            break;
        case 0xA2:
            AND(this->cpu->AF.A, this->cpu->DE.D);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(true);
            this->cpu->setCFlag(false);
            this->delayCycles(4);
            break;
        case 0xA3:
            AND(this->cpu->AF.A, this->cpu->DE.E);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(true);
            this->cpu->setCFlag(false);
            this->delayCycles(4);
            break;
        case 0xA4:
            AND(this->cpu->AF.A, this->cpu->HL.H);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(true);
            this->cpu->setCFlag(false);
            this->delayCycles(4);
            break;
        case 0xA5:
            AND(this->cpu->AF.A, this->cpu->HL.L);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(true);
            this->cpu->setCFlag(false);
            this->delayCycles(4);
            break;
        case 0xA6:
            AND(this->cpu->AF.A, this->cpu->HL.HL);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(true);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0xA7:
            AND(this->cpu->AF.A, this->cpu->AF.A);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(true);
            this->cpu->setCFlag(false);
            this->delayCycles(4);
            break;
        case 0xE6:
            AND(this->cpu->AF.A, fetch());
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(true);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0xC4:
            CALL(NZ, a16);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(24);
            break;
        case 0xCC:
            CALL(Z, a16);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(24);
            break;
        case 0xCD:
            CALL(a16);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(24);
            break;
        case 0xD4:
            CALL(NC, a16);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(24);
            break;
        case 0xDC:
            CALL(this->cpu->BC.C, a16);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(24);
            break;
        case 0x3F:
            CCF();
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            // calculate C  this->cpu->setCFlag();
            this->delayCycles(4);
            break;
        case 0xB8:
            CP(this->cpu->AF.A, this->cpu->BC.B);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(true);
            // calculate H  this->cpu->setHFlag();
            // calculate C  this->cpu->setCFlag();
            this->delayCycles(4);
            break;
        case 0xB9:
            CP(this->cpu->AF.A, this->cpu->BC.C);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(true);
            // calculate H  this->cpu->setHFlag();
            // calculate C  this->cpu->setCFlag();
            this->delayCycles(4);
            break;
        case 0xBA:
            CP(this->cpu->AF.A, this->cpu->DE.D);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(true);
            // calculate H  this->cpu->setHFlag();
            // calculate C  this->cpu->setCFlag();
            this->delayCycles(4);
            break;
        case 0xBB:
            CP(this->cpu->AF.A, this->cpu->DE.E);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(true);
            // calculate H  this->cpu->setHFlag();
            // calculate C  this->cpu->setCFlag();
            this->delayCycles(4);
            break;
        case 0xBC:
            CP(this->cpu->AF.A, this->cpu->HL.H);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(true);
            // calculate H  this->cpu->setHFlag();
            // calculate C  this->cpu->setCFlag();
            this->delayCycles(4);
            break;
        case 0xBD:
            CP(this->cpu->AF.A, this->cpu->HL.L);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(true);
            // calculate H  this->cpu->setHFlag();
            // calculate C  this->cpu->setCFlag();
            this->delayCycles(4);
            break;
        case 0xBE:
            CP(this->cpu->AF.A, this->cpu->HL.HL);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(true);
            // calculate H  this->cpu->setHFlag();
            // calculate C  this->cpu->setCFlag();
            this->delayCycles(8);
            break;
        case 0xBF:
            CP(this->cpu->AF.A, this->cpu->AF.A);
            this->cpu->setZFlag(true);
            this->cpu->setNFlag(true);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(4);
            break;
        case 0xFE:
            CP(this->cpu->AF.A, fetch());
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(true);
            // calculate H  this->cpu->setHFlag();
            // calculate C  this->cpu->setCFlag();
            this->delayCycles(8);
            break;
        case 0x2F:
            CPL();
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(true);
            this->cpu->setHFlag(true);
            this->cpu->setCFlag(false);
            this->delayCycles(4);
            break;
        case 0x27:
            DAA();
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            // calculate C  this->cpu->setCFlag();
            this->delayCycles(4);
            break;
        case 0x05:
            DEC(this->cpu->BC.B);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(true);
            // calculate H  this->cpu->setHFlag();
            this->cpu->setCFlag(false);
            this->delayCycles(4);
            break;
        case 0x0B:
            DEC(this->cpu->BC.BC);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0x0D:
            DEC(this->cpu->BC.C);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(true);
            // calculate H  this->cpu->setHFlag();
            this->cpu->setCFlag(false);
            this->delayCycles(4);
            break;
        case 0x15:
            DEC(this->cpu->DE.D);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(true);
            // calculate H  this->cpu->setHFlag();
            this->cpu->setCFlag(false);
            this->delayCycles(4);
            break;
        case 0x1B:
            DEC(this->cpu->DE.DE);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0x1D:
            DEC(this->cpu->DE.E);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(true);
            // calculate H  this->cpu->setHFlag();
            this->cpu->setCFlag(false);
            this->delayCycles(4);
            break;
        case 0x25:
            DEC(this->cpu->HL.H);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(true);
            // calculate H  this->cpu->setHFlag();
            this->cpu->setCFlag(false);
            this->delayCycles(4);
            break;
        case 0x2B:
            DEC(this->cpu->HL.HL);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0x2D:
            DEC(this->cpu->HL.L);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(true);
            // calculate H  this->cpu->setHFlag();
            this->cpu->setCFlag(false);
            this->delayCycles(4);
            break;
        case 0x35:
            DEC(this->cpu->HL.HL);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(true);
            // calculate H  this->cpu->setHFlag();
            this->cpu->setCFlag(false);
            this->delayCycles(12);
            break;
        case 0x3B:
            DEC(this->cpu->SP);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0x3D:
            DEC(this->cpu->AF.A);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(true);
            // calculate H  this->cpu->setHFlag();
            this->cpu->setCFlag(false);
            this->delayCycles(4);
            break;
        case 0xF3:
            DI();
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(4);
            break;
        case 0xFB:
            EI();
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(4);
            break;
        case 0x76:
            HALT();
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(4);
            break;
        case 0xD3:
            ILLEGAL();
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(4);
            break;
        case 0xDB:
            ILLEGAL();
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(4);
            break;
        case 0xDD:
            ILLEGAL();
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(4);
            break;
        case 0xE3:
            ILLEGAL();
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(4);
            break;
        case 0xE4:
            ILLEGAL();
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(4);
            break;
        case 0xEB:
            ILLEGAL();
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(4);
            break;
        case 0xEC:
            ILLEGAL();
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(4);
            break;
        case 0xED:
            ILLEGAL();
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(4);
            break;
        case 0xF4:
            ILLEGAL();
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(4);
            break;
        case 0xFC:
            ILLEGAL();
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(4);
            break;
        case 0xFD:
            ILLEGAL();
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(4);
            break;
        case 0x03:
            INC(this->cpu->BC.BC);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0x04:
            INC(this->cpu->BC.B);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            // calculate H  this->cpu->setHFlag();
            this->cpu->setCFlag(false);
            this->delayCycles(4);
            break;
        case 0x0C:
            INC(this->cpu->BC.C);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            // calculate H  this->cpu->setHFlag();
            this->cpu->setCFlag(false);
            this->delayCycles(4);
            break;
        case 0x13:
            INC(this->cpu->DE.DE);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0x14:
            INC(this->cpu->DE.D);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            // calculate H  this->cpu->setHFlag();
            this->cpu->setCFlag(false);
            this->delayCycles(4);
            break;
        case 0x1C:
            INC(this->cpu->DE.E);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            // calculate H  this->cpu->setHFlag();
            this->cpu->setCFlag(false);
            this->delayCycles(4);
            break;
        case 0x23:
            INC(this->cpu->HL.HL);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0x24:
            INC(this->cpu->HL.H);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            // calculate H  this->cpu->setHFlag();
            this->cpu->setCFlag(false);
            this->delayCycles(4);
            break;
        case 0x2C:
            INC(this->cpu->HL.L);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            // calculate H  this->cpu->setHFlag();
            this->cpu->setCFlag(false);
            this->delayCycles(4);
            break;
        case 0x33:
            INC(this->cpu->SP);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0x34:
            INC(this->cpu->HL.HL);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            // calculate H  this->cpu->setHFlag();
            this->cpu->setCFlag(false);
            this->delayCycles(12);
            break;
        case 0x3C:
            INC(this->cpu->AF.A);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            // calculate H  this->cpu->setHFlag();
            this->cpu->setCFlag(false);
            this->delayCycles(4);
            break;
        case 0xC2:
            JP(NZ, a16);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(16);
            break;
        case 0xC3:
            JP(a16);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(16);
            break;
        case 0xCA:
            JP(Z, a16);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(16);
            break;
        case 0xD2:
            JP(NC, a16);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(16);
            break;
        case 0xDA:
            JP(this->cpu->BC.C, a16);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(16);
            break;
        case 0xE9:
            JP(this->cpu->HL.HL);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(4);
            break;
        case 0x18:
            JR(fetch());
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(12);
            break;
        case 0x20:
            JR(NZ, fetch());
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(12);
            break;
        case 0x28:
            JR(Z, fetch());
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(12);
            break;
        case 0x30:
            JR(NC, fetch());
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(12);
            break;
        case 0x38:
            JR(this->cpu->BC.C, fetch());
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(12);
            break;
        case 0x01:
            LD(this->cpu->BC.BC, n16);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(12);
            break;
        case 0x02:
            LD(this->cpu->BC.BC, this->cpu->AF.A);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0x06:
            LD(this->cpu->BC.B, fetch());
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0x08:
            LD(a16, this->cpu->SP);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(20);
            break;
        case 0x0A:
            LD(this->cpu->AF.A, this->cpu->BC.BC);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0x0E:
            LD(this->cpu->BC.C, fetch());
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0x11:
            LD(this->cpu->DE.DE, n16);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(12);
            break;
        case 0x12:
            LD(this->cpu->DE.DE, this->cpu->AF.A);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0x16:
            LD(this->cpu->DE.D, fetch());
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0x1A:
            LD(this->cpu->AF.A, this->cpu->DE.DE);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0x1E:
            LD(this->cpu->DE.E, fetch());
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0x21:
            LD(this->cpu->HL.HL, n16);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(12);
            break;
        case 0x22:
            LD(this->cpu->HL.HL, this->cpu->AF.A);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0x26:
            LD(this->cpu->HL.H, fetch());
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0x2A:
            LD(this->cpu->AF.A, this->cpu->HL.HL);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0x2E:
            LD(this->cpu->HL.L, fetch());
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0x31:
            LD(this->cpu->SP, n16);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(12);
            break;
        case 0x32:
            LD(this->cpu->HL.HL, this->cpu->AF.A);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0x36:
            LD(this->cpu->HL.HL, fetch());
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(12);
            break;
        case 0x3A:
            LD(this->cpu->AF.A, this->cpu->HL.HL);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0x3E:
            LD(this->cpu->AF.A, fetch());
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0x40:
            LD(this->cpu->BC.B, this->cpu->BC.B);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(4);
            break;
        case 0x41:
            LD(this->cpu->BC.B, this->cpu->BC.C);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(4);
            break;
        case 0x42:
            LD(this->cpu->BC.B, this->cpu->DE.D);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(4);
            break;
        case 0x43:
            LD(this->cpu->BC.B, this->cpu->DE.E);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(4);
            break;
        case 0x44:
            LD(this->cpu->BC.B, this->cpu->HL.H);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(4);
            break;
        case 0x45:
            LD(this->cpu->BC.B, this->cpu->HL.L);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(4);
            break;
        case 0x46:
            LD(this->cpu->BC.B, this->cpu->HL.HL);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0x47:
            LD(this->cpu->BC.B, this->cpu->AF.A);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(4);
            break;
        case 0x48:
            LD(this->cpu->BC.C, this->cpu->BC.B);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(4);
            break;
        case 0x49:
            LD(this->cpu->BC.C, this->cpu->BC.C);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(4);
            break;
        case 0x4A:
            LD(this->cpu->BC.C, this->cpu->DE.D);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(4);
            break;
        case 0x4B:
            LD(this->cpu->BC.C, this->cpu->DE.E);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(4);
            break;
        case 0x4C:
            LD(this->cpu->BC.C, this->cpu->HL.H);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(4);
            break;
        case 0x4D:
            LD(this->cpu->BC.C, this->cpu->HL.L);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(4);
            break;
        case 0x4E:
            LD(this->cpu->BC.C, this->cpu->HL.HL);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0x4F:
            LD(this->cpu->BC.C, this->cpu->AF.A);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(4);
            break;
        case 0x50:
            LD(this->cpu->DE.D, this->cpu->BC.B);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(4);
            break;
        case 0x51:
            LD(this->cpu->DE.D, this->cpu->BC.C);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(4);
            break;
        case 0x52:
            LD(this->cpu->DE.D, this->cpu->DE.D);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(4);
            break;
        case 0x53:
            LD(this->cpu->DE.D, this->cpu->DE.E);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(4);
            break;
        case 0x54:
            LD(this->cpu->DE.D, this->cpu->HL.H);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(4);
            break;
        case 0x55:
            LD(this->cpu->DE.D, this->cpu->HL.L);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(4);
            break;
        case 0x56:
            LD(this->cpu->DE.D, this->cpu->HL.HL);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0x57:
            LD(this->cpu->DE.D, this->cpu->AF.A);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(4);
            break;
        case 0x58:
            LD(this->cpu->DE.E, this->cpu->BC.B);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(4);
            break;
        case 0x59:
            LD(this->cpu->DE.E, this->cpu->BC.C);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(4);
            break;
        case 0x5A:
            LD(this->cpu->DE.E, this->cpu->DE.D);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(4);
            break;
        case 0x5B:
            LD(this->cpu->DE.E, this->cpu->DE.E);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(4);
            break;
        case 0x5C:
            LD(this->cpu->DE.E, this->cpu->HL.H);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(4);
            break;
        case 0x5D:
            LD(this->cpu->DE.E, this->cpu->HL.L);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(4);
            break;
        case 0x5E:
            LD(this->cpu->DE.E, this->cpu->HL.HL);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0x5F:
            LD(this->cpu->DE.E, this->cpu->AF.A);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(4);
            break;
        case 0x60:
            LD(this->cpu->HL.H, this->cpu->BC.B);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(4);
            break;
        case 0x61:
            LD(this->cpu->HL.H, this->cpu->BC.C);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(4);
            break;
        case 0x62:
            LD(this->cpu->HL.H, this->cpu->DE.D);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(4);
            break;
        case 0x63:
            LD(this->cpu->HL.H, this->cpu->DE.E);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(4);
            break;
        case 0x64:
            LD(this->cpu->HL.H, this->cpu->HL.H);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(4);
            break;
        case 0x65:
            LD(this->cpu->HL.H, this->cpu->HL.L);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(4);
            break;
        case 0x66:
            LD(this->cpu->HL.H, this->cpu->HL.HL);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0x67:
            LD(this->cpu->HL.H, this->cpu->AF.A);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(4);
            break;
        case 0x68:
            LD(this->cpu->HL.L, this->cpu->BC.B);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(4);
            break;
        case 0x69:
            LD(this->cpu->HL.L, this->cpu->BC.C);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(4);
            break;
        case 0x6A:
            LD(this->cpu->HL.L, this->cpu->DE.D);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(4);
            break;
        case 0x6B:
            LD(this->cpu->HL.L, this->cpu->DE.E);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(4);
            break;
        case 0x6C:
            LD(this->cpu->HL.L, this->cpu->HL.H);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(4);
            break;
        case 0x6D:
            LD(this->cpu->HL.L, this->cpu->HL.L);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(4);
            break;
        case 0x6E:
            LD(this->cpu->HL.L, this->cpu->HL.HL);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0x6F:
            LD(this->cpu->HL.L, this->cpu->AF.A);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(4);
            break;
        case 0x70:
            LD(this->cpu->HL.HL, this->cpu->BC.B);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0x71:
            LD(this->cpu->HL.HL, this->cpu->BC.C);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0x72:
            LD(this->cpu->HL.HL, this->cpu->DE.D);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0x73:
            LD(this->cpu->HL.HL, this->cpu->DE.E);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0x74:
            LD(this->cpu->HL.HL, this->cpu->HL.H);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0x75:
            LD(this->cpu->HL.HL, this->cpu->HL.L);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0x77:
            LD(this->cpu->HL.HL, this->cpu->AF.A);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0x78:
            LD(this->cpu->AF.A, this->cpu->BC.B);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(4);
            break;
        case 0x79:
            LD(this->cpu->AF.A, this->cpu->BC.C);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(4);
            break;
        case 0x7A:
            LD(this->cpu->AF.A, this->cpu->DE.D);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(4);
            break;
        case 0x7B:
            LD(this->cpu->AF.A, this->cpu->DE.E);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(4);
            break;
        case 0x7C:
            LD(this->cpu->AF.A, this->cpu->HL.H);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(4);
            break;
        case 0x7D:
            LD(this->cpu->AF.A, this->cpu->HL.L);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(4);
            break;
        case 0x7E:
            LD(this->cpu->AF.A, this->cpu->HL.HL);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0x7F:
            LD(this->cpu->AF.A, this->cpu->AF.A);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(4);
            break;
        case 0xE2:
            LD(this->cpu->BC.C, this->cpu->AF.A);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0xEA:
            LD(a16, this->cpu->AF.A);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(16);
            break;
        case 0xF2:
            LD(this->cpu->AF.A, this->cpu->BC.C);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0xF8:
            LD(this->cpu->HL.HL, this->cpu->SP, fetch());
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            // calculate H  this->cpu->setHFlag();
            // calculate C  this->cpu->setCFlag();
            this->delayCycles(12);
            break;
        case 0xF9:
            LD(this->cpu->SP, this->cpu->HL.HL);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0xFA:
            LD(this->cpu->AF.A, a16);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(16);
            break;
        case 0xE0:
            LDH(fetch(), this->cpu->AF.A);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(12);
            break;
        case 0xF0:
            LDH(this->cpu->AF.A, fetch());
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(12);
            break;
        case 0x00:
            NOP();
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(4);
            break;
        case 0xB0:
            OR(this->cpu->AF.A, this->cpu->BC.B);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(4);
            break;
        case 0xB1:
            OR(this->cpu->AF.A, this->cpu->BC.C);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(4);
            break;
        case 0xB2:
            OR(this->cpu->AF.A, this->cpu->DE.D);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(4);
            break;
        case 0xB3:
            OR(this->cpu->AF.A, this->cpu->DE.E);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(4);
            break;
        case 0xB4:
            OR(this->cpu->AF.A, this->cpu->HL.H);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(4);
            break;
        case 0xB5:
            OR(this->cpu->AF.A, this->cpu->HL.L);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(4);
            break;
        case 0xB6:
            OR(this->cpu->AF.A, this->cpu->HL.HL);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0xB7:
            OR(this->cpu->AF.A, this->cpu->AF.A);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(4);
            break;
        case 0xF6:
            OR(this->cpu->AF.A, fetch());
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0xC1:
            POP(this->cpu->BC.BC);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(12);
            break;
        case 0xD1:
            POP(this->cpu->DE.DE);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(12);
            break;
        case 0xE1:
            POP(this->cpu->HL.HL);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(12);
            break;
        case 0xF1:
            POP(this->cpu->AF.AF);
            // calculate Z  this->cpu->setZFlag();
            // calculate N  this->cpu->setNFlag();
            // calculate H  this->cpu->setHFlag();
            // calculate C  this->cpu->setCFlag();
            this->delayCycles(12);
            break;
        case 0xCB:
            PREFIX();
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(4);
            break;
        case 0xC5:
            PUSH(this->cpu->BC.BC);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(16);
            break;
        case 0xD5:
            PUSH(this->cpu->DE.DE);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(16);
            break;
        case 0xE5:
            PUSH(this->cpu->HL.HL);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(16);
            break;
        case 0xF5:
            PUSH(this->cpu->AF.AF);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(16);
            break;
        case 0xC0:
            RET(NZ);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(20);
            break;
        case 0xC8:
            RET(Z);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(20);
            break;
        case 0xC9:
            RET();
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(16);
            break;
        case 0xD0:
            RET(NC);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(20);
            break;
        case 0xD8:
            RET(this->cpu->BC.C);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(20);
            break;
        case 0xD9:
            RETI();
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(16);
            break;
        case 0x17:
            RLA();
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            // calculate C  this->cpu->setCFlag();
            this->delayCycles(4);
            break;
        case 0x07:
            RLCA();
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            // calculate C  this->cpu->setCFlag();
            this->delayCycles(4);
            break;
        case 0x1F:
            RRA();
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            // calculate C  this->cpu->setCFlag();
            this->delayCycles(4);
            break;
        case 0x0F:
            RRCA();
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            // calculate C  this->cpu->setCFlag();
            this->delayCycles(4);
            break;
        case 0xC7:
            RST(0);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(16);
            break;
        case 0xCF:
            RST(8);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(16);
            break;
        case 0xD7:
            RST(10);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(16);
            break;
        case 0xDF:
            RST(18);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(16);
            break;
        case 0xE7:
            RST(20);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(16);
            break;
        case 0xEF:
            RST(28);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(16);
            break;
        case 0xF7:
            RST(30);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(16);
            break;
        case 0xFF:
            RST(38);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(16);
            break;
        case 0x98:
            SBC(this->cpu->AF.A, this->cpu->BC.B);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(true);
            // calculate H  this->cpu->setHFlag();
            // calculate C  this->cpu->setCFlag();
            this->delayCycles(4);
            break;
        case 0x99:
            SBC(this->cpu->AF.A, this->cpu->BC.C);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(true);
            // calculate H  this->cpu->setHFlag();
            // calculate C  this->cpu->setCFlag();
            this->delayCycles(4);
            break;
        case 0x9A:
            SBC(this->cpu->AF.A, this->cpu->DE.D);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(true);
            // calculate H  this->cpu->setHFlag();
            // calculate C  this->cpu->setCFlag();
            this->delayCycles(4);
            break;
        case 0x9B:
            SBC(this->cpu->AF.A, this->cpu->DE.E);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(true);
            // calculate H  this->cpu->setHFlag();
            // calculate C  this->cpu->setCFlag();
            this->delayCycles(4);
            break;
        case 0x9C:
            SBC(this->cpu->AF.A, this->cpu->HL.H);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(true);
            // calculate H  this->cpu->setHFlag();
            // calculate C  this->cpu->setCFlag();
            this->delayCycles(4);
            break;
        case 0x9D:
            SBC(this->cpu->AF.A, this->cpu->HL.L);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(true);
            // calculate H  this->cpu->setHFlag();
            // calculate C  this->cpu->setCFlag();
            this->delayCycles(4);
            break;
        case 0x9E:
            SBC(this->cpu->AF.A, this->cpu->HL.HL);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(true);
            // calculate H  this->cpu->setHFlag();
            // calculate C  this->cpu->setCFlag();
            this->delayCycles(8);
            break;
        case 0x9F:
            SBC(this->cpu->AF.A, this->cpu->AF.A);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(true);
            // calculate H  this->cpu->setHFlag();
            this->cpu->setCFlag(false);
            this->delayCycles(4);
            break;
        case 0xDE:
            SBC(this->cpu->AF.A, fetch());
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(true);
            // calculate H  this->cpu->setHFlag();
            // calculate C  this->cpu->setCFlag();
            this->delayCycles(8);
            break;
        case 0x37:
            SCF();
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(true);
            this->delayCycles(4);
            break;
        case 0x10:
            STOP(fetch());
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(4);
            break;
        case 0x90:
            SUB(this->cpu->AF.A, this->cpu->BC.B);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(true);
            // calculate H  this->cpu->setHFlag();
            // calculate C  this->cpu->setCFlag();
            this->delayCycles(4);
            break;
        case 0x91:
            SUB(this->cpu->AF.A, this->cpu->BC.C);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(true);
            // calculate H  this->cpu->setHFlag();
            // calculate C  this->cpu->setCFlag();
            this->delayCycles(4);
            break;
        case 0x92:
            SUB(this->cpu->AF.A, this->cpu->DE.D);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(true);
            // calculate H  this->cpu->setHFlag();
            // calculate C  this->cpu->setCFlag();
            this->delayCycles(4);
            break;
        case 0x93:
            SUB(this->cpu->AF.A, this->cpu->DE.E);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(true);
            // calculate H  this->cpu->setHFlag();
            // calculate C  this->cpu->setCFlag();
            this->delayCycles(4);
            break;
        case 0x94:
            SUB(this->cpu->AF.A, this->cpu->HL.H);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(true);
            // calculate H  this->cpu->setHFlag();
            // calculate C  this->cpu->setCFlag();
            this->delayCycles(4);
            break;
        case 0x95:
            SUB(this->cpu->AF.A, this->cpu->HL.L);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(true);
            // calculate H  this->cpu->setHFlag();
            // calculate C  this->cpu->setCFlag();
            this->delayCycles(4);
            break;
        case 0x96:
            SUB(this->cpu->AF.A, this->cpu->HL.HL);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(true);
            // calculate H  this->cpu->setHFlag();
            // calculate C  this->cpu->setCFlag();
            this->delayCycles(8);
            break;
        case 0x97:
            SUB(this->cpu->AF.A, this->cpu->AF.A);
            this->cpu->setZFlag(true);
            this->cpu->setNFlag(true);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(4);
            break;
        case 0xD6:
            SUB(this->cpu->AF.A, fetch());
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(true);
            // calculate H  this->cpu->setHFlag();
            // calculate C  this->cpu->setCFlag();
            this->delayCycles(8);
            break;
        case 0xA8:
            XOR(this->cpu->AF.A, this->cpu->BC.B);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(4);
            break;
        case 0xA9:
            XOR(this->cpu->AF.A, this->cpu->BC.C);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(4);
            break;
        case 0xAA:
            XOR(this->cpu->AF.A, this->cpu->DE.D);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(4);
            break;
        case 0xAB:
            XOR(this->cpu->AF.A, this->cpu->DE.E);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(4);
            break;
        case 0xAC:
            XOR(this->cpu->AF.A, this->cpu->HL.H);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(4);
            break;
        case 0xAD:
            XOR(this->cpu->AF.A, this->cpu->HL.L);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(4);
            break;
        case 0xAE:
            XOR(this->cpu->AF.A, this->cpu->HL.HL);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0xAF:
            XOR(this->cpu->AF.A, this->cpu->AF.A);
            this->cpu->setZFlag(true);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(4);
            break;
        case 0xEE:
            XOR(this->cpu->AF.A, fetch());
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        }
    }
    else {
        switch (opcode) {
        case 0x40:
            BIT(0, this->cpu->BC.B);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(true);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0x41:
            BIT(0, this->cpu->BC.C);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(true);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0x42:
            BIT(0, this->cpu->DE.D);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(true);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0x43:
            BIT(0, this->cpu->DE.E);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(true);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0x44:
            BIT(0, this->cpu->HL.H);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(true);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0x45:
            BIT(0, this->cpu->HL.L);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(true);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0x46:
            BIT(0, this->cpu->HL.HL);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(true);
            this->cpu->setCFlag(false);
            this->delayCycles(12);
            break;
        case 0x47:
            BIT(0, this->cpu->AF.A);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(true);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0x48:
            BIT(1, this->cpu->BC.B);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(true);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0x49:
            BIT(1, this->cpu->BC.C);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(true);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0x4A:
            BIT(1, this->cpu->DE.D);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(true);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0x4B:
            BIT(1, this->cpu->DE.E);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(true);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0x4C:
            BIT(1, this->cpu->HL.H);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(true);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0x4D:
            BIT(1, this->cpu->HL.L);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(true);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0x4E:
            BIT(1, this->cpu->HL.HL);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(true);
            this->cpu->setCFlag(false);
            this->delayCycles(12);
            break;
        case 0x4F:
            BIT(1, this->cpu->AF.A);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(true);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0x50:
            BIT(2, this->cpu->BC.B);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(true);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0x51:
            BIT(2, this->cpu->BC.C);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(true);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0x52:
            BIT(2, this->cpu->DE.D);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(true);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0x53:
            BIT(2, this->cpu->DE.E);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(true);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0x54:
            BIT(2, this->cpu->HL.H);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(true);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0x55:
            BIT(2, this->cpu->HL.L);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(true);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0x56:
            BIT(2, this->cpu->HL.HL);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(true);
            this->cpu->setCFlag(false);
            this->delayCycles(12);
            break;
        case 0x57:
            BIT(2, this->cpu->AF.A);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(true);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0x58:
            BIT(3, this->cpu->BC.B);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(true);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0x59:
            BIT(3, this->cpu->BC.C);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(true);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0x5A:
            BIT(3, this->cpu->DE.D);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(true);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0x5B:
            BIT(3, this->cpu->DE.E);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(true);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0x5C:
            BIT(3, this->cpu->HL.H);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(true);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0x5D:
            BIT(3, this->cpu->HL.L);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(true);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0x5E:
            BIT(3, this->cpu->HL.HL);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(true);
            this->cpu->setCFlag(false);
            this->delayCycles(12);
            break;
        case 0x5F:
            BIT(3, this->cpu->AF.A);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(true);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0x60:
            BIT(4, this->cpu->BC.B);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(true);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0x61:
            BIT(4, this->cpu->BC.C);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(true);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0x62:
            BIT(4, this->cpu->DE.D);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(true);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0x63:
            BIT(4, this->cpu->DE.E);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(true);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0x64:
            BIT(4, this->cpu->HL.H);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(true);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0x65:
            BIT(4, this->cpu->HL.L);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(true);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0x66:
            BIT(4, this->cpu->HL.HL);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(true);
            this->cpu->setCFlag(false);
            this->delayCycles(12);
            break;
        case 0x67:
            BIT(4, this->cpu->AF.A);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(true);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0x68:
            BIT(5, this->cpu->BC.B);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(true);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0x69:
            BIT(5, this->cpu->BC.C);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(true);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0x6A:
            BIT(5, this->cpu->DE.D);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(true);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0x6B:
            BIT(5, this->cpu->DE.E);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(true);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0x6C:
            BIT(5, this->cpu->HL.H);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(true);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0x6D:
            BIT(5, this->cpu->HL.L);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(true);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0x6E:
            BIT(5, this->cpu->HL.HL);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(true);
            this->cpu->setCFlag(false);
            this->delayCycles(12);
            break;
        case 0x6F:
            BIT(5, this->cpu->AF.A);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(true);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0x70:
            BIT(6, this->cpu->BC.B);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(true);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0x71:
            BIT(6, this->cpu->BC.C);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(true);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0x72:
            BIT(6, this->cpu->DE.D);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(true);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0x73:
            BIT(6, this->cpu->DE.E);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(true);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0x74:
            BIT(6, this->cpu->HL.H);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(true);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0x75:
            BIT(6, this->cpu->HL.L);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(true);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0x76:
            BIT(6, this->cpu->HL.HL);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(true);
            this->cpu->setCFlag(false);
            this->delayCycles(12);
            break;
        case 0x77:
            BIT(6, this->cpu->AF.A);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(true);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0x78:
            BIT(7, this->cpu->BC.B);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(true);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0x79:
            BIT(7, this->cpu->BC.C);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(true);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0x7A:
            BIT(7, this->cpu->DE.D);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(true);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0x7B:
            BIT(7, this->cpu->DE.E);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(true);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0x7C:
            BIT(7, this->cpu->HL.H);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(true);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0x7D:
            BIT(7, this->cpu->HL.L);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(true);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0x7E:
            BIT(7, this->cpu->HL.HL);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(true);
            this->cpu->setCFlag(false);
            this->delayCycles(12);
            break;
        case 0x7F:
            BIT(7, this->cpu->AF.A);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(true);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0x80:
            RES(0, this->cpu->BC.B);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0x81:
            RES(0, this->cpu->BC.C);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0x82:
            RES(0, this->cpu->DE.D);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0x83:
            RES(0, this->cpu->DE.E);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0x84:
            RES(0, this->cpu->HL.H);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0x85:
            RES(0, this->cpu->HL.L);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0x86:
            RES(0, this->cpu->HL.HL);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(16);
            break;
        case 0x87:
            RES(0, this->cpu->AF.A);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0x88:
            RES(1, this->cpu->BC.B);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0x89:
            RES(1, this->cpu->BC.C);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0x8A:
            RES(1, this->cpu->DE.D);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0x8B:
            RES(1, this->cpu->DE.E);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0x8C:
            RES(1, this->cpu->HL.H);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0x8D:
            RES(1, this->cpu->HL.L);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0x8E:
            RES(1, this->cpu->HL.HL);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(16);
            break;
        case 0x8F:
            RES(1, this->cpu->AF.A);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0x90:
            RES(2, this->cpu->BC.B);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0x91:
            RES(2, this->cpu->BC.C);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0x92:
            RES(2, this->cpu->DE.D);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0x93:
            RES(2, this->cpu->DE.E);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0x94:
            RES(2, this->cpu->HL.H);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0x95:
            RES(2, this->cpu->HL.L);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0x96:
            RES(2, this->cpu->HL.HL);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(16);
            break;
        case 0x97:
            RES(2, this->cpu->AF.A);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0x98:
            RES(3, this->cpu->BC.B);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0x99:
            RES(3, this->cpu->BC.C);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0x9A:
            RES(3, this->cpu->DE.D);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0x9B:
            RES(3, this->cpu->DE.E);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0x9C:
            RES(3, this->cpu->HL.H);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0x9D:
            RES(3, this->cpu->HL.L);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0x9E:
            RES(3, this->cpu->HL.HL);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(16);
            break;
        case 0x9F:
            RES(3, this->cpu->AF.A);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0xA0:
            RES(4, this->cpu->BC.B);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0xA1:
            RES(4, this->cpu->BC.C);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0xA2:
            RES(4, this->cpu->DE.D);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0xA3:
            RES(4, this->cpu->DE.E);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0xA4:
            RES(4, this->cpu->HL.H);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0xA5:
            RES(4, this->cpu->HL.L);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0xA6:
            RES(4, this->cpu->HL.HL);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(16);
            break;
        case 0xA7:
            RES(4, this->cpu->AF.A);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0xA8:
            RES(5, this->cpu->BC.B);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0xA9:
            RES(5, this->cpu->BC.C);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0xAA:
            RES(5, this->cpu->DE.D);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0xAB:
            RES(5, this->cpu->DE.E);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0xAC:
            RES(5, this->cpu->HL.H);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0xAD:
            RES(5, this->cpu->HL.L);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0xAE:
            RES(5, this->cpu->HL.HL);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(16);
            break;
        case 0xAF:
            RES(5, this->cpu->AF.A);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0xB0:
            RES(6, this->cpu->BC.B);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0xB1:
            RES(6, this->cpu->BC.C);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0xB2:
            RES(6, this->cpu->DE.D);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0xB3:
            RES(6, this->cpu->DE.E);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0xB4:
            RES(6, this->cpu->HL.H);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0xB5:
            RES(6, this->cpu->HL.L);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0xB6:
            RES(6, this->cpu->HL.HL);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(16);
            break;
        case 0xB7:
            RES(6, this->cpu->AF.A);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0xB8:
            RES(7, this->cpu->BC.B);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0xB9:
            RES(7, this->cpu->BC.C);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0xBA:
            RES(7, this->cpu->DE.D);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0xBB:
            RES(7, this->cpu->DE.E);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0xBC:
            RES(7, this->cpu->HL.H);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0xBD:
            RES(7, this->cpu->HL.L);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0xBE:
            RES(7, this->cpu->HL.HL);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(16);
            break;
        case 0xBF:
            RES(7, this->cpu->AF.A);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0x10:
            RL(this->cpu->BC.B);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            // calculate C  this->cpu->setCFlag();
            this->delayCycles(8);
            break;
        case 0x11:
            RL(this->cpu->BC.C);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            // calculate C  this->cpu->setCFlag();
            this->delayCycles(8);
            break;
        case 0x12:
            RL(this->cpu->DE.D);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            // calculate C  this->cpu->setCFlag();
            this->delayCycles(8);
            break;
        case 0x13:
            RL(this->cpu->DE.E);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            // calculate C  this->cpu->setCFlag();
            this->delayCycles(8);
            break;
        case 0x14:
            RL(this->cpu->HL.H);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            // calculate C  this->cpu->setCFlag();
            this->delayCycles(8);
            break;
        case 0x15:
            RL(this->cpu->HL.L);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            // calculate C  this->cpu->setCFlag();
            this->delayCycles(8);
            break;
        case 0x16:
            RL(this->cpu->HL.HL);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            // calculate C  this->cpu->setCFlag();
            this->delayCycles(16);
            break;
        case 0x17:
            RL(this->cpu->AF.A);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            // calculate C  this->cpu->setCFlag();
            this->delayCycles(8);
            break;
        case 0x00:
            RLC(this->cpu->BC.B);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            // calculate C  this->cpu->setCFlag();
            this->delayCycles(8);
            break;
        case 0x01:
            RLC(this->cpu->BC.C);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            // calculate C  this->cpu->setCFlag();
            this->delayCycles(8);
            break;
        case 0x02:
            RLC(this->cpu->DE.D);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            // calculate C  this->cpu->setCFlag();
            this->delayCycles(8);
            break;
        case 0x03:
            RLC(this->cpu->DE.E);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            // calculate C  this->cpu->setCFlag();
            this->delayCycles(8);
            break;
        case 0x04:
            RLC(this->cpu->HL.H);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            // calculate C  this->cpu->setCFlag();
            this->delayCycles(8);
            break;
        case 0x05:
            RLC(this->cpu->HL.L);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            // calculate C  this->cpu->setCFlag();
            this->delayCycles(8);
            break;
        case 0x06:
            RLC(this->cpu->HL.HL);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            // calculate C  this->cpu->setCFlag();
            this->delayCycles(16);
            break;
        case 0x07:
            RLC(this->cpu->AF.A);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            // calculate C  this->cpu->setCFlag();
            this->delayCycles(8);
            break;
        case 0x18:
            RR(this->cpu->BC.B);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            // calculate C  this->cpu->setCFlag();
            this->delayCycles(8);
            break;
        case 0x19:
            RR(this->cpu->BC.C);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            // calculate C  this->cpu->setCFlag();
            this->delayCycles(8);
            break;
        case 0x1A:
            RR(this->cpu->DE.D);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            // calculate C  this->cpu->setCFlag();
            this->delayCycles(8);
            break;
        case 0x1B:
            RR(this->cpu->DE.E);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            // calculate C  this->cpu->setCFlag();
            this->delayCycles(8);
            break;
        case 0x1C:
            RR(this->cpu->HL.H);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            // calculate C  this->cpu->setCFlag();
            this->delayCycles(8);
            break;
        case 0x1D:
            RR(this->cpu->HL.L);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            // calculate C  this->cpu->setCFlag();
            this->delayCycles(8);
            break;
        case 0x1E:
            RR(this->cpu->HL.HL);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            // calculate C  this->cpu->setCFlag();
            this->delayCycles(16);
            break;
        case 0x1F:
            RR(this->cpu->AF.A);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            // calculate C  this->cpu->setCFlag();
            this->delayCycles(8);
            break;
        case 0x08:
            RRC(this->cpu->BC.B);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            // calculate C  this->cpu->setCFlag();
            this->delayCycles(8);
            break;
        case 0x09:
            RRC(this->cpu->BC.C);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            // calculate C  this->cpu->setCFlag();
            this->delayCycles(8);
            break;
        case 0x0A:
            RRC(this->cpu->DE.D);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            // calculate C  this->cpu->setCFlag();
            this->delayCycles(8);
            break;
        case 0x0B:
            RRC(this->cpu->DE.E);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            // calculate C  this->cpu->setCFlag();
            this->delayCycles(8);
            break;
        case 0x0C:
            RRC(this->cpu->HL.H);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            // calculate C  this->cpu->setCFlag();
            this->delayCycles(8);
            break;
        case 0x0D:
            RRC(this->cpu->HL.L);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            // calculate C  this->cpu->setCFlag();
            this->delayCycles(8);
            break;
        case 0x0E:
            RRC(this->cpu->HL.HL);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            // calculate C  this->cpu->setCFlag();
            this->delayCycles(16);
            break;
        case 0x0F:
            RRC(this->cpu->AF.A);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            // calculate C  this->cpu->setCFlag();
            this->delayCycles(8);
            break;
        case 0xC0:
            SET(0, this->cpu->BC.B);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0xC1:
            SET(0, this->cpu->BC.C);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0xC2:
            SET(0, this->cpu->DE.D);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0xC3:
            SET(0, this->cpu->DE.E);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0xC4:
            SET(0, this->cpu->HL.H);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0xC5:
            SET(0, this->cpu->HL.L);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0xC6:
            SET(0, this->cpu->HL.HL);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(16);
            break;
        case 0xC7:
            SET(0, this->cpu->AF.A);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0xC8:
            SET(1, this->cpu->BC.B);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0xC9:
            SET(1, this->cpu->BC.C);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0xCA:
            SET(1, this->cpu->DE.D);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0xCB:
            SET(1, this->cpu->DE.E);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0xCC:
            SET(1, this->cpu->HL.H);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0xCD:
            SET(1, this->cpu->HL.L);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0xCE:
            SET(1, this->cpu->HL.HL);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(16);
            break;
        case 0xCF:
            SET(1, this->cpu->AF.A);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0xD0:
            SET(2, this->cpu->BC.B);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0xD1:
            SET(2, this->cpu->BC.C);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0xD2:
            SET(2, this->cpu->DE.D);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0xD3:
            SET(2, this->cpu->DE.E);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0xD4:
            SET(2, this->cpu->HL.H);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0xD5:
            SET(2, this->cpu->HL.L);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0xD6:
            SET(2, this->cpu->HL.HL);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(16);
            break;
        case 0xD7:
            SET(2, this->cpu->AF.A);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0xD8:
            SET(3, this->cpu->BC.B);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0xD9:
            SET(3, this->cpu->BC.C);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0xDA:
            SET(3, this->cpu->DE.D);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0xDB:
            SET(3, this->cpu->DE.E);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0xDC:
            SET(3, this->cpu->HL.H);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0xDD:
            SET(3, this->cpu->HL.L);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0xDE:
            SET(3, this->cpu->HL.HL);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(16);
            break;
        case 0xDF:
            SET(3, this->cpu->AF.A);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0xE0:
            SET(4, this->cpu->BC.B);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0xE1:
            SET(4, this->cpu->BC.C);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0xE2:
            SET(4, this->cpu->DE.D);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0xE3:
            SET(4, this->cpu->DE.E);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0xE4:
            SET(4, this->cpu->HL.H);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0xE5:
            SET(4, this->cpu->HL.L);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0xE6:
            SET(4, this->cpu->HL.HL);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(16);
            break;
        case 0xE7:
            SET(4, this->cpu->AF.A);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0xE8:
            SET(5, this->cpu->BC.B);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0xE9:
            SET(5, this->cpu->BC.C);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0xEA:
            SET(5, this->cpu->DE.D);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0xEB:
            SET(5, this->cpu->DE.E);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0xEC:
            SET(5, this->cpu->HL.H);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0xED:
            SET(5, this->cpu->HL.L);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0xEE:
            SET(5, this->cpu->HL.HL);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(16);
            break;
        case 0xEF:
            SET(5, this->cpu->AF.A);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0xF0:
            SET(6, this->cpu->BC.B);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0xF1:
            SET(6, this->cpu->BC.C);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0xF2:
            SET(6, this->cpu->DE.D);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0xF3:
            SET(6, this->cpu->DE.E);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0xF4:
            SET(6, this->cpu->HL.H);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0xF5:
            SET(6, this->cpu->HL.L);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0xF6:
            SET(6, this->cpu->HL.HL);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(16);
            break;
        case 0xF7:
            SET(6, this->cpu->AF.A);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0xF8:
            SET(7, this->cpu->BC.B);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0xF9:
            SET(7, this->cpu->BC.C);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0xFA:
            SET(7, this->cpu->DE.D);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0xFB:
            SET(7, this->cpu->DE.E);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0xFC:
            SET(7, this->cpu->HL.H);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0xFD:
            SET(7, this->cpu->HL.L);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0xFE:
            SET(7, this->cpu->HL.HL);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(16);
            break;
        case 0xFF:
            SET(7, this->cpu->AF.A);
            this->cpu->setZFlag(false);
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0x20:
            SLA(this->cpu->BC.B);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            // calculate C  this->cpu->setCFlag();
            this->delayCycles(8);
            break;
        case 0x21:
            SLA(this->cpu->BC.C);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            // calculate C  this->cpu->setCFlag();
            this->delayCycles(8);
            break;
        case 0x22:
            SLA(this->cpu->DE.D);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            // calculate C  this->cpu->setCFlag();
            this->delayCycles(8);
            break;
        case 0x23:
            SLA(this->cpu->DE.E);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            // calculate C  this->cpu->setCFlag();
            this->delayCycles(8);
            break;
        case 0x24:
            SLA(this->cpu->HL.H);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            // calculate C  this->cpu->setCFlag();
            this->delayCycles(8);
            break;
        case 0x25:
            SLA(this->cpu->HL.L);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            // calculate C  this->cpu->setCFlag();
            this->delayCycles(8);
            break;
        case 0x26:
            SLA(this->cpu->HL.HL);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            // calculate C  this->cpu->setCFlag();
            this->delayCycles(16);
            break;
        case 0x27:
            SLA(this->cpu->AF.A);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            // calculate C  this->cpu->setCFlag();
            this->delayCycles(8);
            break;
        case 0x28:
            SRA(this->cpu->BC.B);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            // calculate C  this->cpu->setCFlag();
            this->delayCycles(8);
            break;
        case 0x29:
            SRA(this->cpu->BC.C);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            // calculate C  this->cpu->setCFlag();
            this->delayCycles(8);
            break;
        case 0x2A:
            SRA(this->cpu->DE.D);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            // calculate C  this->cpu->setCFlag();
            this->delayCycles(8);
            break;
        case 0x2B:
            SRA(this->cpu->DE.E);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            // calculate C  this->cpu->setCFlag();
            this->delayCycles(8);
            break;
        case 0x2C:
            SRA(this->cpu->HL.H);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            // calculate C  this->cpu->setCFlag();
            this->delayCycles(8);
            break;
        case 0x2D:
            SRA(this->cpu->HL.L);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            // calculate C  this->cpu->setCFlag();
            this->delayCycles(8);
            break;
        case 0x2E:
            SRA(this->cpu->HL.HL);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            // calculate C  this->cpu->setCFlag();
            this->delayCycles(16);
            break;
        case 0x2F:
            SRA(this->cpu->AF.A);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            // calculate C  this->cpu->setCFlag();
            this->delayCycles(8);
            break;
        case 0x38:
            SRL(this->cpu->BC.B);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            // calculate C  this->cpu->setCFlag();
            this->delayCycles(8);
            break;
        case 0x39:
            SRL(this->cpu->BC.C);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            // calculate C  this->cpu->setCFlag();
            this->delayCycles(8);
            break;
        case 0x3A:
            SRL(this->cpu->DE.D);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            // calculate C  this->cpu->setCFlag();
            this->delayCycles(8);
            break;
        case 0x3B:
            SRL(this->cpu->DE.E);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            // calculate C  this->cpu->setCFlag();
            this->delayCycles(8);
            break;
        case 0x3C:
            SRL(this->cpu->HL.H);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            // calculate C  this->cpu->setCFlag();
            this->delayCycles(8);
            break;
        case 0x3D:
            SRL(this->cpu->HL.L);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            // calculate C  this->cpu->setCFlag();
            this->delayCycles(8);
            break;
        case 0x3E:
            SRL(this->cpu->HL.HL);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            // calculate C  this->cpu->setCFlag();
            this->delayCycles(16);
            break;
        case 0x3F:
            SRL(this->cpu->AF.A);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            // calculate C  this->cpu->setCFlag();
            this->delayCycles(8);
            break;
        case 0x30:
            SWAP(this->cpu->BC.B);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0x31:
            SWAP(this->cpu->BC.C);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0x32:
            SWAP(this->cpu->DE.D);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0x33:
            SWAP(this->cpu->DE.E);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0x34:
            SWAP(this->cpu->HL.H);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0x35:
            SWAP(this->cpu->HL.L);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        case 0x36:
            SWAP(this->cpu->HL.HL);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(16);
            break;
        case 0x37:
            SWAP(this->cpu->AF.A);
            // calculate Z  this->cpu->setZFlag();
            this->cpu->setNFlag(false);
            this->cpu->setHFlag(false);
            this->cpu->setCFlag(false);
            this->delayCycles(8);
            break;
        }
    }
}