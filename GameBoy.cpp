#include "GameBoy.h"
#include "PhysicalRAM.h"
#include <stdlib.h>
#include <iostream>

GameBoy::GameBoy()
{
  this->physicalRAM = new PhysicalRAM();
  this->cartridgeRAM = new CartridgeRAM();
  this->cpu = new CPU();
}

GameBoy::~GameBoy()
{
  delete this->physicalRAM;
  delete this->cartridgeRAM;
  delete cpu;
}

void GameBoy::setValue(u32 location, u8 value)
{
  if (this->physicalRAM->isInRange(location))
  {
    this->physicalRAM->setValue(location, value);
  }
  else if (this->cartridgeRAM->isInRange(location))
  {
    this->cartridgeRAM->setValue(location, value);
  }
  else
  {
    std::cout << "[FAILED] ACCESSING ERROR: NO MODULE IN VALUE RANGE" << std::endl;
  }
}

u8 GameBoy::getValue(u32 location)
{
  if (this->physicalRAM->isInRange(location))
  {
    return this->physicalRAM->getValue(location);
  }
  else if (this->cartridgeRAM->isInRange(location))
  {
    return this->cartridgeRAM->getValue(location);
  }
  else
  {
    std::cout << "[FAILED] ACCESSING ERROR: NO MODULE IN VALUE RANGE" << std::endl;
    return -1;
  }
}

u8 GameBoy::fetch()
{
  u8 value = this->getValue(this->cpu->PC);
  this->cpu->PC++;
  return value;
}

u16 GameBoy::fetch16()
{
  u16 value = this->fetch();
  value = value << 8;
  value += this->fetch();
  return value;
}

void GameBoy::delayCycles(int cycles) {}

#define ADC_4_2(operand1, operand2)             \
  std::cout << "ADC_4" << std::endl;            \
  u32 clone = operand1;                         \
  operand1 += operand2 + this->cpu->getCFlag(); \
  this->delayCycles(4);                         \
  this->cpu->setNFlag(false);
  this->cpu->setZFlag(clone != 0 && operand1 == 0);
// calculate H  this->cpu->setHFlag();
// calculate C  this->cpu->setCFlag();

#define ADC_8_2(operand1, operand2)  \
  std::cout << "ADC_8" << std::endl; \
  this->delayCycles(8);              \
  this->cpu->setNFlag(false);
// calculate Z  this->cpu->setZFlag();
// calculate H  this->cpu->setHFlag();
// calculate C  this->cpu->setCFlag();

#define ADD_16_2(operand1, operand2)  \
  std::cout << "ADD_16" << std::endl; \
  this->delayCycles(16);              \
  this->cpu->setZFlag(false);         \
  this->cpu->setNFlag(false);
// calculate H  this->cpu->setHFlag();
// calculate C  this->cpu->setCFlag();

#define ADD_4_2(operand1, operand2)  \
  std::cout << "ADD_4" << std::endl; \
  this->delayCycles(4);              \
  this->cpu->setNFlag(false);
// calculate Z  this->cpu->setZFlag();
// calculate H  this->cpu->setHFlag();
// calculate C  this->cpu->setCFlag();

#define ADD_8_2(operand1, operand2)  \
  std::cout << "ADD_8" << std::endl; \
  this->delayCycles(8);              \
  this->cpu->setNFlag(false);
// calculate H  this->cpu->setHFlag();
// calculate C  this->cpu->setCFlag();

#define ADD_8_2(operand1, operand2)  \
  std::cout << "ADD_8" << std::endl; \
  this->delayCycles(8);              \
  this->cpu->setNFlag(false);
// calculate Z  this->cpu->setZFlag();
// calculate H  this->cpu->setHFlag();
// calculate C  this->cpu->setCFlag();

#define AND_4_2(operand1, operand2)  \
  std::cout << "AND_4" << std::endl; \
  this->delayCycles(4);              \
  this->cpu->setNFlag(false);        \
  this->cpu->setHFlag(true);         \
  this->cpu->setCFlag(false);
// calculate Z  this->cpu->setZFlag();

#define AND_8_2(operand1, operand2)  \
  std::cout << "AND_8" << std::endl; \
  this->delayCycles(8);              \
  this->cpu->setNFlag(false);        \
  this->cpu->setHFlag(true);         \
  this->cpu->setCFlag(false);
// calculate Z  this->cpu->setZFlag();

#define BIT_12_2(operand1, operand2)  \
  std::cout << "BIT_12" << std::endl; \
  this->delayCycles(12);              \
  this->cpu->setNFlag(false);         \
  this->cpu->setHFlag(true);
// calculate Z  this->cpu->setZFlag();

#define BIT_8_2(operand1, operand2)  \
  std::cout << "BIT_8" << std::endl; \
  this->delayCycles(8);              \
  this->cpu->setNFlag(false);        \
  this->cpu->setHFlag(true);
// calculate Z  this->cpu->setZFlag();

#define CALL_24_1(operand1)            \
  std::cout << "CALL_24" << std::endl; \
  this->delayCycles(24);

#define CALL_24_1_NC(operand1)              \
  if (!this->cpu->getCFlag())               \
  {                                         \
    std::cout << "CALL_24_NC" << std::endl; \
    this->delayCycles(24);                  \
  }
#define CALL_24_1_NZ(operand1)              \
  if (!this->cpu->getZFlag())               \
  {                                         \
    std::cout << "CALL_24_NZ" << std::endl; \
    this->delayCycles(24);                  \
  }
#define CALL_24_1_Z(operand1)              \
  if (this->cpu->getZFlag())               \
  {                                        \
    std::cout << "CALL_24_Z" << std::endl; \
    this->delayCycles(24);                 \
  }
#define CALL_24_2(operand1, operand2)  \
  std::cout << "CALL_24" << std::endl; \
  this->delayCycles(24);

#define CCF_4_0()                    \
  std::cout << "CCF_4" << std::endl; \
  this->delayCycles(4);              \
  this->cpu->setNFlag(false);        \
  this->cpu->setHFlag(false);
// calculate C  this->cpu->setCFlag();

#define CPL_4_0()                    \
  std::cout << "CPL_4" << std::endl; \
  this->delayCycles(4);              \
  this->cpu->setNFlag(true);         \
  this->cpu->setHFlag(true);

#define CP_4_2(operand1, operand2)  \
  std::cout << "CP_4" << std::endl; \
  this->delayCycles(4);             \
  this->cpu->setNFlag(true);
// calculate Z  this->cpu->setZFlag();
// calculate H  this->cpu->setHFlag();
// calculate C  this->cpu->setCFlag();

#define CP_4_2(operand1, operand2)  \
  std::cout << "CP_4" << std::endl; \
  this->delayCycles(4);             \
  this->cpu->setZFlag(true);        \
  this->cpu->setNFlag(true);        \
  this->cpu->setHFlag(false);       \
  this->cpu->setCFlag(false);

#define CP_8_2(operand1, operand2)  \
  std::cout << "CP_8" << std::endl; \
  this->delayCycles(8);             \
  this->cpu->setNFlag(true);

// calculate Z  this->cpu->setZFlag();
// calculate H  this->cpu->setHFlag();
// calculate C  this->cpu->setCFlag();

#define DAA_4_0()                    \
  std::cout << "DAA_4" << std::endl; \
  this->delayCycles(4);              \
  this->cpu->setHFlag(false);
// calculate Z  this->cpu->setZFlag();
// calculate C  this->cpu->setCFlag();

#define DEC_12_1(operand1)            \
  std::cout << "DEC_12" << std::endl; \
  this->delayCycles(12);              \
  this->cpu->setNFlag(true);
// calculate Z  this->cpu->setZFlag();
// calculate H  this->cpu->setHFlag();

#define DEC_4_1(operand1)            \
  std::cout << "DEC_4" << std::endl; \
  this->delayCycles(4);              \
  this->cpu->setNFlag(true);
// calculate Z  this->cpu->setZFlag();
// calculate H  this->cpu->setHFlag();

#define DEC_8_1(operand1)            \
  std::cout << "DEC_8" << std::endl; \
  this->delayCycles(8);

#define DI_4_0()                    \
  std::cout << "DI_4" << std::endl; \
  this->delayCycles(4);

#define EI_4_0()                    \
  std::cout << "EI_4" << std::endl; \
  this->delayCycles(4);

#define HALT_4_0()                    \
  std::cout << "HALT_4" << std::endl; \
  this->delayCycles(4);

#define ILLEGAL_4_0()                    \
  std::cout << "ILLEGAL_4" << std::endl; \
  this->delayCycles(4);

#define INC_12_1(operand1)            \
  std::cout << "INC_12" << std::endl; \
  this->delayCycles(12);              \
  this->cpu->setNFlag(false);
// calculate Z  this->cpu->setZFlag();
// calculate H  this->cpu->setHFlag();

#define INC_4_1(operand1)            \
  std::cout << "INC_4" << std::endl; \
  this->delayCycles(4);              \
  this->cpu->setNFlag(false);
// calculate Z  this->cpu->setZFlag();
// calculate H  this->cpu->setHFlag();

#define INC_8_1(operand1)            \
  std::cout << "INC_8" << std::endl; \
  this->delayCycles(8);

#define JP_16_1(operand1)            \
  std::cout << "JP_16" << std::endl; \
  this->delayCycles(16);

#define JP_16_1_NC(operand1)              \
  if (!this->cpu->getCFlag())             \
  {                                       \
    std::cout << "JP_16_NC" << std::endl; \
    this->delayCycles(16);                \
  }
#define JP_16_1_NZ(operand1)              \
  if (!this->cpu->getZFlag())             \
  {                                       \
    std::cout << "JP_16_NZ" << std::endl; \
    this->delayCycles(16);                \
  }
#define JP_16_1_Z(operand1)              \
  if (this->cpu->getZFlag())             \
  {                                      \
    std::cout << "JP_16_Z" << std::endl; \
    this->delayCycles(16);               \
  }
#define JP_16_2(operand1, operand2)  \
  std::cout << "JP_16" << std::endl; \
  this->delayCycles(16);

#define JP_4_1(operand1)            \
  std::cout << "JP_4" << std::endl; \
  this->delayCycles(4);

#define JR_12_1(operand1)            \
  std::cout << "JR_12" << std::endl; \
  this->delayCycles(12);

#define JR_12_1_NC(operand1)              \
  if (!this->cpu->getCFlag())             \
  {                                       \
    std::cout << "JR_12_NC" << std::endl; \
    this->delayCycles(12);                \
  }
#define JR_12_1_NZ(operand1)              \
  if (!this->cpu->getZFlag())             \
  {                                       \
    std::cout << "JR_12_NZ" << std::endl; \
    this->delayCycles(12);                \
  }
#define JR_12_1_Z(operand1)              \
  if (this->cpu->getZFlag())             \
  {                                      \
    std::cout << "JR_12_Z" << std::endl; \
    this->delayCycles(12);               \
  }
#define JR_12_2(operand1, operand2)  \
  std::cout << "JR_12" << std::endl; \
  this->delayCycles(12);

#define LDH_12_2(operand1, operand2)  \
  std::cout << "LDH_12" << std::endl; \
  this->delayCycles(12);

#define LD_12_2(operand1, operand2)  \
  std::cout << "LD_12" << std::endl; \
  this->delayCycles(12);

#define LD_12_3(operand1, operand2, operand3) \
  std::cout << "LD_12" << std::endl;          \
  this->delayCycles(12);                      \
  this->cpu->setZFlag(false);                 \
  this->cpu->setNFlag(false);
// calculate H  this->cpu->setHFlag();
// calculate C  this->cpu->setCFlag();

#define LD_16_2(operand1, operand2)  \
  std::cout << "LD_16" << std::endl; \
  this->delayCycles(16);

#define LD_20_2(operand1, operand2)  \
  std::cout << "LD_20" << std::endl; \
  this->delayCycles(20);

#define LD_4_2(operand1, operand2)  \
  std::cout << "LD_4" << std::endl; \
  this->delayCycles(4);

#define LD_8_2(operand1, operand2)  \
  std::cout << "LD_8" << std::endl; \
  this->delayCycles(8);

#define NOP_4_0()                    \
  std::cout << "NOP_4" << std::endl; \
  this->delayCycles(4);

#define OR_4_2(operand1, operand2)  \
  std::cout << "OR_4" << std::endl; \
  this->delayCycles(4);             \
  this->cpu->setNFlag(false);       \
  this->cpu->setHFlag(false);       \
  this->cpu->setCFlag(false);
// calculate Z  this->cpu->setZFlag();

#define OR_8_2(operand1, operand2)  \
  std::cout << "OR_8" << std::endl; \
  this->delayCycles(8);             \
  this->cpu->setNFlag(false);       \
  this->cpu->setHFlag(false);       \
  this->cpu->setCFlag(false);
// calculate Z  this->cpu->setZFlag();

#define POP_12_1(operand1)            \
  std::cout << "POP_12" << std::endl; \
  this->delayCycles(12);

#define POP_12_1(operand1)            \
  std::cout << "POP_12" << std::endl; \
  this->delayCycles(12);

// calculate Z  this->cpu->setZFlag();
// calculate N  this->cpu->setNFlag();
// calculate H  this->cpu->setHFlag();
// calculate C  this->cpu->setCFlag();

#define PREFIX_4_0()                    \
  std::cout << "PREFIX_4" << std::endl; \
  this->delayCycles(4);

#define PUSH_16_1(operand1)            \
  std::cout << "PUSH_16" << std::endl; \
  this->delayCycles(16);

#define RES_16_2(operand1, operand2)  \
  std::cout << "RES_16" << std::endl; \
  this->delayCycles(16);

#define RES_8_2(operand1, operand2)  \
  std::cout << "RES_8" << std::endl; \
  this->delayCycles(8);

#define RETI_16_0()                    \
  std::cout << "RETI_16" << std::endl; \
  this->delayCycles(16);

#define RET_16_0()                    \
  std::cout << "RET_16" << std::endl; \
  this->delayCycles(16);

#define RET_20_0_NC()                      \
  if (!this->cpu->getCFlag())              \
  {                                        \
    std::cout << "RET_20_NC" << std::endl; \
    this->delayCycles(20);                 \
  }
#define RET_20_0_NZ()                      \
  if (!this->cpu->getZFlag())              \
  {                                        \
    std::cout << "RET_20_NZ" << std::endl; \
    this->delayCycles(20);                 \
  }
#define RET_20_0_Z()                      \
  if (this->cpu->getZFlag())              \
  {                                       \
    std::cout << "RET_20_Z" << std::endl; \
    this->delayCycles(20);                \
  }
#define RET_20_1(operand1)            \
  std::cout << "RET_20" << std::endl; \
  this->delayCycles(20);

#define RLA_4_0()                    \
  std::cout << "RLA_4" << std::endl; \
  this->delayCycles(4);              \
  this->cpu->setZFlag(false);        \
  this->cpu->setNFlag(false);        \
  this->cpu->setHFlag(false);
// calculate C  this->cpu->setCFlag();

#define RLCA_4_0()                    \
  std::cout << "RLCA_4" << std::endl; \
  this->delayCycles(4);               \
  this->cpu->setZFlag(false);         \
  this->cpu->setNFlag(false);         \
  this->cpu->setHFlag(false);
// calculate C  this->cpu->setCFlag();

#define RLC_16_1(operand1)            \
  std::cout << "RLC_16" << std::endl; \
  this->delayCycles(16);              \
  this->cpu->setNFlag(false);         \
  this->cpu->setHFlag(false);
// calculate Z  this->cpu->setZFlag();
// calculate C  this->cpu->setCFlag();

#define RLC_8_1(operand1)            \
  std::cout << "RLC_8" << std::endl; \
  this->delayCycles(8);              \
  this->cpu->setNFlag(false);        \
  this->cpu->setHFlag(false);
// calculate Z  this->cpu->setZFlag();
// calculate C  this->cpu->setCFlag();

#define RL_16_1(operand1)            \
  std::cout << "RL_16" << std::endl; \
  this->delayCycles(16);             \
  this->cpu->setNFlag(false);        \
  this->cpu->setHFlag(false);
// calculate Z  this->cpu->setZFlag();
// calculate C  this->cpu->setCFlag();

#define RL_8_1(operand1)            \
  std::cout << "RL_8" << std::endl; \
  this->delayCycles(8);             \
  this->cpu->setNFlag(false);       \
  this->cpu->setHFlag(false);
// calculate Z  this->cpu->setZFlag();
// calculate C  this->cpu->setCFlag();

#define RRA_4_0()                    \
  std::cout << "RRA_4" << std::endl; \
  this->delayCycles(4);              \
  this->cpu->setZFlag(false);        \
  this->cpu->setNFlag(false);        \
  this->cpu->setHFlag(false);
// calculate C  this->cpu->setCFlag();

#define RRCA_4_0()                    \
  std::cout << "RRCA_4" << std::endl; \
  this->delayCycles(4);               \
  this->cpu->setZFlag(false);         \
  this->cpu->setNFlag(false);         \
  this->cpu->setHFlag(false);
// calculate C  this->cpu->setCFlag();

#define RRC_16_1(operand1)            \
  std::cout << "RRC_16" << std::endl; \
  this->delayCycles(16);              \
  this->cpu->setNFlag(false);         \
  this->cpu->setHFlag(false);
// calculate Z  this->cpu->setZFlag();
// calculate C  this->cpu->setCFlag();

#define RRC_8_1(operand1)            \
  std::cout << "RRC_8" << std::endl; \
  this->delayCycles(8);              \
  this->cpu->setNFlag(false);        \
  this->cpu->setHFlag(false);
// calculate Z  this->cpu->setZFlag();
// calculate C  this->cpu->setCFlag();

#define RR_16_1(operand1)            \
  std::cout << "RR_16" << std::endl; \
  this->delayCycles(16);             \
  this->cpu->setNFlag(false);        \
  this->cpu->setHFlag(false);
// calculate Z  this->cpu->setZFlag();
// calculate C  this->cpu->setCFlag();

#define RR_8_1(operand1)            \
  std::cout << "RR_8" << std::endl; \
  this->delayCycles(8);             \
  this->cpu->setNFlag(false);       \
  this->cpu->setHFlag(false);
// calculate Z  this->cpu->setZFlag();
// calculate C  this->cpu->setCFlag();

#define RST_16_1(operand1)            \
  std::cout << "RST_16" << std::endl; \
  this->delayCycles(16);

#define SBC_4_2(operand1, operand2)  \
  std::cout << "SBC_4" << std::endl; \
  this->delayCycles(4);              \
  this->cpu->setNFlag(true);
// calculate Z  this->cpu->setZFlag();
// calculate H  this->cpu->setHFlag();

#define SBC_4_2(operand1, operand2)  \
  std::cout << "SBC_4" << std::endl; \
  this->delayCycles(4);              \
  this->cpu->setNFlag(true);
// calculate Z  this->cpu->setZFlag();
// calculate H  this->cpu->setHFlag();
// calculate C  this->cpu->setCFlag();

#define SBC_8_2(operand1, operand2)  \
  std::cout << "SBC_8" << std::endl; \
  this->delayCycles(8);              \
  this->cpu->setNFlag(true);
// calculate Z  this->cpu->setZFlag();
// calculate H  this->cpu->setHFlag();
// calculate C  this->cpu->setCFlag();

#define SCF_4_0()                    \
  std::cout << "SCF_4" << std::endl; \
  this->delayCycles(4);              \
  this->cpu->setNFlag(false);        \
  this->cpu->setHFlag(false);        \
  this->cpu->setCFlag(true);

#define SET_16_2(operand1, operand2)  \
  std::cout << "SET_16" << std::endl; \
  this->delayCycles(16);

#define SET_8_2(operand1, operand2)  \
  std::cout << "SET_8" << std::endl; \
  this->delayCycles(8);

#define SLA_16_1(operand1)            \
  std::cout << "SLA_16" << std::endl; \
  this->delayCycles(16);              \
  this->cpu->setNFlag(false);         \
  this->cpu->setHFlag(false);
// calculate Z  this->cpu->setZFlag();
// calculate C  this->cpu->setCFlag();

#define SLA_8_1(operand1)            \
  std::cout << "SLA_8" << std::endl; \
  this->delayCycles(8);              \
  this->cpu->setNFlag(false);        \
  this->cpu->setHFlag(false);
// calculate Z  this->cpu->setZFlag();
// calculate C  this->cpu->setCFlag();

#define SRA_16_1(operand1)            \
  std::cout << "SRA_16" << std::endl; \
  this->delayCycles(16);              \
  this->cpu->setNFlag(false);         \
  this->cpu->setHFlag(false);
// calculate Z  this->cpu->setZFlag();
// calculate C  this->cpu->setCFlag();

#define SRA_8_1(operand1)            \
  std::cout << "SRA_8" << std::endl; \
  this->delayCycles(8);              \
  this->cpu->setNFlag(false);        \
  this->cpu->setHFlag(false);
// calculate Z  this->cpu->setZFlag();
// calculate C  this->cpu->setCFlag();

#define SRL_16_1(operand1)            \
  std::cout << "SRL_16" << std::endl; \
  this->delayCycles(16);              \
  this->cpu->setNFlag(false);         \
  this->cpu->setHFlag(false);
// calculate Z  this->cpu->setZFlag();
// calculate C  this->cpu->setCFlag();

#define SRL_8_1(operand1)            \
  std::cout << "SRL_8" << std::endl; \
  this->delayCycles(8);              \
  this->cpu->setNFlag(false);        \
  this->cpu->setHFlag(false);
// calculate Z  this->cpu->setZFlag();
// calculate C  this->cpu->setCFlag();

#define STOP_4_1(operand1)            \
  std::cout << "STOP_4" << std::endl; \
  this->delayCycles(4);

#define SUB_4_2(operand1, operand2)  \
  std::cout << "SUB_4" << std::endl; \
  this->delayCycles(4);              \
  this->cpu->setNFlag(true);
// calculate Z  this->cpu->setZFlag();
// calculate H  this->cpu->setHFlag();
// calculate C  this->cpu->setCFlag();

#define SUB_4_2(operand1, operand2)  \
  std::cout << "SUB_4" << std::endl; \
  this->delayCycles(4);              \
  this->cpu->setZFlag(true);         \
  this->cpu->setNFlag(true);         \
  this->cpu->setHFlag(false);        \
  this->cpu->setCFlag(false);

#define SUB_8_2(operand1, operand2)  \
  std::cout << "SUB_8" << std::endl; \
  this->delayCycles(8);              \
  this->cpu->setNFlag(true);
// calculate Z  this->cpu->setZFlag();
// calculate H  this->cpu->setHFlag();
// calculate C  this->cpu->setCFlag();

#define SWAP_16_1(operand1)            \
  std::cout << "SWAP_16" << std::endl; \
  this->delayCycles(16);               \
  this->cpu->setNFlag(false);          \
  this->cpu->setHFlag(false);          \
  this->cpu->setCFlag(false);
// calculate Z  this->cpu->setZFlag();

#define SWAP_8_1(operand1)            \
  std::cout << "SWAP_8" << std::endl; \
  this->delayCycles(8);               \
  this->cpu->setNFlag(false);         \
  this->cpu->setHFlag(false);         \
  this->cpu->setCFlag(false);
// calculate Z  this->cpu->setZFlag();

#define XOR_4_2(operand1, operand2)  \
  std::cout << "XOR_4" << std::endl; \
  this->delayCycles(4);              \
  this->cpu->setNFlag(false);        \
  this->cpu->setHFlag(false);        \
  this->cpu->setCFlag(false);
// calculate Z  this->cpu->setZFlag();

#define XOR_4_2(operand1, operand2)  \
  std::cout << "XOR_4" << std::endl; \
  this->delayCycles(4);              \
  this->cpu->setZFlag(true);         \
  this->cpu->setNFlag(false);        \
  this->cpu->setHFlag(false);        \
  this->cpu->setCFlag(false);

#define XOR_8_2(operand1, operand2)  \
  std::cout << "XOR_8" << std::endl; \
  this->delayCycles(8);              \
  this->cpu->setNFlag(false);        \
  this->cpu->setHFlag(false);        \
  this->cpu->setCFlag(false);
// calculate Z  this->cpu->setZFlag();

void GameBoy::execute(u8 opcode)
{
  if (!this->cpu->isPrefixed)
  {
    switch (opcode)
    {
    case 0x88:

      ADC_4_2(this->cpu->AF.A, this->cpu->BC.B);
      break;
    case 0x89:

      ADC_4_2(this->cpu->AF.A, this->cpu->BC.C);
      break;
    case 0x8A:

      ADC_4_2(this->cpu->AF.A, this->cpu->DE.D);
      break;
    case 0x8B:

      ADC_4_2(this->cpu->AF.A, this->cpu->DE.E);
      break;
    case 0x8C:

      ADC_4_2(this->cpu->AF.A, this->cpu->HL.H);
      break;
    case 0x8D:

      ADC_4_2(this->cpu->AF.A, this->cpu->HL.L);
      break;
    case 0x8E:

      ADC_8_2(this->cpu->AF.A, this->cpu->HL.HL);
      break;
    case 0x8F:

      ADC_4_2(this->cpu->AF.A, this->cpu->AF.A);
      break;
    case 0xCE:
      n8 = fetch();

      ADC_8_2(this->cpu->AF.A, this->cpu->n8);
      break;
    case 0x09:

      ADD_8_2(this->cpu->HL.HL, this->cpu->BC.BC);
      break;
    case 0x19:

      ADD_8_2(this->cpu->HL.HL, this->cpu->DE.DE);
      break;
    case 0x29:

      ADD_8_2(this->cpu->HL.HL, this->cpu->HL.HL);
      break;
    case 0x39:

      ADD_8_2(this->cpu->HL.HL, this->cpu->SP);
      break;
    case 0x80:

      ADD_4_2(this->cpu->AF.A, this->cpu->BC.B);
      break;
    case 0x81:

      ADD_4_2(this->cpu->AF.A, this->cpu->BC.C);
      break;
    case 0x82:

      ADD_4_2(this->cpu->AF.A, this->cpu->DE.D);
      break;
    case 0x83:

      ADD_4_2(this->cpu->AF.A, this->cpu->DE.E);
      break;
    case 0x84:

      ADD_4_2(this->cpu->AF.A, this->cpu->HL.H);
      break;
    case 0x85:

      ADD_4_2(this->cpu->AF.A, this->cpu->HL.L);
      break;
    case 0x86:

      ADD_8_2(this->cpu->AF.A, this->cpu->HL.HL);
      break;
    case 0x87:

      ADD_4_2(this->cpu->AF.A, this->cpu->AF.A);
      break;
    case 0xC6:
      n8 = fetch();

      ADD_8_2(this->cpu->AF.A, this->cpu->n8);
      break;
    case 0xE8:
      e8 = fetch();

      ADD_16_2(this->cpu->SP, this->cpu->e8);
      break;
    case 0xA0:

      AND_4_2(this->cpu->AF.A, this->cpu->BC.B);
      break;
    case 0xA1:

      AND_4_2(this->cpu->AF.A, this->cpu->BC.C);
      break;
    case 0xA2:

      AND_4_2(this->cpu->AF.A, this->cpu->DE.D);
      break;
    case 0xA3:

      AND_4_2(this->cpu->AF.A, this->cpu->DE.E);
      break;
    case 0xA4:

      AND_4_2(this->cpu->AF.A, this->cpu->HL.H);
      break;
    case 0xA5:

      AND_4_2(this->cpu->AF.A, this->cpu->HL.L);
      break;
    case 0xA6:

      AND_8_2(this->cpu->AF.A, this->cpu->HL.HL);
      break;
    case 0xA7:

      AND_4_2(this->cpu->AF.A, this->cpu->AF.A);
      break;
    case 0xE6:
      n8 = fetch();

      AND_8_2(this->cpu->AF.A, this->cpu->n8);
      break;
    case 0xC4:
      a16 = fetch16();

      CALL_24_1_NZ(this->cpu->a16);
      break;
    case 0xCC:
      a16 = fetch16();

      CALL_24_1_Z(this->cpu->a16);
      break;
    case 0xCD:
      a16 = fetch16();

      CALL_24_1(this->cpu->a16);
      break;
    case 0xD4:
      a16 = fetch16();

      CALL_24_1_NC(this->cpu->a16);
      break;
    case 0xDC:
      a16 = fetch16();

      CALL_24_2(this->cpu->BC.C, this->cpu->a16);
      break;
    case 0x3F:

      CCF_4_0();
      break;
    case 0xB8:

      CP_4_2(this->cpu->AF.A, this->cpu->BC.B);
      break;
    case 0xB9:

      CP_4_2(this->cpu->AF.A, this->cpu->BC.C);
      break;
    case 0xBA:

      CP_4_2(this->cpu->AF.A, this->cpu->DE.D);
      break;
    case 0xBB:

      CP_4_2(this->cpu->AF.A, this->cpu->DE.E);
      break;
    case 0xBC:

      CP_4_2(this->cpu->AF.A, this->cpu->HL.H);
      break;
    case 0xBD:

      CP_4_2(this->cpu->AF.A, this->cpu->HL.L);
      break;
    case 0xBE:

      CP_8_2(this->cpu->AF.A, this->cpu->HL.HL);
      break;
    case 0xBF:

      CP_4_2(this->cpu->AF.A, this->cpu->AF.A);
      break;
    case 0xFE:
      n8 = fetch();

      CP_8_2(this->cpu->AF.A, this->cpu->n8);
      break;
    case 0x2F:

      CPL_4_0();
      break;
    case 0x27:

      DAA_4_0();
      break;
    case 0x05:

      DEC_4_1(this->cpu->BC.B);
      break;
    case 0x0B:

      DEC_8_1(this->cpu->BC.BC);
      break;
    case 0x0D:

      DEC_4_1(this->cpu->BC.C);
      break;
    case 0x15:

      DEC_4_1(this->cpu->DE.D);
      break;
    case 0x1B:

      DEC_8_1(this->cpu->DE.DE);
      break;
    case 0x1D:

      DEC_4_1(this->cpu->DE.E);
      break;
    case 0x25:

      DEC_4_1(this->cpu->HL.H);
      break;
    case 0x2B:

      DEC_8_1(this->cpu->HL.HL);
      break;
    case 0x2D:

      DEC_4_1(this->cpu->HL.L);
      break;
    case 0x35:

      DEC_12_1(this->cpu->HL.HL);
      break;
    case 0x3B:

      DEC_8_1(this->cpu->SP);
      break;
    case 0x3D:

      DEC_4_1(this->cpu->AF.A);
      break;
    case 0xF3:

      DI_4_0();
      break;
    case 0xFB:

      EI_4_0();
      break;
    case 0x76:

      HALT_4_0();
      break;
    case 0xD3:

      ILLEGAL_4_0();
      break;
    case 0xDB:

      ILLEGAL_4_0();
      break;
    case 0xDD:

      ILLEGAL_4_0();
      break;
    case 0xE3:

      ILLEGAL_4_0();
      break;
    case 0xE4:

      ILLEGAL_4_0();
      break;
    case 0xEB:

      ILLEGAL_4_0();
      break;
    case 0xEC:

      ILLEGAL_4_0();
      break;
    case 0xED:

      ILLEGAL_4_0();
      break;
    case 0xF4:

      ILLEGAL_4_0();
      break;
    case 0xFC:

      ILLEGAL_4_0();
      break;
    case 0xFD:

      ILLEGAL_4_0();
      break;
    case 0x03:

      INC_8_1(this->cpu->BC.BC);
      break;
    case 0x04:

      INC_4_1(this->cpu->BC.B);
      break;
    case 0x0C:

      INC_4_1(this->cpu->BC.C);
      break;
    case 0x13:

      INC_8_1(this->cpu->DE.DE);
      break;
    case 0x14:

      INC_4_1(this->cpu->DE.D);
      break;
    case 0x1C:

      INC_4_1(this->cpu->DE.E);
      break;
    case 0x23:

      INC_8_1(this->cpu->HL.HL);
      break;
    case 0x24:

      INC_4_1(this->cpu->HL.H);
      break;
    case 0x2C:

      INC_4_1(this->cpu->HL.L);
      break;
    case 0x33:

      INC_8_1(this->cpu->SP);
      break;
    case 0x34:

      INC_12_1(this->cpu->HL.HL);
      break;
    case 0x3C:

      INC_4_1(this->cpu->AF.A);
      break;
    case 0xC2:
      a16 = fetch16();

      JP_16_1_NZ(this->cpu->a16);
      break;
    case 0xC3:
      a16 = fetch16();

      JP_16_1(this->cpu->a16);
      break;
    case 0xCA:
      a16 = fetch16();

      JP_16_1_Z(this->cpu->a16);
      break;
    case 0xD2:
      a16 = fetch16();

      JP_16_1_NC(this->cpu->a16);
      break;
    case 0xDA:
      a16 = fetch16();

      JP_16_2(this->cpu->BC.C, this->cpu->a16);
      break;
    case 0xE9:

      JP_4_1(this->cpu->HL.HL);
      break;
    case 0x18:
      e8 = fetch();

      JR_12_1(this->cpu->e8);
      break;
    case 0x20:
      e8 = fetch();

      JR_12_1_NZ(this->cpu->e8);
      break;
    case 0x28:
      e8 = fetch();

      JR_12_1_Z(this->cpu->e8);
      break;
    case 0x30:
      e8 = fetch();

      JR_12_1_NC(this->cpu->e8);
      break;
    case 0x38:
      e8 = fetch();

      JR_12_2(this->cpu->BC.C, this->cpu->e8);
      break;
    case 0x01:
      n16 = fetch16();

      LD_12_2(this->cpu->BC.BC, this->cpu->n16);
      break;
    case 0x02:

      LD_8_2(this->cpu->BC.BC, this->cpu->AF.A);
      break;
    case 0x06:
      n8 = fetch();

      LD_8_2(this->cpu->BC.B, this->cpu->n8);
      break;
    case 0x08:
      a16 = fetch16();

      LD_20_2(this->cpu->a16, this->cpu->SP);
      break;
    case 0x0A:

      LD_8_2(this->cpu->AF.A, this->cpu->BC.BC);
      break;
    case 0x0E:
      n8 = fetch();

      LD_8_2(this->cpu->BC.C, this->cpu->n8);
      break;
    case 0x11:
      n16 = fetch16();

      LD_12_2(this->cpu->DE.DE, this->cpu->n16);
      break;
    case 0x12:

      LD_8_2(this->cpu->DE.DE, this->cpu->AF.A);
      break;
    case 0x16:
      n8 = fetch();

      LD_8_2(this->cpu->DE.D, this->cpu->n8);
      break;
    case 0x1A:

      LD_8_2(this->cpu->AF.A, this->cpu->DE.DE);
      break;
    case 0x1E:
      n8 = fetch();

      LD_8_2(this->cpu->DE.E, this->cpu->n8);
      break;
    case 0x21:
      n16 = fetch16();

      LD_12_2(this->cpu->HL.HL, this->cpu->n16);
      break;
    case 0x22:

      LD_8_2(this->cpu->HL.HL, this->cpu->AF.A);
      break;
    case 0x26:
      n8 = fetch();

      LD_8_2(this->cpu->HL.H, this->cpu->n8);
      break;
    case 0x2A:

      LD_8_2(this->cpu->AF.A, this->cpu->HL.HL);
      break;
    case 0x2E:
      n8 = fetch();

      LD_8_2(this->cpu->HL.L, this->cpu->n8);
      break;
    case 0x31:
      n16 = fetch16();

      LD_12_2(this->cpu->SP, this->cpu->n16);
      break;
    case 0x32:

      LD_8_2(this->cpu->HL.HL, this->cpu->AF.A);
      break;
    case 0x36:
      n8 = fetch();

      LD_12_2(this->cpu->HL.HL, this->cpu->n8);
      break;
    case 0x3A:

      LD_8_2(this->cpu->AF.A, this->cpu->HL.HL);
      break;
    case 0x3E:
      n8 = fetch();

      LD_8_2(this->cpu->AF.A, this->cpu->n8);
      break;
    case 0x40:

      LD_4_2(this->cpu->BC.B, this->cpu->BC.B);
      break;
    case 0x41:

      LD_4_2(this->cpu->BC.B, this->cpu->BC.C);
      break;
    case 0x42:

      LD_4_2(this->cpu->BC.B, this->cpu->DE.D);
      break;
    case 0x43:

      LD_4_2(this->cpu->BC.B, this->cpu->DE.E);
      break;
    case 0x44:

      LD_4_2(this->cpu->BC.B, this->cpu->HL.H);
      break;
    case 0x45:

      LD_4_2(this->cpu->BC.B, this->cpu->HL.L);
      break;
    case 0x46:

      LD_8_2(this->cpu->BC.B, this->cpu->HL.HL);
      break;
    case 0x47:

      LD_4_2(this->cpu->BC.B, this->cpu->AF.A);
      break;
    case 0x48:

      LD_4_2(this->cpu->BC.C, this->cpu->BC.B);
      break;
    case 0x49:

      LD_4_2(this->cpu->BC.C, this->cpu->BC.C);
      break;
    case 0x4A:

      LD_4_2(this->cpu->BC.C, this->cpu->DE.D);
      break;
    case 0x4B:

      LD_4_2(this->cpu->BC.C, this->cpu->DE.E);
      break;
    case 0x4C:

      LD_4_2(this->cpu->BC.C, this->cpu->HL.H);
      break;
    case 0x4D:

      LD_4_2(this->cpu->BC.C, this->cpu->HL.L);
      break;
    case 0x4E:

      LD_8_2(this->cpu->BC.C, this->cpu->HL.HL);
      break;
    case 0x4F:

      LD_4_2(this->cpu->BC.C, this->cpu->AF.A);
      break;
    case 0x50:

      LD_4_2(this->cpu->DE.D, this->cpu->BC.B);
      break;
    case 0x51:

      LD_4_2(this->cpu->DE.D, this->cpu->BC.C);
      break;
    case 0x52:

      LD_4_2(this->cpu->DE.D, this->cpu->DE.D);
      break;
    case 0x53:

      LD_4_2(this->cpu->DE.D, this->cpu->DE.E);
      break;
    case 0x54:

      LD_4_2(this->cpu->DE.D, this->cpu->HL.H);
      break;
    case 0x55:

      LD_4_2(this->cpu->DE.D, this->cpu->HL.L);
      break;
    case 0x56:

      LD_8_2(this->cpu->DE.D, this->cpu->HL.HL);
      break;
    case 0x57:

      LD_4_2(this->cpu->DE.D, this->cpu->AF.A);
      break;
    case 0x58:

      LD_4_2(this->cpu->DE.E, this->cpu->BC.B);
      break;
    case 0x59:

      LD_4_2(this->cpu->DE.E, this->cpu->BC.C);
      break;
    case 0x5A:

      LD_4_2(this->cpu->DE.E, this->cpu->DE.D);
      break;
    case 0x5B:

      LD_4_2(this->cpu->DE.E, this->cpu->DE.E);
      break;
    case 0x5C:

      LD_4_2(this->cpu->DE.E, this->cpu->HL.H);
      break;
    case 0x5D:

      LD_4_2(this->cpu->DE.E, this->cpu->HL.L);
      break;
    case 0x5E:

      LD_8_2(this->cpu->DE.E, this->cpu->HL.HL);
      break;
    case 0x5F:

      LD_4_2(this->cpu->DE.E, this->cpu->AF.A);
      break;
    case 0x60:

      LD_4_2(this->cpu->HL.H, this->cpu->BC.B);
      break;
    case 0x61:

      LD_4_2(this->cpu->HL.H, this->cpu->BC.C);
      break;
    case 0x62:

      LD_4_2(this->cpu->HL.H, this->cpu->DE.D);
      break;
    case 0x63:

      LD_4_2(this->cpu->HL.H, this->cpu->DE.E);
      break;
    case 0x64:

      LD_4_2(this->cpu->HL.H, this->cpu->HL.H);
      break;
    case 0x65:

      LD_4_2(this->cpu->HL.H, this->cpu->HL.L);
      break;
    case 0x66:

      LD_8_2(this->cpu->HL.H, this->cpu->HL.HL);
      break;
    case 0x67:

      LD_4_2(this->cpu->HL.H, this->cpu->AF.A);
      break;
    case 0x68:

      LD_4_2(this->cpu->HL.L, this->cpu->BC.B);
      break;
    case 0x69:

      LD_4_2(this->cpu->HL.L, this->cpu->BC.C);
      break;
    case 0x6A:

      LD_4_2(this->cpu->HL.L, this->cpu->DE.D);
      break;
    case 0x6B:

      LD_4_2(this->cpu->HL.L, this->cpu->DE.E);
      break;
    case 0x6C:

      LD_4_2(this->cpu->HL.L, this->cpu->HL.H);
      break;
    case 0x6D:

      LD_4_2(this->cpu->HL.L, this->cpu->HL.L);
      break;
    case 0x6E:

      LD_8_2(this->cpu->HL.L, this->cpu->HL.HL);
      break;
    case 0x6F:

      LD_4_2(this->cpu->HL.L, this->cpu->AF.A);
      break;
    case 0x70:

      LD_8_2(this->cpu->HL.HL, this->cpu->BC.B);
      break;
    case 0x71:

      LD_8_2(this->cpu->HL.HL, this->cpu->BC.C);
      break;
    case 0x72:

      LD_8_2(this->cpu->HL.HL, this->cpu->DE.D);
      break;
    case 0x73:

      LD_8_2(this->cpu->HL.HL, this->cpu->DE.E);
      break;
    case 0x74:

      LD_8_2(this->cpu->HL.HL, this->cpu->HL.H);
      break;
    case 0x75:

      LD_8_2(this->cpu->HL.HL, this->cpu->HL.L);
      break;
    case 0x77:

      LD_8_2(this->cpu->HL.HL, this->cpu->AF.A);
      break;
    case 0x78:

      LD_4_2(this->cpu->AF.A, this->cpu->BC.B);
      break;
    case 0x79:

      LD_4_2(this->cpu->AF.A, this->cpu->BC.C);
      break;
    case 0x7A:

      LD_4_2(this->cpu->AF.A, this->cpu->DE.D);
      break;
    case 0x7B:

      LD_4_2(this->cpu->AF.A, this->cpu->DE.E);
      break;
    case 0x7C:

      LD_4_2(this->cpu->AF.A, this->cpu->HL.H);
      break;
    case 0x7D:

      LD_4_2(this->cpu->AF.A, this->cpu->HL.L);
      break;
    case 0x7E:

      LD_8_2(this->cpu->AF.A, this->cpu->HL.HL);
      break;
    case 0x7F:

      LD_4_2(this->cpu->AF.A, this->cpu->AF.A);
      break;
    case 0xE2:

      LD_8_2(this->cpu->BC.C, this->cpu->AF.A);
      break;
    case 0xEA:
      a16 = fetch16();

      LD_16_2(this->cpu->a16, this->cpu->AF.A);
      break;
    case 0xF2:

      LD_8_2(this->cpu->AF.A, this->cpu->BC.C);
      break;
    case 0xF8:
      e8 = fetch();

      LD_12_3(this->cpu->HL.HL, this->cpu->SP, this->cpu->e8);
      break;
    case 0xF9:

      LD_8_2(this->cpu->SP, this->cpu->HL.HL);
      break;
    case 0xFA:
      a16 = fetch16();

      LD_16_2(this->cpu->AF.A, this->cpu->a16);
      break;
    case 0xE0:
      a8 = fetch();

      LDH_12_2(this->cpu->a8, this->cpu->AF.A);
      break;
    case 0xF0:
      a8 = fetch();

      LDH_12_2(this->cpu->AF.A, this->cpu->a8);
      break;
    case 0x00:

      NOP_4_0();
      break;
    case 0xB0:

      OR_4_2(this->cpu->AF.A, this->cpu->BC.B);
      break;
    case 0xB1:

      OR_4_2(this->cpu->AF.A, this->cpu->BC.C);
      break;
    case 0xB2:

      OR_4_2(this->cpu->AF.A, this->cpu->DE.D);
      break;
    case 0xB3:

      OR_4_2(this->cpu->AF.A, this->cpu->DE.E);
      break;
    case 0xB4:

      OR_4_2(this->cpu->AF.A, this->cpu->HL.H);
      break;
    case 0xB5:

      OR_4_2(this->cpu->AF.A, this->cpu->HL.L);
      break;
    case 0xB6:

      OR_8_2(this->cpu->AF.A, this->cpu->HL.HL);
      break;
    case 0xB7:

      OR_4_2(this->cpu->AF.A, this->cpu->AF.A);
      break;
    case 0xF6:
      n8 = fetch();

      OR_8_2(this->cpu->AF.A, this->cpu->n8);
      break;
    case 0xC1:

      POP_12_1(this->cpu->BC.BC);
      break;
    case 0xD1:

      POP_12_1(this->cpu->DE.DE);
      break;
    case 0xE1:

      POP_12_1(this->cpu->HL.HL);
      break;
    case 0xF1:

      POP_12_1(this->cpu->AF.AF);
      break;
    case 0xCB:

      PREFIX_4_0();
      break;
    case 0xC5:

      PUSH_16_1(this->cpu->BC.BC);
      break;
    case 0xD5:

      PUSH_16_1(this->cpu->DE.DE);
      break;
    case 0xE5:

      PUSH_16_1(this->cpu->HL.HL);
      break;
    case 0xF5:

      PUSH_16_1(this->cpu->AF.AF);
      break;
    case 0xC0:

      RET_20_0_NZ();
      break;
    case 0xC8:

      RET_20_0_Z();
      break;
    case 0xC9:

      RET_16_0();
      break;
    case 0xD0:

      RET_20_0_NC();
      break;
    case 0xD8:

      RET_20_1(this->cpu->BC.C);
      break;
    case 0xD9:

      RETI_16_0();
      break;
    case 0x17:

      RLA_4_0();
      break;
    case 0x07:

      RLCA_4_0();
      break;
    case 0x1F:

      RRA_4_0();
      break;
    case 0x0F:

      RRCA_4_0();
      break;
    case 0xC7:
      this->cpu->im = 0;

      RST_16_1();
      break;
    case 0xCF:
      this->cpu->im = 8;

      RST_16_1();
      break;
    case 0xD7:
      this->cpu->im = 10;

      RST_16_1();
      break;
    case 0xDF:
      this->cpu->im = 18;

      RST_16_1();
      break;
    case 0xE7:
      this->cpu->im = 20;

      RST_16_1();
      break;
    case 0xEF:
      this->cpu->im = 28;

      RST_16_1();
      break;
    case 0xF7:
      this->cpu->im = 30;

      RST_16_1();
      break;
    case 0xFF:
      this->cpu->im = 38;

      RST_16_1();
      break;
    case 0x98:

      SBC_4_2(this->cpu->AF.A, this->cpu->BC.B);
      break;
    case 0x99:

      SBC_4_2(this->cpu->AF.A, this->cpu->BC.C);
      break;
    case 0x9A:

      SBC_4_2(this->cpu->AF.A, this->cpu->DE.D);
      break;
    case 0x9B:

      SBC_4_2(this->cpu->AF.A, this->cpu->DE.E);
      break;
    case 0x9C:

      SBC_4_2(this->cpu->AF.A, this->cpu->HL.H);
      break;
    case 0x9D:

      SBC_4_2(this->cpu->AF.A, this->cpu->HL.L);
      break;
    case 0x9E:

      SBC_8_2(this->cpu->AF.A, this->cpu->HL.HL);
      break;
    case 0x9F:

      SBC_4_2(this->cpu->AF.A, this->cpu->AF.A);
      break;
    case 0xDE:
      n8 = fetch();

      SBC_8_2(this->cpu->AF.A, this->cpu->n8);
      break;
    case 0x37:

      SCF_4_0();
      break;
    case 0x10:
      n8 = fetch();

      STOP_4_1(this->cpu->n8);
      break;
    case 0x90:

      SUB_4_2(this->cpu->AF.A, this->cpu->BC.B);
      break;
    case 0x91:

      SUB_4_2(this->cpu->AF.A, this->cpu->BC.C);
      break;
    case 0x92:

      SUB_4_2(this->cpu->AF.A, this->cpu->DE.D);
      break;
    case 0x93:

      SUB_4_2(this->cpu->AF.A, this->cpu->DE.E);
      break;
    case 0x94:

      SUB_4_2(this->cpu->AF.A, this->cpu->HL.H);
      break;
    case 0x95:

      SUB_4_2(this->cpu->AF.A, this->cpu->HL.L);
      break;
    case 0x96:

      SUB_8_2(this->cpu->AF.A, this->cpu->HL.HL);
      break;
    case 0x97:

      SUB_4_2(this->cpu->AF.A, this->cpu->AF.A);
      break;
    case 0xD6:
      n8 = fetch();

      SUB_8_2(this->cpu->AF.A, this->cpu->n8);
      break;
    case 0xA8:

      XOR_4_2(this->cpu->AF.A, this->cpu->BC.B);
      break;
    case 0xA9:

      XOR_4_2(this->cpu->AF.A, this->cpu->BC.C);
      break;
    case 0xAA:

      XOR_4_2(this->cpu->AF.A, this->cpu->DE.D);
      break;
    case 0xAB:

      XOR_4_2(this->cpu->AF.A, this->cpu->DE.E);
      break;
    case 0xAC:

      XOR_4_2(this->cpu->AF.A, this->cpu->HL.H);
      break;
    case 0xAD:

      XOR_4_2(this->cpu->AF.A, this->cpu->HL.L);
      break;
    case 0xAE:

      XOR_8_2(this->cpu->AF.A, this->cpu->HL.HL);
      break;
    case 0xAF:

      XOR_4_2(this->cpu->AF.A, this->cpu->AF.A);
      break;
    case 0xEE:
      n8 = fetch();

      XOR_8_2(this->cpu->AF.A, this->cpu->n8);
      break;
    }
  }
  else
  {
    switch (opcode)
    {
    case 0x40:
      this->cpu->im = 0;

      BIT_8_2(this->cpu->BC.B);
      break;
    case 0x41:
      this->cpu->im = 0;

      BIT_8_2(this->cpu->BC.C);
      break;
    case 0x42:
      this->cpu->im = 0;

      BIT_8_2(this->cpu->DE.D);
      break;
    case 0x43:
      this->cpu->im = 0;

      BIT_8_2(this->cpu->DE.E);
      break;
    case 0x44:
      this->cpu->im = 0;

      BIT_8_2(this->cpu->HL.H);
      break;
    case 0x45:
      this->cpu->im = 0;

      BIT_8_2(this->cpu->HL.L);
      break;
    case 0x46:
      this->cpu->im = 0;

      BIT_12_2(this->cpu->HL.HL);
      break;
    case 0x47:
      this->cpu->im = 0;

      BIT_8_2(this->cpu->AF.A);
      break;
    case 0x48:
      this->cpu->im = 1;

      BIT_8_2(this->cpu->BC.B);
      break;
    case 0x49:
      this->cpu->im = 1;

      BIT_8_2(this->cpu->BC.C);
      break;
    case 0x4A:
      this->cpu->im = 1;

      BIT_8_2(this->cpu->DE.D);
      break;
    case 0x4B:
      this->cpu->im = 1;

      BIT_8_2(this->cpu->DE.E);
      break;
    case 0x4C:
      this->cpu->im = 1;

      BIT_8_2(this->cpu->HL.H);
      break;
    case 0x4D:
      this->cpu->im = 1;

      BIT_8_2(this->cpu->HL.L);
      break;
    case 0x4E:
      this->cpu->im = 1;

      BIT_12_2(this->cpu->HL.HL);
      break;
    case 0x4F:
      this->cpu->im = 1;

      BIT_8_2(this->cpu->AF.A);
      break;
    case 0x50:
      this->cpu->im = 2;

      BIT_8_2(this->cpu->BC.B);
      break;
    case 0x51:
      this->cpu->im = 2;

      BIT_8_2(this->cpu->BC.C);
      break;
    case 0x52:
      this->cpu->im = 2;

      BIT_8_2(this->cpu->DE.D);
      break;
    case 0x53:
      this->cpu->im = 2;

      BIT_8_2(this->cpu->DE.E);
      break;
    case 0x54:
      this->cpu->im = 2;

      BIT_8_2(this->cpu->HL.H);
      break;
    case 0x55:
      this->cpu->im = 2;

      BIT_8_2(this->cpu->HL.L);
      break;
    case 0x56:
      this->cpu->im = 2;

      BIT_12_2(this->cpu->HL.HL);
      break;
    case 0x57:
      this->cpu->im = 2;

      BIT_8_2(this->cpu->AF.A);
      break;
    case 0x58:
      this->cpu->im = 3;

      BIT_8_2(this->cpu->BC.B);
      break;
    case 0x59:
      this->cpu->im = 3;

      BIT_8_2(this->cpu->BC.C);
      break;
    case 0x5A:
      this->cpu->im = 3;

      BIT_8_2(this->cpu->DE.D);
      break;
    case 0x5B:
      this->cpu->im = 3;

      BIT_8_2(this->cpu->DE.E);
      break;
    case 0x5C:
      this->cpu->im = 3;

      BIT_8_2(this->cpu->HL.H);
      break;
    case 0x5D:
      this->cpu->im = 3;

      BIT_8_2(this->cpu->HL.L);
      break;
    case 0x5E:
      this->cpu->im = 3;

      BIT_12_2(this->cpu->HL.HL);
      break;
    case 0x5F:
      this->cpu->im = 3;

      BIT_8_2(this->cpu->AF.A);
      break;
    case 0x60:
      this->cpu->im = 4;

      BIT_8_2(this->cpu->BC.B);
      break;
    case 0x61:
      this->cpu->im = 4;

      BIT_8_2(this->cpu->BC.C);
      break;
    case 0x62:
      this->cpu->im = 4;

      BIT_8_2(this->cpu->DE.D);
      break;
    case 0x63:
      this->cpu->im = 4;

      BIT_8_2(this->cpu->DE.E);
      break;
    case 0x64:
      this->cpu->im = 4;

      BIT_8_2(this->cpu->HL.H);
      break;
    case 0x65:
      this->cpu->im = 4;

      BIT_8_2(this->cpu->HL.L);
      break;
    case 0x66:
      this->cpu->im = 4;

      BIT_12_2(this->cpu->HL.HL);
      break;
    case 0x67:
      this->cpu->im = 4;

      BIT_8_2(this->cpu->AF.A);
      break;
    case 0x68:
      this->cpu->im = 5;

      BIT_8_2(this->cpu->BC.B);
      break;
    case 0x69:
      this->cpu->im = 5;

      BIT_8_2(this->cpu->BC.C);
      break;
    case 0x6A:
      this->cpu->im = 5;

      BIT_8_2(this->cpu->DE.D);
      break;
    case 0x6B:
      this->cpu->im = 5;

      BIT_8_2(this->cpu->DE.E);
      break;
    case 0x6C:
      this->cpu->im = 5;

      BIT_8_2(this->cpu->HL.H);
      break;
    case 0x6D:
      this->cpu->im = 5;

      BIT_8_2(this->cpu->HL.L);
      break;
    case 0x6E:
      this->cpu->im = 5;

      BIT_12_2(this->cpu->HL.HL);
      break;
    case 0x6F:
      this->cpu->im = 5;

      BIT_8_2(this->cpu->AF.A);
      break;
    case 0x70:
      this->cpu->im = 6;

      BIT_8_2(this->cpu->BC.B);
      break;
    case 0x71:
      this->cpu->im = 6;

      BIT_8_2(this->cpu->BC.C);
      break;
    case 0x72:
      this->cpu->im = 6;

      BIT_8_2(this->cpu->DE.D);
      break;
    case 0x73:
      this->cpu->im = 6;

      BIT_8_2(this->cpu->DE.E);
      break;
    case 0x74:
      this->cpu->im = 6;

      BIT_8_2(this->cpu->HL.H);
      break;
    case 0x75:
      this->cpu->im = 6;

      BIT_8_2(this->cpu->HL.L);
      break;
    case 0x76:
      this->cpu->im = 6;

      BIT_12_2(this->cpu->HL.HL);
      break;
    case 0x77:
      this->cpu->im = 6;

      BIT_8_2(this->cpu->AF.A);
      break;
    case 0x78:
      this->cpu->im = 7;

      BIT_8_2(this->cpu->BC.B);
      break;
    case 0x79:
      this->cpu->im = 7;

      BIT_8_2(this->cpu->BC.C);
      break;
    case 0x7A:
      this->cpu->im = 7;

      BIT_8_2(this->cpu->DE.D);
      break;
    case 0x7B:
      this->cpu->im = 7;

      BIT_8_2(this->cpu->DE.E);
      break;
    case 0x7C:
      this->cpu->im = 7;

      BIT_8_2(this->cpu->HL.H);
      break;
    case 0x7D:
      this->cpu->im = 7;

      BIT_8_2(this->cpu->HL.L);
      break;
    case 0x7E:
      this->cpu->im = 7;

      BIT_12_2(this->cpu->HL.HL);
      break;
    case 0x7F:
      this->cpu->im = 7;

      BIT_8_2(this->cpu->AF.A);
      break;
    case 0x80:
      this->cpu->im = 0;

      RES_8_2(this->cpu->BC.B);
      break;
    case 0x81:
      this->cpu->im = 0;

      RES_8_2(this->cpu->BC.C);
      break;
    case 0x82:
      this->cpu->im = 0;

      RES_8_2(this->cpu->DE.D);
      break;
    case 0x83:
      this->cpu->im = 0;

      RES_8_2(this->cpu->DE.E);
      break;
    case 0x84:
      this->cpu->im = 0;

      RES_8_2(this->cpu->HL.H);
      break;
    case 0x85:
      this->cpu->im = 0;

      RES_8_2(this->cpu->HL.L);
      break;
    case 0x86:
      this->cpu->im = 0;

      RES_16_2(this->cpu->HL.HL);
      break;
    case 0x87:
      this->cpu->im = 0;

      RES_8_2(this->cpu->AF.A);
      break;
    case 0x88:
      this->cpu->im = 1;

      RES_8_2(this->cpu->BC.B);
      break;
    case 0x89:
      this->cpu->im = 1;

      RES_8_2(this->cpu->BC.C);
      break;
    case 0x8A:
      this->cpu->im = 1;

      RES_8_2(this->cpu->DE.D);
      break;
    case 0x8B:
      this->cpu->im = 1;

      RES_8_2(this->cpu->DE.E);
      break;
    case 0x8C:
      this->cpu->im = 1;

      RES_8_2(this->cpu->HL.H);
      break;
    case 0x8D:
      this->cpu->im = 1;

      RES_8_2(this->cpu->HL.L);
      break;
    case 0x8E:
      this->cpu->im = 1;

      RES_16_2(this->cpu->HL.HL);
      break;
    case 0x8F:
      this->cpu->im = 1;

      RES_8_2(this->cpu->AF.A);
      break;
    case 0x90:
      this->cpu->im = 2;

      RES_8_2(this->cpu->BC.B);
      break;
    case 0x91:
      this->cpu->im = 2;

      RES_8_2(this->cpu->BC.C);
      break;
    case 0x92:
      this->cpu->im = 2;

      RES_8_2(this->cpu->DE.D);
      break;
    case 0x93:
      this->cpu->im = 2;

      RES_8_2(this->cpu->DE.E);
      break;
    case 0x94:
      this->cpu->im = 2;

      RES_8_2(this->cpu->HL.H);
      break;
    case 0x95:
      this->cpu->im = 2;

      RES_8_2(this->cpu->HL.L);
      break;
    case 0x96:
      this->cpu->im = 2;

      RES_16_2(this->cpu->HL.HL);
      break;
    case 0x97:
      this->cpu->im = 2;

      RES_8_2(this->cpu->AF.A);
      break;
    case 0x98:
      this->cpu->im = 3;

      RES_8_2(this->cpu->BC.B);
      break;
    case 0x99:
      this->cpu->im = 3;

      RES_8_2(this->cpu->BC.C);
      break;
    case 0x9A:
      this->cpu->im = 3;

      RES_8_2(this->cpu->DE.D);
      break;
    case 0x9B:
      this->cpu->im = 3;

      RES_8_2(this->cpu->DE.E);
      break;
    case 0x9C:
      this->cpu->im = 3;

      RES_8_2(this->cpu->HL.H);
      break;
    case 0x9D:
      this->cpu->im = 3;

      RES_8_2(this->cpu->HL.L);
      break;
    case 0x9E:
      this->cpu->im = 3;

      RES_16_2(this->cpu->HL.HL);
      break;
    case 0x9F:
      this->cpu->im = 3;

      RES_8_2(this->cpu->AF.A);
      break;
    case 0xA0:
      this->cpu->im = 4;

      RES_8_2(this->cpu->BC.B);
      break;
    case 0xA1:
      this->cpu->im = 4;

      RES_8_2(this->cpu->BC.C);
      break;
    case 0xA2:
      this->cpu->im = 4;

      RES_8_2(this->cpu->DE.D);
      break;
    case 0xA3:
      this->cpu->im = 4;

      RES_8_2(this->cpu->DE.E);
      break;
    case 0xA4:
      this->cpu->im = 4;

      RES_8_2(this->cpu->HL.H);
      break;
    case 0xA5:
      this->cpu->im = 4;

      RES_8_2(this->cpu->HL.L);
      break;
    case 0xA6:
      this->cpu->im = 4;

      RES_16_2(this->cpu->HL.HL);
      break;
    case 0xA7:
      this->cpu->im = 4;

      RES_8_2(this->cpu->AF.A);
      break;
    case 0xA8:
      this->cpu->im = 5;

      RES_8_2(this->cpu->BC.B);
      break;
    case 0xA9:
      this->cpu->im = 5;

      RES_8_2(this->cpu->BC.C);
      break;
    case 0xAA:
      this->cpu->im = 5;

      RES_8_2(this->cpu->DE.D);
      break;
    case 0xAB:
      this->cpu->im = 5;

      RES_8_2(this->cpu->DE.E);
      break;
    case 0xAC:
      this->cpu->im = 5;

      RES_8_2(this->cpu->HL.H);
      break;
    case 0xAD:
      this->cpu->im = 5;

      RES_8_2(this->cpu->HL.L);
      break;
    case 0xAE:
      this->cpu->im = 5;

      RES_16_2(this->cpu->HL.HL);
      break;
    case 0xAF:
      this->cpu->im = 5;

      RES_8_2(this->cpu->AF.A);
      break;
    case 0xB0:
      this->cpu->im = 6;

      RES_8_2(this->cpu->BC.B);
      break;
    case 0xB1:
      this->cpu->im = 6;

      RES_8_2(this->cpu->BC.C);
      break;
    case 0xB2:
      this->cpu->im = 6;

      RES_8_2(this->cpu->DE.D);
      break;
    case 0xB3:
      this->cpu->im = 6;

      RES_8_2(this->cpu->DE.E);
      break;
    case 0xB4:
      this->cpu->im = 6;

      RES_8_2(this->cpu->HL.H);
      break;
    case 0xB5:
      this->cpu->im = 6;

      RES_8_2(this->cpu->HL.L);
      break;
    case 0xB6:
      this->cpu->im = 6;

      RES_16_2(this->cpu->HL.HL);
      break;
    case 0xB7:
      this->cpu->im = 6;

      RES_8_2(this->cpu->AF.A);
      break;
    case 0xB8:
      this->cpu->im = 7;

      RES_8_2(this->cpu->BC.B);
      break;
    case 0xB9:
      this->cpu->im = 7;

      RES_8_2(this->cpu->BC.C);
      break;
    case 0xBA:
      this->cpu->im = 7;

      RES_8_2(this->cpu->DE.D);
      break;
    case 0xBB:
      this->cpu->im = 7;

      RES_8_2(this->cpu->DE.E);
      break;
    case 0xBC:
      this->cpu->im = 7;

      RES_8_2(this->cpu->HL.H);
      break;
    case 0xBD:
      this->cpu->im = 7;

      RES_8_2(this->cpu->HL.L);
      break;
    case 0xBE:
      this->cpu->im = 7;

      RES_16_2(this->cpu->HL.HL);
      break;
    case 0xBF:
      this->cpu->im = 7;

      RES_8_2(this->cpu->AF.A);
      break;
    case 0x10:

      RL_8_1(this->cpu->BC.B);
      break;
    case 0x11:

      RL_8_1(this->cpu->BC.C);
      break;
    case 0x12:

      RL_8_1(this->cpu->DE.D);
      break;
    case 0x13:

      RL_8_1(this->cpu->DE.E);
      break;
    case 0x14:

      RL_8_1(this->cpu->HL.H);
      break;
    case 0x15:

      RL_8_1(this->cpu->HL.L);
      break;
    case 0x16:

      RL_16_1(this->cpu->HL.HL);
      break;
    case 0x17:

      RL_8_1(this->cpu->AF.A);
      break;
    case 0x00:

      RLC_8_1(this->cpu->BC.B);
      break;
    case 0x01:

      RLC_8_1(this->cpu->BC.C);
      break;
    case 0x02:

      RLC_8_1(this->cpu->DE.D);
      break;
    case 0x03:

      RLC_8_1(this->cpu->DE.E);
      break;
    case 0x04:

      RLC_8_1(this->cpu->HL.H);
      break;
    case 0x05:

      RLC_8_1(this->cpu->HL.L);
      break;
    case 0x06:

      RLC_16_1(this->cpu->HL.HL);
      break;
    case 0x07:

      RLC_8_1(this->cpu->AF.A);
      break;
    case 0x18:

      RR_8_1(this->cpu->BC.B);
      break;
    case 0x19:

      RR_8_1(this->cpu->BC.C);
      break;
    case 0x1A:

      RR_8_1(this->cpu->DE.D);
      break;
    case 0x1B:

      RR_8_1(this->cpu->DE.E);
      break;
    case 0x1C:

      RR_8_1(this->cpu->HL.H);
      break;
    case 0x1D:

      RR_8_1(this->cpu->HL.L);
      break;
    case 0x1E:

      RR_16_1(this->cpu->HL.HL);
      break;
    case 0x1F:

      RR_8_1(this->cpu->AF.A);
      break;
    case 0x08:

      RRC_8_1(this->cpu->BC.B);
      break;
    case 0x09:

      RRC_8_1(this->cpu->BC.C);
      break;
    case 0x0A:

      RRC_8_1(this->cpu->DE.D);
      break;
    case 0x0B:

      RRC_8_1(this->cpu->DE.E);
      break;
    case 0x0C:

      RRC_8_1(this->cpu->HL.H);
      break;
    case 0x0D:

      RRC_8_1(this->cpu->HL.L);
      break;
    case 0x0E:

      RRC_16_1(this->cpu->HL.HL);
      break;
    case 0x0F:

      RRC_8_1(this->cpu->AF.A);
      break;
    case 0xC0:
      this->cpu->im = 0;

      SET_8_2(this->cpu->BC.B);
      break;
    case 0xC1:
      this->cpu->im = 0;

      SET_8_2(this->cpu->BC.C);
      break;
    case 0xC2:
      this->cpu->im = 0;

      SET_8_2(this->cpu->DE.D);
      break;
    case 0xC3:
      this->cpu->im = 0;

      SET_8_2(this->cpu->DE.E);
      break;
    case 0xC4:
      this->cpu->im = 0;

      SET_8_2(this->cpu->HL.H);
      break;
    case 0xC5:
      this->cpu->im = 0;

      SET_8_2(this->cpu->HL.L);
      break;
    case 0xC6:
      this->cpu->im = 0;

      SET_16_2(this->cpu->HL.HL);
      break;
    case 0xC7:
      this->cpu->im = 0;

      SET_8_2(this->cpu->AF.A);
      break;
    case 0xC8:
      this->cpu->im = 1;

      SET_8_2(this->cpu->BC.B);
      break;
    case 0xC9:
      this->cpu->im = 1;

      SET_8_2(this->cpu->BC.C);
      break;
    case 0xCA:
      this->cpu->im = 1;

      SET_8_2(this->cpu->DE.D);
      break;
    case 0xCB:
      this->cpu->im = 1;

      SET_8_2(this->cpu->DE.E);
      break;
    case 0xCC:
      this->cpu->im = 1;

      SET_8_2(this->cpu->HL.H);
      break;
    case 0xCD:
      this->cpu->im = 1;

      SET_8_2(this->cpu->HL.L);
      break;
    case 0xCE:
      this->cpu->im = 1;

      SET_16_2(this->cpu->HL.HL);
      break;
    case 0xCF:
      this->cpu->im = 1;

      SET_8_2(this->cpu->AF.A);
      break;
    case 0xD0:
      this->cpu->im = 2;

      SET_8_2(this->cpu->BC.B);
      break;
    case 0xD1:
      this->cpu->im = 2;

      SET_8_2(this->cpu->BC.C);
      break;
    case 0xD2:
      this->cpu->im = 2;

      SET_8_2(this->cpu->DE.D);
      break;
    case 0xD3:
      this->cpu->im = 2;

      SET_8_2(this->cpu->DE.E);
      break;
    case 0xD4:
      this->cpu->im = 2;

      SET_8_2(this->cpu->HL.H);
      break;
    case 0xD5:
      this->cpu->im = 2;

      SET_8_2(this->cpu->HL.L);
      break;
    case 0xD6:
      this->cpu->im = 2;

      SET_16_2(this->cpu->HL.HL);
      break;
    case 0xD7:
      this->cpu->im = 2;

      SET_8_2(this->cpu->AF.A);
      break;
    case 0xD8:
      this->cpu->im = 3;

      SET_8_2(this->cpu->BC.B);
      break;
    case 0xD9:
      this->cpu->im = 3;

      SET_8_2(this->cpu->BC.C);
      break;
    case 0xDA:
      this->cpu->im = 3;

      SET_8_2(this->cpu->DE.D);
      break;
    case 0xDB:
      this->cpu->im = 3;

      SET_8_2(this->cpu->DE.E);
      break;
    case 0xDC:
      this->cpu->im = 3;

      SET_8_2(this->cpu->HL.H);
      break;
    case 0xDD:
      this->cpu->im = 3;

      SET_8_2(this->cpu->HL.L);
      break;
    case 0xDE:
      this->cpu->im = 3;

      SET_16_2(this->cpu->HL.HL);
      break;
    case 0xDF:
      this->cpu->im = 3;

      SET_8_2(this->cpu->AF.A);
      break;
    case 0xE0:
      this->cpu->im = 4;

      SET_8_2(this->cpu->BC.B);
      break;
    case 0xE1:
      this->cpu->im = 4;

      SET_8_2(this->cpu->BC.C);
      break;
    case 0xE2:
      this->cpu->im = 4;

      SET_8_2(this->cpu->DE.D);
      break;
    case 0xE3:
      this->cpu->im = 4;

      SET_8_2(this->cpu->DE.E);
      break;
    case 0xE4:
      this->cpu->im = 4;

      SET_8_2(this->cpu->HL.H);
      break;
    case 0xE5:
      this->cpu->im = 4;

      SET_8_2(this->cpu->HL.L);
      break;
    case 0xE6:
      this->cpu->im = 4;

      SET_16_2(this->cpu->HL.HL);
      break;
    case 0xE7:
      this->cpu->im = 4;

      SET_8_2(this->cpu->AF.A);
      break;
    case 0xE8:
      this->cpu->im = 5;

      SET_8_2(this->cpu->BC.B);
      break;
    case 0xE9:
      this->cpu->im = 5;

      SET_8_2(this->cpu->BC.C);
      break;
    case 0xEA:
      this->cpu->im = 5;

      SET_8_2(this->cpu->DE.D);
      break;
    case 0xEB:
      this->cpu->im = 5;

      SET_8_2(this->cpu->DE.E);
      break;
    case 0xEC:
      this->cpu->im = 5;

      SET_8_2(this->cpu->HL.H);
      break;
    case 0xED:
      this->cpu->im = 5;

      SET_8_2(this->cpu->HL.L);
      break;
    case 0xEE:
      this->cpu->im = 5;

      SET_16_2(this->cpu->HL.HL);
      break;
    case 0xEF:
      this->cpu->im = 5;

      SET_8_2(this->cpu->AF.A);
      break;
    case 0xF0:
      this->cpu->im = 6;

      SET_8_2(this->cpu->BC.B);
      break;
    case 0xF1:
      this->cpu->im = 6;

      SET_8_2(this->cpu->BC.C);
      break;
    case 0xF2:
      this->cpu->im = 6;

      SET_8_2(this->cpu->DE.D);
      break;
    case 0xF3:
      this->cpu->im = 6;

      SET_8_2(this->cpu->DE.E);
      break;
    case 0xF4:
      this->cpu->im = 6;

      SET_8_2(this->cpu->HL.H);
      break;
    case 0xF5:
      this->cpu->im = 6;

      SET_8_2(this->cpu->HL.L);
      break;
    case 0xF6:
      this->cpu->im = 6;

      SET_16_2(this->cpu->HL.HL);
      break;
    case 0xF7:
      this->cpu->im = 6;

      SET_8_2(this->cpu->AF.A);
      break;
    case 0xF8:
      this->cpu->im = 7;

      SET_8_2(this->cpu->BC.B);
      break;
    case 0xF9:
      this->cpu->im = 7;

      SET_8_2(this->cpu->BC.C);
      break;
    case 0xFA:
      this->cpu->im = 7;

      SET_8_2(this->cpu->DE.D);
      break;
    case 0xFB:
      this->cpu->im = 7;

      SET_8_2(this->cpu->DE.E);
      break;
    case 0xFC:
      this->cpu->im = 7;

      SET_8_2(this->cpu->HL.H);
      break;
    case 0xFD:
      this->cpu->im = 7;

      SET_8_2(this->cpu->HL.L);
      break;
    case 0xFE:
      this->cpu->im = 7;

      SET_16_2(this->cpu->HL.HL);
      break;
    case 0xFF:
      this->cpu->im = 7;

      SET_8_2(this->cpu->AF.A);
      break;
    case 0x20:

      SLA_8_1(this->cpu->BC.B);
      break;
    case 0x21:

      SLA_8_1(this->cpu->BC.C);
      break;
    case 0x22:

      SLA_8_1(this->cpu->DE.D);
      break;
    case 0x23:

      SLA_8_1(this->cpu->DE.E);
      break;
    case 0x24:

      SLA_8_1(this->cpu->HL.H);
      break;
    case 0x25:

      SLA_8_1(this->cpu->HL.L);
      break;
    case 0x26:

      SLA_16_1(this->cpu->HL.HL);
      break;
    case 0x27:

      SLA_8_1(this->cpu->AF.A);
      break;
    case 0x28:

      SRA_8_1(this->cpu->BC.B);
      break;
    case 0x29:

      SRA_8_1(this->cpu->BC.C);
      break;
    case 0x2A:

      SRA_8_1(this->cpu->DE.D);
      break;
    case 0x2B:

      SRA_8_1(this->cpu->DE.E);
      break;
    case 0x2C:

      SRA_8_1(this->cpu->HL.H);
      break;
    case 0x2D:

      SRA_8_1(this->cpu->HL.L);
      break;
    case 0x2E:

      SRA_16_1(this->cpu->HL.HL);
      break;
    case 0x2F:

      SRA_8_1(this->cpu->AF.A);
      break;
    case 0x38:

      SRL_8_1(this->cpu->BC.B);
      break;
    case 0x39:

      SRL_8_1(this->cpu->BC.C);
      break;
    case 0x3A:

      SRL_8_1(this->cpu->DE.D);
      break;
    case 0x3B:

      SRL_8_1(this->cpu->DE.E);
      break;
    case 0x3C:

      SRL_8_1(this->cpu->HL.H);
      break;
    case 0x3D:

      SRL_8_1(this->cpu->HL.L);
      break;
    case 0x3E:

      SRL_16_1(this->cpu->HL.HL);
      break;
    case 0x3F:

      SRL_8_1(this->cpu->AF.A);
      break;
    case 0x30:

      SWAP_8_1(this->cpu->BC.B);
      break;
    case 0x31:

      SWAP_8_1(this->cpu->BC.C);
      break;
    case 0x32:

      SWAP_8_1(this->cpu->DE.D);
      break;
    case 0x33:

      SWAP_8_1(this->cpu->DE.E);
      break;
    case 0x34:

      SWAP_8_1(this->cpu->HL.H);
      break;
    case 0x35:

      SWAP_8_1(this->cpu->HL.L);
      break;
    case 0x36:

      SWAP_16_1(this->cpu->HL.HL);
      break;
    case 0x37:

      SWAP_8_1(this->cpu->AF.A);
      break;
    }
  }
}
