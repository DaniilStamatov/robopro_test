
#pragma once
#include <array>
#include <cmath>
#include <iostream>
namespace sla {

struct vec3 {
  vec3() : x(0.0f), y(0.0f), z(0.0f) {}

  vec3(double x_, double y_, double z_) : x(x_), y(y_), z(z_) {}

  vec3(const vec3& other) = default;

  auto operator[](int n) const -> const double& {
    switch (n) {
      case 0:
        return x;
      case 1:
        return y;
      case 2:
        return z;
      default:
        throw std::out_of_range("Index out of range");
    }
  }

  auto operator[](int n) -> double& {
    switch (n) {
      case 0:
        return x;
      case 1:
        return y;
      case 2:
        return z;
      default:
        throw std::out_of_range("Index out of range");
    }
  }

  void print() const { std::cout << "vec3(" << x << ", " << y << ", " << z << ")"; }

  double x, y, z;
};

struct vec4 {
  vec4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}
  vec4(double x_, double y_, double z_, double w_) : x(x_), y(y_), z(z_), w(w_) {}
  vec4(const vec4& other) = default;
  auto operator[](int n) const -> const double& {
    switch (n) {
      case 0:
        return x;
      case 1:
        return y;
      case 2:
        return z;
      case 3:
        return w;
      default:
        throw std::out_of_range("Index out of range");
    }
  }

  auto operator[](int n) -> double& {
    switch (n) {
      case 0:
        return x;
      case 1:
        return y;
      case 2:
        return z;
      case 3:
        return w;
      default:
        throw std::out_of_range("Index out of range");
    }
  }

  double x, y, z, w;
};

struct mat4 {
  mat4(const mat4& other) = default;

  mat4() {
    mat[0] = vec4(1, 0, 0, 0);
    mat[1] = vec4(0, 1, 0, 0);
    mat[2] = vec4(0, 0, 1, 0);
    mat[3] = vec4(0, 0, 0, 1);
  }

  mat4(double val) {
    mat[0] = vec4(val, 0, 0, 0);
    mat[1] = vec4(0, val, 0, 0);
    mat[2] = vec4(0, 0, val, 0);
    mat[3] = vec4(0, 0, 0, val);
  }

  auto operator[](int row) -> vec4& { return mat[row]; }

  auto operator*(const mat4& other) const -> mat4 {
    mat4 result;

    for (int i = 0; i < 4; ++i) {
      for (int j = 0; j < 4; ++j) {
        result[i][j] = 0;
        for (int k = 0; k < 4; ++k) {
          result[i][j] += mat[i][k] * other[k][j];
        }
      }
    }

    return result;
  }

  auto operator[](int row) const -> const vec4& { return mat[row]; }

  [[nodiscard]] auto GetData() const -> const double* { return &mat[0].x; }

  void print() const {
    std::cout << "[Matrix] [\n";
    for (int i = 0; i < 4; ++i) {
      std::cout << mat[i][0] << ", " << mat[i][1] << ", " << mat[i][2] << ", " << mat[i][3] << ";\n";
    }
    std::cout << "]\n";
  }

  std::array<vec4, 4> mat;
};
}  // namespace sla