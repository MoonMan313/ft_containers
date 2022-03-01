//
// Created by evelina on 28.02.2022.
//

#include "map.hpp"
#include <map>
#include <vector>
#include <iostream>

int main ()
{
    ft::map<int,int> first;

    std::cout << "empty = " << first.empty() << "\n";
    std::cout << "size = " << first.size() << "\n";
    std::cout << "max_size = " << first.max_size() << "\n";

    first.insert(ft::make_pair(1,1));

//    std::map<int, int> vec_1;
//
//    for(int i = 0; i < 5; ++i)
//        vec_1[i] = i*2;
//    std::cout << "vector.lower_bound = " << vec_1.lower_bound(1)->first << "\n";
//    std::cout << "vector.upper_bound = " << vec_1.upper_bound(1)->first << "\n";
    return 0;
}