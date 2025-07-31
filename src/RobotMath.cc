#include "RobotMath.h"
#include <iostream>

void RobotMath::AddJoint(const Joint& joint) {
  if (std::isnan(joint.theta)) {
    std::cout << "Invalid joint angle\n";
    return;
  }
  m_Joints.push_back(joint);
}

auto RobotMath::ComputeSingleJointTransform(const Joint& joint) const -> sla::mat4 {
  sla::mat4 T(1.0);
  double theta_rad = joint.theta * M_PI / 180.0;
  double ct = std::cos(theta_rad);
  double st = std::sin(theta_rad);
  double ca = std::cos(joint.alpha);
  double sa = std::sin(joint.alpha);

  T[0][0] = ct;
  T[0][1] = -ca * st;
  T[0][2] = sa * st;
  T[0][3] = joint.a * ct;

  T[1][0] = st;
  T[1][1] = ca * ct;
  T[1][2] = -sa * ct;
  T[1][3] = joint.a * st;

  T[2][0] = 0.0;
  T[2][1] = sa;
  T[2][2] = ca;
  T[2][3] = joint.d;

  T[3][0] = 0.0;
  T[3][1] = 0.0;
  T[3][2] = 0.0;
  T[3][3] = 1.0;

  T.print();
  return T;
}

auto RobotMath::ComputeForwardKinematics() const -> sla::vec3 {
  if (m_Joints.empty()) {
    std::cout << "[Warning] Empty list of joints" << '\n';
    return {};
  }
  sla::mat4 T(1.0);

  for (const auto& joint : m_Joints) {
    T = T * ComputeSingleJointTransform(joint);
  }

  T.print();

  return {T[0][3], T[1][3], T[2][3]};
}