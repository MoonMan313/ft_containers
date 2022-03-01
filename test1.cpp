////
//// Created by Cheryle Dionna on 2/20/22.
////
//
//#include <iostream>
//#include <string>
//#include <deque>
//#if 1 //CREATE A REAL STL EXAMPLE
//#include <map>
//#include <stack>
//#include <vector>
//namespace ft = std;
//#else
//#include <map.hpp>
//	#include <stack.hpp>
//	#include <vector.hpp>
//#endif
//
//#include <stdlib.h>
//
//#define MAX_RAM 4294967296
//#define BUFFER_SIZE 4096
//struct Buffer
//{
//    int idx;
//    char buff[BUFFER_SIZE];
//};
//
//
//#define COUNT (MAX_RAM / (int)sizeof(Buffer))
//
//template<typename T>
//class MutantStack : public ft::stack<T>
//{
//public:
//    MutantStack() {}
//    MutantStack(const MutantStack<T>& src) { *this = src; }
//    MutantStack<T>& operator=(const MutantStack<T>& rhs)
//    {
//        this->c = rhs.c;
//        return *this;
//    }
//    ~MutantStack() {}
//
//    typedef typename ft::stack<T>::container_type::iterator iterator;
//
//    iterator begin() { return this->c.begin(); }
//    iterator end() { return this->c.end(); }
//};
//
//int main(int argc, char** argv) {
//    if (argc != 2)
//    {
//        std::cerr << "Usage: ./test seed" << std::endl;
//        std::cerr << "Provide a seed please" << std::endl;
//        std::cerr << "Count value:" << COUNT << std::endl;
//        return 1;
//    }
//    const int seed = atoi(argv[1]);
//    srand(seed);
//    ft::vector<std::string> vector_str;
//    ft::vector<int> vector_int;
//    ft::stack<int> stack_int;
//    ft::vector<Buffer> vector_buffer;
//    ft::stack<Buffer, std::deque<Buffer> > stack_deq_buffer;
////    ft::map<int, int> map_int;
//
//    for (int i = 0; i < COUNT; i++)
//    {
//        vector_buffer.push_back(Buffer());
//    }
//
//    for (int i = 0; i < COUNT; i++)
//    {
//        const int idx = rand() % COUNT;
//        vector_buffer[idx].idx = 5;
//    }
//    ft::vector<Buffer>().swap(vector_buffer);
//
//    try
//    {
//        for (int i = 0; i < COUNT; i++)
//        {
//            const int idx = rand() % COUNT;
//            vector_buffer.at(idx);
//            std::cerr << "Error: THIS VECTOR SHOULD BE EMPTY!!" <<std::endl;
//        }
//    }
//    catch(const std::exception& e)
//    {
//        //NORMAL ! :P
//    }
//
////    for (int i = 0; i < COUNT; ++i)
////    {
////        map_int.insert(ft::make_pair(rand(), rand()));
////    }
////
////    int sum = 0;
////    for (int i = 0; i < 10000; i++)
////    {
////        int access = rand();
////        sum += map_int[access];
////    }
////    std::cout << "should be constant with the same seed: " << sum << std::endl;
////
////    {
////        ft::map<int, int> copy = map_int;
////    }
//    MutantStack<char> iterable_stack;
//    for (char letter = 'a'; letter <= 'z'; letter++)
//        iterable_stack.push(letter);
//    for (MutantStack<char>::iterator it = iterable_stack.begin(); it != iterable_stack.end(); it++)
//    {
//        std::cout << *it;
//    }
//    std::cout << std::endl;
//    return (0);
//}

#include "iteratorVector.hpp"
#include "Iterator_traits.hpp"
#include "Reverse_iterator.hpp"
#include "Utils_iterator.hpp"
#include "vector.hpp"
#include "stack.hpp"

#include <iostream>


#include <fstream>
#include <iostream>
#include <vector>

#define MY_OUTPUT "my_output"
#define STD_OUTPUT "std_output"

#define RESET   "\033[0m"
#define MAGENTA "\033[35m"      /* Magenta */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */

void check_diff() {
    std::ifstream my_output;
    std::ifstream std_output;

    my_output.open(MY_OUTPUT);
    std_output.open(STD_OUTPUT);
    std::string my, std;
    std::cout << "Result: ";
    if (my_output.is_open() && std_output.is_open()) {
        while (std::getline(my_output, my) && std::getline(std_output, std)) {
            if (my == std) {
                std::cout << BOLDGREEN << "OK" << RESET << std::endl;
            } else {
                std::cout << BOLDRED << "KO" << RESET << std::endl;
                break;
            }
        }
        if (my != std)
            std::cout << BOLDRED << "KO" << RESET << std::endl;

        my_output.close();
        std_output.close();
        std::remove(MY_OUTPUT);
        std::remove(STD_OUTPUT);
    } else {
        std::cout << BOLDRED << "KO" << RESET << std::endl;
    }
}

void test_constructor() {
    std::ofstream my_output;
    std::ofstream std_output;

    my_output.open(MY_OUTPUT);
    std_output.open(STD_OUTPUT);
    std::cout << "Test default constructor..." << std::endl;
    {
        ft::vector<int> v_my;
        std::vector<int> v_std;
        v_my.push_back(1);
        v_std.push_back(1);
        v_my.push_back(2);
        v_std.push_back(2);
        v_my.push_back(3);
        v_std.push_back(3);
        ft::vector<int>::iterator my_i = v_my.begin();
        std::vector<int>::iterator std_i = v_std.begin();
        for (; my_i != v_my.end(); my_i++)
            my_output << *my_i;
        for (; std_i != v_std.end(); std_i++)
            std_output << *std_i;
    }
    std::cout << "Test fill constructor..." << std::endl;
    {
        size_t n = 5000;
        ft::vector<int> v_my(n, 999999);
        std::vector<int> v_std(n, 999999);

        ft::vector<int>::iterator my_i = v_my.begin();
        std::vector<int>::iterator std_i = v_std.begin();
        for (; my_i != v_my.end(); my_i++)
            my_output << *my_i;
        for (; std_i != v_std.end(); std_i++)
            std_output << *std_i;

        std::cout << "Test range constructor..." << std::endl;
        for (int i = 0; i < 10; i++) {
            v_my.push_back(i);
            v_std.push_back(i);
        }
        ft::vector<int> v_2_my(v_my.begin(), v_my.end());
        std::vector<int> v_2_std(v_std.begin(), v_std.end());
        ft::vector<int>::iterator my_2_i = v_2_my.begin();
        std::vector<int>::iterator std_2_i = v_2_std.begin();
        for (; my_2_i != v_2_my.end(); my_2_i++)
            my_output << *my_2_i;
        for (; std_2_i != v_2_std.end(); std_2_i++)
            std_output << *std_2_i;

        std::cout << "Test copy constructor..." << std::endl;

        ft::vector<int> v_3_my(v_my);
        std::vector<int> v_3_std(v_std);
        ft::vector<int>::iterator my_3_i = v_3_my.begin();
        std::vector<int>::iterator std_3_i = v_3_std.begin();
        for (; my_3_i != v_3_my.end(); my_3_i++)
            my_output << *my_3_i;
        for (; std_3_i != v_3_std.end(); std_3_i++)
            std_output << *std_3_i;
    }
    my_output.close();
    std_output.close();
    check_diff();
}

void test_emty() {
    std::ofstream my_output;
    std::ofstream std_output;

    my_output.open(MY_OUTPUT);
    std_output.open(STD_OUTPUT);
    std::cout << "Test empty() function" << std::endl;
    size_t n = 5000;
    ft::vector<int> v_my(n, 999999);
    std::vector<int> v_std(n, 999999);
    my_output << v_my.size() << v_my.empty();
    std_output << v_std.size() << v_std.empty();
    v_my.erase(v_my.begin(), v_my.end());
    v_std.erase(v_std.begin(), v_std.end());
    my_output << v_my.size() << v_my.empty();
    std_output << v_std.size() << v_std.empty();
    my_output.close();
    std_output.close();
    check_diff();
}

void test_operator() {
    std::ofstream my_output;
    std::ofstream std_output;

    my_output.open(MY_OUTPUT);
    std_output.open(STD_OUTPUT);
    std::cout << "Test operator[]" << std::endl;
    size_t n = 5000;
    ft::vector<int> v_my(n, 999999);
    std::vector<int> v_std(n, 999999);
    for (size_t i = 0; i < n; i++) {
        my_output << v_my[i];
        std_output << v_std[i];
    }
    my_output.close();
    std_output.close();
    check_diff();
}

void test_at() {
    std::ofstream my_output;
    std::ofstream std_output;

    my_output.open(MY_OUTPUT);
    std_output.open(STD_OUTPUT);
    std::cout << "Test at" << std::endl;
    size_t n = 5000;
    ft::vector<int> v_my(n, 999999);
    std::vector<int> v_std(n, 999999);
    for (size_t i = 0; i < n; i++) {
        my_output << v_my.at(i);
        std_output << v_std.at(i);
    }
    my_output.close();
    std_output.close();
    check_diff();
}

void test_front() {
    std::ofstream my_output;
    std::ofstream std_output;

    my_output.open(MY_OUTPUT);
    std_output.open(STD_OUTPUT);
    std::cout << "Test front" << std::endl;
    size_t n = 5000;
    ft::vector<int> v_my(n, 999999);
    std::vector<int> v_std(n, 999999);
    for (size_t i = 0; i < n - 1; i++) {
        my_output << v_my.front();
        std_output << v_std.front();
        v_my.erase(v_my.begin());
        v_std.erase(v_std.begin());
    }
    my_output.close();
    std_output.close();
    check_diff();
}

void test_back() {
    std::ofstream my_output;
    std::ofstream std_output;

    my_output.open(MY_OUTPUT);
    std_output.open(STD_OUTPUT);
    std::cout << "Test back" << std::endl;
    size_t n = 5000;
    ft::vector<int> v_my(n, 999999);
    std::vector<int> v_std(n, 999999);
    for (size_t i = 0; i < n - 1; i++) {
        my_output << v_my.back();
        std_output << v_std.back();
        v_my.erase(v_my.begin());
        v_std.erase(v_std.begin());
    }
    my_output.close();
    std_output.close();
    check_diff();
}

void test_assign() {
    std::ofstream my_output;
    std::ofstream std_output;

    my_output.open(MY_OUTPUT);
    std_output.open(STD_OUTPUT);
    std::cout << "Test assign" << std::endl;
    {
        std::cout << "Test range (1) assign..." << std::endl;
        size_t n = 5000;
        ft::vector<int> v_my(n, 999999);
        std::vector<int> v_std(n, 999999);
        ft::vector<int> v_2_my(100, 300);
        std::vector<int> v_2_std(100, 300);
        v_2_my.assign(v_my.begin(), v_my.end());
        v_2_std.assign(v_std.begin(), v_std.end());

        for (size_t i = 0; i < n; i++) {
            my_output << v_my[i];
            std_output << v_std[i];
        }
    }
    {
        std::cout << "Test fill (2) assign..." << std::endl;
        size_t n = 5000;
        ft::vector<int> v_my(n, 999999);
        std::vector<int> v_std(n, 999999);
        v_my.assign(n * 2, 20000);
        v_std.assign(n * 2, 20000);

        for (size_t i = 0; i < n; i++) {
            my_output << v_my[i];
            std_output << v_std[i];
        }
    }
    my_output.close();
    std_output.close();
    check_diff();
}

void test_push_back() {
    std::ofstream my_output;
    std::ofstream std_output;

    my_output.open(MY_OUTPUT);
    std_output.open(STD_OUTPUT);
    std::cout << "Test push back" << std::endl;
    int n = 5000;
    ft::vector<int> v_my(5000, 999999);
    std::vector<int> v_std(5000, 999999);
    for (int i = 0; i < n * 2; i++) {
        v_my.push_back(i);
        v_std.push_back(i);
    }
    for (size_t i = 0; i < 5000 * 2; i++) {
        my_output << v_my[i];
        std_output << v_std[i];
    }
    my_output.close();
    std_output.close();
    check_diff();
}

void test_pop_back() {
    std::ofstream my_output;
    std::ofstream std_output;

    my_output.open(MY_OUTPUT);
    std_output.open(STD_OUTPUT);
    std::cout << "Test pop_back()" << std::endl;
    size_t n = 5000;
    ft::vector<int> v_my(n, 999999);
    std::vector<int> v_std(n, 999999);
    for (int i = 0; i < 5000 / 2; i++) {
        v_my.pop_back();
        v_std.pop_back();
        my_output << v_my.back();
        std_output << v_std.back();
    }
    my_output.close();
    std_output.close();
    check_diff();
}

void test_insert() {
    std::ofstream my_output;
    std::ofstream std_output;

    my_output.open(MY_OUTPUT);
    std_output.open(STD_OUTPUT);
    std::cout << "Test insert" << std::endl;
    {
        std::cout << "Test single element (1) insert..." << std::endl;

        size_t n = 5000;
        ft::vector<int> v_my;
        std::vector<int> v_std;
        for (int i = 0; i < 5000; i++) {
            v_my.insert(v_my.begin(), i);
            v_std.insert(v_std.begin(), i);
        }
        v_my.insert(v_my.begin() + 1000, 99999);
        v_std.insert(v_std.begin() + 1000, 99999);
        for (size_t i = 0; i < n; i++) {
            my_output << v_my[i];
            std_output << v_std[i];
        }
    }
    {
        std::cout << "Test fill (2) insert..." << std::endl;

        size_t n = 5000;
        ft::vector<int> v_my(n, 999999);
        std::vector<int> v_std(n, 999999);

        v_my.insert(v_my.begin() + 1000, 99999);
        v_std.insert(v_std.begin() + 1000, 99999);
        for (size_t i = 0; i < n; i++) {
            my_output << v_my[i];
            std_output << v_std[i];
        }
    }
    {
        std::cout << "Test range (3) insert..." << std::endl;

        size_t n = 50;
        ft::vector<int> v_my(4, 1);
        std::vector<int> v_std(4, 1);
        ft::vector<int> v_2_my(n, 8);
        std::vector<int> v_2_std(n, 8);

        v_my.insert(v_my.begin(), n, 1);
        v_std.insert(v_std.begin(), n, 1);
        v_my.insert(v_my.begin() + 3, 99999);
        v_std.insert(v_std.begin() + 3, 99999);

        v_my.insert(v_my.begin() + 2, v_2_my.begin(), v_2_my.end());
        v_std.insert(v_std.begin() + 2, v_2_std.begin(), v_2_std.end());

        for (size_t i = 0; i < n; i++) {
            my_output << v_my[i];
            std_output << v_std[i];
        }
    }
    my_output.close();
    std_output.close();
    check_diff();
}


void test_erase() {
    std::ofstream my_output;
    std::ofstream std_output;

    my_output.open(MY_OUTPUT);
    std_output.open(STD_OUTPUT);
    std::cout << "Test erase()" << std::endl;
    {
        std::cout << "Test erase with iterator position..." << std::endl;

        size_t n = 5000;
        ft::vector<int> v_my(n, 999999);
        std::vector<int> v_std(n, 999999);

        v_my.erase(v_my.begin());
        v_std.erase(v_std.begin());
        my_output << v_my.size();
        std_output << v_std.size();
        v_my.erase(v_my.begin() + 1000);
        v_std.erase(v_std.begin() + 1000);
        my_output << v_my.size();
        std_output << v_std.size();
        v_my.erase(v_my.begin() + 2000);
        v_std.erase(v_std.begin() + 2000);
        my_output << v_my.size();
        std_output << v_std.size();
    }
    {
        std::cout << "Test erase with first and last position..." << std::endl;

        size_t n = 5000;
        ft::vector<int> v_my(n, 999999);
        std::vector<int> v_std(n, 999999);
        ft::vector<int>::iterator first_my = v_my.begin();
        std::vector<int>::iterator first_std = v_std.begin();
        my_output << v_my.size();
        std_output << v_std.size();
        v_my.erase(first_my, v_my.end());
        v_std.erase(first_std, v_std.end());
        my_output << v_my.size();
        std_output << v_std.size();

        my_output << v_my.empty();
        std_output << v_std.empty();
    }
    my_output.close();
    std_output.close();
    check_diff();
}

void test_swap() {
    std::ofstream my_output;
    std::ofstream std_output;

    my_output.open(MY_OUTPUT);
    std_output.open(STD_OUTPUT);
    std::cout << "Test swap()" << std::endl;
    {
        size_t n = 5000;
        ft::vector<int> v_my;
        std::vector<int> v_std;
        ft::vector<int> v_2_my(n, 999999);
        std::vector<int> v_2_std(n, 999999);
        my_output << v_my.size();
        std_output << v_std.size();
        my_output << v_2_my.size();
        std_output << v_2_std.size();
        v_my.swap(v_2_my);
        v_std.swap(v_2_std);
        my_output << v_my.size();
        std_output << v_std.size();
        my_output << v_2_my.size();
        std_output << v_2_std.size();
        v_my.swap(v_2_my);
        v_std.swap(v_2_std);
        my_output << v_my.size();
        std_output << v_std.size();
        my_output << v_2_my.size();
        std_output << v_2_std.size();
    }
    {
        size_t n = 5000;
        ft::vector<int> v_my(n, 11);
        std::vector<int> v_std(n, 11);
        ft::vector<int> v_2_my(n/2, 999999);
        std::vector<int> v_2_std(n/2, 999999);
        my_output << v_my.size();
        std_output << v_std.size();
        my_output << v_2_my.size();
        std_output << v_2_std.size();
        v_my.swap(v_2_my);
        v_std.swap(v_2_std);
        my_output << v_my.size();
        std_output << v_std.size();
        my_output << v_2_my.size();
        std_output << v_2_std.size();
        v_my.swap(v_2_my);
        v_std.swap(v_2_std);
        my_output << v_my.size();
        std_output << v_std.size();
        my_output << v_2_my.size();
        std_output << v_2_std.size();
    }
    my_output.close();
    std_output.close();
    check_diff();
}

void test_clear() {
    std::ofstream my_output;
    std::ofstream std_output;

    my_output.open(MY_OUTPUT);
    std_output.open(STD_OUTPUT);
    std::cout << "Test clear()" << std::endl;
    {
        size_t n = 5000;
        ft::vector<int> v_my;
        std::vector<int> v_std;
        ft::vector<int> v_2_my(n, 999999);
        std::vector<int> v_2_std(n, 999999);
        my_output << v_my.size();
        std_output << v_std.size();
        my_output << v_2_my.size();
        std_output << v_2_std.size();
        v_my.clear();
        v_std.clear();
        v_2_my.clear();
        v_2_std.clear();
        my_output << v_my.size();
        std_output << v_std.size();
        my_output << v_2_my.size();
        std_output << v_2_std.size();
    }
    my_output.close();
    std_output.close();
    check_diff();
}

void make_vector_test() {
    std::cout << MAGENTA << "-------------------------------" << std::endl;
    std::cout << "     VECTOR TESTER STARTED" << std::endl;
    std::cout << "-------------------------------" << RESET << std::endl;

    test_constructor();
//    test_emty();
//    test_operator();
//    test_at();
//    test_front();
//    test_back();
//    test_assign();
//    test_push_back();
//    test_pop_back();
//    test_insert();
//    test_erase();
//    test_swap();
//    test_clear();
}

int main (){
    make_vector_test();
}