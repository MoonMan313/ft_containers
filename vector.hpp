//
// Created by Cheryle Dionna on 2/20/22.
//

#ifndef FT_CONTAINERS_VECTOR_HPP
#define FT_CONTAINERS_VECTOR_HPP

#include <memory>
#include "Utils_iterator.hpp"
#include "Reverse_iterator.hpp"

namespace ft {
    template<class T, class Alloc = std::allocator <T> >
    class vector{
    public:
        typedef T                                           value_type;
        typedef Alloc                                       allocator_type;
        typedef typename allocator_type::reference          reference;
        typedef typename allocator_type::const_reference    const_reference;
        typedef typename allocator_type::pointer            pointer;
        typedef typename allocator_type::const_pointer      const_pointer;
        typedef iteratorVector<value_type>                    iterator;
        typedef iteratorVector<value_type const>              const_iterator;
        typedef ft::reverse_iterator<const_iterator>        const_reverse_iterator;
        typedef ft::reverse_iterator<iterator>              reverse_iterator;
        typedef size_t                                      size_type;
        typedef std::ptrdiff_t                               difference_type;

    private:
        size_type       _size;
        size_type       _capacity;
        allocator_type  _alloc;
        value_type      *_arr;

    public:
        //(constructor)
        explicit vector (const allocator_type& alloc = allocator_type())
            :   _size(0),
                _capacity(0),
                _alloc(alloc),
                _arr(NULL){}

        explicit vector (size_type n, const value_type& val = value_type(),
                         const allocator_type& alloc = allocator_type())
             :  _size(n),
                _capacity(n),
                _alloc(alloc),
                _arr(NULL){
            _arr = _alloc.allocate(n);
            for(size_type i = 0; i < n; ++i)
                _alloc.construct(_arr + i, val);
        }

        template <class InputIterator>
                 vector (InputIterator first, InputIterator last,
                         const allocator_type& alloc = allocator_type(),
                         typename ft::enable_if<!ft::is_integral<InputIterator>::value >::type* = 0)
              : _size(0),
                _capacity(1),
                _alloc(alloc),
                _arr(NULL) {
            _arr = _alloc.allocate(_capacity);
            insert(begin(), first, last);
        }

        vector (const vector& x){
            clear();
            insert(end(), x.begin(), x.end());
        }

        //(destructor)
        ~vector(){
            clear();
            if (_capacity)
                _alloc.deallocate(_arr, _capacity);
        }

        //operator=
        vector& operator= (const vector& x){
            if (x == *this)
                return (*this);
            clear();
            insert(this->end(), x.begin(), x.end());
            return (*this);
        }

        /*
         *  Iterators
         */

        //begin
        iterator begin() {
            return (iterator(_arr));
        }
        const_iterator begin() const{
            return (const_iterator(_arr));
        }
        //end
        iterator end(){
            return (iterator(_arr + _size));
        }
        const_iterator end() const{
            return (const_iterator(_arr + _size));
        }
        //rbegin
        reverse_iterator rbegin(){
            return (reverse_iterator(--end()));
        }
        const_reverse_iterator rbegin() const{
            return (reverse_iterator(--end()));
        }
        //rend
        reverse_iterator rend(){
            return (reverse_iterator(begin()));
        }
        const_reverse_iterator rend() const{
            return (reverse_iterator(begin()));
        }

        /*
         *Capacity
         */

        //size
        size_type size() const{
            return (_size);
        }
        //max_size
        size_type max_size() const{
            size_type max = _alloc.max_size();
            return (max);
        }
        //resize
        void resize (size_type n, value_type val = value_type()){
            if (n > _capacity){
                reserve(n * 2);
            }
            for(size_type i = _size; i< n; ++i){
                _alloc.construct(_arr + i, val);
            }
            for(size_type i = n; i < _size; ++i){
                _alloc.destroy(_arr + i);
            }
            _size = n;
        }
        //capacity
        size_type capacity() const{
            return (_capacity);
        }
        //empty
        bool empty() const{
            return (_size == 0);
        }
        //reserve
        void reserve (size_type n){
            if (n > _capacity){
                value_type *new_arr = _alloc.allocate(n);
                _capacity = n;
                for(size_type i = 0; i < _size; ++i){
                    _alloc.construct(new_arr + i, *(_arr + 1));
                    _alloc.destroy(_arr + i);
                }
                if(_capacity)
                    _alloc.deallocate(_arr, _capacity);
                _arr = new_arr;
            }
        }

        /*
         * Element access
         */

        // operator[]
        reference operator[] (size_type n){
            return (_arr[n]);
        }
        const_reference operator[] (size_type n) const{
            return (_arr[n]);
        }
        // at
        reference at (size_type n){
            if (n < 0 || n >= _size)
                throw std::out_of_range("Index out of range");
            return (_arr[n]);
        }
        const_reference at (size_type n) const{
            if (n < 0 || n >= _size)
                throw std::out_of_range("Index out of range");
            return (_arr[n]);
        }
        // front
        reference front(){
            return (_arr[0]);
        }
        const_reference front() const{
            return (_arr[0]);
        }
        // back
        reference back(){
            return (_arr[_size - 1]);
        }
        const_reference back() const{
            return (_arr[_size - 1]);
        }

        /*
         * Modifiers
         */

        // assign
        template <class InputIterator>
          void assign (InputIterator first, InputIterator last,
                       typename ft::enable_if<!ft::is_integral<InputIterator>::value >::type* = 0){
            erase(begin(), end());
            insert(begin(), first, ++last);
          }
        void assign (size_type n, const value_type& val){
            erase(begin(), end());
            insert(begin(), n, val);
        }
        // push_back
        void push_back (const value_type& val){
            if (_size == _capacity){
                if (_capacity == 0)
                    reserve(1);
                else
                    reserve(_capacity * 2);
            }
            _alloc.construct(_arr + _size, val);
            ++_size;
        }
        // pop_back
        void pop_back(){
            if (_size) {
                --_size;
                _alloc.destroy(_arr + _size);
            }
        }
        // insert
        iterator insert (iterator position, const value_type& val){
            return (push_val(position, val));
        }

        void insert (iterator position, size_type n, const value_type& val){
            for(size_type i = 0; i < n; ++i)
                push_val(position, val);
        }
        template <class InputIterator>
            void insert (iterator position, InputIterator first, InputIterator last,
                         typename ft::enable_if<!ft::is_integral<InputIterator>::value >::type* = 0) {
            iterator it = begin();
            size_type pos_it = 0;
            while (it != position && it != end()) {
                ++pos_it;
                ++it;
            }
            while (first != last){
                it = begin();
                for (size_type i = 0; i < pos_it; i++, it++);
                push_val(it, *first);
                ++first;
            }
        }
        // erase
        iterator erase (iterator position){
            _alloc.destroy(&(*position));
            for(iterator p = position; p != end(); ++p){
                    _alloc.construct(&(*p),*(p + 1));
                    _alloc.destroy(&(*(p + 1)));
            }
            --_size;
            return (position);

        }
        iterator erase (iterator first, iterator last){
            for(iterator p = first; p != last; ++p) {
                _alloc.destroy(&(*p));
            }
            iterator i = first;
            for(iterator p = last; p != end(); ++p){
                _alloc.construct(&(*i), *p);
                _alloc.destroy(&(*p));
                ++i;
            }
            _size -= (last - first);
            return (first);
        }
        //swap
        void swap (vector& x){
            if (x != *this){
                pointer         save_arr = _arr;
                size_type       save_size = _size;
                size_type       save_capacity = _capacity;
                allocator_type  save_alloc = _alloc;

                _arr = x._arr;
                _size = x._size;
                _capacity = x._capacity;
                _alloc = x._alloc;

                x._arr = save_arr;
                x._size = save_size;
                x._capacity = save_capacity;
                x._alloc = save_alloc;
            }
        }
        //clear
        void clear(){
            for(; _size != 0 ; --_size)
                _alloc.destroy(_arr + (_size - 1));
        }

        /*
         * Allocator
         */

        // get_allocator
         allocator_type get_allocator() const{
            return (_alloc);
         }

    private:
        iterator push_val(iterator position, const value_type &val){
            size_type pos = get_position(position);
             if(_size + 1 >= _capacity)
                reserve(_capacity * 2);
            array_shift(iterator(_arr + pos));
            _size++;
            _alloc.construct((_arr + pos), val);
            return (iterator(_arr + pos));
        }

        void array_shift(iterator position){
            size_type count = 0;
            iterator first = begin();
            if (position == end())
                return;
            while(first != position && first != end()) {
                first++;
                count++;
            }
            value_type next;
            for (value_type current = _arr[count]; count < _size; count++) {
                next = _arr[count + 1];
                _arr[count + 1] = current;
                current = next;
            }
        }

        size_type get_position(iterator it) {
            iterator new_it = begin();
            size_type i = 0;
            while(new_it != it && new_it != end()){
                ++new_it;
                ++i;
            }
            return (i);
        }
    };
         /*
          * Non-member function overloads
          */

         //  relational operators
         template <class T, class Alloc>
           bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs){
             if (lhs.size() != rhs.size())
                 return (false);
             for (size_t i = 0; i < lhs.size(); ++i)
                 if (lhs[i] != rhs[i])
                     return (false);
             return (true);
           }
         template <class T, class Alloc>
           bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs){
             return (!(lhs == rhs));
           }
         template <class T, class Alloc>
           bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs){
              return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
           }
         template <class T, class Alloc>
           bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs){
             return (!(rhs < lhs));
           }
         template <class T, class Alloc>
           bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs){
             return (rhs < lhs);
           }
         template <class T, class Alloc>
           bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs){
             return (!(lhs < rhs));
           }

         // swap
         template <class T, class Alloc>
           void swap (vector<T,Alloc>& x, vector<T,Alloc>& y){
               x.swap(y);
           }
}

#endif //FT_CONTAINERS_VECTOR_HPP
