#ifndef SIMPLE_INCLUDE_SIMPLE_H_
#define SIMPLE_INCLUDE_SIMPLE_H_

#include "types.h"

/** This class is used to test
 *   * simple bindings
 *   * default parameters
 *   * overloaded methods.
 */
class Simple {

  double value_;
public:
  Simple(double v) : value_(v) {}
  
  ~Simple() {}

  double value() {
    return value_;
  }

  /** Test typedef resolution in methods and
   * default values in arguments.
   */
  MyFloat add(MyFloat v, double w = 10) {
    return v + w;
  }

  /** Test method overloading with default parameters.
   */
  Simple add(const Simple &o) {
    return Simple(value_ + o.value_);
  }

  /** Method overloading without default parameters.
   */
  Simple mul(const Simple &o) {
    return Simple(value_ * o.value_);
  }

  double mul(double d) {
    return value_ * d;
  }

  double mul(double d, double d2) {
    return d * d2;
  }

  double mul() {
    return 0;
  }

  void setValue(double v) {
    value_ = v;
  }

  /** To test simple static methods.
   */
  static double pi() {
    return 3.14;
  }

  bool isZero() {
    return value_ == 0;
  }
};

#endif // SIMPLE_INCLUDE_SIMPLE_H_
