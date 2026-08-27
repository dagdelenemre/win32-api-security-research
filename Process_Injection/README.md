# Process Injection

Bu modül, bir shellcode'u başka bir process'in belleğine yazıp orada çalıştırmayı gösteren klasik bir örnektir.

## Kullandığım API'ler

- **VirtualAllocEx**: Hedef process'in belleğinde shellcode için yer açar.
- **WriteProcessMemory**: Shellcode baytlarını hedef process'e yazar.
- **CreateRemoteThread**: Hedef process'te yeni bir thread başlatarak shellcode'u çalıştırır.

## İşlem Akışı

1. **OpenProcess** ile hedef PID'ye bağlanıyorum.
2. **VirtualAllocEx** ile hedefin belleğinde shellcode boyutunda alan ayırıyorum.
3. **WriteProcessMemory** ile shellcode'u o alana yazıyorum.
4. **CreateRemoteThread** ile hedef process içinde o adresi çalıştırıyorum.

## Savunma Perspektifi

Bu yöntem çok iyi bilindiği için EDR'ler `CreateRemoteThread` çağrısını ve `PAGE_EXECUTE_READWRITE` ile ayrılmış bellek bölgelerini izler. Ayrıca shellcode'un calc.exe açması gibi basit davranışlar da hemen yakalanır. Bu örnek, process'ler arası kod çalıştırmanın temelini gösteriyor. İleride daha gizli teknikler (Process Hollowing, APC Injection, vb.) öğrenmek için iyi bir başlangıç.
