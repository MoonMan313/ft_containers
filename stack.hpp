//
// Created by Cheryle Dionna on 2/20/22.
//

#ifndef FT_CONTAINERS_STACK_HPP
#define FT_CONTAINERS_STACK_HPP

#include "vector.hpp"
#include <vector>
namespace ft {
    template<class T, class Container = ft::vector<T> >
    class stack {
    public:
        typedef T value_type;
        typedef Container container_type;
        typedef size_t size_type;

        /*
         * Member functions
         */

        // (constructor)
        explicit stack(const container_type &container = container_type()) : container(container) {};

        // empty
        bool empty() const {
            return (this->container.empty());
        }

        // size
        size_type size() const {
            return (this->container.size());
        }

        // top
        value_type &top() {
            return (this->container.back());
        }

        const value_type &top() const {
            return (this->container.back());
        }

        // push
        void push(const value_type &val) {
            this->container.push_back(val);
        }

        // pop
        void pop() {
            this->container.pop_back();
        }

        template<class T_compare, class Container_compare>
        friend bool
        operator==(const stack<T_compare, Container_compare> &lhs, const stack<T_compare, Container_compare> &rhs);

        template<class T_compare, class Container_compare>
        friend bool
        operator!=(const stack<T_compare, Container_compare> &lhs, const stack<T_compare, Container_compare> &rhs);

        template<class T_compare, class Container_compare>
        friend bool
        operator<(const stack<T_compare, Container_compare> &lhs, const stack<T_compare, Container_compare> &rhs);

        template<class T_compare, class Container_compare>
        friend bool
        operator<=(const stack<T_compare, Container_compare> &lhs, const stack<T_compare, Container_compare> &rhs);

        template<class T_compare, class Container_compare>
        friend bool
        operator>(const stack<T_compare, Container_compare> &lhs, const stack<T_compare, Container_compare> &rhs);

        template<class T_compare, class Container_compare>
        friend bool
        operator>=(const stack<T_compare, Container_compare> &lhs, const stack<T_compare, Container_compare> &rhs);

    protected:
        container_type container;
    };

    template<class T, class Container>
    bool operator==(const stack<T, Container> &lhs, const stack<T, Container> &rhs) {
        return (lhs.container == rhs.container);
    };

    template<class T, class Container>
    bool operator!=(const stack<T, Container> &lhs, const stack<T, Container> &rhs) {
        return (lhs.container != rhs.container);
    };

    template<class T, class Container>
    bool operator<(const stack<T, Container> &lhs, const stack<T, Container> &rhs) {
        return (lhs.container < rhs.container);
    };

    template<class T, class Container>
    bool operator<=(const stack<T, Container> &lhs, const stack<T, Container> &rhs) {
        return (lhs.container <= rhs.container);
    };

    template<class T, class Container>
    bool operator>(const stack<T, Container> &lhs, const stack<T, Container> &rhs) {
        return (lhs.container > rhs.container);
    };

    template<class T, class Container>
    bool operator>=(const stack<T, Container> &lhs, const stack<T, Container> &rhs) {
        return (lhs.container >= rhs.container);
    };
}
#endif //FT_CONTAINERS_STACK_HPP
