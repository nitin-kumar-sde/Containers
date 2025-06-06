#pragma once
#include <cstddef>
#include <utility>

namespace mystl {

template <std::size_t Index, typename T>
struct tuple_leaf {
    T value;

    tuple_leaf() = default;

    template <typename U>
    tuple_leaf(U&& val) : value(std::forward<U>(val)) {}
};

template <std::size_t Index, typename... Types>
struct tuple_impl;

template <std::size_t Index, typename Head, typename... Tail>
struct tuple_impl<Index, Head, Tail...>
    : public tuple_leaf<Index, Head>,
      public tuple_impl<Index + 1, Tail...> {

    tuple_impl() = default;

    template <typename H, typename... T>
    tuple_impl(H&& h, T&&... t)
        : tuple_leaf<Index, Head>(std::forward<H>(h)),
          tuple_impl<Index + 1, Tail...>(std::forward<T>(t)...) {}
};


template <std::size_t Index>
struct tuple_impl<Index> {};


template <typename... Types>
class tuple : public tuple_impl<0, Types...> {
public:
    tuple() = default;

    template <typename... Args>
    tuple(Args&&... args)
        : tuple_impl<0, Types...>(std::forward<Args>(args)...) {}
};

template <std::size_t N, typename T>
T& get_leaf(tuple_leaf<N, T>& leaf) {
    return leaf.value;
}

template <std::size_t N, typename T>
const T& get_leaf(const tuple_leaf<N, T>& leaf) {
    return leaf.value;
}

template <std::size_t N, typename... Types>
auto& get(tuple<Types...>& t) {
    return get_leaf<N>(t);
}

template <std::size_t N, typename... Types>
const auto& get(const tuple<Types...>& t) {
    return get_leaf<N>(t);
}

template <typename... Args>
tuple<Args...> make_tuple(Args&&... args) {
    return tuple<Args...>(std::forward<Args>(args)...);
}

}
