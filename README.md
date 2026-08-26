# Win32 API Security Research & Proof of Concepts

Bu repo, Windows mimarisi, bellek yönetimi ve Win32 API'nin nasıl çalıştığını anlama amacıyla geliştirdiğim C++ kodlarını içermektedir.

Geliştirilen modüller tamamen **eğitim ve Konsept Kanıtı** amaçlıdır. Temel hedef işletim sistemindeki processes, threads ve memory allocation gibi mekanikleri incelemektir.

## İçerik 

* **API HOOKING:** Fonksiyon çağrılarının bellekte nasıl yakalandığı/yönlendirildiği
* **Process Injection:** Hedef process'lerin bellek alanına dışarıdan veri yazma/çalıştırma
* **DLL Injection:** 'CreateRemoteThread' ve 'LoadLibraryA' kullanılarak hedef process'e dışarıdan DLL(kütüphane) yükleme
* **Memory Manipulation:** Çalışan process'lerin bellek alanlarını okuma/değiştirme
* **Encrypted Execution:** Bellek içi XOR şifreleme/çözme işlemleriyle statik analizi zorlaştırma
* **System & Process Enum:** İşletim sistemi bilgilerini çekme ve mevcut process'leri listeleme (Görev yöneticisi gibi)
* **Local Monitoring:** Temel seviye tuş yakalama (Keylogger)

# Neden Bu Proje?

Siber güvenlikte saldırganların yöntemlerini ve mantıklarını anlamanın ve EDR/AV teknolojilerinin neyi yakalaması gerektiğini bilmenin önemli olduğunu düşünüyorum.

> **Uyarı:** Bu depodaki kodlar gelişmiş bir evasion mekanizması içermez ve modern güvenlik çözümleri (Windows Defender vb.) tarafından anında tespit edilecek temel seviye örneklerdir. Kötü amaçlı kullanım için uygun değildir.
