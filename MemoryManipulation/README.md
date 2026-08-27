# Memory Manipulation

Bu modül, çalışan bir process'in bellek alanına dışarıdan nasıl müdahale edilebileceğini gösteren iki parçalı bir PoC'dir. Hedef olarak yazılmış basit bir oyun (KurbanOyun.cpp) ve bu oyunun can değerini değiştiren araçtan oluşur.

## Kullandığım API'ler

- **OpenProcess**: Hedef process'e PROCESS_ALL_ACCESS ile bağlanır.
- **ReadProcessMemory**: Hedef process'teki belirli bir adresten veri okur.
- **VirtualAllocEx**: Hedefin belleğinde yeni bir alan tahsis eder (CrossProcessMemory örneğinde).
- **WriteProcessMemory**: Tahsis edilen veya okunan adrese yeni veri yazar.

## İşlem Akışı

1. **CrossProcessMemory**: Başka bir process'in belleğinde yer açıp oraya "Hacked by Attacker" yazıyorum (sadece yazma örneği).
2. **MemoryScanner**: KurbanOyun'un PID'sini ve can değerinin adresini kullanarak:
   - `ReadProcessMemory` ile mevcut canı okuyorum.
   - `WriteProcessMemory` ile canı 9999 yapıyorum.

## Savunma Perspektifi

`ReadProcessMemory` ve `WriteProcessMemory` çağrıları, AV/EDR sistemleri için klasik sinyallerdir. Özellikle `PROCESS_ALL_ACCESS` ile açılan bir process hemen şüphe uyandırır. Bu nedenle bu yöntem günümüzde çok gürültülüdür. Ama burada amaç, Windows bellek yönetimini ve process'ler arası veri alışverişini anlamak. Gerçek saldırılarda bu işlemler daha gizli API'lerle veya driver seviyesinde yapılır.
