#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int MOD = 998244353;

class Matrix {
public:
  vector<vector<int>> _matrix;
  int _rows, _cols;

  Matrix(int rows, int cols) : _rows(rows), _cols(cols) { _matrix.resize(rows, vector<int>(cols)); }
  Matrix(const vector<vector<int>>& mat) : _cols(mat[0].size()), _rows(mat.size()), _matrix(mat) {}
  Matrix(const Matrix& matrix) : _cols(matrix._cols), _rows(matrix._rows), _matrix(matrix._matrix) {}

  Matrix operator+(const Matrix& matrix) const {
    assert(_rows == matrix._rows && _cols == matrix._cols);

    Matrix result(_rows, _cols);
    for (int i = 0; i < _rows; ++i) {
      for (int j = 0; j < _cols; ++j) {
        result._matrix[i][j] = (_matrix[i][j] + matrix._matrix[i][j]) % MOD;
      }
    }

    return result;
  }

  Matrix operator-(const Matrix& matrix) const {
    assert(_rows == matrix._rows && _cols == matrix._cols);

    Matrix result(_rows, _cols);
    for (int i = 0; i < _rows; ++i) {
      for (int j = 0; j < _cols; ++j) {
        result._matrix[i][j] = (_matrix[i][j] - matrix._matrix[i][j] + MOD) % MOD;
      }
    }

    return result;
  }

  Matrix operator*(const Matrix& matrix) const {
    assert(_cols == matrix._rows);

    Matrix result(_rows, matrix._cols);
    for (int i = 0; i < _rows; ++i) {
      for (int j = 0; j < matrix._cols; ++j) {
        for (int k = 0; k < _cols; ++k) {
          result._matrix[i][j] = (result._matrix[i][j] + (1LL * _matrix[i][k] * matrix._matrix[k][j]) % MOD) % MOD;
        }
      }
    }

    return result;
  }

  Matrix& operator+=(const Matrix& matrix) { return *this = *this + matrix; }
  Matrix& operator-=(const Matrix& matrix) { return *this = *this - matrix; }
  Matrix& operator*=(const Matrix& matrix) { return *this = *this * matrix; }
  bool operator==(const Matrix& matrix) const { return _matrix == matrix._matrix; }
  bool operator!=(const Matrix& matrix) const { return _matrix != matrix._matrix; }

  static Matrix identity(int size) {
    Matrix result(size, size);
    for (int i = 0; i < size; ++i) {
      result._matrix[i][i] = 1;
    }

    return result;
  }

  Matrix power(long long exp) const {
    assert(_rows == _cols);

    Matrix result = identity(_rows);
    Matrix base = *this;

    while (exp) {
      if (exp & 1) {
        result = result * base;
      }
      base = base * base;
      exp >>= 1;
    }

    return result;
  }
};

int32_t main() {
  ios_base::sync_with_stdio(false); cin.tie(0);

  int n; cin >> n;
  ll k; cin >> k;

  vector<vector<int>> mat(n, vector<int>(n));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      cin >> mat[i][j];
    }
  }

  Matrix matrix(mat);
  Matrix result = matrix.power(k);

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      cout << result._matrix[i][j] << ' ';
    }
    cout << '\n';
  }
    
  return 0;
}

// Problem Link: https://judge.yosupo.jp/problem/pow_of_matrix
