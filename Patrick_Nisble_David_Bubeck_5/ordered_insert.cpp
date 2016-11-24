#include <iostream>
#include <vector>



int main() {

    std::vector<int> sorted_list{};
    int in = 0;

    while (true) {
        std::cout << std::endl << "Zahl bitte: ";
        std::cin >> in;

        // stop at: in < 0 after std::cin
        if (in < 0) break;

        // in initial state sorted_list.size() == 0
        if (sorted_list.size() == 0) {
            sorted_list.push_back(in);
            continue;
        }

        for (int i = 0; i < sorted_list.size(); i++){
            if (in <= sorted_list[i]){
                sorted_list.insert(sorted_list.begin()+i, in);
                break;
            } else if (i == sorted_list.size()-1){
                sorted_list.push_back(in);
                break;
            }
            // break after any kind of insertion
        }
    }

    std::cout << "{ ";
    for (auto sorted_value: sorted_list) {
        std::cout << std::to_string(sorted_value) << " ";
    }
    std::cout << "}";

    return 0;
}
