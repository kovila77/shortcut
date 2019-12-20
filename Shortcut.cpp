// ConsoleApplication8.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <Windows.h>
#include <string>
#include <map>
#include <functional>

#define PLAY_PAUSE "PLAY_PAUSE"

//bool findArg(int argc, char* argv[], const char* arg) {
//	for (int i = 1; i < argc; i++) {
//		if (!strcmp(argv[i], arg))
//			return true;
//	}
//	return false;
//}

bool choseType(KEYBDINPUT &kbi, DWORD arg) {
	kbi.wVk = arg;
	return true;
}

int main(int argc, char* argv[])
{
	//if (argc <= 1) return 0;
	//std::string whatDo = argv[1];

	KEYBDINPUT kbi;

	kbi.wVk = VK_VOLUME_MUTE;

	std::map <std::string, std::function < bool(DWORD arg)>> data;
	data.insert(std::pair<std::string, std::function < bool(DWORD arg)>>(PLAY_PAUSE, []() { choseType(kbi)}));
	data[PLAY_PAUSE](kbi, VK_MEDIA_PLAY_PAUSE);

	//kbi.wVk = VK_MEDIA_PLAY_PAUSE; // Provide your own


	kbi.wScan = 0;
	kbi.dwFlags = 0;  // See docs for flags (mm keys may need Extended key flag)
	kbi.time = 0;
	kbi.dwExtraInfo = (ULONG_PTR)GetMessageExtraInfo();

	INPUT input;
	input.type = INPUT_KEYBOARD;
	input.ki = kbi;

	SendInput(1, &input, sizeof(INPUT));
	//kbi.dwFlags = KEYEVENTF_KEYUP;

	//SendInput(1, &input, sizeof(INPUT));
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
