# Digitoy Okey Oyunu

C++ ile geleneksel Okey oyununun implementasyonu. Bu proje, tüm oyuncuların ellerini değerlendirir ve kazanmaya en yakın olanı belirler.

## Özellikler
- C++17 .
- Taşları oyunculara dağıtır ve ellerini değerlendirir.
- Olası perleri ve sıraları analiz ederek kazanmaya en yakın oyuncuyu belirler.
- Okey (joker) taşının kullanımını destekler.
- Normal sıralamalar ve çift açma stratejilerini içeren detaylı bir el değerlendirmesi yapar.

## Yaklaşım
1. **Ardışık Perleri Bulma**: 
   - Öncelikle çifte gitmeden eli değerlendirir.
   - Taşlar önce renklerine göre gruplandırılır ve sıralanır.
   - Ardışık perler belirlenir.(1,2,3)
   - Tüm olası geçerli perler (Okey kullanımı dahil) `std::vector<std::vector<Tile*>>` yapısında saklanır.
   
2. **Aynı Sayı İçeren Perleri Bulma**:
   - Taşlar sayısal değerlerine göre gruplandırılır.
   - Okey kullanımı dahil olmak üzere olası tüm perler perler belirlenir.(12,12,12)
   - Aynı veri yapısında saklanır.
   
3. **En Uzun Olası Perleri Bulma**:
   - Bulunan perler uzunluklarına göre büyükten küçüğe sıralanır.
   - Kullanılan taşlar işaretlenerek maksimum geçerli perler belirlenir.
   - Kazanmaya kalan taş sayısı hesaplanır.
     
4. **Çift Açma Stratejisi**:
   - Taşlar sayılarına göre sınıflandırılır.
   - Geçerli çiftler belirlenir ve ayrı bir `std::vector<std::vector<Tile*>>` yapısında saklanır.
   - Kazanmaya kalan taş sayısı hesaplanır.

5. **Kazanmaya En Yakın Oyuncunun Belirlenmesi**:
   - Oyuncuların çift veya düz açma stratejilerinden hangisine elleri daha uygunsa o kullanılır
   - Her oyuncunun elini tamamlaması için gereken taş sayısı hesaplanır.
   - Sonuçlar karşılaştırılarak kazanmaya en yakın oyuncu belirlenir.

## Derleme ve Çalıştırma
### Derleme
```sh
g++ -std=c++17 -g src/*.cpp -I include -o bin/output
```

### Çalıştırma
```sh
./bin/output
```

## Notlar
- Proje ağırlıklı olarak İngilizce yazılmıştır, ancak önemli kısımlarda açıklayıcı Türkçe yorumlar eklenmiştir.

## Lisans
Bu proje açık kaynaklıdır. Katkıda bulunmaktan çekinmeyin!

