#ifndef POINTERS_VECT_H_
#define POINTERS_VECT_H_

#include <cstdio>
#include <cstring> // size_t
#define MAX_DIM 3

/** This class is used to test:
 *   * accessing public attributes
 *   * return value optimization
 *   * basic memory leakage
 *   * operator overloading
 *   * C array attributes
 *   * unamed and void parameters
 *   * ignore attributes
 *
 * @dub ignore: z
 */
struct Vect {
  double x;
  double y;
  double z;

  double d[MAX_DIM];

  // static member access
  static size_t create_count;
  static size_t copy_count;
  static size_t destroy_count;

  Vect(double tx, double ty)
    : x(tx)
    , y(ty) {
    // to test return value optimization.
    // and memory leakage.
    ++create_count;
    for (size_t i=0; i<MAX_DIM; ++i)
      d[i] = i + 1 + tx + ty;
  }

  Vect(const Vect &v)
    : x(v.x)
    , y(v.y) {
    // To test return value optimization.
    // and memory leakage.
    ++copy_count;
  }

  Vect(const Vect *v)
    : x(v->x)
    , y(v->y) {
    // To test return value optimization.
    // and memory leakage.
    ++copy_count;
  }

  ~Vect() {
    // To test return value optimization.
    // and memory leakage.
    ++destroy_count;
  }

  double surface() const {
    return x * y;
  }

  // operator overloading

  void operator=(const Vect &v) {
    x = v.x;
    y = v.y;
  }

  Vect operator+(const Vect &v) {
    return Vect(x + v.x, y + v.y);
  }

  void operator+=(const Vect &v) {
    x += v.x;
    y += v.y;
  }

  Vect operator-(const Vect &v) {
    return Vect(x - v.x, y - v.y);
  }

  /** Unary minus.
   */
  Vect operator-() {
    return Vect(-x, -y);
  }

  void operator-=(const Vect &v) {
    x -= v.x;
    y -= v.y;
  }

  Vect operator*(double d) {
    return Vect(d*x, d*y);
  }

  // overloaded operators
  // cross product
  double operator*(const Vect &v) {
    return x*v.y - y*v.x;
  }

  Vect operator/(double d) {
    return Vect(x/d, y/d);
  }

  bool operator<(const Vect &s) {
    return surface() < s.surface();
  }

  bool operator<=(const Vect &s) {
    return surface() <= s.surface();
  }

  bool operator==(const Vect &s) {
    return s.x == x && s.y == y;
  }

  // return element at position i
  double operator()(int i) {
    if (i == 1) {
      return x;
    } else if (i == 2) {
      return y;
    } else {
      return 0;
    }
  }

  // return element at position i
  double operator[](int i) {
    if (i == 1) {
      return x;
    } else if (i == 2) {
      return y;
    } else {
      return 0;
    }
  }

  // unknown operator should be ignored.
  Vect& operator=( int px ) {
    x = px;
    return *this;
  }

  // char mapped to number
  char someChar(char c) {
    return c;
  }

  // const char * mapped to string
  const char *someStr(const char *s) {
    return s;
  }

  /** Unamed parameters.
   */
  double unamed(double, int);

  int noparam(void) {
    return 1;
  }
};


#endif // POINTERS_VECT_H_

