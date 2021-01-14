#ifndef __T_MATRIX_H___
#define __T_MATRIX_H___

#include <assert.h>

#include <cstdlib>
#include <iostream>
#include <vector>
template<typename T>

//YOUR CODE GOES HERE!
class Matrix {
 private:
  int numRows;
  int numColumns;
  std::vector<std::vector<T> > rows;

 public:
  Matrix() : numRows(0), numColumns(0) {}
  Matrix(int r, int c) : numRows(r), numColumns(c) {
    for (int i = 0; i < numRows; i++) {
      std::vector<T> vec(c);
      rows.push_back(vec);
    }
  }
  Matrix(const Matrix<T> & rhs) :
      numRows(rhs.numRows),
      numColumns(rhs.numColumns),
      rows(rhs.rows) {}
  ~Matrix() {}
  Matrix<T> & operator=(const Matrix<T> & rhs) {
    if (this != &rhs) {
      rows.clear();
    }
    numRows = rhs.numRows;
    numColumns = rhs.numColumns;
    rows = rhs.rows;
    return *this;
  }
  int getRows() const { return numRows; }
  int getColumns() const { return numColumns; }
  const std::vector<T> & operator[](int index) const {
    assert(numRows > index && index >= 0);
    return rows[index];
  }
  std::vector<T> & operator[](int index) {
    assert(numRows > index && index >= 0);
    return rows[index];
  }
  bool operator==(const Matrix<T> & rhs) const {
    if (numRows != rhs.numRows) {
      return false;
    }
    if (numColumns != rhs.numColumns) {
      return false;
    }
    if (rows != rhs.rows) {
      return false;
    }
    return true;
  }
  Matrix<T> operator+(const Matrix<T> & rhs) const {
    assert(numRows == rhs.numRows && numColumns == rhs.numColumns);
    Matrix<T> result(numRows, numColumns);
    for (int i = 0; i < numRows; i++) {
      for (int j = 0; j < numColumns; j++) {
        result[i][j] = rows[i][j] + rhs[i][j];
      }
    }
    return result;
  }
};

template<typename T>
std::ostream & operator<<(std::ostream & s, const Matrix<T> & rhs) {
  if (rhs.getRows() == 0) {
    s << "[  ]";
    return s;
  }
  s << "[ ";
  for (int i = 0; i < rhs.getRows() - 1; i++) {
    s << rhs[i] << ",\n";
  }
  s << rhs[rhs.getRows() - 1] << " ]";
  return s;
}
template<typename T>
std::ostream & operator<<(std::ostream & s, const std::vector<T> & rhs) {
  s << "{";
  for (size_t i = 0; i < rhs.size() - 1; i++) {
    s << rhs[i] << ", ";
  }
  if (rhs.size() != 0) {
    s << rhs[rhs.size() - 1] << "}";
  }
  else {
    s << "}";
  }
  return s;
}
#endif
