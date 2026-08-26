#include <iostream>
#include <windows.h>
#include <clocale>

using namespace std;

typedef int(WINAPI* OriginalMessageBoxA)(HWND, LPCSTR, LPCSTR, UINT); //WINAPI = __stdcall yani fonksiyonu çağırma sırası, dizilme ve temizlenme

int WINAPI HookedMessageBoxA(HWND hWnd, LPCSTR lpText, LPCSTR lpCaption, UINT uType)
{
	cout << "Kanca Yakaladi! Orijinal mesaj engellendi." << endl;

	// Kancalanmamış MessageBoxW çağrılarak sonsuz döngü kırılır:
	return MessageBoxW(hWnd, L"Mesaj kanca tarafindan havada degistirildi!", L"HACKLENDI", uType);
}

int main()
{
  setlocale(LC_ALL, "Turkish"); // Konsolu Türkçe karakterlere uyumlu hale getirir. debug için faydalı
  

}

void SetupHook()
{
  // Adım A: user32.dll içindeki gerçek MessageBoxA adresini buluyoruz
  HMODULE hUser32 = LoadLibraryA("user32.dll");
  LPVOID targetFunc = (LPVOID)GetProcAddress(hUser32, "MessageBoxA");

  // Adım B: Bellek korumasını kaldırıp yazılabilir yapıyoruz
  DWORD oldProtect;
  VirtualProtect(targetFunc, 12, PAGE_EXECUTE_READWRITE, &oldProtect);

  // Adım C: Orijinal fonksiyonu saklıyoruz ki istersek sonradan çağırabilelim
  oMessageBoxA = (OriginalMessageBoxA)targetFunc;

  // Adım D: Burada bellek üzerine sıçrama (JMP) byte'larını yazacağız
  BYTE patch[] = {
	0x48, 0xB8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0xFF, 0xE0 // jmp rax
  };

  // Sahte fonksiyonumuzun adresini alıp patch dizisinin içine yerleştiriyoruz
  uintptr_t hookAddress = (uintptr_t)HookedMessageBoxA;
  memcpy(&patch[2], &hookAddress, sizeof(uintptr_t)); // memcpy ile hookAddress'i patch dizisine kopyalıyoruz

  // Hazırladığımız bu 12 baytlık yamayı orijinal fonksiyonun başına yazıyoruz
  memcpy(targetFunc, patch, sizeof(patch));

  // Adım E: Bellek korumasını eski haline geri alıyoruz
  VirtualProtect(targetFunc, 12, oldProtect, &oldProtect);
  
}
