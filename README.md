# GTU-Electronic-Projects

Coursework from the Electronics Engineering program at Gebze Technical University (GTU): Introduction to Programming / Algorithms and Programming (Python & C) project assignments, plus a Jupyter notebook exercise on YOLOv10 object detection.

---

## Türkçe

Bu repo, Gebze Teknik Üniversitesi Elektronik Mühendisliği bölümünde alınan "Introduction to Programming" ve "Algorithms and Programming I/II" derslerine ait proje ödevlerini ve bir nesne tanıma (object detection) not defterini içerir.

### Inf projeler/

#### INF 211P (Algorithms and Programming I - Python)

- **P3/**
  - `euroleague_simulation.py` – Nesne yönelimli (OOP) bir EuroLeague basketbol sezonu simülasyonu. `Person`, `Player`, `Manager`, `Team`, `Match` ve `Season` sınıflarıyla haftalık fikstür oluşturma, maç sonuçlarını rastgele üretme, oyuncu/menajer/takım istatistiklerini takip etme ve sezon şampiyonunu belirleme işlevlerini içerir.
  - `project4_submission.py` – Aynı proje için verilen sınıf iskeleti/şablon dosyası (boş metodlarla).
  - `players.txt`, `managers.txt`, `teams.txt` – Simülasyonda kullanılan örnek EuroLeague oyuncu, menajer ve takım isimleri (herkese açık, gerçek basketbolcu/menajer/takım isimleri, kişisel veri değildir).

- **P4/**
  - `word_puzzle_solver.py` – Bir kelime bulmacası (crossword) tahtası oluşturma, kelime yerleştirme, tutarlılık kontrolü ve otomatik çözüm bulma mantığı içeren komut satırı oyunu.
  - `INF211_Proje_3.rar` – Bu projeye ait ek bir teslim arşivi (içeriği ayrıca incelenmemiştir).

#### INF 212P (Algorithms and Programming II - C)

- **P3/** – "Grocery Delivery Automation Program": Tek yönlü bağlı listeler (singly linked list) kullanılarak müşteri, ürün ve mağaza bilgilerinin yönetildiği bir market teslimat otomasyonu.
  - `delivery_automation.c` / `delivery_automation.h` – Müşteri, ürün, mağaza ve satın alma kayıtlarını yöneten bağlı liste yapıları ve menü tabanlı arayüz fonksiyonları.
  - `main.c` – Örnek müşteri/ürün/mağaza verileriyle programı çalıştıran giriş noktası.
  - `INF212_P3_Report.docx`, `INF212 Project-3.pdf` – Proje raporu ve ödev tanım dosyası.
  - `INF212_Project_Report_Template.docx` – Ders için sağlanan boş rapor şablonu.
  - `Proje3.xlsx` – Proje için kullanılan örnek müşteri/ürün/mağaza veri tablosu.

- **P4/** – "Create a Project with Your Array Library": İki boyutlu diziler (matrisler) üzerinde işlem yapan özel bir C kütüphanesi.
  - `matrix_operations.c` / `matrix_operations.h` – Değer arama, tekrarsız eleman sayma, min/max bulma, satırları sıralama, transpoze alma, matris çarpımı, birim/simetrik matris kontrolü ve LU ayrıştırması (decomposition) fonksiyonları.
  - `main.c` – Kütüphaneyi test eden örnek program.
  - `INF212_P4_Report.docx`, `INF212 Project-4.pdf` – Proje raporu ve ödev tanım dosyası.

### notebooks/

- `train-yolov10-object-detection-on-custom-dataset.ipynb` – Roboflow'un genel YOLOv10 nesne tanıma eğitim eğitimi (tutorial) baz alınarak, Roboflow Universe üzerinden indirilen özel bir veri kümesi (tümör tespiti) üzerinde model eğitimi, doğrulama ve çıkarım (inference) adımlarını gösteren Google Colab not defteri.

---

## Not / Note

Bazı dosyalarda daha önce yer alan öğrenci adı, öğrenci numarası ve kişisel e-posta adresi gibi bilgiler genel yer tutucularla (placeholder) değiştirilmiştir.

Personal identifiers (student name, student ID, personal email) previously embedded in a few source files and report documents have been replaced with generic placeholders.
