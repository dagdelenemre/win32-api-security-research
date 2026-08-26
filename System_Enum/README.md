# System & Process Enumeration

Bu modül, Windows'da temel sistem bilgilerinin ve mevcut process'lerin Win32 API kullanılarak nasıl çekileceğini anlatıyor.

## Kullanılan Win32 API'leri ve İşlevleri

Bu araç temel olarak aşağıdaki API'leri kullanarak sistemde keşif (discovery) yapar:

*   **`CreateToolhelp32Snapshot`**: Sistemde çalışan process'lerin anlık olarak fotoğrafını çeker(snapshot). 
*   **`Process32First` / `Process32Next`**: Mevcut Processlerin okunması için kullanırız. Koddaki while döngüsünden hemen önce ilk process'i okuruz daha sonra döngüyle sonraki processleri sonuna kadar okuruz. 
*   **`GetComputerNameA` & `GetUserNameA`**: Bilgisayar adını ve kullanıcı adını char[] olarak döndürür.

## Güvenlik ve Denetim Perspektifi (Defensive View)

Saldırganlar, malware geliştirirken Windows'un sürüm ve uyumluluklarına göre davranmak zorundadırlar. Dolayısıyla enjekte edilmiş bir zararlı yazılımın doğru çalışabilmesi için bu kontrolü yapması gerekebilir.

Sağlam ve profesyonel bir mimari için konuşacak olursak, normal bir kullanıcı uygulamasının durduk yere 'CreateToolhelp32Snapshot' çağırdığında EDR(Endpoint Detection and Response) sistemleri şüpheyle yaklaşmalıdır. Bu kod örneği, bahsettiğimiz keşif aşamasının alt seviyede nasıl gerçekleştiğini kanıtlar. 
