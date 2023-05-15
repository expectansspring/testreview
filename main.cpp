#include <iostream>
#include <vector>

template<typename T>
class Matrix {
 public:
  size_t n, m;
  std::vector<std::vector<T>> matrix;

  Matrix(size_t n_, size_t m_, std::vector<std::vector<T>> &matrix_) {
    n = n_, m = m_;
    for (size_t i = 0; i < n; ++i) {
      std::vector<T> temporary;
      for (size_t j = 0; j < m; ++j) {
        temporary.push_back(matrix_[i][j]);
      }
      matrix.push_back(temporary);
    }
  }

  Matrix<T> &operator=(const Matrix<int> &matrix_) {
    if (this->n == matrix_.n && this->m == matrix_.m) {
      for (size_t i = 0; i < this->n; ++i) {
        for (size_t j = 0; j < this->m; ++j) {
          this->matrix[i][j] = matrix_.matrix[i][j];
        }
      }
    } else {
      std::cerr << "Error: Matrices of different sizes" << std::endl;
    }
    return *this;
  }

  Matrix<T> &operator+(const Matrix<int> &matrix_) {
    if (this->n == matrix_.n && this->m == matrix_.m) {
      for (size_t i = 0; i < this->n; ++i) {
        for (size_t j = 0; j < this->m; ++j) {
          this->matrix[i][j] += matrix_.matrix[i][j];
        }
      }
    } else {
      std::cerr << "Error: Matrices of different sizes" << std::endl;
    }
    return *this;
  }

  Matrix<T> &operator-(const Matrix<int> &matrix_) {
    if (this->n == matrix_.n && this->m == matrix_.m) {
      for (size_t i = 0; i < this->n; ++i) {
        for (size_t j = 0; j < this->m; ++j) {
          this->matrix[i][j] -= matrix_.matrix[i][j];
        }
      }
    } else {
      std::cerr << "Error: Matrices of different sizes" << std::endl;
    }
    return *this;
  }

  bool operator==(const Matrix<int> &matrix_) {
    bool flag = true;
    if (this->n == matrix_.n && this->m == matrix_.m) {
      for (size_t i = 0; i < this->n; ++i) {
        for (size_t j = 0; j < this->m; ++j) {
          if (this->matrix[i][j] != matrix_.matrix[i][j]) {
            flag = false;
            break;
          }
        }
        if (!flag) {
          break;
        }
      }
      return flag;
    } else {
      std::cerr << "Error: Matrices of different sizes" << std::endl;
      return false;
    }
  }

  bool operator==(size_t value) {
    bool flag = true;
    if (this->m == this->n) {
      if (value == 1) {
        for (size_t i = 0; i < this->n; ++i) {
          for (size_t j = 0; j < this->m; ++j) {
            if (i == j && this->matrix[i][j] != 1) {
              flag = false;
              break;
            } else if (i != j && this->matrix[i][j] != 0) {
              flag = false;
              break;
            }
          }
          if (!flag) {
            break;
          }
        }
        return flag;
      } else if (value == 0) {
        for (size_t i = 0; i < this->n; ++i) {
          for (size_t j = 0; j < this->m; ++j) {
            if (this->matrix[i][j] != 0) {
              flag = false;
              break;
            }
          }
          if (!flag) {
            break;
          }
        }
        return flag;
      } else {
        std::cerr << "Error: Value entered incorrectly" << std::endl;
        return false;
      }
    } else {
      std::cerr << "Error: The matrix is not square" << std::endl;
      return false;
    }
  }

  Matrix<T> &operator*(T value) {
    for (size_t i = 0; i < this->n; ++i) {
      for (size_t j = 0; j < this->m; ++j) {
        this->matrix[i][j] *= value;
      }
    }
    return *this;
  }

  Matrix<T> &operator*(const Matrix<T> &matrix_) {
    if (this->m == matrix_.n) {
      std::vector<std::vector<T>> temporary;
      for (size_t i = 0; i < this->n; ++i) {
        std::vector<T> vector1 = matrix[i];
        std::vector<T> result;
        for (size_t j = 0; j < matrix_.m; ++j) {
          std::vector<T> vector2;
          for (size_t k = 0; k < matrix_.n; ++k) {
            vector2.push_back(matrix_.matrix[k][j]);
          }
          T sum = 0;
          for (size_t h = 0; h < this->m; ++h) {
            sum += vector1[h] * vector2[h];
          }
          result.push_back(sum);
        }
        temporary.push_back(result);
      }
      this->matrix.clear();
      for (size_t i = 0; i < this->n; ++i) {
        this->matrix[i] = temporary[i];
      }
      this->m = matrix_.m;
    } else {
      std::cerr << "Error: Matrices of unsuitable size" << std::endl;
    }
    return *this;
  }

  void changeMatrix(size_t n_, size_t m_, T value) {
    matrix[n_][m_] = value;
  }

  static Matrix<T>& unitMatrix(size_t n_) {
    Matrix<T> matrix_;
    matrix_.n = n_, matrix_.m = n_;
    for (size_t i = 0; i < matrix_.n; ++i) {
      std::vector<T> temporary;
      for (size_t j = 0; j < matrix_.m; ++j) {
        if (i == j) {
          temporary.push_back(1);
        } else {
          temporary.push_back(0);
        }
      }
      matrix_.matrix.push_back(temporary);
    }
    return *matrix_;
  }

  static Matrix<T>& zeroMatrix(size_t n_) {
    Matrix<T> matrix_;
    matrix_.n = n_, matrix_.m = n_;
    for (size_t i = 0; i < matrix_.n; ++i) {
      std::vector<T> temporary;
      for (size_t j = 0; j < matrix_.m; ++j) {
        temporary.push_back(0);
      }
      matrix_.matrix.push_back(temporary);
    }
    return *matrix_;
  }

  void printMatrix() {
    for (size_t i = 0; i < n; ++i) {
      for (size_t j = 0; j < m; ++j) {
        std::cout << matrix[i][j] << ' ';
      }
      std::cout << '\n';
    }
  }
};

int main() {
  size_t n1, m1, n2, m2;
  std::vector<std::vector<int>> vector1;
  std::vector<std::vector<int>> vector2;
  int value;
  std::cin >> n1 >> m1;
  std::cin >> n2 >> m2;
  for (size_t i = 0; i < n1; ++i) {
    std::vector<int> temporary;
    for (size_t j = 0; j < m1; ++j) {
      std::cin >> value;
      temporary.push_back(value);
    }
    vector1.push_back(temporary);
  }
  for (size_t i = 0; i < n2; ++i) {
    std::vector<int> temporary;
    for (size_t j = 0; j < m2; ++j) {
      std::cin >> value;
      temporary.push_back(value);
    }
    vector2.push_back(temporary);
  }

  Matrix<int> matrix1(n1, m1, vector1);
  Matrix<int> matrix2(n2, m2, vector2);
//  matrix2 = matrix1;
//  matrix2 * 2;
//  matrix1 + matrix2;
//  matrix1.printMatrix();
//  matrix2.printMatrix();
//  if (matrix1 == 1) {
//    matrix1.printMatrix();
//  }
  matrix1 = matrix1 * matrix2;
  matrix1.printMatrix();
  return 0;
}
