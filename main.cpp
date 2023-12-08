#include "GameBoy.h"
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <chrono>
int main() {
	GameBoy* gb = new GameBoy();
	//for (int i = 0; i < 0xffff + 1; i++) {
	//	gb->setValue(i, 50);
	//}
	//for (int i = 0x0000; i < 0x7fff + 1; i++) {
	//	std::cout << "Location [" << i << "] value (" << (int)gb->getValue(i) << ")" << std::endl;
	//}
	gb->execute(0x88);
	gb->cpu->AF.A = 0xff;
	std::cout << "gb->cpu->A: " << (int)gb->cpu->AF.A << std::endl;
	std::cout << "gb->cpu->FLAGS: " << (int)gb->cpu->AF.FLAGS << std::endl;
	std::cout << "gb->cpu->AF: " <<(int) gb->cpu->AF.AF<< std::endl;
	delete gb;
	return 0;
}