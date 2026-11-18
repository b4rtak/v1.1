#pragma once
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <ctime>
#include "studentas.h"

using namespace std;

void generuotiFaila(const string &failas, int kiekis, mt19937 &gen);

template <typename Konteineris>
bool skaitytiFaila(const string &failas, Konteineris &studentai)
{
    ifstream in(failas);
    if (!in)
    {
        cout << "Nepavyko atidaryti failo " << failas << "\n";
        return false;
    }
    string eil;
    getline(in, eil);
    while (getline(in, eil))
    {
        istringstream ss(eil);
        string vardas, pavarde;
        vector<int> nd;
        ss >> vardas >> pavarde;
        int x;
        while (ss >> x)
            nd.push_back(x);
        if (nd.empty())
            continue;
        int egzaminas = nd.back();
        nd.pop_back();
        studentai.push_back(Studentas(vardas, pavarde, nd, egzaminas));
    }
    in.close();
    return true;
}

template <typename Konteineris>
void spausdinti(const Konteineris &studentai, ostream &out)
{
    out << left << setw(20) << "Pavarde" << setw(20) << "Vardas"
        << setw(20) << "Galutinis (Vid.)" << "Galutinis (Med.)\n";
    out << string(76, '-') << "\n"
        << fixed << setprecision(2);
    char eil[100];
    for (const auto &s : studentai)
    {
        snprintf(eil, sizeof(eil), "%-20s%-20s%-20.2f%.2f\n",
                 s.pavarde().c_str(), s.vardas().c_str(), s.galVid(), s.galMed());
        out << eil;
    }
}

template <typename Konteineris>
void testas(const string &failas, int kriterijus, int strategija)
{
    double tSk = 0, tDal = 0, tRus = 0, tRas = 0;
    for (int k = 0; k < 3; k++)
    {
        Konteineris studentai, vargsiukai, kietiakiai;

        clock_t t = clock();
        if (!skaitytiFaila(failas, studentai))
            return;
        tSk += double(clock() - t) / CLOCKS_PER_SEC;

        t = clock();
        if (strategija == 1)
        {
            strategija1(studentai, vargsiukai, kietiakiai);
        }
        else
        {
            if (strategija == 2)
                strategija2(studentai, vargsiukai);
            else
                strategija3(studentai, vargsiukai);
            kietiakiai.swap(studentai);
        }
        tDal += double(clock() - t) / CLOCKS_PER_SEC;

        t = clock();
        rusiuoti(vargsiukai, kriterijus);
        rusiuoti(kietiakiai, kriterijus);
        tRus += double(clock() - t) / CLOCKS_PER_SEC;

        t = clock();
        ofstream f1("vargsiukai.txt"), f2("kietiakiai.txt");
        spausdinti(vargsiukai, f1);
        spausdinti(kietiakiai, f2);
        f1.close();
        f2.close();
        tRas += double(clock() - t) / CLOCKS_PER_SEC;
    }
    cout << "\n"
         << failas << " (3 testu vidurkis):\n"
         << "Nuskaitymas:          " << tSk / 3 << " s\n"
         << "Dalijimas i 2 grupes: " << tDal / 3 << " s\n"
         << "Rusiavimas:           " << tRus / 3 << " s\n"
         << "Isvedimas i 2 failus: " << tRas / 3 << " s\n"
         << "Is viso:              " << (tSk + tDal + tRus + tRas) / 3 << " s\n";
}