# Keylogger

Bu modül, Windows'ta `GetAsyncKeyState` fonksiyonunu kullanarak klavye girişlerini doğrudan donanımdan okuyan basit bir polling (yoklama) örneğidir.

## Kullandığım API'ler

- **GetAsyncKeyState**: Belirtilen tuşun o anki durumunu (basılı mı değil mi) döndürür.
- **Sleep**: Döngüye bekleme ekleyerek CPU yükünü azaltır.

## İşlem Akışı

1. Sonsuz döngü içinde `'A'`'dan `'Z'`'ye kadar tüm harfleri tarıyorum.
2. Her tuş için `GetAsyncKeyState(tus)` çağrısı yapıyorum.
3. Dönen değerin en anlamlı bitini (`0x8000`) kontrol ederek tuşun basılı olup olmadığını anlıyorum.
4. Basılıysa o harfi ekrana yazıyorum.
5. `Sleep(100)` ile CPU'yu dinlendiriyorum.

## Savunma Perspektifi

Bu kadar basit bir polling, günümüz EDR'leri tarafından hemen fark edilir. Çünkü normal bir uygulamanın sürekli olarak tüm tuşları yoklaması anormal bir davranıştır. Ayrıca bu yöntem mesaj kuyruğunu atladığı için bazı tuşları kaçırabilir. Gerçek keylogger'lar genelde `SetWindowsHookEx` gibi daha gizli yöntemler kullanır. Bu örnek sadece temel mantığı anlamak için.
