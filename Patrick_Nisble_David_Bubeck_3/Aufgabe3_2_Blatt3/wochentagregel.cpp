//der online calculator welcher auf dem uebungsblatt steht ist nicht korrekt der ignoriert schaltjahre

#include <iostream>
#include <string>
#include <cassert>

//funktion fuer year > 2001
int weekday2001(int day, int month, int year) {
    int z = year - 2001;
    int j1 = ((365 * z) + (z/4) - (z / 100) + (z/400)) % 7;

    bool leapyear = ((((year % 4) == 0) && ((year % 100) != 0)) || ((year % 400) == 0)) ? true : false;

    int p = (month == 1) ? day : (month == 2) ? day + 31 : (month > 2 && leapyear == false) ? day + 59 + (((153 * month) - 457) / 5) : (month > 2 && leapyear == true) ? day + 60 + (((153 * month) - 457) / 5) : -1; //-1 ist für Fehlerabfrage

    int weekday = (j1 + p - 1) % 7;

    return weekday;
}

//funktion zur berechnung des betrages
int functionAbs(int a) {
    int abs = (a >= 0) ? a : -a;
    return abs;
}

//floor division funktion
int floorDiv(int a, int b) {
    int div = (a < 0) ? - (functionAbs(a) / functionAbs(b)) - 1 : a/b; //Hierbei ist c = |b|
    return div;
}

//floor mod funktion
//floorMod unterscheidet sich von der normalen mod funktion darin das für negative zahlen der mod faktor zum
//ergebnis dazu addiert werden muss, da fuer negative zahlen wir einen im betrag groesseren wert bekommen
//was wir damit beruecksichtigen
int floorMod(int a, int b) {
    int mod = ((a < 0 ) ? b : 0) + (a % b); //dazuaddieren um einen faktor b für negative zahlen
    return mod;
}

//funktion fuer bestimmung mit floorDiv() und floorMod()
int weekday(int day, int month, int year) {
    int z = year - 2001;
    int j1 = floorMod(((365 * z) + floorDiv(z, 4) - floorDiv(z, 100) + floorDiv(z, 400)), 7);

    assert(z == (floorDiv(z, 4) * 4) + floorMod(z, 4));

    bool leapyear = ((((year % 4) == 0) && ((year % 100) != 0)) || ((year % 400) == 0)) ? true : false;

    int p = (month == 1) ? day : (month == 2) ? day + 31 : (month > 2 && leapyear == false) ? day + 59 + floorDiv(((153 * month) - 457), 5) : (month > 2 && leapyear == true) ? day + 60 + floorDiv(((153 * month) - 457), 5) : -1; //-1 ist für Fehlerabfrage

    int weekday = floorMod((j1 + p - 1), 7);

    return weekday;
}

//funktion mit year >= 1583 ohne floorDiv() und floorMod()
//subtrahieren wir nur eine 1 so erhalten wir fuer z immer positive werte was wir fuer eine subtraktion mit 2001
//nicht bekommen, somit benoetigen wir keine floorDiv(), floorMod() funktion welche sich positive und negative
//zahlen eine "unterschiedliche" rechnung durchfuert d.h. fuer negative eine floor division und fuer positive
//die truncating division. hierbei wird alles ueber die truncating division bestimmt da nur positive zahlen
int weekday1(int day, int month, int year) {
    int z = year - 1;
    int j1 = ((365 * z) + (z/4) - (z / 100) + (z/400)) % 7;

    bool leapyear = ((((year % 4) == 0) && ((year % 100) != 0)) || ((year % 400) == 0)) ? true : false;

    int p = (month == 1) ? day : (month == 2) ? day + 31 : (month > 2 && leapyear == false) ? day + 59 + (((153 * month) - 457) / 5) : (month > 2 && leapyear == true) ? day + 60 + (((153 * month) - 457) / 5) : -1; //-1 ist für Fehlerabfrage

    int weekday = (j1 + p - 1) % 7;

    return weekday;
}




int main() {
    //ueberpruefung der korrektheit des algorithmus
    assert(weekday(5, 1, 1583) == 2); //Mittwoch
    assert(weekday1(5, 1, 1583) == 2);

    assert(weekday(28, 2, 1904) == 6); //Sonntag
    assert(weekday1(28, 2, 1904) == 6);
    assert(weekday(29, 2, 1904) == 0); //Montag
    assert(weekday1(29, 2, 1904) == 0);
    assert(weekday(1, 3, 1904) == 1); //Dienstag
    assert(weekday1(1, 3, 1904) == 1);

    assert(weekday(28, 2, 1960) == 6); //Sonntag
    assert(weekday1(28, 2, 1960) == 6);
    assert(weekday(29, 2, 1960) == 0); //Montag
    assert(weekday1(29, 2, 1960) == 0);
    assert(weekday(1, 3, 1960) == 1); //Dienstag
    assert(weekday1(1, 3, 1960) == 1);

    assert(weekday(28, 2, 2020) == 4); //Freitag
    assert(weekday1(28, 2, 2020) == 4);
    assert(weekday(29, 2, 2020) == 5); //Samstag
    assert(weekday1(29, 2, 2020) == 5);
    assert(weekday(1, 3, 2020) == 6); //Sonntag
    assert(weekday1(1, 3, 2020) == 6);

    assert(weekday(28, 2, 2088) == 5); //Samstag
    assert(weekday1(28, 2, 2088) == 5);
    assert(weekday(29, 2, 2088) == 6); //Sonntag
    assert(weekday1(29, 2, 2088) == 6);
    assert(weekday(1, 3, 2088) == 0); //Montag
    assert(weekday1(1, 3, 2088) == 0);

    assert(weekday(28, 2, 2160) == 3); //Donnerstag
    assert(weekday1(28, 2, 2160) == 3);
    assert(weekday(29, 2, 2160) == 4); //Freitag
    assert(weekday1(29, 2, 2160) == 4);
    assert(weekday(1, 3, 2160) == 5); //Samstag
    assert(weekday1(1, 3, 2160) == 5);

    int day;
    int month;
    int year;
    //eingabe
    std::cout << "Bitte geben sie einen Tag ein (in Zahlen): " << std::endl;
    std::cin >> day;
    std::cout << "Bitte geben sie einen Monat ein (in Zahlen): " << std::endl;
    std::cin >> month;
    std::cout << "Bitte geben sie eine Jahr ein (in Zahlen): " << std::endl;
    std::cin >> year;

    //aufrufen der einzelnen funktionen
    int weekdayZ2001 = weekday2001(day, month, year);
    int weekdayFloor = weekday(day, month, year);
    int weekdayZ1 = weekday1(day, month, year);

    //ausgabe für weekdayZ2001()
    std::string weekday = (weekdayZ2001 == 0) ? "Montag" : (weekdayZ2001 == 1) ? "Dienstag" : (weekdayZ2001 == 2) ? "Mittwoch" : (weekdayZ2001 == 3) ? "Donnerstag" : (weekdayZ2001 == 4) ? "Freitag" : (weekdayZ2001 == 5) ? "Samstag" : (weekdayZ2001 == 6) ? "Sonntag" : "Fehler";
    std::cout << "truncating division ... Der Wochentag ist: " + weekday << std::endl;
    //ausgabe für weekdayFloor()
    weekday = (weekdayFloor == 0) ? "Montag" : (weekdayFloor == 1) ? "Dienstag" : (weekdayFloor == 2) ? "Mittwoch" : (weekdayFloor == 3) ? "Donnerstag" : (weekdayFloor == 4) ? "Freitag" : (weekdayFloor == 5) ? "Samstag" : (weekdayFloor == 6) ? "Sonntag" : "Fehler";
    std::cout << "floor division ... Der Wochentag ist: " + weekday << std::endl;
    //ausgabe für weekdayZ1()
    weekday = (weekdayZ1 == 0) ? "Montag" : (weekdayZ1 == 1) ? "Dienstag" : (weekdayZ1 == 2) ? "Mittwoch" : (weekdayZ1 == 3) ? "Donnerstag" : (weekdayZ1 == 4) ? "Freitag" : (weekdayZ1 == 5) ? "Samstag" : (weekdayZ1 == 6) ? "Sonntag" : "Fehler";
    std::cout << "truncating division z = year -1 ... Der Wochentag ist: " + weekday << std::endl;

    return 0;
}