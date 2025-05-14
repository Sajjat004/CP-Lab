#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int MOD = 998244353;

class MatrixExpo {
public:
  vector<vector<int>> matrix;
  int rows, cols;

  MatrixExpo(int rows, int cols) : rows(rows), cols(cols) { matrix.resize(rows, vector<int>(cols)); }
  MatrixExpo(const vector<vector<int>>& mat) : rows(mat.size()), cols(mat[0].size()), matrix(mat) {}
  MatrixExpo(const MatrixExpo& other) : rows(other.rows), cols(other.cols), matrix(other.matrix) {}

  MatrixExpo operator+(const MatrixExpo& other) const {
    assert(rows == other.rows && cols == other.cols);

    MatrixExpo result(rows, cols);
    for (int i = 0; i < rows; ++i) {
      for (int j = 0; j < cols; ++j) {
        result.matrix[i][j] = (matrix[i][j] + other.matrix[i][j]) % MOD;
      }
    }

    return result;
  }

  MatrixExpo operator-(const MatrixExpo& other) const {
    assert(rows == other.rows && cols == other.cols);

    MatrixExpo result(rows, cols);
    for (int i = 0; i < rows; ++i) {
      for (int j = 0; j < cols; ++j) {
        result.matrix[i][j] = (matrix[i][j] - other.matrix[i][j] + MOD) % MOD;
      }
    }

    return result;
  }

  MatrixExpo operator*(const MatrixExpo& other) const {
    assert(cols == other.rows);

    MatrixExpo result(rows, other.cols);
    for (int i = 0; i < rows; ++i) {
      for (int j = 0; j < other.cols; ++j) {
        for (int k = 0; k < cols; ++k) {
          result.matrix[i][j] = (result.matrix[i][j] + (1LL * matrix[i][k] * other.matrix[k][j]) % MOD) % MOD;
        }
      }
    }

    return result;
  }

  MatrixExpo& operator+=(const MatrixExpo& other) { return *this = *this + other; }
  MatrixExpo& operator-=(const MatrixExpo& other) { return *this = *this - other; }
  MatrixExpo& operator*=(const MatrixExpo& other) { return *this = *this * other; }
  bool operator==(const MatrixExpo& other) const { return matrix == other.matrix; }
  bool operator!=(const MatrixExpo& other) const { return matrix != other.matrix; }

  static MatrixExpo identity(int size) {
    MatrixExpo result(size, size);
    for (int i = 0; i < size; ++i) {
      result.matrix[i][i] = 1;
    }

    return result;
  }

  MatrixExpo power(long long exp) const {
    assert(rows == cols);

    MatrixExpo result = identity(rows);
    MatrixExpo base = *this;

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

  MatrixExpo matrix(mat);
  MatrixExpo result = matrix.power(k);

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      cout << result.matrix[i][j] << ' ';
    }
    cout << '\n';
  }
    
  return 0;
}

// Problem Link: https://judge.yosupo.jp/problem/pow_of_matrix
