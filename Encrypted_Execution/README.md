# Encrypted Execution

Bu modül, statik analizi zorlaştırmak (obfuscation) amacıyla şifrelenmiş bir shellcode'un runtime bellekte nasıl çözülüp çalıştırıldığını gösteren temel bir örnektir.

## Mantık ve Kullanılan API'ler

*   **XOR Şifreleme:** Shellcode'lar antivirüse takılmamak için XOR ile şifrelenir. (Ör. 0x5A anahtarıyla)
*   **`VirtualAlloc`:** Bellekte şifreli kodun BYTE değeri sığacak kadar, çalıştırılabilir (`PAGE_EXECUTE_READWRITE`) bir alan tahsis eder.
*   **Bellek İçi Çözme (Decryption):** Şifreli baytlar bu alana kopyalanır ve C++ içindeki bir `for` döngüsüyle tekrar aynı XOR anahtarına sokularak orijinal makine koduna dönüştürülür.
*   **`CreateThread`:** Çözülen temiz makine kodunu yeni bir thread üzerinden çalıştırır.

# Perspektif

Saldırganların, antivirüslerin davranışlarına göre davrandığını ve nasıl davrandığını incelemiş oluyoruz. Bu örnek gelişmiş antivirüsleri bypass edebilecek bir örnek olmasa dahi temeller buradan geliyorlar.
