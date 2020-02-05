/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <string>

#include <frc/TimedRobot.h>
#include <frc/smartdashboard/SendableChooser.h>

#include <frc/Joystick.h>

#include <ctre/Phoenix.h>

#include "RobotUtilities.h"

class Robot : public frc::TimedRobot {
 public:
  void RobotInit() override;
  void RobotPeriodic() override;
  void AutonomousInit() override;
  void AutonomousPeriodic() override;
  void TeleopInit() override;
  void TeleopPeriodic() override;
  void TestPeriodic() override;

  void DreadbotTankDrive(double y_axis, double rot_axis, bool turbo_button, bool turtle_button);

 private:
  frc::SendableChooser<std::string> m_chooser;
  const std::string kAutoNameDefault = "Default";
  const std::string kAutoNameCustom = "My Auto";
  std::string m_autoSelected;

  WPI_TalonSRX* left_motor_1;
  WPI_TalonSRX* left_motor_2;

  WPI_TalonSRX* right_motor_1;
  WPI_TalonSRX* right_motor_2;

  frc::Joystick* joystick_1;

  double const kTurtleSpeed = 0.2;
  double const kNormalSpeed = 0.4;
  double const kTurboSpeed = 0.8;

  double current_speed = 0.0;

  const double kJoystickDeadband = 0.2;

  double y_speed;
  double rot_speed;

  double left_final_speed;
  double right_final_speed;
};
