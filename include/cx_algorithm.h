#pragma once

#include <cstddef>
#include <utility>

//----------------------------------------------------------------------------
// constexpr algorithms

namespace cx {
  template <typename It, typename T> constexpr size_t count(It first, It last, const T& value) {
    return first == last ? 0 : (*first == value) + count(first + 1, last, value);
  }

  template <typename It, typename Pred> constexpr size_t count_if(It first, It last, Pred p) {
    return first == last ? 0 : p(*first) + count_if(first + 1, last, p);
  }

  template <typename It, typename T> constexpr It find(It first, It last, const T& value) {
    return first == last || *first == value ? first : find(first + 1, last, value);
  }

  template <typename It, typename Pred> constexpr It find_if(It first, It last, Pred p) {
    return first == last || p(*first) ? first : find_if(first + 1, last, p);
  }

  template <typename It, typename Pred> constexpr It find_if_not(It first, It last, Pred p) {
    return first == last || !p(*first) ? first : find_if_not(first + 1, last, p);
  }

  template <class It, class Pred> constexpr bool all_of(It first, It last, Pred p) {
    return find_if_not(first, last, p) == last;
  }

  template <class It, class Pred> constexpr bool any_of(It first, It last, Pred p) {
    return find_if(first, last, p) != last;
  }

  template <class It, class Pred> constexpr bool none_of(It first, It last, Pred p) {
    return find_if(first, last, p) == last;
  }

  namespace detail {
    template <typename It1, typename It2> constexpr bool equal(It1 first1, It1 last1, It2 first2) {
      return first1 == last1 ? true
                             : *first1 != *first2 ? false : equal(first1 + 1, last1, first2 + 1);
    }

    template <typename It1, typename It2, typename Pred>
    constexpr bool equal(It1 first1, It1 last1, It2 first2, Pred p) {
      return first1 == last1
                 ? true
                 : !p(*first1, *first2) ? false : equal(first1 + 1, last1, first2 + 1, p);
    }
  }  // namespace detail

  template <typename It1, typename It2> constexpr bool equal(It1 first1, It1 last1, It2 first2) {
    return detail::equal(first1, last1, first2);
  }

  template <typename It1, typename It2, typename Pred>
  constexpr bool equal(It1 first1, It1 last1, It2 first2, Pred p) {
    return detail::equal(first1, last1, first2, p);
  }

  template <typename It1, typename It2>
  constexpr bool equal(It1 first1, It1 last1, It2 first2, It2 last2) {
    return (last1 - first1) != (last2 - first2) ? false : detail::equal(first1, last1, first2);
  }

  template <typename It1, typename It2, typename Pred>
  constexpr bool equal(It1 first1, It1 last1, It2 first2, It2 last2, Pred p) {
    return (last1 - first1) != (last2 - first2) ? false : detail::equal(first1, last1, first2, p);
  }

  template <typename T1, typename T2> struct pair {
    T1 first;
    T2 second;
  };

  template <typename It1, typename It2>
  constexpr pair<It1, It2> mismatch(It1 first1, It1 last1, It2 first2) {
    return (first1 == last1 || *first1 != *first2) ? pair<It1, It2>{first1, first2}
                                                   : mismatch(first1 + 1, last1, first2 + 1);
  }

  template <typename It1, typename It2, typename Pred>
  constexpr pair<It1, It2> mismatch(It1 first1, It1 last1, It2 first2, Pred p) {
    return (first1 == last1 || !p(*first1, *first2)) ? pair<It1, It2>{first1, first2}
                                                     : mismatch(first1 + 1, last1, first2 + 1);
  }

  template <typename It1, typename It2>
  constexpr pair<It1, It2> mismatch(It1 first1, It1 last1, It2 first2, It2 last2) {
    return (first1 == last1 || first2 == last2 || *first1 != *first2)
               ? pair<It1, It2>{first1, first2}
               : mismatch(first1 + 1, last1, first2 + 1, last2);
  }

  template <typename It1, typename It2, typename Pred>
  constexpr pair<It1, It2> mismatch(It1 first1, It1 last1, It2 first2, It2 last2, Pred p) {
    return (first1 == last1 || first2 == last2 || !p(*first1, *first2))
               ? pair<It1, It2>{first1, first2}
               : mismatch(first1 + 1, last1, first2 + 1, last2, p);
  }

  namespace detail {
    template <typename It, typename Pred, typename T = decltype(*std::declval<It>())>
    constexpr bool contains_match(It first, It last, T value, Pred p) {
      return first == last ? false : p(*first, value) || contains_match(first + 1, last, value, p);
    }
  }  // namespace detail

  template <typename It1, typename It2>
  constexpr It1 find_first_of(It1 first1, It1 last1, It2 first2, It2 last2) {
    return first1 == last1 || find(first2, last2, *first1) != last2
               ? first1
               : find_first_of(first1 + 1, last1, first2, last2);
  }

  template <typename It1, typename It2, typename Pred>
  constexpr It1 find_first_of(It1 first1, It1 last1, It2 first2, It2 last2, Pred p) {
    return first1 == last1 || detail::contains_match(first2, last2, *first1, p)
               ? first1
               : find_first_of(first1 + 1, last1, first2, last2, p);
  }

  template <typename It> constexpr It adjacent_find(It first, It last) {
    return last - first <= 1 ? last
                             : *first == *(first + 1) ? first : adjacent_find(first + 1, last);
  }

  template <typename It, typename Pred> constexpr It adjacent_find(It first, It last, Pred p) {
    return last - first <= 1 ? last
                             : p(*first, *(first + 1)) ? first : adjacent_find(first + 1, last, p);
  }

  template <typename It1, typename It2>
  constexpr It1 search(It1 first1, It2 last1, It2 first2, It2 last2) {
    return (last2 - first2 > last1 - first1)
               ? last1
               : equal(first2, last2, first1) ? first1 : search(first1 + 1, last1, first2, last2);
  }

  template <typename It1, typename It2, typename Pred>
  constexpr It1 search(It1 first1, It2 last1, It2 first2, It2 last2, Pred p) {
    return (last2 - first2 > last1 - first1)
               ? last1
               : equal(first2, last2, first1, p) ? first1
                                                 : search(first1 + 1, last1, first2, last2);
  }

  namespace detail {
    template <typename It, typename T> constexpr static It search_n(It first, It last, size_t count,
                                                                    const T& value,
                                                                    size_t sofar = 0) {
      return static_cast<decltype(last - first)>(count - sofar) > last - first
                 ? last
                 : sofar == count
                       ? first - sofar
                       : *first != value ? search_n(first + 1, last, count, value)
                                         : search_n(first + 1, last, count, value, sofar + 1);
    }

    template <typename It, typename T, typename Pred>
    constexpr static It search_np(It first, It last, size_t count, const T& value, Pred p,
                                  size_t sofar = 0) {
      return static_cast<decltype(last - first)>(count - sofar) > last - first
                 ? last
                 : sofar == count
                       ? first - sofar
                       : !p(*first, value) ? search_np(first + 1, last, count, value, p)
                                           : search_np(first + 1, last, count, value, p, sofar + 1);
    }
  }  // namespace detail

  template <typename It, typename T>
  constexpr It search_n(It first, It last, size_t count, const T& value) {
    return detail::search_n(first, last, count, value);
  }

  template <typename It, typename T, typename Pred>
  constexpr It search_n(It first, It last, size_t count, const T& value, Pred p) {
    return detail::search_np(first, last, count, value, p);
  }
}  // namespace cx
