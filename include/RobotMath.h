#pragma once

#include <cmath>
#include <vector>
#include "SimpleLinearAlgebra.h"

struct Joint {
  double theta;  // Угол поворота в градусах
  double a;      // Длина звена
  double d;      // Смещение звена
  double alpha;  // Угол между z-осями
};

class RobotMath {
 public:
  RobotMath() = default;
  void AddJoint(const Joint& joint);
  [[nodiscard]] auto ComputeSingleJointTransform(Joint const& joint) const -> sla::mat4;
  [[nodiscard]] auto ComputeForwardKinematics() const -> sla::vec3;

 private:
  std::vector<Joint> m_Joints;
};