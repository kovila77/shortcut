// ConsoleApplication8.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <Windows.h>
#include <tchar.h>

#define HOTKEY_EXIT 5555

KEYBDINPUT kbi;
INPUT input;

const TCHAR* szWinClass = _T("Shortcut");
const TCHAR* szWinNameCross = _T("Shortcut");

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
	//std::cout << message << " " << (char)wParam << std::endl;
	switch (message) {
	case WM_HOTKEY: {
		switch (wParam) {
		case VK_MEDIA_PLAY_PAUSE: {
			kbi.wVk = VK_MEDIA_PLAY_PAUSE;
			input.type = INPUT_KEYBOARD;
			input.ki = kbi;
			SendInput(1, &input, sizeof(INPUT));
			break;
		}
		case VK_VOLUME_UP: {
			kbi.wVk = VK_VOLUME_UP;
			input.type = INPUT_KEYBOARD;
			input.ki = kbi;
			SendInput(1, &input, sizeof(INPUT));
			break;
		}
		case VK_VOLUME_DOWN: {
			kbi.wVk = VK_VOLUME_DOWN;
			input.type = INPUT_KEYBOARD;
			input.ki = kbi;
			SendInput(1, &input, sizeof(INPUT));
			break;
		}
		case VK_MEDIA_NEXT_TRACK: {
			kbi.wVk = VK_MEDIA_NEXT_TRACK;
			input.type = INPUT_KEYBOARD;
			input.ki = kbi;
			SendInput(1, &input, sizeof(INPUT));
			break;
		}
		case VK_MEDIA_PREV_TRACK: {
			kbi.wVk = VK_MEDIA_PREV_TRACK;
			input.type = INPUT_KEYBOARD;
			input.ki = kbi;
			SendInput(1, &input, sizeof(INPUT));
			break;
		}
		case HOTKEY_EXIT:
		{
			PostMessageW(hwnd, WM_QUIT, 0, 0);
			break;
		}
		}
		break;
	}
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}


int main(int argc, const char* argv[])
{
	ShowWindow(GetConsoleWindow(), SW_HIDE);

	kbi.wScan = 0;
	kbi.dwFlags = 0;
	kbi.time = 0;
	kbi.dwExtraInfo = (ULONG_PTR)GetMessageExtraInfo();

	input.type = INPUT_KEYBOARD;
	input.ki = kbi;

	BOOL bMessageOk;
	MSG message;
	WNDCLASSEX wincl = { 0 };
	HINSTANCE hThisInstance = GetModuleHandle(NULL);

	wincl.lpszClassName = szWinClass;
	wincl.hInstance = hThisInstance;
	wincl.lpfnWndProc = WindowProcedure;
	wincl.cbSize = sizeof(WNDCLASSEX);

	if (!RegisterClassEx(&wincl)) {
		ShowWindow(GetConsoleWindow(), SW_SHOW);
		std::cout << "cant registerClass" << std::endl;
		system("PAUSE");
		return 0;
	}

	HWND hwnd = CreateWindowEx(
		NULL,
		szWinClass,          /* Classname */
		szWinNameCross,       /* Title Text */
		WS_OVERLAPPEDWINDOW, /* default window */
		CW_USEDEFAULT,       /* Windows decides the position */
		CW_USEDEFAULT,       /* where the window ends up on the screen */
		100,                 /* The programs width */
		100,                 /* and height in pixels */
		HWND_DESKTOP,        /* The window is a child-window to desktop */
		NULL,                /* No menu */
		hThisInstance,       /* Program Instance handler */
		NULL                 /* No Window Creation data */
	);

	if (hwnd == NULL) {
		ShowWindow(GetConsoleWindow(), SW_SHOW);
		std::cout << "hwnd cant create" << std::endl;
		system("PAUSE");
		UnregisterClass(szWinClass, hThisInstance);
		return 0;
	}

	bool d = true;

	d = d && RegisterHotKey(hwnd, VK_MEDIA_PLAY_PAUSE, MOD_CONTROL | MOD_ALT, VK_SPACE);
	d = d && RegisterHotKey(hwnd, VK_VOLUME_UP, MOD_CONTROL | MOD_ALT, VK_OEM_PLUS);
	d = d && RegisterHotKey(hwnd, VK_VOLUME_DOWN, MOD_CONTROL | MOD_ALT, VK_OEM_MINUS);

	d = d && RegisterHotKey(hwnd, VK_MEDIA_PLAY_PAUSE, MOD_CONTROL | MOD_ALT, VK_MULTIPLY);
	d = d && RegisterHotKey(hwnd, VK_MEDIA_PLAY_PAUSE, MOD_CONTROL, VK_NUMPAD0);
	d = d && RegisterHotKey(hwnd, VK_MEDIA_PLAY_PAUSE, MOD_CONTROL, VK_INSERT);

	d = d && RegisterHotKey(hwnd, VK_VOLUME_UP, MOD_CONTROL | MOD_ALT, VK_ADD);
	d = d && RegisterHotKey(hwnd, VK_VOLUME_DOWN, MOD_CONTROL | MOD_ALT, VK_SUBTRACT);

	d = d && RegisterHotKey(hwnd, VK_VOLUME_UP, MOD_CONTROL | MOD_ALT, VK_UP);
	d = d && RegisterHotKey(hwnd, VK_VOLUME_UP, MOD_CONTROL | MOD_ALT, VK_NUMPAD8);
	d = d && RegisterHotKey(hwnd, VK_VOLUME_DOWN, MOD_CONTROL | MOD_ALT, VK_DOWN);
	d = d && RegisterHotKey(hwnd, VK_VOLUME_DOWN, MOD_CONTROL | MOD_ALT, VK_NUMPAD2);
	d = d && RegisterHotKey(hwnd, VK_MEDIA_NEXT_TRACK, MOD_CONTROL | MOD_ALT, VK_RIGHT);
	d = d && RegisterHotKey(hwnd, VK_MEDIA_NEXT_TRACK, MOD_CONTROL | MOD_ALT, VK_NUMPAD6);
	d = d && RegisterHotKey(hwnd, VK_MEDIA_PREV_TRACK, MOD_CONTROL | MOD_ALT, VK_LEFT);
	d = d && RegisterHotKey(hwnd, VK_MEDIA_PREV_TRACK, MOD_CONTROL | MOD_ALT, VK_NUMPAD4);


	d = d && RegisterHotKey(hwnd, HOTKEY_EXIT, MOD_CONTROL | MOD_ALT | MOD_NOREPEAT, 'Q');

	if (!d) {
		ShowWindow(GetConsoleWindow(), SW_SHOW);
		std::cout << "cant RegisterHotKey" << std::endl;
		system("PAUSE");
		DestroyWindow(hwnd);
		UnregisterClass(szWinClass, hThisInstance);
		return 0;
	}

	//ShowWindow(hwnd, SW_SHOW);

	while ((bMessageOk = GetMessage(&message, NULL, 0, 0)) != 0) {
		if (bMessageOk == -1) {
			ShowWindow(GetConsoleWindow(), SW_SHOW);
			puts("Suddenly, GetMessage failed! You can call GetLastError() to see what happend");
			break;
		}

		TranslateMessage(&message);
		DispatchMessage(&message);
	}

	UnregisterHotKey(hwnd, VK_MEDIA_PLAY_PAUSE);
	UnregisterHotKey(hwnd, VK_VOLUME_UP);
	UnregisterHotKey(hwnd, VK_VOLUME_DOWN);
	UnregisterHotKey(hwnd, HOTKEY_EXIT);
	UnregisterHotKey(hwnd, VK_MEDIA_NEXT_TRACK);
	UnregisterHotKey(hwnd, VK_MEDIA_PREV_TRACK);
	DestroyWindow(hwnd);
	UnregisterClass(szWinClass, hThisInstance);
}
