//
// Edited by Patrick Nisble, 2016.12.16
// read/write and locale Implementation provided by a course tutor
//
// "decrypt a encrypted text, in german language"
//

#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <locale>
#include <codecvt>
#include <algorithm>


// custom struct for decryption
struct Character {
    wchar_t encrypted;
    wchar_t clear;
    int count = 0;

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

//global vector of Character type
std::vector<Character> characters;

/// calculate maximum char-code for alpha-chars in text
/// \param text utf-8 encoded string
/// \return char code of highest alpha-chR
int biggest_code(std::wstring const & text);

/// write utf8-encoded string to a file
/// \param filename
/// \param text utf8-encoded string
void write_file(std::string filename, std::wstring const & text) ;

/// read utf8-encoded file to string
/// \param filename
/// \return utf8-encoded string
std::wstring read_file(std::string filename) ;


/// define and set locale to use, red file, decrypt it and write file
/// \return 0
int main() {
#if defined(_MSC_VER)
    // unter Windows/Visual Studio: locale fuer Deutsch definieren
    std::locale german("de-de");
#elif defined(__APPLE__)
    // unter MacOS: locale fuer Deutsch mit UTF-8 definieren
    std::locale german("de_DE.UTF-8");
#elif defined(__linux__)
    // unter Linux: locale fuer sprachunabhaengiges UTF-8 definieren
    // INFO: "de_DE.UTF-8" instead of "C.UTF-8" because of used linux distro not supporting the latter
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

    //filll List with max Characters using Constructor
    for (int i = 0; i < max; i++){
        characters.push_back(Character(i,i));
    }

    //fcount encrypted lowercase characters
    for (auto elem: text){
        if (std::isalpha(elem, german)) {
            characters[std::tolower(elem,german)].count++;
        }
    }

    //sort in decending oreder because of ease of use, using the overloaded operator of Character
    std::sort(characters.begin(), characters.end(), [](Character a, Character b){return a > b;});

    //read and reverse the characters used in german language
    std::wstring decr = read_file("buchstaben_haeufigkeit_utf8.txt");
    std::reverse(decr.begin(), decr.end());

    // match enrypted and clear characters if they are of alpha-type
    auto posd = decr.begin();
    for (auto pose = characters.begin(); posd < decr.end(); pose++){
        pose->clear = *posd;
        posd++;
    }

    // sort by enryped character order
    std::sort(characters.begin(), characters.end(), [](Character a, Character b){return ((int)a.encrypted < (int)b.encrypted);});

    // swap encrypted with clear characters
    for (int i = 0; i < text.size(); i++){
        if (std::isupper(text[i], german)) {
            text[i] = std::toupper(characters[std::tolower(wchar_t(text[i]), german)].clear,german);
        }else {
            text[i] = characters[(int) text[i]].clear;
        }
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

