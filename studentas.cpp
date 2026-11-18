#include "studentas.h"
#include <iostream>
#include <algorithm>
#include <limits>

using namespace std;

double vidurkis(const vector<int> &v)
{
    if (v.empty())
        return 0.0;
    double suma = 0;
    for (int p : v)
        suma += p;
    return suma / v.size();
}

double mediana(vector<int> v)
{
    if (v.empty())
        return 0.0;
    sort(v.begin(), v.end());
    size_t n = v.size();
    if (n % 2 == 0)
        return (v[n / 2 - 1] + v[n / 2]) / 2.0;
    return v[n / 2];
}

Studentas::Studentas() : egzaminas_(0), galVid_(0), galMed_(0) {}
Studentas::Studentas(const string &vardas, const string &pavarde,
                     const vector<int> &nd, int egzaminas)
    : vardas_(vardas), pavarde_(pavarde), nd_(nd), egzaminas_(egzaminas)
{
    skaiciuoti();
}

Studentas::Studentas(const Studentas &kitas)
    : vardas_(kitas.vardas_), pavarde_(kitas.pavarde_), nd_(kitas.nd_),
      egzaminas_(kitas.egzaminas_), galVid_(kitas.galVid_), galMed_(kitas.galMed_) {}

void Studentas::skaiciuoti()
{
    galVid_ = 0.4 * vidurkis(nd_) + 0.6 * egzaminas_;
    galMed_ = 0.4 * mediana(nd_) + 0.6 * egzaminas_;
}

Studentas ivestiStudenta(bool generuoti, mt19937 &gen)
{
    string vardas, pavarde;
    vector<int> nd;
    int egzaminas;
    cout << "Vardas: ";
    cin >> vardas;
    cout << "Pavarde: ";
    cin >> pavarde;
    if (generuoti)
    {
        uniform_int_distribution<int> balas(1, 10);
        int n = balas(gen);
        for (int i = 0; i < n; i++)
            nd.push_back(balas(gen));
        egzaminas = balas(gen);
    }
    else
    {
        cout << "ND rezultatai (po viena eiluteje, baigti - tuscia eilute):\n";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        string eil;
        while (getline(cin, eil) && !eil.empty())
        {
            try
            {
                nd.push_back(stoi(eil));
            }
            catch (...)
            {
                cout << "Netinkamas skaicius, praleidziama\n";
            }
        }
        cout << "Egzamino rezultatas: ";
        while (!(cin >> egzaminas))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Iveskite skaiciu: ";
        }
    }
    return Studentas(vardas, pavarde, nd, egzaminas);
}

bool pagalPavarde(const Studentas &a, const Studentas &b) { return a.pavarde() < b.pavarde(); }
bool pagalVarda(const Studentas &a, const Studentas &b) { return a.vardas() < b.vardas(); }
bool pagalBala(const Studentas &a, const Studentas &b) { return a.galVid() > b.galVid(); }

void rusiuoti(vector<Studentas> &studentai, int kriterijus)
{
    if (kriterijus == 2)
        sort(studentai.begin(), studentai.end(), pagalVarda);
    else if (kriterijus == 3)
        sort(studentai.begin(), studentai.end(), pagalBala);
    else
        sort(studentai.begin(), studentai.end(), pagalPavarde);
}

void rusiuoti(list<Studentas> &studentai, int kriterijus)
{
    if (kriterijus == 2)
        studentai.sort(pagalVarda);
    else if (kriterijus == 3)
        studentai.sort(pagalBala);
    else
        studentai.sort(pagalPavarde);
}

bool kietiakas(const Studentas &s)
{
    return s.galVid() >= 5.0;
}