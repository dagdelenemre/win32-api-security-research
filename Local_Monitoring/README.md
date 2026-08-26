# Keylogger

Bu modül, Windows işletim sisteminde standart mesaj kuyruklarını atlayarak klavye donanımının anlık durumunu doğrudan sorgulayan **Asenkron Polling** yaklaşımının mimari incelemesidir.

## 📌 Amaç ve Kapsam

Bu çalışma, `user32.dll` alt sistemindeki `GetAsyncKeyState` fonksiyonunun sanal tuş kodları (Virtual-Key Codes) üzerinden donanım durumunu nasıl okuduğunu, dönen 16-bitlik verinin bit düzeyinde nasıl maskelendiğini ve mesaj kuyruğu bağımsız girdi modellerinin davranışını incelemek amacıyla hazırlanmıştır.

## ⚙️ Kullanılan Win32 API'leri ve İşlevleri

* **`GetAsyncKeyState`**: Belirtilen sanal tuşun (`vKey`) fonksiyon çağrıldığı andaki fiziksel basılma durumunu ve önceki çağrıdan bu yana basılıp bırakılma bilgisini 16-bitlik bir tam sayı olarak döndürür.
* **`Sleep`**: Polling döngüsünün işlemciyi (CPU) aşırı tüketmesini engellemek ve donanım okuma frekansını dengelemek amacıyla iş parçacığını belirli bir milisaniye boyunca askıya alır.

## 🔄 İşlem Akışı

1. **Tuş Aralığının Taranması:** Tanımlanan sanal tuş kodları (örneğin ASCII `'A'` - `'Z'` aralığı) bir döngü aracılığıyla sırayla gezilir.
2. **Donanım Durumu Sorgulama:** Her tuş için `GetAsyncKeyState(key)` çağrısı yapılarak çekirdekteki (kernel) anlık durum tablosu okunur.
3. **Bit Düzeyinde Maskeleme:** Dönen 16-bitlik değer `& 0x8000` mantıksal VE işlemine tabi tutularak En Anlamlı Bit (MSB - tuşun o an basılı olup olmadığı) filtrelenir.
4. **Veri İşleme:** Basılı olduğu tespit edilen tuşun karakter değeri standart çıktı akışına aktarılır.
5. **Döngü Frekansı Dengesi:** `Sleep()` ile bir sonraki tarama döngüsüne kadar iş parçacığı bekletilerek CPU yükü sınırlandırılır.

## 📝 Mimari ve Savunma Perspektifi

* **Mekanik Fark:** Standart konsol girdi fonksiyonları (`_getch`, `ReadConsoleInput`) işletim sisteminin olay kuyruğunu (FIFO Buffer) kullanırken; bu model doğrudan donanım durumunu yoklar (polling). Bu nedenle girdi sırası garantisi vermez ve tuş kaçırma/çift basma (bounce) sorunlarına açıktır.
* **Güvenlik Perspektifi:** Arka planda global olarak tuş durumlarını yoklayan döngüler, uç nokta izleme çözümleri (EDR/AV) ve davranışsal analiz sistemleri tarafından şüpheli girdi izleme aktivitesi (Input Capture / Polling Anomaly) olarak değerlendirilebilir.
