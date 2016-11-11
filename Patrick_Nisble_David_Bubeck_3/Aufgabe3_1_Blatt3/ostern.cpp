#include <iostream>
#include <string>
#include <cassert>


std::string easter(int year) {
    int a = year % 19;
    int b = year % 4;
    int c = year % 7;
    int k = year / 100;
    int p = ((8 * k) + 13) / 25;
    int q = k / 4;
    int m = (15 + k - p - q) % 30;
    int d = ((19 * a) + m) % 30;
    int n = (4 + k - q) % 7;
    int e = ((2 * b) + (4 * c) + (6 * d) + n) % 7;
    int x = 22 + d + e;

    int z = (x == 57) ? 50 : ((x == 56) && (d == 28) && (a > 10)) ? 49 : x;

    //caste auf den wert z einen string
    std::string date = (z < 32) ? std::to_string(z) + ". März" : std::to_string((z - 31)) + ". April";

    //return string
    return date;
}


int main() {

    //assert abfragen zur ueberpruefung der korrektheit des berechnung
    assert(easter(2018) == "1. April"); //2018
    assert(easter(2019) == "21. April"); //2019
    assert(easter(2020) == "12. April"); //2020
    assert(easter(2021) == "4. April"); //2021
    assert(easter(2022) == "17. April"); //2022
    assert(easter(2023) == "9. April"); //2023
    assert(easter(2024) == "31. März"); //2024
    assert(easter(2025) == "20. April"); //2025
    assert(easter(2026) == "5. April"); //2026
    assert(easter(2027) == "28. März"); //2027

    //jahreszahl eingeben
    int year_enter;
    std::cout << "Bitte ein Jahr eingeben: " << std::endl;
    std::cin >> year_enter;
    std::string easterDate = easter(year_enter);

    //ausgabe des datums
    std::cout << "Ostern ist am " + easterDate << std::endl;

    return 0;
}