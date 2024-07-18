#include <windows.h>
#include <iostream>
#include <urlmon.h>
#include <string>
#include <conio.h>

///inject includes
#include "define/stdafx.h"
#include "api/xor.h"
#include "api/api.h"
#include "driver/driver.h"
#include "inject/injector.h"
#include "api/drvutils.h"
#include "xorstr.h"
#pragma comment(lib, "urlmon.lib")

HWND fnt = NULL;
char title[100];
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

void getrandomnumber(char* sStr, unsigned int iLen)
{
	char Syms[] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	unsigned int Ind = 0;
	srand(time(NULL) + rand());
	while (Ind < iLen)
	{
		sStr[Ind++] = Syms[rand() % 62];
	}
	sStr[iLen] = '\0';
}

std::string randomstringtorenameexe(const size_t length)
{
	std::string r;
	static const char bet[] = { "abcdefghijklmnopqrstuvwxyzz" };
	srand((unsigned)time(NULL) * 10);
	for (int i = 0; i < length; ++i)
		r += bet[rand() % (sizeof(bet) - 1)];
	return r;
}

std::string path()
{
	char shitter[_MAX_PATH];
	GetModuleFileNameA(NULL, shitter, _MAX_PATH);
	return std::string(shitter);
}

void checkadmin() {

	bool admin = false;

	BOOL fRet = FALSE;
	HANDLE hToken = NULL;
	if (OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hToken)) {
		TOKEN_ELEVATION Elevation;
		DWORD cbSize = sizeof(TOKEN_ELEVATION);
		if (GetTokenInformation(hToken, TokenElevation, &Elevation, sizeof(Elevation), &cbSize)) {
			fRet = Elevation.TokenIsElevated;
		}
	}
	if (hToken) {
		CloseHandle(hToken);
	}
	admin = fRet;

	if (!admin) {
		exit(0);
	}

}


int main()
{		
	system("mode con cols=90 lines=25");
	std::string name = "NSA-" + randomstringtorenameexe(10) + ".exe";
	std::rename(path().c_str(), name.c_str());
	getrandomnumber(title, 32);
	SetConsoleTitle(title);
	SetConsoleTextAttribute(hConsole, 7);
	std::cout << R"(
                 ▐ ▄ .▄▄ ·  ▄▄▄·     ▄▄▄ .▐▄• ▄ ▄▄▄▄▄▄▄▄ .▄▄▄   ▐ ▄  ▄▄▄· ▄▄▌  
                •█▌▐█▐█ ▀. ▐█ ▀█     ▀▄.▀· █▌█▌▪•██  ▀▄.▀·▀▄ █·•█▌▐█▐█ ▀█ ██•  
                ▐█▐▐▌▄▀▀▀█▄▄█▀▀█     ▐▀▀▪▄ ·██·  ▐█.▪▐▀▀▪▄▐▀▀▄ ▐█▐▐▌▄█▀▀█ ██▪  
                ██▐█▌▐█▄▪▐█▐█ ▪▐▌    ▐█▄▄▌▪▐█·█▌ ▐█▌·▐█▄▄▌▐█•█▌██▐█▌▐█ ▪▐▌▐█▌▐▌
                ▀▀ █▪ ▀▀▀▀  ▀  ▀      ▀▀▀ •▀▀ ▀▀ ▀▀▀  ▀▀▀ .▀  ▀▀▀ █▪ ▀  ▀ .▀▀▀   
                                           
)" << '\n';
	std::cout << xor("\n\n                         [!] @humbleness made this :3") << std::endl;
	
	Sleep(3000);
	std::cout << xor("                         [+] Loading Driver") << std::endl;
	// startdriver();
	// find a way to use https://github.com/armvirus/fs_driver_loader  to automatically load the driver before the anticheat 
	// THE DRIVERS HAVE TO BE SIGNED. USE THE EAC OR NVIDEA CERTS
	std::cout << xor ("                         [+] Locating Window") << std::endl;
	while (fnt == NULL)
	{
		fnt = FindWindowA(0, "Fortnite");    // change this shit to whatever i wanna inj too :D
		Sleep(1);
	}
	Sleep(5000);
	std::cout << xor ("                         [+] Process Found!") << std::endl;
	std::cout << xor ("                         [+] Press Any Key To Start Process Injecting (Must Be In Lobby)") << std::endl;
	getch();

	        // Injector Notes 
		// (Respawn001 - Apex Legends Window Class Name)
		// (UnrealWindow - Valorant Window Class Name	
	        // then enter the dll name for the cheeto :D 
	    injector(xor_a("Respawn001"), xor_w(L"google.dll"));

		std::cout << xor ("                        [+] Application Exiting In 5 seconds") << std::endl;
		Sleep(5000);
		return 0;
}

