# DLL Injection

Bu modül, hedef bir process'in içine dışarıdan DLL yükleyerek kod çalıştırmayı gösteriyor.

## Kullandığım API'ler

- **OpenProcess**: Hedef process'e bağlanmak için.
- **VirtualAllocEx**: Hedefin belleğinde DLL yolunu yazmak için yer ayırıyorum.
- **WriteProcessMemory**: DLL yolunu o ayırdığım alana yazıyorum.
- **GetProcAddress + GetModuleHandle**: kernel32.dll'deki LoadLibraryA'nın adresini buluyorum.
- **CreateRemoteThread**: Hedef process'te LoadLibraryA'yı çalıştırarak DLL'in yüklenmesini sağlıyorum.

## Çalışma Mantığı

1. `OpenProcess` ile hedef PID'ye tam erişim alıyorum.
2. `VirtualAllocEx` ile hedefin belleğinde DLL yolumun sığacağı kadar yer açıyorum.
3. `WriteProcessMemory` ile o yere DLL yolunu yazıyorum.
4. `CreateRemoteThread` ile hedef process içinde LoadLibraryA'yı çağırarak DLL'imi yüklüyorum.

## Perspektif

Bu yöntem klasik DLL injection'dır. Günümüz AV/EDR sistemleri bu davranışı bilir ve hemen yakalar. Ama burada amaç, Windows'un process ve bellek yönetimini anlamak. Gerçek saldırılarda bu yöntem yerine Reflective DLL Injection veya başka teknikler kullanılır.
