//
// Created by evelina on 28.02.2022.
//

#ifndef FT_CONTAINERS_ITERATORMAP_HPP
#define FT_CONTAINERS_ITERATORMAP_HPP

#include "Pair.hpp"
#include <iostream>
#include <cstddef>

namespace ft{
    template <typename T>
    struct Node {
        T       value;
        Node    *left;
        Node    *right;
        Node    *parent;

        Node(T value, Node *left, Node *right, Node *parent)
                : value(value), left(left), right(right), parent(parent) {}
    };

    template <typename T>
    class iteratorMap {
    protected:
        typedef ft::Node<T>                 node;
        node                                *it;

    public:
        typedef T                                   value_type;
        typedef T*                                  pointer;
        typedef T&                                  reference;
        typedef ptrdiff_t                           difference_type;
        typedef std::bidirectional_iterator_tag     iterator_category;

        iteratorMap() : it(NULL) {}
        iteratorMap(node *it_node) : it(it_node) {}
        iteratorMap(iteratorMap const &copy) : it(copy.it) {}
        virtual ~iteratorMap() {}

        iteratorMap &operator=(const iteratorMap& value){
            if (this != &value)
                it = value.it;
            return (*this);
        }
        iteratorMap &operator ++ (void){
            if (it->right) {
                it = it->right;
                while (it && it->left)
                    it = it->left;
            }
            else {
                node *tmp = it;
                it = it->parent;
                while (it && it->left != tmp && !(it->left != tmp && it->right != tmp)) {
                    tmp = it;
                    it = it->parent;
                }
            }
            return (*this);

        }
        iteratorMap operator ++ (int) {
            iteratorMap tmp = *this;
            ++(*this);
            return (tmp);
        }
        iteratorMap &operator -- (void) {
            if (it->left) {
                it = it->left;
                while (it && it->right)
                    it = it->right;
            } else {
                node *tmp = it;
                it = it->parent;
                while (it && it->right != tmp && !(it->left != tmp && it->right != tmp)) {
                    tmp = it;
                    it = it->parent;
                }
            }
            return (*this);
        }
        iteratorMap operator -- (int) {
            iteratorMap tmp = *this;
            --(*this);
            return (tmp);
        }
        bool operator == (const iteratorMap& value) const{
            return (it == value.it);
        }
        bool operator != (const iteratorMap& value) const{
            return (it != value.it);
        }
        reference	operator*() {
            return (it->value);
        }
        pointer operator->() {
            return (&(it->value));
        }

    };



    template <typename T>
    class constIteratorMap {
    protected:
        typedef ft::Node<T>                 node;
        node                                *it;

    public:
        typedef T                                   value_type;
        typedef T const *                                  pointer;
        typedef T const &                                  reference;
        typedef ptrdiff_t                           difference_type;
        typedef std::bidirectional_iterator_tag     iterator_category;

        constIteratorMap() : it(NULL) {}
        constIteratorMap(node *it_node) : it(it_node) {}
        constIteratorMap(constIteratorMap const &copy) : it(copy.it) {}
        virtual ~constIteratorMap() {}

        constIteratorMap &operator=(const constIteratorMap& value){
            if (this != &value)
                it = value.it;
            return (*this);
        }
        constIteratorMap &operator ++ (void){
            if (it->right) {
                it = it->right;
                while (it && it->left)
                    it = it->left;
            }
            else {
                node *tmp = it;
                it = it->parent;
                while (it && it->left != tmp && !(it->left != tmp && it->right != tmp)) {
                    tmp = it;
                    it = it->parent;
                }
            }
            return (*this);

        }
        constIteratorMap operator ++ (int) {
            constIteratorMap tmp = *this;
            ++(*this);
            return (tmp);
        }
        constIteratorMap &operator -- (void) {
            if (it->left) {
                it = it->left;
                while (it && it->right)
                    it = it->right;
            } else {
                node *tmp = it;
                it = it->parent;
                while (it && it->right != tmp && !(it->left != tmp && it->right != tmp)) {
                    tmp = it;
                    it = it->parent;
                }
            }
            return (*this);
        }
        constIteratorMap operator -- (int) {
            constIteratorMap tmp = *this;
            --(*this);
            return (tmp);
        }
        bool operator == (const constIteratorMap& value) const{
            return (it == value.it);
        }
        bool operator != (const constIteratorMap& value) const{
            return (it != value.it);
        }
        reference	operator*() {
            return (it->value);
        }
        pointer operator->() {
            return (&(it->value));
        }

    };
}



#endif //FT_CONTAINERS_ITERATORMAP_HPP
