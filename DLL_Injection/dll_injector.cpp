#include <iostream>
#include <windows.h>
#include <clocale>

using namespace std;


void DllInjector();

int main()
{
  setlocale(LC_ALL, "Turkish"); // Konsolu Türkçe karakterlere uyumlu hale getirir. debug için faydalı
  
  DllInjector();
  
}

void DllInjector()
{
	const char* dllPath = "C:\\temp\\mydll.dll";
	SIZE_T pathSize = strlen(dllPath) + 1; //yolun boyutu (+1 null karakteri için)

	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, 384);

	LPVOID lpAdrress = VirtualAllocEx(hProcess, NULL, pathSize, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	WriteProcessMemory(hProcess, lpAdrress, dllPath, pathSize, NULL);

	// kernel32.dll'in icindeki LoadLibraryA fonksiyonunun bellek adresini buluyoruz
	LPVOID loadLibraryAddr = (LPVOID)GetProcAddress(GetModuleHandleA("kernel32.dll"), "LoadLibraryA");

	// Notepad'e: "Yeni bir is parcacigi baslat, LoadLibraryA motorunu calistir ve icine benim yazdigim adresi (lpAdress) ver."
	HANDLE hThread = CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)loadLibraryAddr, lpAdrress, 0, NULL);

	if (hThread != NULL)
	{
		cout << "DLL basariyla enjekte edildi ve çalıştırıldı." << endl;
		CloseHandle(hThread);
	}
}
