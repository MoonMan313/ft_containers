//
// Created by evelina on 23.02.2022.
//

#ifndef FT_CONTAINERS_REVERSE_ITERATOR_HPP
#define FT_CONTAINERS_REVERSE_ITERATOR_HPP

#include "Utils_iterator.hpp"
#include "iteratorVector.hpp"

namespace ft {
    template <class Iterator>
    class reverse_iterator {
    protected:
        Iterator    rev_it;
    public:
        typedef Iterator                                               iterator_type;
        typedef typename iterator_traits<Iterator>::iterator_category  iterator_category;
        typedef typename iterator_traits<Iterator>::value_type         value_type;
        typedef typename iterator_traits<Iterator>::difference_type    difference_type;
        typedef typename iterator_traits<Iterator>::pointer            pointer;
        typedef typename iterator_traits<Iterator>::reference          reference;


        reverse_iterator() : rev_it(){}
        explicit reverse_iterator (iterator_type it) : rev_it(it) {};
        template <class Iter>
        reverse_iterator (const reverse_iterator<Iter>& it) {
            rev_it = it.base();
        }

        iterator_type base() const {
            return (rev_it);
        }

        reference operator*() const {
            iterator_type tmp = rev_it;
            --tmp;
            return (*tmp);
        }

        reverse_iterator operator+ (difference_type n) const {
            return (reverse_iterator(rev_it - n));
        }

        reverse_iterator& operator++() {
            --rev_it;
            return (*this);
        }

        reverse_iterator  operator++(int) {
            reverse_iterator temp = *this;
            --rev_it;
            return (temp);
        }

        reverse_iterator& operator+= (difference_type n) {
            rev_it -= n;
            return (*this);
        }

        reverse_iterator operator- (difference_type n) const {
            return (reverse_iterator(rev_it + n));
        }

        reverse_iterator& operator--() {
            ++rev_it;
            return (*this);
        }

        reverse_iterator  operator--(int) {
            reverse_iterator temp = *this;
            ++rev_it;
            return (temp);
        }

        reverse_iterator& operator-= (difference_type n) {
            rev_it += n;
            return (*this);
        }

        pointer operator->() const {
            return &(operator*());
        }

        reference operator[] (difference_type n) const{
            return (*(rev_it -n -1));
        }
    };

    template <class Iter>
    bool operator== (const reverse_iterator<Iter>& lhs,
                     const reverse_iterator<Iter>& rhs) {
        return (lhs.base() == rhs.base());
    }
    template <class Iter>
    bool operator!= (const reverse_iterator<Iter>& lhs,
                     const reverse_iterator<Iter>& rhs){
        return (lhs.base() != rhs.base());
    }
    template <class Iter>
    bool operator<  (const reverse_iterator<Iter>& lhs,
                     const reverse_iterator<Iter>& rhs){
        return (lhs.base() < rhs.base());
    }
    template <class Iter>
    bool operator<= (const reverse_iterator<Iter>& lhs,
                     const reverse_iterator<Iter>& rhs) {
        return (lhs.base() <= rhs.base());
    }
    template <class Iter>
    bool operator>  (const reverse_iterator<Iter>& lhs,
                     const reverse_iterator<Iter>& rhs){
        return (lhs.base() > rhs.base());
    }
    template <class Iter>
    bool operator>= (const reverse_iterator<Iter>& lhs,
                     const reverse_iterator<Iter>& rhs) {
        return (lhs.base() >= rhs.base());
    }

    template <class Iter>
    reverse_iterator<Iter> operator+ (
            typename reverse_iterator<Iter>::difference_type n,
            const reverse_iterator<Iter>& rev_it) {
        return (reverse_iterator<Iter>(rev_it.base() - n));
    }

    template <class Iter>
    typename reverse_iterator<Iter>::difference_type operator- (
            const reverse_iterator<Iter>& lhs,
            const reverse_iterator<Iter>& rhs) {
        return (lhs.base() - rhs.base());
    }
}
#endif //FT_CONTAINERS_REVERSE_ITERATOR_HPP
