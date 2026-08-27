# API Hooking

Bu modül, çalışan bir process'in runtime'da çağırdığı Win32 API fonksiyonlarının akışını değiştirmek için kullanılan **Inline Hooking (Detours)** tekniğinin konsept kanıtıdır (PoC). Yani MessageBoxA çağrısını kendi fonksiyonuma yönlendiriyorum.

## Kullandığım Win32 API'leri

* **`LoadLibraryA`**: user32.dll'yi process'in adresler bölgesine yükler.
* **`GetProcAddress`**: MessageBoxA fonksiyonunun bellek adresini bulur.
* **`VirtualProtect`**: Hedef fonksiyonun bulunduğu bellek bölgesinin korumasını kaldırıp yazılabilir yapar (sonra eski haline döndürür).
* **`memcpy`**: Hazırladığım 12 baytlık makine kodunu (mov rax, addr; jmp rax) hedef fonksiyonun başına yazar.

## İşlem Akışı

1. **Adres tespiti**: LoadLibraryA ve GetProcAddress ile MessageBoxA'nın başlangıç adresini alıyorum.
2. **Bellek izni**: VirtualProtect ile o bölgeyi yazılabilir yapıyorum.
3. **Yama hazırlığı**: x64 mimarisine uygun mutlak atlama (JMP) baytlarını oluşturup sahte fonksiyonumun adresini içine gömüyorum.
4. **Kanca yerleşimi**: memcpy ile o atlama kodunu orijinal fonksiyonun başına yazıyorum.
5. **İzinleri geri alıyorum**: VirtualProtect ile korumayı eski haline döndürüyorum.

## Savunma Perspektifi (EDR / AV)

Bu yöntem, güvenlik yazılımlarının da kritik API'leri izlemek için kullandığı bir teknik. Ama aynı zamanda saldırganlar da bu kancaları tespit edip kaldırmak (unhooking) için aynı mantığı kullanır. Yani bu örnek, EDR'lerin nasıl çalıştığını anlamak için temel bir adım. İleride bu kancaları atlatmak için syscall kullanmayı da deneyeceğim.
