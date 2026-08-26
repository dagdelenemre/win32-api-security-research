#include <iostream>
#include <windows.h>

using namespace std;

int main()
{
    // Oyunumuzun can degeri. Hafizada bir yerde tutuluyor.
    int canDegeri = 100;

    cout << "--- HEDEF OYUN CALISIYOR ---" << endl;
    cout << "Oyun PID Numarasi: " << GetCurrentProcessId() << endl;

    // C++'ta bir degiskenin basina '&' koyarsan, onun hafizadaki (RAM) adresini verir!
    cout << "Can Degerinin Hafiza Adresi: " << &canDegeri << endl;
    cout << "----------------------------" << endl;

    // Program kapanmasin diye sonsuz dongu
    while (true)
    {
        cout << "Anlik Can: " << canDegeri << endl;
        Sleep(3000); // 3 saniyede bir ekrana yazar
    }

    return 0;
}
