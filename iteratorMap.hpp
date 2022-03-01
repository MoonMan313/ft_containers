//
// Created by evelina on 28.02.2022.
//

#ifndef FT_CONTAINERS_ITERATORMAP_HPP
#define FT_CONTAINERS_ITERATORMAP_HPP

#include "Pair.hpp"
#include <iostream>

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

    template <typename T, typename node>
    class iteratorMap {
    protected:
        typedef ft::Node<T>             Node;
        node                            *it;

    public:
        typedef T                                   value_type;
        typedef T*                                  pointer;
        typedef T&                                  reference;
        typedef ptrdiff_t                           difference_type;
        typedef std::bidirectional_iterator_tag     iterator_category;

        iteratorMap() : it(nullptr) {}
        iteratorMap(node *it_node) : it(it_node) {}
        iteratorMap(const iteratorMap &copy) : it(copy.it) {}
        virtual ~iteratorMap() {}

        iteratorMap &operator=(const iteratorMap& value){
            if (this != &value)
                it = value.it;
            return (*this);
        }
        iteratorMap &operator ++ (void){
            if (it->parent == nullptr)
                it = nullptr;
            else if (it->right) {
                it = it->parent;
                while (it->left)
                    it = it->left;
            }
            else {
                node *tmp = it;
                it = it->parent;
                while (it->left != tmp) {
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
                while (it->right)
                    it = it->right;
            } else {
                node tmp = it;
                it = it->parent;
                while (it->right != tmp) {
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
}



#endif //FT_CONTAINERS_ITERATORMAP_HPP
