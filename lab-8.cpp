#include <iostream>
#include <string>
#include <vector>
#include <limits>

struct Kniga
{
    std::string avtor;
    std::string nazvanie;
    int nomer_toma;
    int stranic;
    Kniga* sled_tom;

    Kniga(std::string a, std::string n, int nom, int str)
    {
        avtor = a;
        nazvanie = n;
        nomer_toma = nom;
        stranic = str;
        sled_tom = nullptr;
    }
};

struct Avtor
{
    std::string imya;
    Kniga* pervy_tom;

    Avtor(std::string im) : imya(im), pervy_tom(nullptr) {}
    Avtor() : imya(""), pervy_tom(nullptr) {}
};


void ProsmotrVseh(std::vector<Avtor>& Avtori)
{
    std::cout << "\nВсе собрания сочинений:\n";
    if (Avtori.empty()) {
        std::cout << "Пусто.\n";
        return;
    }

    for (int i = 0; i < Avtori.size(); i++)
    {
        std::cout << "\nАвтор " << i + 1 << ": " << Avtori[i].imya << "\nКниги: ";

        Kniga* tek = Avtori[i].pervy_tom;
        if (!tek) std::cout << "нет";

        while (tek)
        {
            std::cout << tek->nazvanie << " (т." << tek->nomer_toma << ") ";
            tek = tek->sled_tom;
        }
    }
    std::cout << "\n";
}


void SozdatAvtora(std::vector<Avtor>& Avtori)
{
    std::string imya;
    std::cout << "Имя автора: ";
    std::cin.ignore();
    std::getline(std::cin, imya);

    Avtori.push_back(Avtor(imya));
    std::cout << "Автор создан!\n";
}


void DobavitKnigu(std::vector<Avtor>& Avtori)
{
    if (Avtori.empty()) {
        std::cout << "Сначала создайте автора.\n";
        return;
    }

    std::cout << "Выберите автора (1-" << Avtori.size() << "):\n";
    for (int i = 0; i < Avtori.size(); i++)
        std::cout << i + 1 << ". " << Avtori[i].imya << "\n";

    int vybor;
    std::cin >> vybor;
    if (vybor < 1 || vybor > Avtori.size()) {
        std::cout << "Неверно!\n";
        return;
    }

    std::string nazvanie;
    int nomer, stranic;

    std::cout << "Название: ";
    std::cin.ignore();
    std::getline(std::cin, nazvanie);

    std::cout << "Номер тома: ";
    std::cin >> nomer;

    // Проверка номера
    Kniga* tek = Avtori[vybor - 1].pervy_tom;
    while (tek) {
        if (tek->nomer_toma == nomer) {
            std::cout << "Том " << nomer << " уже есть!\n";
            return;
        }
        tek = tek->sled_tom;
    }

    std::cout << "Страниц: ";
    std::cin >> stranic;


    Kniga* novaya = new Kniga(Avtori[vybor - 1].imya, nazvanie, nomer, stranic);


    if (!Avtori[vybor - 1].pervy_tom || nomer < Avtori[vybor - 1].pervy_tom->nomer_toma) {
        novaya->sled_tom = Avtori[vybor - 1].pervy_tom;
        Avtori[vybor - 1].pervy_tom = novaya;
    }
    else {
        Kniga* pred = Avtori[vybor - 1].pervy_tom;
        while (pred->sled_tom && pred->sled_tom->nomer_toma < nomer) {
            pred = pred->sled_tom;
        }
        novaya->sled_tom = pred->sled_tom;
        pred->sled_tom = novaya;
    }

    std::cout << "Книга добавлена!\n";
}


void PoiskKnigi(std::vector<Avtor>& Avtori)
{
    if (Avtori.empty()) {
        std::cout << "Нет авторов.\n";
        return;
    }

    std::cout << "Выберите автора (1-" << Avtori.size() << "):\n";
    for (int i = 0; i < Avtori.size(); i++)
        std::cout << i + 1 << ". " << Avtori[i].imya << "\n";

    int vybor;
    std::cin >> vybor;
    if (vybor < 1 || vybor > Avtori.size()) return;

    std::cout << "1. Самая толстая\n2. Самая тонкая\nВыбор: ";
    int tip;
    std::cin >> tip;

    if (!Avtori[vybor - 1].pervy_tom) {
        std::cout << "Нет книг.\n";
        return;
    }

    Kniga* result = Avtori[vybor - 1].pervy_tom;
    Kniga* tek = result->sled_tom;

    while (tek) {
        if (tip == 1 && tek->stranic > result->stranic) result = tek;
        if (tip == 2 && tek->stranic < result->stranic) result = tek;
        tek = tek->sled_tom;
    }

    std::cout << (tip == 1 ? "Толстая: " : "Тонкая: ")
        << result->nazvanie << " (т." << result->nomer_toma
        << ", " << result->stranic << " стр.)\n";
}


void Ochered(std::vector<Avtor>& Avtori)
{
    std::cout << "\nСОЗДАНИЕ ОЧЕРЕДИ ДЛЯ ЧТЕНИЯ\n";

    if (Avtori.empty()) {
        std::cout << "Нет авторов.\n";
        return;
    }

    std::vector<Kniga*> ochered;


    std::cout << "Все доступные книги:\n";
    std::cout << "====================\n";

    int book_counter = 0;
    std::vector<Kniga*> vse_knigi;

    for (int i = 0; i < Avtori.size(); i++) {
        Kniga* tek = Avtori[i].pervy_tom;
        while (tek) {
            std::cout << book_counter + 1 << ". " << tek->avtor
                << " - " << tek->nazvanie
                << " (т." << tek->nomer_toma
                << ", " << tek->stranic << " стр.)\n";
            vse_knigi.push_back(tek);
            book_counter++;
            tek = tek->sled_tom;
        }
    }

    if (book_counter == 0) {
        std::cout << "Нет книг.\n";
        return;
    }


    std::cout << "\nВыбирайте книги по номерам (0 = закончить):\n";

    while (true) {
        int nomer_knigi;
        std::cout << "Номер книги для добавления в очередь: ";
        std::cin >> nomer_knigi;

        if (nomer_knigi == 0) break;

        if (nomer_knigi < 1 || nomer_knigi > book_counter) {
            std::cout << "Неверный номер!\n";
            continue;
        }


        bool uzhe_dobavlena = false;
        for (Kniga* k : ochered) {
            if (k == vse_knigi[nomer_knigi - 1]) {
                uzhe_dobavlena = true;
                break;
            }
        }

        if (uzhe_dobavlena) {
            std::cout << "Эта книга уже в очереди!\n";
        }
        else {
            ochered.push_back(vse_knigi[nomer_knigi - 1]);
            std::cout << "Книга добавлена в очередь.\n";
        }
    }


    if (ochered.empty()) {
        std::cout << "Очередь пуста.\n";
        return;
    }

    std::cout << "\nВАША ОЧЕРЕДЬ ДЛЯ ЧТЕНИЯ\n";
    for (int i = 0; i < ochered.size(); i++) {
        std::cout << i + 1 << ". " << ochered[i]->avtor
            << " - " << ochered[i]->nazvanie
            << " (т." << ochered[i]->nomer_toma
            << ", " << ochered[i]->stranic << " стр.)\n";
    }
}


void Init(std::vector<Avtor>& Avtori)
{
    Avtori.push_back(Avtor("Лев Толстой"));
    Avtori.push_back(Avtor("Федор Достоевский"));
    Avtori.push_back(Avtor("Александр Пушкин"));
    Avtori.push_back(Avtor("Антон Чехов"));

    Kniga* k1 = new Kniga("Лев Толстой", "Война и мир", 1, 1225);
    Kniga* k2 = new Kniga("Лев Толстой", "Война и мир", 3, 1180);
    Kniga* k3 = new Kniga("Лев Толстой", "Война и мир", 5, 956);
    Avtori[0].pervy_tom = k1;
    k1->sled_tom = k2;
    k2->sled_tom = k3;

    Kniga* k4 = new Kniga("Федор Достоевский", "Братья Карамазовы", 1, 824);
    Kniga* k5 = new Kniga("Федор Достоевский", "Братья Карамазовы", 2, 768);
    Kniga* k6 = new Kniga("Федор Достоевский", "Братья Карамазовы", 4, 912);
    Avtori[1].pervy_tom = k4;
    k4->sled_tom = k5;
    k5->sled_tom = k6;

    Kniga* k7 = new Kniga("Александр Пушкин", "Евгений Онегин", 1, 320);
    Kniga* k8 = new Kniga("Александр Пушкин", "Евгений Онегин", 4, 285);
    Avtori[2].pervy_tom = k7;
    k7->sled_tom = k8;

    Kniga* k9 = new Kniga("Антон Чехов", "Рассказы", 1, 256);
    Kniga* k10 = new Kniga("Антон Чехов", "Рассказы", 2, 198);
    Kniga* k11 = new Kniga("Антон Чехов", "Рассказы", 3, 312);
    Kniga* k12 = new Kniga("Антон Чехов", "Рассказы", 6, 275);
    Avtori[3].pervy_tom = k9;
    k9->sled_tom = k10;
    k10->sled_tom = k11;
    k11->sled_tom = k12;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    std::vector<Avtor> Avtori;
    Init(Avtori);

    int vybor;
    do {
        std::cout << "\nБИБЛИОТЕКА\n"
            << "1. Показать всех авторов\n"
            << "2. Создать автора\n"
            << "3. Добавить книгу\n"
            << "4. Найти толстую/тонкую книгу\n"
            << "5. Создать очередь для чтения\n"
            << "0. Выход\n"
            << "Выбор: ";
        std::cin >> vybor;

        switch (vybor) {
        case 1: ProsmotrVseh(Avtori); break;
        case 2: SozdatAvtora(Avtori); break;
        case 3: DobavitKnigu(Avtori); break;
        case 4: PoiskKnigi(Avtori); break;
        case 5: Ochered(Avtori); break;
        case 0: std::cout << "Выход.\n"; break;
        default: std::cout << "Неверно!\n";
        }
    } while (vybor != 0);

    return 0;
}
