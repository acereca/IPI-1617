#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <vector>


/*
 * Function to open the file and convert the content into a string.
 * Code was given in the exercise sheet.
 */
std::string readFile(std::string file) {
    std::ifstream infile(file);
    std::string text;
    std::string line;

    while(infile) {
        std::getline(infile, line);
        text += line + "\n";
    }

    return text;
}

/*
 * Function to count letters in the text.
 * Therefore we iterate over the text and increment our value for a key char in our map.
 */
std::map<char, int> countLetters(std::string text) {
    std::map<char, int> count;

    for(int i = 0; i < text.length(); i++) {
        if(isalpha(text[i])) {          //we check if we have an alphabetic value and if so we increment the map value
            count[tolower(text[i])]++;  //tolower because we need to ignore uppercase and lowercase differences
        }
    }

    return count;
}

/*
 * Function to change key and value of the map.
 * So we can sort it indirectly after our incrementation.
 * Therefore we iterate over the map with the alphabetic keys and change value and key of the map
 * and save them into another one with transposed key and value.
 */
std::map<int, char> sorted(std::map<char, int> countedLetters) {
    std::map<int, char> sorted;

    for(std::map<char, int>::iterator i = countedLetters.begin(); i != countedLetters.end(); i++) {
        sorted[i -> second] = i -> first;
    }

    return sorted;
}

/*
 * Function to decrypt the alphabetic values.
 * Therefore we set a vector with the alphabetic values in ascending order of a common english text.
 * Now we iterate over the map with the sorted encrypted values as keys and save as values the
 * corresponding letter of the vector.
 * It will be saved in a new map with encrypted letters as keys and decrypted letters as values.
 */
std::map<char, char> decrypt(std::map<int, char> sortedLetters) {
    std::vector<char> letters = {'z', 'j', 'q', 'x', 'k', 'v', 'b', 'y', 'g', 'p', 'w', 'f', 'm', 'c', 'u', 'l', 'd', 'r', 'h', 's', 'n', 'i', 'o', 'a', 't', 'e'};
    int countVector = 0;
    std::map<char, char> decrypt;
    for(std::map<int, char>::iterator i = sortedLetters.begin(); i != sortedLetters.end(); i++) {
        decrypt[i -> second] = letters[countVector];
        countVector++;
    }

    return decrypt;
}

/*
 * Function to decrypt the text and save into a textfile.
 * It will iterate through the text and replace the encrypted letter (key of the map) with the
 * decrypted letter (value of the map).
 * Also it will check if there is an uppercase or a lowercase letter.
 * If there is an uppercase letter we set our decrypted value to uppercase, otherwise we just replace the letter with
 * the decrypted one.
 * We going to ignore other token than alphabetic token.
 * At the end the decrypted text will be saved into a new textfile.
 */
void decryptedText(std::string text, std::map<char, char> decrypt) {
    for(int i = 0; i < text.length(); i++) {
        if(std::isalpha(text[i])) {
            if (text[i] == toupper(text[i])) {
                text[i] = toupper(decrypt[tolower(text[i])]);
            } else if (text[i] == tolower(text[i])) {
                text[i] = decrypt[text[i]];
            } else {
                continue;
            }
        }
    }

    std::ofstream outfile("decrypted_text.txt");
    outfile << text;
}


int main() {
    std::string encryptedText = readFile("encrypted_text.txt");
    decryptedText(encryptedText, decrypt(sorted(countLetters(encryptedText))));

    return 0;
}