#pragma once
#include <string>
#include <vector>
#include <list>
#include <random>
#include <algorithm>

using namespace std;

class Studentas
{
private:
    string vardas_;
    string pavarde_;
    vector<int> nd_; // nd rez
    int egzaminas_;
    double galVid_;
    double galMed_;
    void skaiciuoti();

public:
    Studentas(); // numat konstr
    Studentas(const string &vardas, const string &pavarde,
              const vector<int> &nd, int egzaminas); // konstr su par
    Studentas(const Studentas &kitas);               // kopijavimo konstruktorius
    Studentas &operator=(const Studentas &kitas);    // kopijavimo priskyrimas
    ~Studentas();                                    // destruktorius

    const string &vardas() const { return vardas_; }
    const string &pavarde() const { return pavarde_; }
    const vector<int> &nd() const { return nd_; }
    int egzaminas() const { return egzaminas_; }
    double galVid() const { return galVid_; }
    double galMed() const { return galMed_; }
};

double vidurkis(const vector<int> &v);
double mediana(vector<int> v);
Studentas ivestiStudenta(bool generuoti, mt19937 &gen);
void rusiuoti(vector<Studentas> &studentai, int kriterijus);
void rusiuoti(list<Studentas> &studentai, int kriterijus);
bool kietiakas(const Studentas &s);

template <typename Konteineris>
void strategija1(const Konteineris &studentai, Konteineris &vargsiukai, Konteineris &kietiakiai)
{
    for (const auto &s : studentai)
    {
        if (s.galVid() < 5.0)
            vargsiukai.push_back(s);
        else
            kietiakiai.push_back(s);
    }
}

template <typename Konteineris>
void strategija2(Konteineris &studentai, Konteineris &vargsiukai)
{
    auto it = studentai.begin();
    while (it != studentai.end())
    {
        if (it->galVid() < 5.0)
        {
            vargsiukai.push_back(*it);
            it = studentai.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

template <typename Konteineris>
void strategija3(Konteineris &studentai, Konteineris &vargsiukai)
{
    auto riba = partition(studentai.begin(), studentai.end(), kietiakas);
    vargsiukai.assign(riba, studentai.end());
    studentai.erase(riba, studentai.end());
}