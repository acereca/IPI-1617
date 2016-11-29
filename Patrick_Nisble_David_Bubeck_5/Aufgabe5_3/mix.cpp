#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "text.hpp"

/*
 * Function to split the input string.
 * It will check every char in the string.
 * The chars will be set together to a split string until a space was found
 * this split string will pushed into the vector.
 * For the last word, it means if the control variable reached the length of the string,
 * we don't have a space to split so we push the split word directly into the vector after
 * checking on the control variable.
*/
std::vector<std::string> split_words(std::string stringInput) {
    std::vector<std::string> splitWords;
    std::string splitString;

    for(int i = 0; i < stringInput.length(); i++) {
        if(stringInput[i] == ' ') {
            splitWords.push_back(splitString);
            splitString = "";
        } else {
            splitString += stringInput[i];
            if(i == stringInput.length() - 1) {
                splitWords.push_back(splitString);
            }
        }
    }

    return splitWords;
}

/*
 * Function to mix the input string.
 * First the function will search for the first and the last letter in the input string.
 * Therefor we set the position of the first letter at the length of the input string.
 * Now if a letter char will be found and the value of the position of the first letter
 * is greater than the control variable it will set the value of the control variable as
 * position of the first letter.
 * Analog for the position of the last letter, only with a start value of 0 and checking on
 * the control variable if it is smaller or equal to the position.
 * After we found the position we shuffle the string with fixed first and last letter, meaning
 * we shuffle between the letters.
 */
std::string mix(std::string stringInput) {
    int positionFirstLetter = stringInput.length();
    int positionLastLetter = 0;
    for(int i = 0; i < stringInput.length(); i++) {
        if(std::isalnum(stringInput[i]) && positionFirstLetter > i) {
            positionFirstLetter = i;
        }
        else if(std::isalnum(stringInput[i]) && positionLastLetter <= i) {
            positionLastLetter = i;
        }
    }

    //if there is a "-" in our word it will destroy the readable effect so
    //we check on that and make two substrings which will be shuffled
    //the calculation will be done as the normal string without "-"
    int positionLine = stringInput.find('-');
    if(positionLine != std::string::npos) {
        std::string substringLeft = stringInput.substr(0, positionLine);
        std::string substringRight = stringInput.substr(positionLine);
        //the position of the first letter of the left substring is equal to the whole string with "-"
        int shuffleStartLeftString = positionFirstLetter + 1;
        //the position of the end of the left substring is our position of "-" with add 1 because of the 0 counting start
        int shuffleEndLeftString = substringLeft.length() - positionLine + 1;
        //we want to hold the position for "-" and the first letter of the right substring
        int shuffleStartRightString = 2;
        //the end of the right substring is equal to the whole string with "-"
        int shuffleEndRightString = stringInput.size() - positionLastLetter;

        std::random_shuffle(substringLeft.begin() + shuffleStartLeftString, substringLeft.end() - shuffleEndLeftString);
        std::random_shuffle(substringRight.begin() + shuffleStartRightString, substringRight.end() - shuffleEndRightString);
        std::string shuffledSubstring = substringLeft + substringRight;

        return shuffledSubstring;
    }

    //calculating the beginning and the end of the string without the first and the last letter
    //of the input string for shuffling
    int shuffleStart = positionFirstLetter + 1;
    int shuffleEnd = stringInput.length() - positionLastLetter;
    std::random_shuffle(stringInput.begin() + shuffleStart, stringInput.end() - shuffleEnd);

    return stringInput;
}

/*
 * Function to split and mix the input String.
 * Therefor we save our split string into a vector, by using the function split_words().
 * After that we go through the vector and mix the strings with the function mix()
 * for every entry separately and put them after the shuffle into a new string seperated by a space.
 */
std::string split_and_mix(std::string stringInput) {
    std::vector<std::string> splitString = split_words(stringInput);
    std::string mixedString;

    for(int i = 0; i < splitString.size(); i++) {
        mixedString += mix(splitString[i]) + " ";
    }

    return mixedString;
}


/*
 * Main function.
 * Push every string from text.hpp into a vector.
 * For each entry in the vector give an output of the original text and the shuffled text.
 *
 * Note: on windows is a problem with to_string so it will have an output of the number of
 * str as an integer (it has no effect at all).
 * Also for a random shuffle we need to seed the random function but it was not ask in the sheet, because
 * without a seed our random_shuffle() will always have the same "random" output.
 */
int main() {
    std::vector<std::string> text = {str1, str2, str3, str4, str5};
    for(int i = 0; i < 5; i++) {
        std::cout << "urspruenglicher Text in " << "str" << i + 1 << ": " << std::endl;
        std::cout << text[i] << std::endl;
        std::cout << "Ergebnis von split_and_mix(str" << i + 1 << "): " << std::endl;
        std::cout << split_and_mix(text[i]) << std::endl;
    }

    return 0;
}