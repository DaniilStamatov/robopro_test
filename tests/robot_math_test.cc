#include <gtest/gtest.h>
#include <cmath>
#include "RobotMath.h"

const float EPSILON = 1e-5f;

TEST(RobotMathTest, TwoJointRightAngle) {
  RobotMath rm;
  rm.AddJoint({.theta = 0.0, .a = 1.0, .d = 0.0, .alpha = 0.0});
  rm.AddJoint({.theta = 0.0, .a = 1.0, .d = 0.0, .alpha = M_PI_2});
  auto result = rm.ComputeForwardKinematics();

  EXPECT_NEAR(result.x, 2.0, EPSILON);
  EXPECT_NEAR(result.y, 0.0, EPSILON);
  EXPECT_NEAR(result.z, 0.0, EPSILON);
}

TEST(RobotMathTest, TwoJointRightAngleReverse) {
  RobotMath rm;
  rm.AddJoint({.theta = 0.0, .a = 1.0, .d = 0.0, .alpha = 0.0});
  rm.AddJoint({.theta = 90.0, .a = 1.0, .d = 0.0, .alpha = M_PI_2});
  auto result = rm.ComputeForwardKinematics();

  EXPECT_NEAR(result.x, 1.0, EPSILON);
  EXPECT_NEAR(result.y, 1.0, EPSILON);
  EXPECT_NEAR(result.z, 0.0, EPSILON);
}

TEST(RobotMathTest, OneJointForward) {
  RobotMath rm;
  rm.AddJoint({.theta = 0.0, .a = 1.0, .d = 0.0, .alpha = 0.0});

  auto result = rm.ComputeForwardKinematics();

  EXPECT_DOUBLE_EQ(result.x, 1.0);
  EXPECT_DOUBLE_EQ(result.y, 0.0);
  EXPECT_DOUBLE_EQ(result.z, 0.0);
}

TEST(RobotMathTest, SixJoints) {
  RobotMath robot;
  robot.AddJoint({15.0, 0.0, 0.213, M_PI / 2});
  robot.AddJoint({-50.0, -0.8, 0.193, 0.0});
  robot.AddJoint({-60.0, -0.59, -0.16, 0.0});
  robot.AddJoint({95.0, 0.0, 0.25, M_PI / 2});
  robot.AddJoint({50.0, 0.0, 0.28, -M_PI / 2});
  robot.AddJoint({0.0, 0.0, 0.25, 0.0});

  auto result = robot.ComputeForwardKinematics();

  EXPECT_NEAR(result[0], -0.435637, EPSILON);
  EXPECT_NEAR(result[1], -0.576077, EPSILON);
  EXPECT_NEAR(result[2], 1.15936, EPSILON);
}

TEST(RobotMathTest, ThreeJointStraightLine) {
  RobotMath rm;
  rm.AddJoint({.theta = 0.0, .a = 1.0, .d = 0.0, .alpha = 0.0});
  rm.AddJoint({.theta = 90.0, .a = 1.0, .d = 0.0, .alpha = M_PI_2});
  rm.AddJoint({.theta = 0.0, .a = 1.0, .d = 0.0, .alpha = 0.0});
  auto result = rm.ComputeForwardKinematics();

  EXPECT_NEAR(result[0], 1.0, EPSILON);
  EXPECT_NEAR(result[1], 2.0, EPSILON);
  EXPECT_NEAR(result[2], 0.0, EPSILON);
}