//
// Created by patrick on 24.11.16.
//

#include <vector>
#include <numeric>
#include <cassert>
#include <iostream>

typedef std::vector<int> Deck;

Deck init_deck();
bool check_deck(Deck deck);
Deck shuffle(Deck vector, bool out);

int main() {
    Deck deck = init_deck();
    assert(check_deck(deck));


    deck = shuffle(deck, true);
    int out_iter = 1;
    while(!check_deck(deck)){
        deck = shuffle(deck, true);
        out_iter++;
    }
    std::cout << "Der Perfect-Out-Shuffle benötigt " << out_iter << " Wiederholungen, für ein Deck der Größe " << deck.size() << "\n";

    deck = shuffle(deck, false);
    int in_iter = 1;
    while(!check_deck(deck)){
        deck = shuffle(deck, false);
        in_iter++;
    }
    std::cout << "Der Perfect-In-Shuffle benötigt " << in_iter << " Wiederholungen, für ein Deck der Größe " << deck.size() << "\n";

}

Deck shuffle(Deck deck, bool out){
    Deck right_part(deck.begin()+deck.size()/2, deck.end());
    Deck left_part(deck.begin(), deck.end()-deck.size()/2);

    Deck result(deck.size());
    for (int i = 0; i < deck.size()/2; i++){
        if (out) {
            result[i*2] = left_part[i];
            result[i*2+1] = right_part[i];
        } else {
            result[i*2] = right_part[i];
            result[i*2+1] = left_part[i];
        }
    }
    return result;
}

Deck init_deck(){
    Deck deck(52);
    std::iota(deck.begin(), deck.end(), 0);
    return deck;
}

bool check_deck(Deck deck){
    for (int i = 0; i< deck.size()-1; i++) {
        if (deck[i] >= deck[i+1]) {
            return false;
        }
    }
    return true;
}

