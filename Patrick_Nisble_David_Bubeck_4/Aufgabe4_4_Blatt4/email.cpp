#include <iostream>
#include <string>
#include <cassert>
#include <cctype>


bool is_email(std::string s) {
    bool isAt = false;
    int positionAt = 0;
    int positionLastPoint = 0;
    std::string leftString;
    std::string rightString;

    for(int i = 0; i < s.length(); i++) {
        if(std::isalnum(s[i]) == false) {
            if(s[i] == '@') {
                if(isAt == false) {
                    positionAt = i;
                    isAt = true;
                } else {
                    std::cout << "Ungueltige Eingabe: zu viele @" << std::endl;
                    return false;
                }
            }
            if(s[i] == '.') {
                if(positionLastPoint < i && positionAt < i) {
                    positionLastPoint = i;
                }
            }
            if(s[i] == '@' || s[i] == '.' || s[i] == '_' || s[i] == '-') {
                continue;
            } else {
                std::cout << "Ungueltige Eingabe: " << s[i] << " ist kein gueltiges Zeichen" << std::endl;
                return false;
            }
        }
    }

    leftString = s.substr(0, positionAt);
    rightString = s.substr(positionAt + 1);

    //before @ must be a valid character
    if(positionAt == 0) {
        std::cout << "Ungueltige Eingabe: vor @ muss mindestens ein gueltiges Zeichen stehen" << std::endl;
        return false;
    }

    //after @ must be a point
    if(rightString.find('.') == std::string::npos) {
        std::cout << "Ungueltige Eingabe: nach @ muss mindestens ein Punkt stehen" << std::endl;
        return false;
    }

    //between @ and the last point must be a valid character
    if(positionLastPoint - positionAt == 1) {
        std::cout << "Ungueltige Eingabe: zwischen @ und letztem Punkt muss mindestens ein gueltiges Zeichen stehen" << std::endl;
        return false;
    }

    //after the last point must be a valid character
    if(positionLastPoint == s.length() - 1) {
        std::cout << "Ungueltige Eingabe: nach letztem Punkt muss mindestens ein gueltiges Zeichen stehen" << std::endl;
        return false;
    }

    return true;
}





int main() {
    //assert valid email
    assert(is_email("hallo@world.de"));
    assert(is_email("haLLo@wOrld.de"));
    assert(is_email("h@w.de"));
    assert(is_email("h.a.l.l.o@world.de"));
    assert(is_email("h4l-l0@w0r7d.de"));
    assert(is_email("hal_lo@wor-ld.de"));

    //assert invalid email
    std::cout << "assert Ungueltige Email 1" << std::endl;
    assert(! is_email("@world.de"));
    std::cout << "assert Ungueltige Email 2" << std::endl;
    assert(! is_email("l%o@world.de"));
    std::cout << "assert Ungueltige Email 3" << std::endl;
    assert(! is_email("hallo@.de"));
    std::cout << "assert Ungueltige Email 4" << std::endl;
    assert(! is_email("hallo@world.de."));
    std::cout << "assert Ungueltige Email 5" << std::endl;
    assert(! is_email("hallo@worldde"));
    std::cout << "assert Ungueltige Email 6" << std::endl;
    assert(! is_email("hal@lo@world.de"));

    return 0;
}