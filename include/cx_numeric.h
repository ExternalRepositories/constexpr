#pragma once

#include <cstddef>
#include <utility>

//----------------------------------------------------------------------------
// constexpr numeric algorithms

namespace cx
{

  // accumulate
  template <typename It, typename T>
  constexpr T accumulate(It first, It last, T init)
  {
    return first == last ? init :
      accumulate(first + 1, last, init + *first);
  }

  template <typename It, typename T, typename BinaryOp>
  constexpr T accumulate(It first, It last, T init, BinaryOp op)
  {
    return first == last ? init :
      accumulate(first + 1, last, op(init, *first), op);
  }

  // inner_product
  template <typename It1, typename It2, typename T>
  constexpr T inner_product(It1 first1, It1 last1, It2 first2, T value)
  {
    return 
      first1 == last1 ? value :
      inner_product(first1 + 1, last1, first2 + 1,
                    value + *first1 * *first2);
  }

  template <typename It1, typename It2, typename T,
            typename BinaryOp1, typename BinaryOp2>
  constexpr T inner_product(It1 first1, It1 last1, It2 first2, T value,
                            BinaryOp1 op1, BinaryOp2 op2)
  {
    return first1 == last1 ? value :
      inner_product(first1 + 1, last1, first2 + 1,
                    op1(value, op2(*first1, *first2)),
                    op1, op2);
  }
}
