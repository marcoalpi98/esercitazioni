#ifndef __SORTING_H
#define __SORTING_H

#include "iostream"
#include "list"
#include "Eigen/Eigen"
#include "map"
#include <vector>
#include <algorithm>

using namespace std;
using namespace Eigen;

namespace SortLibrary {


  struct DecreasingInt {
    int value;
    DecreasingInt() = default;
    DecreasingInt(const int& value): value(value){}

    friend std::ostream &operator<<(std::ostream &os, const DecreasingInt &obj)
  {
    os << obj.value;
    return os;
  }

  inline bool operator==(const DecreasingInt &obj) const
  {
    return value == obj.value;
  }

  inline bool operator!=(const DecreasingInt &obj) const
  {
    return !(*this == obj);
  }

  inline bool operator<(const DecreasingInt &obj) const
  {
    return value > obj.value;
  }

  inline bool operator>(const DecreasingInt &obj) const
  {
    return value < obj.value;
  }
 };


  template<typename T>
 std::vector<T> HeapSort(const vector<T>& v){
    vector<T> sortedV = v;
  std::make_heap(sortedV.begin(), sortedV.end());
    std::sort_heap(sortedV.begin(), sortedV.end());
    return sortedV;
  }

}




#endif // __SORTING_H
