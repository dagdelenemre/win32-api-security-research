#include <iostream>
#include <windows.h> //win32 api kütüphanesi
#include <TlHelp32.h> //windowsta çalışan process ve thread'leri listelemek için kullanılır. birazdan snapshot alacağım.
#include <clocale> 

using namespace std;

//Kullanacağım fonksiyonları önden tanımlıyorum.
void DeviceInfos();
void ProcessManager();

int main()
{
  setlocale(LC_ALL, "Turkish"); //konsolu türkçe karakterlere uygun hale getirir. debug aşaması için faydalı.
  DeviceInfos();
  ProcessManager();
}

void DeviceInfos()
{
  // Mevcut Process'leri Snapshot Alıyorum
  CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0); 
  DWORD pid = GetCurrentProcessId();

  // Bilgisayarın adını alıyorum
  char compName[256];
  DWORD compSize= 256;
  GetComputerNameA(compName, &compSize);

  // Kullanıcı adını alıyorum
  char userName[256];
  DWORD userSize = 256;
  GetUserNameA(userName, &userSize);
  
  cout << "Computer Name: " << compName << endl;
  cout << "Current Process ID: " << pid << endl;
  cout << "User Name: " << userName << endl << endl;
}

void ProcessManager()
{
  //Process'leri alıyorum
  HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

  //Aldığım process bilgilerini tutuyorum
  PROCESSENTRY32 pe32;
  pe32.dwSize = sizeof(PROCESSENTRY32);

  // İlk Process'i okuyup sonrakileri de while döngüsünde okuyorum
  Process32First(hSnapshot, &pe32);
  while(Process32Next(hSnapshot, &pe32))
  {
   wcout << "Process ID: " << pe32.th32ProcessID << endl;
   wcout << pe32.szExeFile << endl << endl; 
  }
  // HANDLE'ı kapatıyorum bellek şişmesin diye.
  CloseHandle(hSnapshot); 
}
  
  
