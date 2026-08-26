# Memory Manipulation

Bu modül, çalışan bir process'in bellek alanına dışarıdan nasıl müdahale edilebileceğini gösteren iki parçalı bir PoC(Konsept Kanıtıdır)

Çalışma, hedef olarak yazılmış basit bir C++ uygulaması (KurbanOyun.cpp) ve bu uygulamanın bellek adreslerini okuyup değiştiren asıl manipülasyon aracından oluşmaktadır.

## Kullanılan Win32 API'leri ve Mantığı
Tool, işletim sistemi seviyesinde bellek sınırlarını aşmak için aşağıdaki API'leri kullanır:

*  **`OpenProcess`**: Hedef process'in pid'sini kullanarak process'e 'PROCESS_ALL_ACCESS' ile tam yetkili erişim atar.
*  **`ReadProcessMemory`**: Hedef process'deki spesifik bir adresteki veriyi okur. (can değeri)
*  **`VirtualAllocEx`**: Hedef sürecin belleğinde belirtilen büyüklükte alan tahsis eder.
*  **`WriteProcessMemory`**: Tahsis ettiğimiz alana veri yazarız ve programı manipüle etmiş oluruz. (Can değeri artık 9999)

## Perspektif

Yaptığımız işlem günümüz güvenlik yazılımları tarafından anında tespit edilecek kadar gürültülü olsa da ileri seviye saldırıların temelleri buradan geliyor.
