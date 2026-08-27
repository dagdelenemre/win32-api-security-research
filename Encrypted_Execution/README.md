# Encrypted Execution

Bu modül, statik analizi zorlaştırmak için şifrelenmiş bir shellcode'u runtime'da çözüp çalıştırmayı gösteren basit bir örnektir.

## Kullandığım Win32 API'leri

- **VirtualAlloc**: Bellekte şifreli kodun sığacağı kadar çalıştırılabilir (`PAGE_EXECUTE_READWRITE`) alan tahsis eder.
- **memcpy**: Şifreli baytları o alana kopyalar.
- **XOR döngüsü**: Şifreli baytları aynı anahtarla tekrar XOR'layarak orijinal shellcode'u elde eder.
- **CreateThread**: Çözülen shellcode'u yeni bir thread'de çalıştırır.

## İşlem Akışı

1. **XOR ile şifrelenmiş** calc.exe shellcode'u elimde hazır.
2. **VirtualAlloc** ile RAM'de yer açıyorum.
3. **memcpy** ile şifreli baytları oraya kopyalıyorum.
4. **For döngüsü** ile her baytı XOR anahtarıyla çözüyorum.
5. **CreateThread** ile çözülen kodu çalıştırıyorum.

## Savunma Perspektifi

Bu yöntem basit imza tabanlı antivirüsleri atlatabilir ama gelişmiş EDR'ler şifrelenmiş olsa bile runtime'da bellek taraması yaparak shellcode'u tespit eder. Ayrıca XOR gibi basit şifreleme, statik analizde hemen fark edilir. Gerçek saldırılarda daha güçlü şifreleme (AES) ve polimorfik kod kullanılır. Ama bu örnek, bellekte kod çözme mantığını öğrenmek için iyi bir başlangıç.
