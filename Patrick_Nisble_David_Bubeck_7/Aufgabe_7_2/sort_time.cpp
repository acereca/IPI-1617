#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <ctime>


//insertion_sort() was implemented like the given code on the sheet.
void insertion_sort(std::vector<double> & v) {
    for(int i = 1; i < v.size(); i++) {
        double current = v[i];
        int j = i;
        while(j > 0) {
            if(current < v[j - 1]) {
                v[j] = v[j - 1];
            } else {
                break;
            }
            j--;
        }
        v[j] = current;
    }
}

//sort_time was also given on the sheet.
double std_sort_time(int n) {
    std::vector<double> v(n);
    for(int i = 0; i < n; i++) {
        v[i] = i;
    }
    std::random_shuffle(v.begin(), v.end());

    auto start = std::chrono::high_resolution_clock::now();
    std::sort(v.begin(), v.end());
    auto stop = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> diff = stop - start;
    return diff.count();
}

/*
 * insertion_sort_best_time is like sort_time.
 * Also we have a specific order of the vector, the values are sorted in ascending order.
 */
double insertion_sort_best_time(int n) {
    std::vector<double> v(n);
    for(int i = 0; i < n; i++) {
        v[i] = i;
    }

    auto start = std::chrono::high_resolution_clock::now();
    insertion_sort(v);
    auto stop = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> diff = stop - start;
    return diff.count();
}

/*
 * insertion_sort_worst_time is like sort_time.
 * Also we have a specific order of the vector, the values are sorted in descending order.
 */
double insertion_sort_worst_time(int n) {
    std::vector<double> v(n);
    int k = n;
    for(int i = 0; i < n; i++, k--) {
        v[i] = k;
    }

    auto start = std::chrono::high_resolution_clock::now();
    insertion_sort(v);
    auto stop = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> diff = stop - start;
    return diff.count();
}

/*
 * insertion_sort_typical_time is like sort_time.
 * The difference here is that the function will call insertion_sort() instead of std::sort().
 */
double insertion_sort_typical_time(int n) {
    std::vector<double> v(n);
    for(int i = 0; i < n; i++) {
        v[i] = i;
    }
    std::random_shuffle(v.begin(), v.end());

    auto start = std::chrono::high_resolution_clock::now();
    insertion_sort(v);
    auto stop = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> diff = stop - start;
    return diff.count();
}


/*
 * The main function will repeat five times with a different vectors.
 * For each vector the measurement will be repeated three times.
 */
int main() {
    //define different vector sizes
    std::vector<int> vectorSizes = {5000, 7000, 9000, 11000, 13000};

    //go through the vector for the different vector sizes for a time between 0.02 and 3.0 sec
    for(int i = 0; i < 5; i++) {

        //repeat the measurement for each vector three times
        for (int j = 0; j < 3; j++) {
            std::cout << "Durchgang " << j << ", Vektorgroesse: " << vectorSizes[i] << std::endl << std::endl;

            std::cout << "std_sort_time():               " << std_sort_time(vectorSizes[i]) << std::endl;
            std::cout << "insertion_sort_typical_time(): " << insertion_sort_typical_time(vectorSizes[i]) << std::endl;
            std::cout << "insertion_sort_best_time():    " << insertion_sort_best_time(vectorSizes[i]) << std::endl;
            std::cout << "insertion_sort_worst_time():   " << insertion_sort_worst_time(vectorSizes[i] ) << std::endl;

            std::cout << std::endl << "---------------------------------------------------" << std::endl << std::endl;
        }
        std::cout << "###################################################" << std::endl << std::endl;
    }

    return 0;
}