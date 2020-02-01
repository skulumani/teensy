#ifndef EIGEN_TEENSY_H
#define EIGEN_TEENSY_H

#include "Arduino.h"
#include <Eigen.h>
#include <Eigen/Dense>

void print_matrixf(const Eigen::MatrixXf& K);

void test_eigen();

#endif
