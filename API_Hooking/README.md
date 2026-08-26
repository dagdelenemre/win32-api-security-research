# API Hooking 

Bu modül, bir process'in runtime'da çağırdığı Win32 API fonksiyonlarının akışını değiştirmek için kullanılan **Inline Hooking (Detours)** tekniğinin konsept kanıtıdır (PoC).

## Amaç ve Kapsam

Bu çalışma, `user32.dll` deki `MessageBoxA` fonksiyonunun bellek adresine dinamik olarak müdahale eder. Fonksiyonun ilk baytları değiştirilerek, çağrının orijinal fonksiyon yerine kendi tanımladığımız sahte fonksiyona (`HookedMessageBoxA`) yönlendirilmesi sağlanır.

## Kullanılan Win32 API'leri ve İşlevleri

* **`LoadLibraryA`**: İlgili kütüphaneyi (`user32.dll`) sürecin adres uzayına yükler ve modül tanıtıcısını (handle) döndürür.
* **`GetProcAddress`**: Yüklenen DLL içerisindeki hedeflenen fonksiyonun (`MessageBoxA`) sanal bellek adresini bulur.
* **`VirtualProtect`**: Hedef fonksiyonun kod segmentindeki bellek koruma bayraklarını değiştirir (kod yazabilmek için `PAGE_EXECUTE_READWRITE` yapar, ardından orijinal haline geri döndürür).
* **`memcpy`**: Hazırlanan 12 baytlık makine kodu yamasını (trampoline/jump) hedef fonksiyonun giriş adresine (prologue) yazar.

## İşlem Akışı

1. **Adres Tespiti:** `LoadLibraryA` ve `GetProcAddress` ile kancalanacak API'nin bellekteki başlangıç adresi tespit edilir.
2. **Bellek İzni:** `VirtualProtect` kullanılarak hedef kod alanındaki salt-okunur/çalıştırılır koruma kısıtı kaldırılarak yazma izni alınır.
3. **Yama Hazırlığı (Patching):** x64 mimarisine uygun mutlak atlama (Absolute Jump) baytları (`mov rax, addr; jmp rax`) oluşturulur ve sahte fonksiyonun adresi bu baytlara gömülür.
4. **Kanca Yerleşimi:** `memcpy` ile hedef fonksiyonun ilk baytları bu atlama komutuyla ezilir.
5. **İzinlerin Geri Yüklenmesi:** `VirtualProtect` ile bellek koruması eski güvenli durumuna döndürülür.

## Güvenlik ve EDR Perspektifi

Inline Hooking tekniği iki taraflı bir öneme sahiptir:

* **Defansif Kullanım:** Güvenlik yazılımları (EDR/AV), kritik API çağrılarını (`ntdll.dll` veya `kernel32.dll` seviyesinde) analiz etmek ve zararlı davranışları yakalamak için tam olarak bu yöntemle API'leri kancalar.
* **Ofansif / Evasion Boyutu:** EDR çözümlerinin kancalarını tespit etmek (Hook Detection) veya bu kancaları temizlemek (Unhooking) için aynı bellek yamalama mantığı kullanılır.
