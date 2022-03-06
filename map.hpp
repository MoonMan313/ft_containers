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
            class T,                                                 // map::mapped_type
            class Compare = std::less<Key>,                     // map::key_compare
            class Alloc = std::allocator<ft::pair<const Key,T> >    // map::allocator_type
    > class map{
    private:
        typedef ft::Node<ft::pair<const Key, T> > node_type;
        std::allocator<node_type>            _alloc;
        size_t                               _size;
        Compare                              _keyComp;
        node_type*                           _rootNode;
        node_type*                           _endNode;

    public:
        typedef Key                                                     key_type;
        typedef T                                                       mapped_type;
        typedef ft::pair<const key_type, mapped_type>                   value_type;
        typedef Compare                                                 key_compare;
        typedef Alloc                                                   allocator_type;
        typedef typename allocator_type::reference                      reference;
        typedef typename allocator_type::const_reference                const_reference;
        typedef typename allocator_type::pointer                        pointer;
        typedef typename allocator_type::const_pointer                  const_pointer;
        typedef iteratorMap<value_type>                                 iterator;
        typedef constIteratorMap<value_type>                            const_iterator;
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
                      : _alloc(alloc),
                        _size(0),
                        _keyComp(comp),
                        _rootNode(_alloc.allocate(1)),
                        _endNode(_alloc.allocate(1)) {}

        template <class InputIterator>
        map (InputIterator first, InputIterator last,
             const key_compare& comp = key_compare(),
             const allocator_type& alloc = allocator_type(),
             typename ft::enable_if<!ft::is_integral<InputIterator>::value >::type* = 0)
             : _alloc(alloc),
               _size(0),
               _keyComp(comp),
               _rootNode(_alloc.allocate(1)),
               _endNode(_alloc.allocate(1)) {
            insert(first, last);
        }

        map (const map& x)
        : _alloc(x._alloc),
            _size(x._size),
            _keyComp(x._keyComp) {
            insert(x.begin(), x.end());
        }

        // (destructor)
        ~map(){
            clear();
            _alloc.deallocate(_rootNode, 1);
            _alloc.deallocate(_endNode, 1);
        }

        // operator=
        map& operator= (const map& x){
            clear();
            insert(x.begin(), x.end());
            return *this;
        }

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
            return (iterator(_endNode));
        }
        const_iterator end() const{
            return (const_iterator(_endNode));
        }
        //rbegin
        reverse_iterator rbegin(){
            return (reverse_iterator(end()));
        }
        const_reverse_iterator rbegin() const{
            return (const_reverse_iterator(end()));
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
            if (_size != 0 && (find(val.first) != _endNode))
                return (ft::pair<iterator, bool>(find((val.first)), false));
            node_type *p_node = findNodeAndPush( val, _rootNode, NULL);
            return (ft::pair<iterator, bool>(find((val.first)), true));
        }
        iterator insert (iterator position, const value_type& val){
            (void)position;
            return (insert(val).first);
        }
        template <class InputIterator>
            void insert (InputIterator first, InputIterator last,
                          typename ft::enable_if<!ft::is_integral<InputIterator>::value >::type* = 0) {
            while (first != last){
                insert(*first);
                first++;
            }
        }
        //erase
        void erase (iterator position){
            erase((*position).first);
        }

        size_type erase (const key_type& k){
            if (find(k) == _endNode || _size == 0)
                return (0);
            node_type *tmp = find_node(_rootNode, k);
            if (tmp->left && tmp->right)
                removeNodeWithChildren(tmp);
            else if (tmp->right){
                if (tmp->value.first == tmp->right->value.first){
                    if (tmp->parent)
                        editEndNode(tmp->parent);
                    else {
                        _alloc.destroy(_rootNode);
                        _alloc.destroy(_endNode);
                    }
                } else if (tmp->parent)
                    removeNodeWithRightChild(tmp);
                else {
                    tmp->right->parent = NULL;
                    remove_node(_rootNode);
                    _rootNode = tmp->right;
                }
            }
            else if (tmp->left)
                removeNodeWithLeftChild(tmp);
            else
                removeNodeWithoutChildren(tmp);
            --_size;
            return (1);
        }

        void erase (iterator first, iterator last){
            for (;first != last; ++first)
                erase((*first).first);
        }
        //swap
        void swap (map& x){
            node_type* rootNode = _rootNode;
            node_type* endNode = _endNode;
            size_type size = _size;
            key_compare keyComp = _keyComp;
            allocator_type alloc = _alloc;

            _rootNode = x._rootNode;
            _endNode = x._endNode;
            _size = x._size;
            _keyComp = x._keyComp;
            _alloc = x._alloc;

            x._rootNode = rootNode;
            x._endNode = endNode;
            x._size = size;
            x._keyComp = keyComp;
            x._alloc = alloc;
        }

        //clear
        void clear(){
            erase(begin(), _endNode);
        }

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
            for(; it != NULL && it != _endNode && it->first != k; ++it);
            return (it);
        }
        const_iterator find (const key_type& k) const{
            const_iterator it = begin();
            for(; it != _endNode && it->first != k; ++it);
            return (it);
        }
        //count
        size_type count (const key_type& k) const{
            if (find(k) != _endNode)
                return (1);
            return (0);
        }
        //lower_bound
        iterator lower_bound (const key_type& k){
            iterator it = begin();
            for(; it != _endNode && _keyComp(it->first, k); ++it);
            return (it);
        }
        const_iterator lower_bound (const key_type& k) const{
            const_iterator it = begin();
            for(; it != _endNode && _keyComp(it->first, k); ++it);
            return (it);
        }
        //upper_bound
        iterator upper_bound (const key_type& k){
            iterator it = lower_bound(k);
            if (it->first == k && it != _endNode)
                ++it;
            return (it);
        }
        const_iterator upper_bound (const key_type& k) const{
            const_iterator it = lower_bound(k);
            if (it->first == k && it != _endNode)
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
            if (!current || _size == 0 || ((_keyComp(_endNode->value.first, val.first))
                    && parent && (current->value.first == parent->value.first)))
                return (create_new_node(val,parent));
            if (_keyComp(val.first, current->value.first))
                current->left = findNodeAndPush(val, current->left, current);
            else if (_keyComp(current->value.first, val.first))
                current->right = findNodeAndPush(val, current->right, current);
            return (current);
        }

        node_type *find_node(node_type* current, const key_type& k){
            if (_keyComp(k, current->value.first))
                find_node(current->left, k);
            else if (_keyComp(current->value.first, k))
                find_node(current->right, k);
            else
                return (current);
        }

        node_type *create_new_node(const value_type& val, node_type* parent){
            if (_size == 0)
                return (create_root_node(val));
            node_type *node = _alloc.allocate(1);
            _alloc.construct(node, node_type(val, NULL, NULL, parent));
            node->parent = parent;
            node->right = NULL;
            node->left = NULL;
            _size++;
            if (_keyComp(_endNode->value.first, val.first)){
                _alloc.destroy(_endNode);
                _alloc.construct(_endNode, node_type(make_pair(val.first, NULL), NULL, NULL, NULL));
                _endNode->parent = node;
                node->right = _endNode;
            }
            return (node);
        }

        node_type *create_root_node(const value_type& val){
            _alloc.construct(_rootNode, node_type(val, NULL, NULL, NULL));
            _rootNode->parent = NULL;
            _rootNode->right = NULL;
            _rootNode->left = NULL;
            _size++;
            _alloc.construct(_endNode, node_type(make_pair(val.first, NULL), NULL, NULL, NULL));
            _endNode->parent = _rootNode;
            _rootNode->right = _endNode;
            return (_rootNode);
        }

        void remove_node(node_type *node){
            _alloc.destroy(node);
            _alloc.deallocate(node, 1);
        }

        void removeNodeWithoutChildren(node_type *tmp){
            node_type *parentNode = tmp->parent;
            if (parentNode->left && parentNode->right){
                if (parentNode->right == tmp)
                    parentNode->right = NULL;
                else
                    parentNode->left = NULL;
            } else if (parentNode->right)
                parentNode->right = NULL;
            else
                parentNode->left = NULL;
            remove_node(tmp);
        }

        void removeNodeWithLeftChild(node_type *tmp) {
            node_type *parentNode = tmp->parent;
            if (parentNode->left && parentNode->right) {
                if (parentNode->right == tmp)
                    parentNode->right = tmp->left;
                else
                    parentNode->left = tmp->left;
            } else if (parentNode->right)
                parentNode->right = tmp->left;
            else
                parentNode->left = tmp->left;
            tmp->left->parent = parentNode;
            remove_node(tmp);
        }

        void removeNodeWithRightChild(node_type *tmp) {
            node_type *parentNode = tmp->parent;
            if (parentNode->left && parentNode->right) {
                if (parentNode->right == tmp)
                    parentNode->right = tmp->right;
                else
                    parentNode->left = tmp->right;
            } else if (parentNode->right)
                parentNode->right = tmp->right;
            else
                parentNode->left = tmp->right;
            tmp->right->parent = parentNode;
            remove_node(tmp);
        }

        void removeNodeWithChildren(node_type *tmp) {
            if (tmp->parent) {
                if (tmp->value.first == tmp->right->value.first) {
                    node_type *end_node = tmp->left;
                    for (; end_node && end_node->right; end_node = end_node->right);
                    editEndNode(end_node);
                    removeNodeWithLeftChild(tmp);
                } else {
                    findNextNodeAndConnect(tmp);;
                    removeNodeWithRightChild(tmp);
                }
            } else {
                if (tmp->value.first == tmp->right->value.first) {
                    tmp->left->parent = NULL;
                    remove_node(_rootNode);
                    _rootNode = tmp->left;
                    node_type *end_node = tmp->left;
                    for (; end_node && end_node->right; end_node = end_node->right);
                    editEndNode(end_node);
                } else {
                    findNextNodeAndConnect(tmp);
                    tmp->right->parent = NULL;
                    remove_node(_rootNode);
                    _rootNode = tmp->right;
                }
            }
        }

        node_type *findNextNodeAndConnect(node_type *tmp){
            node_type *node_next = tmp->right;
            while (node_next && node_next->left)
                node_next = node_next->left;
            tmp->left->parent = node_next;
            node_next->left = tmp->left;
        }

        void editEndNode(node_type *new_end) {
            _alloc.destroy(_endNode);
            _alloc.construct(_endNode,
                             node_type(make_pair(new_end->value.first, NULL), NULL, NULL, NULL));
            _endNode->parent = new_end;
            new_end->right = _endNode;
        }
    };
}


#endif //FT_CONTAINERS_MAP_HPP
