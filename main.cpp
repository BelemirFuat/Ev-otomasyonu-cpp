#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include <ctime>
#include <chrono>

class zaman;
class simdikiZaman;
class Isik;
class IsikKontrol;
class sicaklikKontrol;
class guvenlikKamerasi;
class hirsizlikAlarmi;
class perdeKontrol;
class otomasyon;
class guvenlikSistemi;
class konum;

class konum
{
public:
    int x;
    int y;
    int z;

    konum()
    {
        x = 0;
        y = 0;
        z = 0;
    }
};
class zaman
{
private:
    int saat;
    int dakika;

public:
    zaman(int s, int d)
    {
        this->saat = s;
        this->dakika = d;
    }
    zaman() : saat(0), dakika(0) {}

    bool SetSaat(int s_)
    {
        if (s_ < 24 && s_ >= 0)
            this->saat = s_;
        else
            return false;
        return true;
    }
    bool SetDakika(int d_)
    {
        if (d_ < 60 && d_ >= 0)
            this->dakika = d_;
        else
            return false;
        return true;
    }

    int getSaat() { return this->saat; }
    int getDakika() { return this->dakika; }

    zaman *getZaman() { return this; }
    std::string toString() const
    {
        return std::to_string(saat) + ":" + std::to_string(dakika);
    }

    friend std::ostream &operator<<(std::ostream &os, const zaman &z)
    {
        os << z.toString();
        return os;
    }
    bool operator>=(const zaman &other) const
    {
        if (this->saat > other.saat)
            return true;
        else if (this->saat == other.saat && this->dakika >= other.dakika)
            return true;
        else
            return false;
    }
};

class simdikiZaman
{
public:
    zaman simdiKi;
    simdikiZaman()
    {
        simdiKi = zamanHesapla();
    }

    zaman zamanHesapla()
    {
        auto simdi = std::chrono::system_clock::now();
        std::time_t simdiTime = std::chrono::system_clock::to_time_t(simdi);
        std::tm *gercekZaman = std::localtime(&simdiTime);
        simdiKi.SetSaat(gercekZaman->tm_hour);
        simdiKi.SetDakika(gercekZaman->tm_min);
        return simdiKi;
    }
};

class Isik
{
public:
    std::string isim;
    float isikParlaklik;
    bool otomatikKapan;
    bool otomatikAcil;
    bool acikMi;
    zaman kapanmaZamani;
    zaman acilmaZamani;

    void print()
    {
        std::cout << "Isim: " << this->isim << std::endl;
        std::cout << "Parlaklik " << this->isikParlaklik << std::endl;
        std::cout << "Acik mi: ";

        if (this->acikMi)
            std::cout << "Acik " << std::endl;
        else
            std::cout << "Kapali " << std::endl;

        std::cout << "Otomatik acilma programi: ";

        if (otomatikAcil)
            std::cout << "Acik : " << this->acilmaZamani << std::endl;
        else
            std::cout << "Kapali" << std::endl;

        std::cout << "Otomatik Kapanma Programi: ";

        if (this->otomatikKapan)
            std::cout << "Acik: " << this->kapanmaZamani << std::endl;
        else
            std::cout << "Kapali. " << std::endl;
    }
};

class IsikKontrol
{
public:
    std::vector<Isik> isiklar;

    void zamaniGelenleriKapat()
    {
        simdikiZaman zmn;
        zaman smd = zmn.simdiKi;
        for (auto &it : isiklar)
        {
            if (it.kapanmaZamani >= smd)
            {
                std::cout << "Kapandi: " << it.isim << " " << it.kapanmaZamani << "\n";
                it.acikMi = false;
            }
        }
    }

    void zamaniGelenleriAc()
    {
        simdikiZaman zmn;
        zaman smd = zmn.simdiKi;
        for (auto &it : isiklar)
        {
            if (it.acilmaZamani >= smd)
            {
                std::cout << "Acildi: " << it.isim << " " << it.acilmaZamani << "\n";
                it.acikMi = true;
            }
        }
    }

    void tumIsiklarinOtomatikKapanmaZamanlariniAyarla(zaman z)
    {
        for (auto &it : isiklar)
        {
            it.kapanmaZamani = z;
        }
    }
    void tumIsiklarinOtomatikAcilmaZamanlariniAyarla(zaman z)
    {
        for (auto &it : isiklar)
        {
            it.acilmaZamani = z;
        }
    }

    void print()
    {
        if (isiklar.size() == 0)
        {
            std::cout << "Isik Yok." << std::endl;
            return;
        }
        for (auto &it : isiklar)
        {
            it.print();
        }
    }

    void guncelle()
    {
        zamaniGelenleriAc();
        zamaniGelenleriKapat();
    }
};

class sicaklikCihazi
{
public:
    std::string isim;
    std::string tur;
    float sicaklik;
    bool otomatikAcil;
    bool otomatikKapan;
    zaman acilmaZamani;
    zaman kapanmaZamani;
    bool acikMi;

    void print()
    {
        std::cout << "Isim: " << this->isim << std::endl;
        std::cout << "Sicaklik: " << this->sicaklik << std::endl;
        std::cout << "Acik mi: ";

        if (this->acikMi)
            std::cout << "Acik " << std::endl;
        else
            std::cout << "Kapali " << std::endl;

        std::cout << "Otomatik acilma programi: ";

        if (otomatikAcil)
            std::cout << "Acik : " << this->acilmaZamani << std::endl;
        else
            std::cout << "Kapali" << std::endl;

        std::cout << "Otomatik Kapanma Programi: ";

        if (this->otomatikKapan)
            std::cout << "Acik: " << this->kapanmaZamani << std::endl;
        else
            std::cout << "Kapali. " << std::endl;
    }
};

class sicaklikKontrol
{
public:
    std::vector<sicaklikCihazi> sicaklikCihazlari;

    void zamaniGelenleriKapat()
    {
        simdikiZaman zmn;
        zaman smd = zmn.simdiKi;
        for (auto &it : sicaklikCihazlari)
        {
            if (it.kapanmaZamani >= smd)
            {
                std::cout << "Kapandi: " << it.isim << " " << it.kapanmaZamani << "\n";
                it.acikMi = false;
            }
        }
    }

    void zamaniGelenleriAc()
    {
        simdikiZaman zmn;
        zaman smd = zmn.simdiKi;
        for (auto &it : sicaklikCihazlari)
        {
            if (it.acilmaZamani >= smd)
            {
                std::cout << "Acildi: " << it.isim << " " << it.acilmaZamani << "\n";
                it.acikMi = true;
            }
        }
    }

    void tumIsiklarinOtomatikKapanmaZamanlariniAyarla(zaman z)
    {
        for (auto &it : sicaklikCihazlari)
        {
            it.kapanmaZamani = z;
        }
    }
    void tumIsiklarinOtomatikAcilmaZamanlariniAyarla(zaman z)
    {
        for (auto &it : sicaklikCihazlari)
        {
            it.acilmaZamani = z;
        }
    }

    void print()
    {
        if (sicaklikCihazlari.size() == 0)
        {
            std::cout << "Cihaz Yok." << std::endl;
            return;
        }
        for (auto &it : sicaklikCihazlari)
        {
            it.print();
        }
    }
    void guncelle()
    {
        zamaniGelenleriAc();
        zamaniGelenleriKapat();
    }
};

class guvenlikKamerasi
{
public:
    std::string isim;
    konum kameraKonumu;
    bool acikMi;
    int goruntuKalitesi = 10;
    int goruntu[10][10];

    guvenlikKamerasi()
    {
        goruntuGuncelle();
    }
    void goruntuGuncelle()
    {
        for (int i = 0; i < this->goruntuKalitesi; i++)
        {
            for (int j = 0; j < this->goruntuKalitesi; j++)
            {
                this->goruntu[i][j] = rand() % 255;
            }
        }
    }
    void yazdir()
    {
        std::cout << "Kamera: " << this->isim << "\nGoruntu : \n";
        for (int i = 0; i < this->goruntuKalitesi; i++)
        {
            for (int j = 0; j < this->goruntuKalitesi; j++)
            {
                std::cout << this->goruntu[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }
    void guncelle()
    {
        goruntuGuncelle();
    }
};

class hirsizAlarmi
{
public:
    bool acikMi;
    int calmaOlasiligi = rand() % 100;
    std::string isim;

    void cal()
    {
        if (this->acikMi)
        {
            if (rand() % 100 == this->calmaOlasiligi)
            {
                std::cout << "Alarm Caliyor! : " << this->isim << std::endl;
            }
        }
    }
};

class guvenlikSistemi
{
public:
    std::vector<guvenlikKamerasi> kameralar;
    std::vector<hirsizAlarmi> alarmlar;

    void guncelle()
    {
        for (auto &it : kameralar)
        {
            it.guncelle();
        }
        for (auto &it : alarmlar)
        {
            it.cal();
        }
    }
    void goruntule()
    {
        for (auto &it : kameralar)
        {
            it.yazdir();
        }
    }
};

class perdeler
{
public:
    std::string isim;
    std::string tur;
    bool otomatikAcil;
    bool otomatikKapan;
    zaman acilmaZamani;
    zaman kapanmaZamani;
    int aciklik; // 0-100 arasinda

    void print()
    {
        std::cout << "Isim: " << this->isim << std::endl;
        std::cout << "Acik mi: ";

        if (this->aciklik > 0)
            std::cout << "Acik : % " << this->aciklik << std::endl;
        else
            std::cout << "Kapali " << std::endl;

        std::cout << "Otomatik acilma programi: ";

        if (otomatikAcil)
            std::cout << "Acik : " << this->acilmaZamani << std::endl;
        else
            std::cout << "Kapali" << std::endl;

        std::cout << "Otomatik Kapanma Programi: ";

        if (this->otomatikKapan)
            std::cout << "Acik: " << this->kapanmaZamani << std::endl;
        else
            std::cout << "Kapali. " << std::endl;
    }
};

class perdeKontrol
{
public:
    std::vector<perdeler> perdeler;

    void zamaniGelenleriKapat()
    {
        simdikiZaman zmn;
        zaman smd = zmn.simdiKi;
        for (auto &it : perdeler)
        {
            if (it.kapanmaZamani >= smd)
            {
                std::cout << "Kapandi: " << it.isim << " " << it.kapanmaZamani << "\n";
                it.aciklik = 0;
            }
        }
    }

    void zamaniGelenleriAc()
    {
        simdikiZaman zmn;
        zaman smd = zmn.simdiKi;
        for (auto &it : perdeler)
        {
            if (it.acilmaZamani >= smd)
            {
                std::cout << "Acildi: " << it.isim << " " << it.acilmaZamani << "\n";
                it.aciklik = 100;
            }
        }
    }

    void tumIsiklarinOtomatikKapanmaZamanlariniAyarla(zaman z)
    {
        for (auto &it : perdeler)
        {
            it.kapanmaZamani = z;
        }
    }
    void tumIsiklarinOtomatikAcilmaZamanlariniAyarla(zaman z)
    {
        for (auto &it : perdeler)
        {
            it.acilmaZamani = z;
        }
    }

    void print()
    {
        if (perdeler.size() == 0)
        {
            std::cout << "Perde Yok." << std::endl;
            return;
        }
        for (auto &it : perdeler)
        {
            it.print();
        }
    }

    void ac(int acOran, std::string ismi)
    {
        for (auto &it : perdeler)
        {
            if (it.isim == ismi)
            {
                it.aciklik = acOran;
            }
        }
    }
    void guncelle()
    {
        zamaniGelenleriAc();
        zamaniGelenleriKapat();
    }
};

class otomasyon
{
public:
    IsikKontrol isikKontrol;
    sicaklikKontrol sicaklikSistemi;
    guvenlikSistemi guvenlikKontrol;
    perdeKontrol perdeSistemi;

    void guncelle()
    {
        isikKontrol.guncelle();
        sicaklikSistemi.guncelle();
        guvenlikKontrol.guncelle();
        perdeSistemi.guncelle();
    }
};

otomasyon globalOtomasyon;

void sistemDurumunuGoruntule();
void isikMenusu();
void sicaklikMenusu();
void guvenlikMenusu();
void perdeMenusu();

int main()
{
    srand(time(NULL));
    while (true)
    {
        globalOtomasyon.guncelle();
        std::cout << std::endl;
        std::cout << "1. Sistem Durumunu Goruntule" << std::endl;
        std::cout << "2. Isik Menusu" << std::endl;
        std::cout << "3. Sicaklik Menusu" << std::endl;
        std::cout << "4. Guvenlik Menusu" << std::endl;
        std::cout << "5. Perde Menusu" << std::endl;
        std::cout << "-1. Cikis" << std::endl;
        int secim;
        std::cout << "Seciminiz: ";
        std::cin >> secim;

        switch (secim)
        {
        case 1:
            sistemDurumunuGoruntule();
            break;
        case 2:
            isikMenusu();
            break;
        case 3:
            sicaklikMenusu();
            break;
        case 4:
            guvenlikMenusu();
            break;
        case 5:
            perdeMenusu();
            break;
        case -1:
            std::cout << "Programdan Cikiliyor..." << std::endl;
            exit(1);
            break;
        default:
            break;
        }
    }
}

void sistemDurumunuGoruntule()
{
    std::cout << "Saat ve dakika: " << simdikiZaman().simdiKi.toString() << std::endl;
    std::cout << "Isiklar: " << std::endl;
    globalOtomasyon.isikKontrol.print();
    std::cout << "Sicakliklar: " << std::endl;
    globalOtomasyon.sicaklikSistemi.print();
    std::cout << "Guvenlik Kameralari: " << std::endl;
    globalOtomasyon.guvenlikKontrol.goruntule();
    std::cout << "Perdeler: " << std::endl;
    globalOtomasyon.perdeSistemi.print();
}

void isikMenusu()
{
    std::cout << "1. Isiklari Goruntule" << std::endl;
    std::cout << "2. Isiklari Ac" << std::endl;
    std::cout << "3. Isiklari Kapat" << std::endl;
    std::cout << "4. Isiklarin Otomatik Kapatma Zamanlarini Ayarla" << std::endl;
    std::cout << "5. Isiklarin Otomatik Acilma Zamanlarini Ayarla" << std::endl;
    std::cout << "6. Isik Ekle" << std::endl;
    std::cout << "-1. Cikis" << std::endl;
    int secim;
    std::cin >> secim;

    if (secim == 1)
    {
        globalOtomasyon.isikKontrol.print();
    }
    else if (secim == 2)
    {
        std::cout << "Isiklar Aciliyor..." << std::endl;
        for (auto &it : globalOtomasyon.isikKontrol.isiklar)
        {
            it.acikMi = true;
        }
    }
    else if (secim == 3)
    {
        std::cout << "Isiklar Kapatiliyor..." << std::endl;
        for (auto &it : globalOtomasyon.isikKontrol.isiklar)
        {
            it.acikMi = false;
        }
    }
    else if (secim == 4)
    {
        std::cout << "Kapanma Zamanini Giriniz: ";
        int saat, dakika;
        std::cin >> saat >> dakika;
        zaman z(saat, dakika);
        globalOtomasyon.isikKontrol.tumIsiklarinOtomatikKapanmaZamanlariniAyarla(z);
    }
    else if (secim == 5)
    {
        std::cout << "Acilma Zamanini Giriniz: ";
        int saat, dakika;
        std::cin >> saat >> dakika;
        zaman z(saat, dakika);
        globalOtomasyon.isikKontrol.tumIsiklarinOtomatikAcilmaZamanlariniAyarla(z);
    }
    else if (secim == 6)
    {
        Isik yeniIsik;
        std::cout << "Isim: ";
        std::cin >> yeniIsik.isim;
        std::cout << "Parlaklik: ";
        std::cin >> yeniIsik.isikParlaklik;
        std::cout << "Otomatik Kapanacak mi? (1/0): ";
        std::cin >> yeniIsik.otomatikKapan;
        std::cout << "Otomatik Acilacak mi? (1/0): ";
        std::cin >> yeniIsik.otomatikAcil;
        std::cout << "Acik mi? (1/0): ";
        std::cin >> yeniIsik.acikMi;
        if (yeniIsik.otomatikKapan)
        {
            std::cout << "Kapanma Zamanini Giriniz: ";
            int saat, dakika;
            std::cin >> saat >> dakika;
            zaman z(saat, dakika);
            yeniIsik.kapanmaZamani = z;
        }
        if (yeniIsik.otomatikAcil)
        {
            std::cout << "Acilma Zamanini Giriniz: ";
            int saat, dakika;
            std::cin >> saat >> dakika;
            zaman z(saat, dakika);
            yeniIsik.acilmaZamani = z;
        }
        globalOtomasyon.isikKontrol.isiklar.push_back(yeniIsik);
    }
    else if (secim == -1)
        return;
}

void sicaklikMenusu()
{
    std::cout << "1. Sicakliklari Goruntule" << std::endl;
    std::cout << "2. Sicaklik cihazlarini Ac" << std::endl;
    std::cout << "3. Sicaklik cihazlarini Kapat" << std::endl;
    std::cout << "4. Sicaklik cihazlarinin Otomatik Kapatma Zamanlarini Ayarla" << std::endl;
    std::cout << "5. Sicaklik cihazlarinin Otomatik Acilma Zamanlarini Ayarla" << std::endl;
    std::cout << "6. Sicaklik Cihazi Ekle" << std::endl;
    std::cout << "-1. Cikis" << std::endl;
    int secim;
    std::cin >> secim;

    if (secim == 1)
    {
        globalOtomasyon.sicaklikSistemi.print();
    }
    else if (secim == 2)
    {
        std::cout << "Sicaklik cihazlari Aciliyor..." << std::endl;
        for (auto &it : globalOtomasyon.sicaklikSistemi.sicaklikCihazlari)
        {
            it.acikMi = true;
        }
    }
    else if (secim == 3)
    {
        std::cout << "Sicaklik cihazlari Kapatiliyor..." << std::endl;
        for (auto &it : globalOtomasyon.sicaklikSistemi.sicaklikCihazlari)
        {
            it.acikMi = false;
        }
    }
    else if (secim == 4)
    {
        std::cout << "Kapanma Zamanini Giriniz: ";
        int saat, dakika;
        std::cin >> saat >> dakika;
        zaman z(saat, dakika);
        globalOtomasyon.sicaklikSistemi.tumIsiklarinOtomatikKapanmaZamanlariniAyarla(z);
    }
    else if (secim == 5)
    {
        std::cout << "Acilma Zamanini Giriniz: ";
        int saat, dakika;
        std::cin >> saat >> dakika;
        zaman z(saat, dakika);
        globalOtomasyon.sicaklikSistemi.tumIsiklarinOtomatikAcilmaZamanlariniAyarla(z);
    }
    else if (secim == 6)
    {
        sicaklikCihazi yeniCihaz;
        std::cout << "Isim: ";
        std::cin >> yeniCihaz.isim;
        std::cout << "Sicaklik: ";
        std::cin >> yeniCihaz.sicaklik;
        std::cout << "Otomatik Kapanacak mi? (1/0): ";
        std::cin >> yeniCihaz.otomatikKapan;
        std::cout << "Otomatik Acilacak mi? (1/0): ";
        std::cin >> yeniCihaz.otomatikAcil;
        std::cout << "Acik mi? (1/0): ";
        std::cin >> yeniCihaz.acikMi;
        if (yeniCihaz.otomatikKapan)
        {
            std::cout << "Kapanma Zamanini Giriniz: ";
            int saat, dakika;
            std::cin >> saat >> dakika;
            zaman z(saat, dakika);
            yeniCihaz.kapanmaZamani = z;
        }
        if (yeniCihaz.otomatikAcil)
        {
            std::cout << "Acilma Zamanini Giriniz: ";
            int saat, dakika;
            std::cin >> saat >> dakika;
            zaman z(saat, dakika);
            yeniCihaz.acilmaZamani = z;
        }
        globalOtomasyon.sicaklikSistemi.sicaklikCihazlari.push_back(yeniCihaz);
    }
    else if (secim == -1)
        return;
}

void guvenlikMenusu()
{
    std::cout << "1. Guvenlik Kameralarini Goruntule" << std::endl;
    std::cout << "2. Guvenlik Kameralarini Ac" << std::endl;
    std::cout << "3. Guvenlik Kameralarini Kapat" << std::endl;
    std::cout << "4. Hirsiz Alarmi Ac" << std::endl;
    std::cout << "5. Hirsiz Alarmi Kapat" << std::endl;
    std::cout << "6. Kamera Ekle" << std::endl;
    std::cout << "7. Alarm Ekle" << std::endl;
    std::cout << "-1. Cikis" << std::endl;
    int secim;
    std::cin >> secim;

    if (secim == 1)
    {
        globalOtomasyon.guvenlikKontrol.goruntule();
    }
    else if (secim == 2)
    {
        std::cout << "Guvenlik Kameralari Aciliyor..." << std::endl;
        for (auto &it : globalOtomasyon.guvenlikKontrol.kameralar)
        {
            it.acikMi = true;
        }
    }
    else if (secim == 3)
    {
        std::cout << "Guvenlik Kameralari Kapatiliyor..." << std::endl;
        for (auto &it : globalOtomasyon.guvenlikKontrol.kameralar)
        {
            it.acikMi = false;
        }
    }
    else if (secim == 4)
    {
        std::cout << "Hirsiz Alarmi Aciliyor..." << std::endl;
        for (auto &it : globalOtomasyon.guvenlikKontrol.alarmlar)
        {
            it.acikMi = true;
        }
    }
    else if (secim == 5)
    {
        std::cout << "Hirsiz Alarmi Kapatiliyor..." << std::endl;
        for (auto &it : globalOtomasyon.guvenlikKontrol.alarmlar)
        {
            it.acikMi = false;
        }
    }
    else if (secim == 6)
    {
        guvenlikKamerasi yeniKamera;
        std::cout << "Isim: ";
        std::cin >> yeniKamera.isim;
        std::cout << "Konum: (x,y,z)";
        std::cin >> yeniKamera.kameraKonumu.x >> yeniKamera.kameraKonumu.y >> yeniKamera.kameraKonumu.z;
        std::cout << "Acik mi? (1/0): ";
        std::cin >> yeniKamera.acikMi;
        globalOtomasyon.guvenlikKontrol.kameralar.push_back(yeniKamera);
    }
    else if (secim == 7)
    {
        hirsizAlarmi yeniAlarm;
        std::cout << "Isim: ";
        std::cin >> yeniAlarm.isim;
        std::cout << "Acik mi? (1/0): ";
        std::cin >> yeniAlarm.acikMi;
        globalOtomasyon.guvenlikKontrol.alarmlar.push_back(yeniAlarm);
    }
}

void perdeMenusu()
{
    std::cout << "1. Perdeleri Goruntule" << std::endl;
    std::cout << "2. Perdeleri Ac" << std::endl;
    std::cout << "3. Perdeleri Kapat" << std::endl;
    std::cout << "4. Perdelerin Otomatik Kapanma Zamanlarini Ayarla" << std::endl;
    std::cout << "5. Perdelerin Otomatik Acilma Zamanlarini Ayarla" << std::endl;
    std::cout << "6. Perde Ekle" << std::endl;
    std::cout << "-1. Cikis" << std::endl;
    int secim;
    std::cin >> secim;

    if (secim == 1)
    {
        globalOtomasyon.perdeSistemi.print();
    }
    else if (secim == 2)
    {
        std::cout << "Perdeler Aciliyor..." << std::endl;
        for (auto &it : globalOtomasyon.perdeSistemi.perdeler)
        {
            it.aciklik = 100;
        }
    }
    else if (secim == 3)
    {
        std::cout << "Perdeler Kapatiliyor..." << std::endl;
        for (auto &it : globalOtomasyon.perdeSistemi.perdeler)
        {
            it.aciklik = 0;
        }
    }
    else if (secim == 4)
    {
        std::cout << "Kapanma Zamanini Giriniz: ";
        int saat, dakika;
        std::cin >> saat >> dakika;
        zaman z(saat, dakika);
        globalOtomasyon.perdeSistemi.tumIsiklarinOtomatikKapanmaZamanlariniAyarla(z);
    }
    else if (secim == 5)
    {
        std::cout << "Acilma Zamanini Giriniz: ";
        int saat, dakika;
        std::cin >> saat >> dakika;
        zaman z(saat, dakika);
        globalOtomasyon.perdeSistemi.tumIsiklarinOtomatikAcilmaZamanlariniAyarla(z);
    }
    else if (secim == 6)
    {
        perdeler yeniPerde;
        std::cout << "Isim: ";
        std::cin >> yeniPerde.isim;
        std::cout << "Aciklik: ";
        std::cin >> yeniPerde.aciklik;
        std::cout << "Otomatik Kapanacak mi? (1/0): ";
        std::cin >> yeniPerde.otomatikKapan;
        std::cout << "Otomatik Acilacak mi? (1/0): ";
        std::cin >> yeniPerde.otomatikAcil;
        if (yeniPerde.otomatikKapan)
        {
            std::cout << "Kapanma Zamanini Giriniz: ";
            int saat, dakika;
            std::cin >> saat >> dakika;
            zaman z(saat, dakika);
            yeniPerde.kapanmaZamani = z;
        }
        if (yeniPerde.otomatikAcil)
        {
            std::cout << "Acilma Zamanini Giriniz: ";
            int saat, dakika;
            std::cin >> saat >> dakika;
            zaman z(saat, dakika);
            yeniPerde.acilmaZamani = z;
        }
        globalOtomasyon.perdeSistemi.perdeler.push_back(yeniPerde);
    }
}