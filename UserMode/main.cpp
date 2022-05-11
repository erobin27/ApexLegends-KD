#include "UM-Memory.h"
#include <iostream>
#include <windows.h> //for colors
#include <iomanip>
#include "skCrypter.h"
#include "Entity.h"
#include <thread>

Memory* mem = nullptr;
UINT64 StringAddress = 0;

void GlowThread() {
	bool glow = false;
	while (true) {
		if (glow) {
			Glow();
			Sleep(5000);
		}

		if (GetKeyState(VK_HOME) & 0x8000) {
			glow = !glow;
			std::cout << skCrypt("Glow: ") << glow << std::endl;
			if(!glow) disableGlow();
			Sleep(1000);
		}
	}
}

void RecoilThread() {
	bool recoil = true;
	bool reset = false;
	while (true) {
		if (GetKeyState(VK_LBUTTON) & 0x8000 && recoil) {
			NoRecoil(reset);
			//printViewAngles();
			reset = false;
		}

		if (!(GetKeyState(VK_LBUTTON) & 0x8000)) {
			reset = true;
		}



		if (GetKeyState(VK_INSERT) & 0x8000) {
			recoil = !recoil;
			std::cout << recoil << std::endl;
			Sleep(1000);
		}
		Sleep(50);
	}
}

int main()
{
	bool breakVal = false;
	
	auto gameName = skCrypt("r5apex.exe");
	process_id = mem->get_process_id(gameName.decrypt());
	base_address = mem->get_module_base_address(gameName.decrypt());
	gameName.clear();

	if (!base_address)
	{
		printf(skCrypt("Could Not Find Game..."));
		Sleep(5000);
	}
	else
	{
		std::cout << std::hex;
		std::cout << skCrypt("Base Address: ") << base_address << std::endl;
		std::cout << std::dec;
			
		//initializeSettings();
		std::thread recoil(RecoilThread);
		std::thread glow(GlowThread);
		recoil.join();
		glow.join();

		breakVal = true;
	}
	std::cout << skCrypt("CLOSING");
	Sleep(1000);
	return NULL;
}