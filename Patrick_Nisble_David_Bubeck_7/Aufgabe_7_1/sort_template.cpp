#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cassert>


/*
 * a) like in the course
 */
template <typename ElementType, typename LessThanFunctor>
bool check_sorted(std::vector<ElementType> const & v, LessThanFunctor lessThan) {
    for(int i = 1; i < v.size(); i++) {
        if(lessThan(v[i], v[i - 1])) {
            return false;
        }
    }
    return true;
}

/*
 * b) like in the course
 */
template <typename Iterator, typename LessThanFunctor>
bool check_sorted(Iterator begin, Iterator end, LessThanFunctor lessThan) {
    if(begin == end) {
        return true;
    }
    Iterator next = begin;
    next++;

    for( ; next != end; begin++, next++) {
        if(lessThan(*next, *begin)) {
            return false;
        }
    }
    return true;
}

/*
 * c) like on the sheet
 */
template <typename ElementType, typename LessThanFunctor>
void insertion_sort(std::vector<ElementType> & v, LessThanFunctor lessThan) {
    for(int i = 1; i < v.size(); i++) {
        ElementType current = v[i];
        int j = i;
        while(j > 0) {
            if(lessThan(current, v[j - 1])) {
                v[j] = v[j - 1];
            } else {
                break;
            }
            j--;
        }
        v[j] = current;
    }
}

/*
 * d) like on the sheet
 */
template <typename Iterator, typename LessThanFunctor>
void insertion_sort(Iterator begin, Iterator end, LessThanFunctor lessThan) {
    //if its empty return
    if(begin == end) {
        return;
    }

    for(auto iter = begin + 1; iter < end; iter++) {
        auto current = *iter;
        auto j = iter;
        while(j > begin) {
            if(lessThan(current, *(j - 1))) {
                *j = *(j - 1);
            } else {
                break;
            }
            j--;
        }
        *j = current;
    }
}


int main() {
    //generate random seed
    std::srand(time(0));

    //generate four random sized vectors
    for(int i = 0; i < 4; i++) {
        //generate random vector size
        int randomSize = std::rand() % 10 + 5;
        std::vector<int> testVector;
        //generate random vector with random values
        for(int j = 0; j < randomSize; j++) {
            testVector.push_back(std::rand() % 100);
        }

        //Output random vector
        std::cout << "###############################################" << std::endl;
        std::cout << std::endl << "Random Vektor " << i << std::endl;
        for(int it = 0; it < testVector.size(); it++) {
            std::cout << testVector[it] << " ";
        }
        std::cout << std::endl << "-----------------------------------------------" << std::endl;

        //test the functions for more iterations
        for(int k = 0; k < 4; k++) {
            //sort vector values
            std::sort(testVector.begin(), testVector.end());

            //Output sorted vector
            std::cout << "Random Vektor " << i << " sorted Durchgang " << k << std::endl;
            for(int it = 0; it < testVector.size(); it++) {
                std::cout << testVector[it] << " ";
            }
            std::cout << std::endl << std::endl;

            //assert function for check_sorted() of exercise a) of sort()
            assert(check_sorted(testVector, [](int a, int b){return a < b;}));
            //assert function for check_sorted() of exercise b) of sort()
            assert(check_sorted(testVector.begin(), testVector.end(), [](int a, int b){return a < b;}));


            //randomize vector values
            std::random_shuffle(testVector.begin(), testVector.end());

            //Output randomized vector
            std::cout << "Random Vektor " << i << " randomized Durchgang " << k << std::endl;
            for(int it = 0; it < testVector.size(); it++) {
                std::cout << testVector[it] << " ";
            }
            std::cout << std::endl << std::endl;

            //assert function for check_sorted() of exercise a) of random_shuffle()
            assert(!check_sorted(testVector, [](int a, int b){ return a < b;}));
            //assert function for check_sorted() of exercise b) of random_shuffle()
            assert(!check_sorted(testVector.begin(), testVector.end(), [](int a, int b){ return a < b;}));


            //sort vector values with insertion sort
            insertion_sort(testVector, [](int a, int b){ return a < b;});

            //Output insertion sort vector c)
            std::cout << "Random Vektor " << i << " insertion_sort c) Durchgang " << k << std::endl;
            for(int it = 0; it < testVector.size(); it++) {
                std::cout << testVector[it] << " ";
            }
            std::cout << std::endl << std::endl;

            //assert function for check_sorted() of exercise a) of insertion_sort()
            assert(check_sorted(testVector, [](int a, int b){return a < b;}));
            //assert function for check_sorted() of exercise b) of insertion_sort()
            assert(check_sorted(testVector.begin(), testVector.end(), [](int a, int b){return a < b;}));


            //randomize vector values
            std::random_shuffle(testVector.begin(), testVector.end());

            //sort vector values with insertion sort iterator version
            insertion_sort(testVector.begin(), testVector.end(), [](int a, int b){ return a < b;});

            //Output insertion sort vector d)
            std::cout << "Random Vektor " << i << " insertion_sort d) Durchgang " << k << std::endl;
            for(int it = 0; it < testVector.size(); it++) {
                std::cout << testVector[it] << " ";
            }
            std::cout << std::endl << "-----------------------------------------------" << std::endl;

            //assert function for check_sorted() of exercise a) of insertion_sort() iterator version
            assert(check_sorted(testVector, [](int a, int b){return a < b;}));
            //assert function for check_sorted() of exercise b) of insertion_sort() iterator version
            assert(check_sorted(testVector.begin(), testVector.end(), [](int a, int b){return a < b;}));
        }
    }

    return 0;
}