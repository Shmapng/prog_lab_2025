#include <iostream>
#include <vector>
#include <array>
#include <ctime>

void Zapolnit(std::array<int, 10>& mas)
{
    const size_t RAZMER = 10;
    std::srand(std::time(0));
    for (size_t i = 0; i < RAZMER; ++i)
    {
        mas[i] = std::rand() % 21 - 10;
    }
    std::cout << "[";
    for (const int& el : mas)
    {
        std::cout << el << " ";
    }
    std::cout << "\b]" << std::endl;
}


void Vivesti(std::array<int, 10> mas)
{
    std::cout << "[";
    for (const int& el : mas)
    {
        std::cout << el << " ";
    }
    std::cout << "\b]" << std::endl;
}

void SortKop(std::array<int, 10> mas)
{
    for (size_t i = 0; i < mas.size() - 1; ++i)
    {
        for (size_t j = 0; j < mas.size() - 1 - i; ++j)
        {
            if (mas[j] > mas[j + 1])
            {
                std::swap(mas[j], mas[j + 1]);
            }
        }
    }
    std::cout << "Sortirovka kopii: ";
    Vivesti(mas);
}

void SortSsil(std::array<int, 10>& mas)
{
    for (size_t i = 0; i < mas.size() - 1; ++i)
    {
        for (size_t j = 0; j < mas.size() - 1 - i; ++j)
        {
            if (mas[j] > mas[j + 1])
            {
                std::swap(mas[j], mas[j + 1]);
            }
        }
    }
    std::cout << "Sortirovka po vozrastaniu: ";
    Vivesti(mas);

    for (size_t i = 0; i < mas.size() - 1; ++i)
    {
        for (size_t j = 0; j < mas.size() - 1 - i; ++j)
        {
            if (mas[j] < mas[j + 1])
            {
                std::swap(mas[j], mas[j + 1]);
            }
        }
    }
    std::cout << "Sortirovka po ubivaniu: ";
    Vivesti(mas);
}

void SortUkaz(std::array<int, 10>* mas)
{
    for (int i = 0; i < (*mas).size() - 1; ++i)
    {
        for (int j = 0; j < (*mas).size() - 1 - i; ++j)
        {
            if ((*mas)[j] > (*mas)[j + 1])
            {
                std::swap((*mas)[j], (*mas)[j + 1]);
            }
        }
    }
    std::cout << "Sortirovka po vozrastaniu: ";
    Vivesti((*mas));

    for (int i = 0; i < (*mas).size() - 1; ++i)
    {
        for (int j = 0; j < (*mas).size() - 1 - i; ++j)
        {
            if ((*mas)[j] < (*mas)[j + 1])
            {
                std::swap((*mas)[j], (*mas)[j + 1]);
            }
        }
    }
    std::cout << "Sortirovka po ubivaniu: ";
    Vivesti((*mas));
}

void VivestiDin(std::vector<int>& mas)
{
    std::cout << "[";
    for (size_t i = 0; i < mas.size(); ++i)
    {
        std::cout << mas[i];
        if (i != mas.size() - 1)
        {
            std::cout << " ";
        }
    }
    std::cout << "]";
}

void DobNach(std::vector<int>& mas, int num)
{
    mas.insert(mas.begin(), num);
}

void DobKon(std::vector<int>& mas, int num)
{
    mas.push_back(num);
}

void Ochistit(std::vector<int>& mas)
{
    mas.clear();
}

void NaitiEl(std::vector<int>& mas, int num)
{
    bool naideno = false;
    std::cout << "Naidennye indeksy: [";
    for (int i = 0; i < mas.size(); ++i)
    {
        if (mas[i] == num)
        {
            if (naideno)
            {
                std::cout << ", ";
            }
            std::cout << i;
            naideno = true;
        }
    }
    std::cout << "]" << std::endl;
}

void Zadanie(std::vector<int> mas)
{
    std::cout << "Do: " << std::endl;
    VivestiDin(mas);
    std::cout << std::endl;

    if (mas.size() % 2 == 0)
    {
        if (!mas.empty())
        {
            std::vector<int> temp;
            for (size_t i = 1; i < mas.size(); ++i)
            {
                temp.push_back(mas[i]);
            }
            mas = temp;
        }
    }
    else
    {
        if (mas.size() > 4)
        {
            std::vector<int> temp;
            for (size_t i = 0; i < mas.size() - 4; ++i)
            {
                temp.push_back(mas[i]);
            }
            mas = temp;
        }
    }

    std::cout << "Posle: " << std::endl;
    VivestiDin(mas);
}

int main()
{
    std::array<int, 10> masFix;    
    std::vector<int> masDin;       
    int vybor;                     
    int num;                       

    do
    {
        std::cout << "\n---Menyu--- " << std::endl;
        std::cout << "0. Vyjod." << std::endl;
        std::cout << "1. Prosmotr massiva." << std::endl;
        std::cout << "2. Dobavit' element v nachalo. " << std::endl;
        std::cout << "3. Dobavit' element v konets. " << std::endl;
        std::cout << "4. Ochistka Massiva. " << std::endl;
        std::cout << "5. Poisk indeksa po znacheniu. " << std::endl;
        std::cout << "6. Zadanie varianta. " << std::endl;
        std::cout << "7. Prosmotr massiva fiksirovannoj dliny: " << std::endl;
        std::cout << "8. Demonstraciya raznicy peredachi argumentov. " << std::endl;
        std::cout << "Vybor punkta: ";
        std::cin >> vybor;

        switch (vybor)
        {
        case 0:
            std::cout << "Vyjod. " << std::endl;
            break;

        case 1:
            std::cout << "Prosmotr Massiva: " << std::endl;
            VivestiDin(masDin);
            std::cout << std::endl;
            break;

        case 2:
            std::cout << "Dobavit' element v nachalo: " << std::endl;
            std::cin >> num;
            DobNach(masDin, num);
            break;

        case 3:
            std::cout << "Dobavit' element v konets: " << std::endl;
            std::cin >> num;
            DobKon(masDin, num);
            break;

        case 4:
            std::cout << "Ochistka vsego massiva." << std::endl;
            Ochistit(masDin);
            break;

        case 5:
            std::cout << "Poisk elementa: " << std::endl;
            std::cin >> num;
            NaitiEl(masDin, num);
            break;

        case 6:
            std::cout << "Zadanie po variantu: " << std::endl;
            Zadanie(masDin);
            break;

        case 7:
            std::cout << "Massiv Array: ";
            Zapolnit(masFix);
            break;

        case 8:
            std::cout << "Sortirovka: " << std::endl;
            std::cout << "Do sortirovki: ";
            Zapolnit(masFix);
            SortKop(masFix);
            std::cout << "Posle sortirovki: ";
            Vivesti(masFix);
            std::cout << std::endl;

            std::cout << "Do sortirovki: ";
            Zapolnit(masFix);
            SortSsil(masFix);
            std::cout << "Posle sortirovki: ";
            Vivesti(masFix);
            std::cout << std::endl;

            std::cout << "Do sortirovki: ";
            Zapolnit(masFix);
            SortUkaz(&masFix);
            std::cout << "Posle sortirovki: ";
            Vivesti(masFix);
            std::cout << std::endl;
            break;

        default:
            std::cout << "Nevernyj vvod. " << std::endl;
            break;
        }
    } while (vybor != 0);

    return 0;
}
