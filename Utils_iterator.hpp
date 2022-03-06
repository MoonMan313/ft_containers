//
// Created by evelina on 27.02.2022.
//

#ifndef FT_CONTAINERS_UTILS_ITERATOR_HPP
#define FT_CONTAINERS_UTILS_ITERATOR_HPP

#include <iostream>
#include "iteratorVector.hpp"

namespace ft {
    //iterator_traits
    template<class IteratorMain>
    class iterator_traits {
    public:
        typedef typename IteratorMain::value_type           value_type;
        typedef typename IteratorMain::pointer              pointer;
        typedef typename IteratorMain::reference            reference;
        typedef typename IteratorMain::difference_type      difference_type;
        typedef typename IteratorMain::iterator_category    iterator_category;
    };

    template<class T>
    class iterator_traits<T *> {
    public:
        typedef T                               value_type;
        typedef T*                              pointer;
        typedef T&                              reference;
        typedef std::ptrdiff_t                  difference_type;
        typedef std::random_access_iterator_tag iterator_category;
    };

    template<class T>
    class iterator_traits<const T *> {
    public:
        typedef T                               value_type;
        typedef const T*                        pointer;
        typedef const T&                        reference;
        typedef std::ptrdiff_t                  difference_type;
        typedef std::random_access_iterator_tag iterator_category;
    };

    //lexicographical_compare
    template <class InputIterator1, class InputIterator2>
    bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
                                  InputIterator2 first2, InputIterator2 last2){
        while ((first1 != last1) && (first2 != last2))
        {
            if (*first1 < *first2)
                return (false);
            else if (*first2 < *first1)
                return (true);
            ++first1;
            ++first2;
        }
        return (first1 == last1) && (first2 != last2);
    }

    // enable_if
    template<bool B, class T = void> struct enable_if {};

    template<class T> struct enable_if<true, T> {
        typedef T type;
    };

    //is_integral
    template <class T> struct is_integral{
        static const bool value = false;
    };
    template <> struct is_integral<bool>                    {static const bool value = true;};
    template <> struct is_integral<char>                    {static const bool value = true;};
//    template <> struct is_integral<char16_t>                {static const bool value = true;};
//    template <> struct is_integral<char32_t>                {static const bool value = true;};
    template <> struct is_integral<wchar_t>                 {static const bool value = true;};
    template <> struct is_integral<signed char >            {static const bool value = true;};
    template <> struct is_integral<short int>               {static const bool value = true;};
    template <> struct is_integral<int>                     {static const bool value = true;};
    template <> struct is_integral<long int>                {static const bool value = true;};
    template <> struct is_integral<long long int>           {static const bool value = true;};
    template <> struct is_integral<unsigned char >          {static const bool value = true;};
    template <> struct is_integral<unsigned short int>      {static const bool value = true;};
    template <> struct is_integral<unsigned int>            {static const bool value = true;};
    template <> struct is_integral<unsigned long int>       {static const bool value = true;};
    template <> struct is_integral<unsigned long long int>  {static const bool value = true;};
}

#endif //FT_CONTAINERS_UTILS_ITERATOR_HPP
