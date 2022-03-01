//
// Created by Cheryle Dionna on 2/20/22.
//

#ifndef FT_CONTAINERS_MAP_HPP
#define FT_CONTAINERS_MAP_HPP

#include <memory>
#include "Pair.hpp"
#include "iteratorMap.hpp"
#include "Reverse_iterator.hpp"
#include "Iterator_traits.hpp"
#include <iostream>

namespace ft{
    template < class Key,                                     // map::key_type
            class T,                                       // map::mapped_type
            class Compare = std::less<Key>,                     // map::key_compare
            class Alloc = std::allocator<ft::pair<const Key,T> >    // map::allocator_type
    > class map{
    private:
        typedef ft::Node<ft::pair<const Key, T>> node_type;
        Alloc                                _alloc;
        size_t                               _size;
        node_type*                            _rootNode;
        Compare                              _keyComp;

    public:
        typedef Key                                                     key_type;
        typedef T                                                       mapped_type;
        typedef ft::pair<const key_type, mapped_type>                   value_type; //ft::pair реализовать
        typedef Compare                                                 key_compare;
        typedef Alloc                                                   allocator_type;
        typedef typename allocator_type::reference                      reference;
        typedef typename allocator_type::const_reference                const_reference;
        typedef typename allocator_type::pointer                        pointer;
        typedef typename allocator_type::const_pointer                  const_pointer;
        typedef iteratorMap<value_type, node_type>                      iterator;
        typedef iteratorMap<value_type const, node_type>                const_iterator;
        typedef ft::reverse_iterator<const_iterator>                    const_reverse_iterator;
        typedef ft::reverse_iterator<iterator>                          reverse_iterator;
        typedef typename ft::iterator_traits<iterator>::difference_type difference_type;
        typedef size_t                                                  size_type;

        class value_compare : public std::binary_function<value_type, value_type, bool> {
            friend class map;
        protected:
            key_compare comp;
            value_compare(key_compare c) : comp(c) {}
        public:
            bool operator() (const value_type& x, const value_type& y) const{
                return comp(x.first, y.first);
            }
        };


        // (constructor)
        explicit map (const key_compare& comp = key_compare(),
                      const allocator_type& alloc = allocator_type())
                      : _keyComp(comp),
                        _alloc(alloc),
                        _size(0),
                        _rootNode(NULL) {}
                        //дописать

//        template <class InputIterator>
//        map (InputIterator first, InputIterator last,
//             const key_compare& comp = key_compare(),
//             const allocator_type& alloc = allocator_type()){
//
//        }
//        map (const map& x);
//
//        // (destructor)
//        ~map();
//
//        // operator=
//        map& operator= (const map& x);
//
        /*
         * Iterators
         */
        //begin
        iterator begin(){
            if (!_size)
                return (iterator(_rootNode));
            node_type *tmp = _rootNode;
            while(tmp && tmp->left)
                tmp = tmp->left;
            return (iterator(tmp));
        }
        const_iterator begin() const{
            if (!_size)
                return (const_iterator(_rootNode));
            node_type *tmp = _rootNode;
            while(tmp && tmp->left)
                tmp = tmp->left;
            return (const_iterator(tmp));
        }
        //end
        iterator end(){
            if (!_size)
                return (iterator(_rootNode));
            node_type *tmp = _rootNode;
            while(tmp && tmp->right)
                tmp = tmp->right;
            return (iterator(tmp));
        }
        const_iterator end() const{
            if (!_size)
                return (const_iterator(_rootNode));
            node_type *tmp = _rootNode;
            while(tmp && tmp->right)
                tmp = tmp->right;
            return (const_iterator(tmp));
        }
        //rbegin
        reverse_iterator rbegin(){
            return (reverse_iterator(--end()));
        }
        const_reverse_iterator rbegin() const{
            return (const_reverse_iterator(--end()));
        }
        //rend
        reverse_iterator rend(){
            return (reverse_iterator(begin()));
        }
        const_reverse_iterator rend() const{
            return (const_reverse_iterator(begin()));
        }

        /*
         * Capacity
         */
        //empty
        bool empty() const{
            return (_size == 0);
        }
        //size
        size_type size() const{
            return (_size);
        }
        //max_size
        size_type max_size() const{
            size_type max = _alloc.max_size();
            return (max);
        }

        /*
         * Element access
         */
        //operator[]
        mapped_type& operator[] (const key_type& k){
            return (insert(ft::make_pair(k, mapped_type())).first->second);
        }

        /*
         * Modifiers
        */
        //insert
        ft::pair<iterator,bool> insert (const value_type& val){
            node_type *p_node = findNodeAndPush(val, _rootNode, NULL);
            if (p_node->value.first == val.first)
                return (ft::pair<iterator, bool>(find((val.first)), false));
            else if (p_node == NULL){
                return (ft::pair<iterator, bool>(findNodeAndPush(val, NULL, NULL), true));
            } else {
                findNodeAndPush(val, _rootNode, NULL);
                return (ft::pair<iterator, bool>(find((val.first)), true));
            }
        }
        iterator insert (iterator position, const value_type& val){
            (void)position;
            return (insert(val).first);
        }
        template <class InputIterator>
            void insert (InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value >::type* = 0) {
            while (first != last){
                insert(*first);
                first++;
            }
        }
//        //erase
//        void erase (iterator position);
//        size_type erase (const key_type& k);
//        void erase (iterator first, iterator last);
//        //swap
//        void swap (map& x);
//        //clear
//        void clear();

        /*
         * Observers
         */
        //key_comp
        key_compare key_comp() const{
            return (_keyComp);
        }
        //value_comp
        value_compare value_comp() const{
            return (value_compare(_keyComp));
        }

        /*
         * Operations
         */
        //find
        iterator find (const key_type& k){
            iterator it = begin();
            for(; it != end() && it->first != k; ++it);
            return (it);
        }
        const_iterator find (const key_type& k) const{
            const_iterator it = begin();
            for(; it != end() && it->first != k; ++it);
            return (it);
        }
        //count
        size_type count (const key_type& k) const{
            if (find(k) != end())
                return (1);
            return (0);
        }
        //lower_bound
        iterator lower_bound (const key_type& k){
            iterator it = begin();
            for(iterator end_it = end(); it != end_it && _keyComp(it->first, k); ++it);
            return (it);
        }
        const_iterator lower_bound (const key_type& k) const{
            const_iterator it = begin();
            for(const_iterator end_it = end(); it != end_it && _keyComp(it->first, k); ++it);
            return (it);
        }
        //upper_bound
        iterator upper_bound (const key_type& k){
            iterator it = lower_bound(k);
            if (it->first == k && it != end())
                ++it;
            return (it);
        }
        const_iterator upper_bound (const key_type& k) const{
            const_iterator it = lower_bound(k);
            if (it->first == k && it != end())
                ++it;
            return (it);
        }
        //equal_range
        ft::pair<const_iterator,const_iterator> equal_range (const key_type& k) const{
            return (ft::make_pair(lower_bound(k), upper_bound(k)));
        }
        ft::pair<iterator,iterator> equal_range (const key_type& k){
            return (ft::make_pair(lower_bound(k), upper_bound(k)));
        }
        /*
         * Allocator
         */
        //get_allocator
        allocator_type get_allocator() const{
            return (_alloc);
        }

    private:
        node_type *findNodeAndPush(const value_type& val, node_type* current, node_type* parent) {
            if (!current) {
                node_type *node = _alloc.allocate(1);
                _alloc.construct(node, node_type(val, NULL, NULL, parent));
                node->parent = parent;
                node->right = NULL;
                node->left = NULL;
                _size++;
                return (node);
            }
            if (_keyComp(val.first, current->value.first))
                current->left = findNodeAndPush(val, current->left, current);
            else if (_keyComp(current->value.first, val.first))
                current->right = findNodeAndPush(val, current->right, current);
            return (current);
        }

    };
}


#endif //FT_CONTAINERS_MAP_HPP
