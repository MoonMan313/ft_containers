//
// Created by evelina on 28.02.2022.
//

#include "map.hpp"
#include "vector.hpp"
#include "stack.hpp"
#include <map>
#include <stack>
#include <vector>
#include <iostream>
#include <cstdlib>

int main ()
{
    ft::stack<int> first;
//    ft::map<int, int>::iterator it = first.begin();

    std::cout << "empty = " << first.empty() << "\n";
    std::cout << "size = " << first.size() << "\n";

    first.push(1);
    first.push(2);
    first.pop();
    std::cout << first.top() << "\n";

    ft::stack<int> second;

    second.push(3);
    second.push(0);

    if (first == second)
        std::cout << "да\n";
    std::cout << "нет\n";

////    first.insert(ft::make_pair(1,1));
////    std::cout <<  "1234\n";
////    first.insert(ft::make_pair(3,3));
////    std::cout <<  "1234\n";
////    first.insert(ft::make_pair(2,2));
////    ft::map<int, int>::iterator it = first.begin();
////    ft::map<int, int>::iterator it_end = first.end();
////    for (; it != it_end; ++it)
////        std::cout << it->first  << "\n";
////    --it_end;
////    --it_end;
////    std::cout << it_end->first << "\n";
////    ++it_end;
//////    std::cout << first.begin()->first  << "\n";
////    first.erase(3);
//
//
////
////    std::map<int,int> first;
//////    std::map<int, int>::iterator it = first.begin();
////
////    std::cout << "empty = " << first.empty() << "\n";
////    std::cout << "size = " << first.size() << "\n";
////    std::cout << "max_size = " << first.max_size() << "\n";
////
////    first.insert(std::make_pair(10,1));
////    std::cout <<  "1234\n";
////    first.insert(std::make_pair(5,3));
////    std::cout <<  "1234\n";
//    first.insert(ft::make_pair(20,2));
//    first.insert(ft::make_pair(1,2));
//    first.insert(ft::make_pair(7,2));
//    first.insert(ft::make_pair(15,2));
//    first.insert(ft::make_pair(50,2));
//    first.insert(ft::make_pair(0,2));
//    first.insert(ft::make_pair(3,2));
//    first.insert(ft::make_pair(6,2));
//    first.insert(ft::make_pair(8,2));
//    first.insert(ft::make_pair(11,2));
//    first.insert(ft::make_pair(16,2));
//    first.insert(ft::make_pair(30,2));
//    first.insert(ft::make_pair(60,2));
//
//
//
//    std::cout << "empty = " << first.empty() << "\n";
//    std::cout << "size = " << first.size() << "\n";
//    std::cout << "max_size = " << first.max_size() << "\n";
//
//    ft::map<int, int>::reverse_iterator it = first.rbegin();
//    ft::map<int, int>::reverse_iterator it_end = first.rend();
//
//
//    for (; it != it_end; ++it)
//        std::cout << it->first  << "\n";
//
////    first.erase(it, it_end);
//    std::cout << "empty = " << first.empty() << "\n";
//    std::cout << "size = " << first.size() << "\n";
//    std::cout << "max_size = " << first.max_size() << "\n";
//
//
//    ft::map<int,int> second;
////    ft::map<int, int>::iterator it = first.begin();
//    second.insert(ft::make_pair(1,1));
//    second.insert(ft::make_pair(3,3));
//    second.insert(ft::make_pair(2,2));
//
//    std::cout << "!empty = " << second.empty() << "\n";
//    std::cout << "!size = " << second.size() << "\n";
//    std::cout << "!max_size = " << second.max_size() << "\n";
//    second.swap(first);
//    std::cout << "!empty = " << second.empty() << "\n";
//    std::cout << "!size = " << second.size() << "\n";
//    std::cout << "!max_size = " << second.max_size() << "\n";
////    std::cout << "lower_bound = " << first.lower_bound(1)->first << "\n";
////    std::cout << "upper_bound = " << first.upper_bound(1)->first << "\n";
////
////    ft::map<int, int> vec_1;
////
////    for(int i = 0; i < 5; ++i) {
////        vec_1[i] = i * 2;
////        std::cout << vec_1[i] << "\n";
////    }
////    std::cout << "vector.lower_bound = " << vec_1.lower_bound(1)->first << "\n";
////    std::cout << "vector.upper_bound = " << vec_1.upper_bound(1)->first << "\n";
////    system("leaks a.out");

//    ft::vector<int> first;
//    for(int i = 0; i < 10; ++i) {
//        first[i] = i;
//        std::cout << first[i] << "\n";
//    }
//    ft::vector<int> second;
//    ft::vector<int>::iterator it = second.begin();
//    for(int i = 10; i < 100 ; ++i t, i += 10)
//        second.insert(it, i);

    return 0;
}
