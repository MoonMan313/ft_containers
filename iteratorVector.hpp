//
// Created by evelina on 23.02.2022.
//

#ifndef FT_CONTAINERS_ITERATORVECTOR_HPP
#define FT_CONTAINERS_ITERATORVECTOR_HPP

#include <iostream>
#include "Utils_iterator.hpp"

namespace ft{
    template <typename T>
    class iteratorVector {

    protected:
        T *it;

    public:
        typedef T       value_type;
        typedef T*      pointer;
        typedef T&      reference;
        typedef std::ptrdiff_t                  difference_type;
        typedef std::random_access_iterator_tag iterator_category;

        iteratorVector() : it(NULL){}
        iteratorVector(pointer it) : it(it) {}
        iteratorVector(const iteratorVector &copy) : it(copy.it) {}
        virtual ~iteratorVector() {}

        iteratorVector &operator=(const iteratorVector& value){
            if (this != &value)
                this->it = value.it;
            return (*this);
        }
        iteratorVector &operator ++ (void){
            ++it;
            return (*this);
        }
        iteratorVector operator ++ (int) {
            iteratorVector tmp = *this;
            ++it;
            return (tmp);
        }
        iteratorVector &operator -- (void) {
            --it;
            return (*this);
        }
        iteratorVector operator -- (int) {
            iteratorVector tmp(*this);
            --it;
            return (tmp);
        }
        iteratorVector &operator -= (difference_type value) {
            it -= value;
            return (*this);
        }
        iteratorVector &operator += (difference_type value) {
            it += value;
            return (*this);
        }
        difference_type operator+(const iteratorVector &value) const {
            return (it + value.it);
        }
        difference_type	 operator - (const iteratorVector& value) const{
            return (it - value.it);
        }
        iteratorVector operator - (difference_type value){
            return (it - value);
        }
        iteratorVector operator + (difference_type value){
            return (it + value);
        }
        bool operator == (const iteratorVector& value) const{
            return (it == value.it);
        }
        bool operator != (const iteratorVector& value) const{
            return (it != value.it);
        }
        bool operator <= (const iteratorVector& value) const{
            return (it <= value.it);
        }
        bool operator >= (const iteratorVector& value) const{
            return (it >= value.it);
        }
        bool operator < (const iteratorVector& value) const{
            return (it < value.it);
        }
        bool operator > (const iteratorVector& value) const{
            return (it > value.it);
        }
        reference	operator*() {
            return (*it);
        }
        pointer operator->() {
            return (it);
        }
        reference	operator[] (int index){
            return (*(it + index));
        }
    };
}

#endif //FT_CONTAINERS_ITERATORVECTOR_HPP
