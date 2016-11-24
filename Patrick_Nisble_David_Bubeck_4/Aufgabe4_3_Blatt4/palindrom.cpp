#include <iostream>
#include <string>
#include <cctype>
#include <cassert>


//transform string into lowercase
std::string to_lower(std::string s) {
    std::string stringLower;
    //check for each character of the string
    for(int i = 0; i < s.length(); i++) {
        stringLower += std::tolower(s[i]);
    }

    return stringLower;
}


//delete character which are no alphabetic characters
std::string letters_only(std::string s) {
    std::string stringCharacter;

    for(int i = 0; i < s.length(); i++) {
        //if alphabetic character put it together in to a new string
        if(isalpha(s[i])) {
            stringCharacter += s[i];
        }
    }

    return stringCharacter;
}


//check if input string is a palindrom
bool is_palindrom(std::string s) {
    bool palindrom;
    //make string lowercase and delete non alphabetic characters
    std::string stringInput = letters_only(to_lower(s));
    std::string stringReverse;

    //reverse input string
    for(int i = stringInput.length() - 1; i >= 0; i--) {
        stringReverse += stringInput[i];
    }

    //compare input and reverse string
    if(stringInput == stringReverse) {
        palindrom = true;
    } else {
        palindrom = false;
    }

    return palindrom;
}




int main() {
    //assert function to check if algorithm is correct
    std::string stringArray[] = {"Otto", "Anna", "Rentner", "Lagerregal", "Ein Neger mit Gazelle zagt im Regen nie"};
    for(int i = 0; i < 5; i++) {
        assert(is_palindrom(stringArray[i]) == true);
    }

    //input for user
    std::string input;
    std::cout << "Geben sie ein Wort oder einen Satz ein:" << std::endl;
    std::getline(std::cin, input);

    //output if palindrom or not
    if(is_palindrom(input) == true) {
        std::cout << input << " ist ein Palindrom!" << std::endl;
    } else {
        std::cout << input << " ist KEIN Palindrom!" << std::endl;
    }

    return 0;
}
