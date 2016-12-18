#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <locale>
#include <codecvt>
#include <algorithm>



struct Character {
    wchar_t encrypted;
    wchar_t clear;
    int count = 0;

    Character(){
        encrypted = 0;
        clear = 0;
        count = 0;
    }

    Character(wchar_t enc, wchar_t cl, int c = 0){
        encrypted = enc;
        clear = cl;
        count = c;
    }

    bool operator==(wchar_t b){
        return (this->encrypted==b)!=0;
    }

    bool operator<(const Character b){
        return (this->count < b.count);
    }
    bool operator>(const Character b){
        return (b.count < this->count);
    }
};

int biggest_code(std::wstring const & text);

void write_file(std::string filename, std::wstring const & text) ;

std::wstring read_file(std::string filename) ;

std::vector<Character> characters;

int main() {
#if defined(_MSC_VER)
    // unter Windows/Visual Studio: locale fuer Deutsch definieren
    std::locale german("de-de");
#elif defined(__APPLE__)
    // unter MacOS: locale fuer Deutsch mit UTF-8 definieren
    std::locale german("de_DE.UTF-8");
#elif defined(__linux__)
    // unter Linux: locale fuer sprachunabhaengiges UTF-8 definieren
    std::locale german("de_DE.UTF-8");
#else
    // sonst: verwende die Spracheinstellungen des Betriebssystems
    std::locale german("");
#endif

    // Konverter zwischen UTF-8 (Zeichentyp in der Datei) und
    // wchar_t (Zeichentyp im Programm) erzeugen
    std::locale codec(german, new std::codecvt_utf8<wchar_t>);

    // Konverter global setzen (er wird ab jetzt von allen
    // Ein-/Ausgabeoperationen in diesem Programm verwendet)
    std::locale::global(codec);

    // Datei einlesen
    std::wstring text = read_file("verschluesselt_utf8.txt");

    // Ihre Loesung hier

    int max = biggest_code(text) + 1;

    for (int i = 0; i < max; i++){
        characters.push_back(Character(i,i));
    }

    //fill characters with encrypted characters and their count.
    for (auto elem: text){
        //TODO: np how to excep
        characters[elem].count++;
    }

    //
    std::sort(characters.begin(), characters.end(), [](Character a, Character b){return a > b;});

    std::wstring decr = read_file("buchstaben_haeufigkeit_utf8.txt");

    std::reverse(decr.begin(), decr.end());

    auto posd = decr.begin();
    for (auto pose = characters.begin(); posd < decr.end(); pose++){
        if (std::islower(pose->encrypted, german)) {
            pose->clear = *posd;
            std::cout << (char)pose->clear << "\n";
            posd++;
        }
    }

    std::sort(characters.begin(), characters.end(), [](Character a, Character b){return ((int)a.encrypted < (int)b.encrypted);});

    for (int i = 0; i < text.size(); i++){
        text[i] = characters[(int)text[i]].clear;
    }

    // Ergebnis in Datei schreiben
    write_file("entschluesselt.txt", text);
}

int biggest_code(std::wstring const & text){

    wchar_t re;
    for (int i = 0; i < text.size(); i++) {
        re = (text[i] > re)? text[i] : re;
    }

    return re;
}

std::wstring read_file(std::string filename) {
    // Datei zum Lesen von wchar_t oeffnen
    std::wifstream infile(filename);

    // Daten einlesen
    std::wstringstream textstream;
    textstream << infile.rdbuf();

    // Inhalt als std::wstring zurueckgeben
    return textstream.str();
}

void write_file(std::string filename, std::wstring const & text) {
    // Datei zum Schreiben von wchar_t oeffnen
    std::wofstream outfile(filename);

    // Text in Datei schreiben
    outfile << text;
}

