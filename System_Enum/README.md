# System & Process Enumeration

Bu modül, Windows'ta temel sistem bilgilerini ve çalışan process'leri listelemek için Win32 API'lerini kullanır. Yani bir nevi basit bir Görev Yöneticisi gibi düşünün.

## Kullandığım API'ler

- **CreateToolhelp32Snapshot**: Sistemdeki process'lerin anlık görüntüsünü alır.
- **Process32First / Process32Next**: Snapshot'tan sırayla process'leri okur.
- **GetComputerNameA**: Bilgisayar adını alır.
- **GetUserNameA**: Oturum açmış kullanıcı adını alır.

## İşlem Akışı

1. `GetComputerNameA` ve `GetUserNameA` ile cihaz bilgilerini alıp ekrana yazdırıyorum.
2. `CreateToolhelp32Snapshot` ile process listesinin fotoğrafını çekiyorum.
3. `Process32First` ile ilk process'i alıp, `Process32Next` ile döngüde hepsini tek tek yazdırıyorum.

## Savunma Perspektifi

Sıradan bir uygulamanın bu API'leri çağırması normal olabilir, ama bir malware genellikle bu bilgiyi kendi davranışını (örneğin AV process'lerini tespit etmek için) kullanır. Bu yüzden EDR'ler, keşif (discovery) amaçlı bu tür çağrıları şüpheli aktivite olarak loglar. Ben burada bu mekaniği öğreniyorum, ileride daha sofistike keşif yöntemlerine geçeceğim.
