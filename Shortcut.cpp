// ConsoleApplication8.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>

bool findArg(int argc, char* argv[], const char* arg) {
	for (int i = 0; i < argc; i++) {
		if (!strcmp(argv[i], arg))
			std::cout << "lol" << std::endl;
	}
}

int main(int argc, char* argv[])
{
	const char* vv = "lol";
	findArg(argc, argv, vv);
	KEYBDINPUT kbi;
	kbi.wVk = VK_MEDIA_PLAY_PAUSE; // Provide your own
	kbi.wScan = 0;
	kbi.dwFlags = 0;  // See docs for flags (mm keys may need Extended key flag)
	kbi.time = 0;
	kbi.dwExtraInfo = (ULONG_PTR)GetMessageExtraInfo();

	INPUT input;
	input.type = INPUT_KEYBOARD;
	input.ki = kbi;

	SendInput(1, &input, sizeof(INPUT));
	kbi.dwFlags = KEYEVENTF_KEYUP;

	SendInput(1, &input, sizeof(INPUT));
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
