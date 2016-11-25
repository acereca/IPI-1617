//
// Created by patrick on 24.11.16.
// IPI-WS1617 5.2
// "Perfect-Shuffle"
// calculate operations needed for complete shuffle (perfect-in/out-shuffle)
//

#include <vector>
#include <numeric>
#include <cassert>
#include <iostream>

// using shorthand
typedef std::vector<int> Deck;

/// generate a vector of 52 ints
/// \return deck from 0 to 51
Deck init_deck();

/// check or correctly sorted
/// \param deck
/// \return true if sorted
bool check_deck(Deck deck);

/// perform a perfect-shuffle-operation
/// \param deck
/// \param out perform out shuffle?
/// \return deck after perfect-shuffle-operation
Deck shuffle(Deck deck, bool out);

int main() {
    Deck deck = init_deck();
    assert(check_deck(deck));

    // perfect-out-shuffle
    // do once as starting point
    deck = shuffle(deck, true);
    int out_iter = 1;
    while(!check_deck(deck)){
        deck = shuffle(deck, true);
        out_iter++;
    }
    std::cout << "Der Perfect-Out-Shuffle benötigt " << out_iter << " Wiederholungen, für ein Deck der Größe " << deck.size() << "\n";

    // perfect-in-shuffle
    // do once as starting point
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

        // out bestimmt die reihenfolge eines Paars -> lr || rl
        result[i*2+!out] = left_part[i];
        result[i*2+out] = right_part[i];
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

