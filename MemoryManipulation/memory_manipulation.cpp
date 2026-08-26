#include <iostream>
#include <windows.h>
#include <clocale>

using namespace std;


void CrossProcessMemory();
void MemoryScanner();

int main()
{
  setlocale(LC_ALL, "Turkish"); // Konsolu Türkçe karakterlere uyumlu hale getirir. debug için faydalı
  
  CrossProcessMemory();
  MemoryScanner();
}

void CrossProcessMemory()
{
  // Process'i yakalıyoruz
  HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE , 13256); //13256 Hedef process id. Örneğin: Notepad.exe pid = 13256
  if(hProcess != NULL)
  {
    cout << "1. Adım Processe bağlanıldı." << endl;
  } else {
    cout << "HATA: Process bulunamadı.." << endl;
  }
  
  // External(Dışarıdan) olarak Bellekte yer açıyoruz. Ör. Notepad.exe'nin belleğinde 100 BYTE'LIK yer açıyoruz.
  
  LPVOID lpAddress = VirtualAllocEx(hProcess, NULL, 100, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
  if(lpAddress != NULL)
  {
    cout << "2. adım Process'e hafıza ayrıldı. Ayrilan Adres:" << lpAddress << endl;
  } else {
	cout << "HATA: Process'e hafıza ayrılamadı" << endl;
  }

  // Bellekte açtığımız yere yazma işlemi yapıyoruz.

  BOOL sonuc = WriteProcessMemory(hProcess, lpAddress, "Ben Emre Kadir", 15, NULL);

  if(sonuc)
  {
    cout << "3. adım Process'e yazıldı." << endl;
  } else {
	cout << "HATA: Process'e yazılamadı" << endl;
  }
  CloseHandle(hProcess);
}

void MemoryScanner()
{
  HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, 1996);
  if(hProcess != NULL)
  {
    cout << "1. Adım Processe bağlanıldı." << endl;
  } else {
    cout << "HATA: Process bulunamadı.." << endl;
  }

  
	LPCVOID hedefAdres = (LPCVOID)0X000000FFE63DF744; // hedef adresi belirliyoruz

  int okunanCan = 0;
  SIZE_T okunanByteSayisi;

  BOOL sonuc = ReadProcessMemory(hProcess, hedefAdres, &okunanCan, sizeof(int), &okunanByteSayisi);

  if(sonuc == TRUE)
  {
    cout << "2. Adim Process'in hafizasi okundu." << endl;
    cout << "Hile Basarili! Okunan Can Degeri: " << okunanCan << endl;
  } else { 
    cout << "HATA: Process'in hafizasi okunamadi" << endl;
  } 

  int yeniCan = 9999;

  BOOL yazmaSonucu = WriteProcessMemory(hProcess, (LPVOID)hedefAdres, &yeniCan, sizeof(int), NULL);

  if (yazmaSonucu == TRUE) {
	  cout << "3. Adim: HACK BASARILI! Kurbanin cani 9999 yapildi!" << endl;
  } else {
	  cout << "HATA: Can degistirilemedi. Hata Kodu: " << GetLastError() << endl;
  }

  CloseHandle(hProcess); 
  
  
}

