//
// Created by patrick on 24.11.16.
// IPI-WS1617 5.1
// "sorted insertion into array"
// perform sorted insertion for random numbers
//

#include <iostream>
#include <vector>

/// insertion sort, elementwise
/// \param list reference of sorted list
/// \param in positive value to be inserted
/// \throws invalid_argument for negative in
void sorted_insertion(std::vector<int>& list, int in);

int main() {

    std::vector<int> sorted_list{};
    int in = 0;

    // do until interrupted
    while (true) {
        std::cout << "Zahl bitte: ";
        std::cin >> in;

        // catch negative numbers
        try {
            sorted_insertion(sorted_list, in);
        } catch (std::invalid_argument& e) {
            std::cout << "Zahl negativ!\n";
            break;
        }
    }

    // write sorted_list to console
    std::cout << "Terminiere mit entstandener Liste: { ";
    for (int i = 0; i < sorted_list.size(); i++) {
        std::cout << std::to_string(sorted_list[i]) << ((sorted_list.size()-1 == i)? "" :", ");
    }
    std::cout << " }";

    return 0;
}

void sorted_insertion (std::vector<int> &list, int in){
    if (in < 0) throw std::invalid_argument("");

    // either list is empty or the last elemnt is leq to in
    if (list.empty() || list.at(list.size()-1) <= in) {
        list.push_back(in);
    } else {
        // go through every elemnt of list
        for (auto it = list.begin(); it < list.end(); it++){

            // find first element in list to be greq to in
            if (in <= *it){
                list.insert(it, in);

                // break after insertion
                break;
            }
        }
    }
}
