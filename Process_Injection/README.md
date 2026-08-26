# Process Injection

Bu modül, Windows'da bir shellcodu'un başka bir process'in içerisine enjekte edilmesini anlatır.

## Kullanılan Win32 API'leri ve İşlevleri

Bu çalışmada yararlanılan temel sistem fonksiyonları:

* **`VirtualAlloc/VirtualAllocEx`**: Bellekte shellcode'un sığacağı kadar yer tahsis edilir
* **`memcpy/WriteProcessMemory`**: memcpy iile kopyalama işlemi WriteProcessMemory ile belleğe yazma işlemi yapılır.
* **`CreateThread/CreateRemoteThread`**: Thread(iş parçacıkları) oluşturmaya yarar

## Perspektif

Bu çalışma, Windows'da process'ler arası bellek yönetimini ve kod yürütme akışını incelemek amacıyla hazırlanmıştır.
Standart Win32 API'lerinin ardışık kullanımı yüksek bir davranışsal imza (behavioral heuristic) oluşturduğundan,
güncel sistemlerde savunma mekanizmalarının ve telemetri loglarının nasıl çalıştığını anlamak için temel bir referanstır.
