/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.h"

#include <iostream>

#include <frc/smartdashboard/SmartDashboard.h>

void Robot::RobotInit() {
  std::cout << "Test 1" << std::endl;
  
  m_chooser.SetDefaultOption(kAutoNameDefault, kAutoNameDefault);
  m_chooser.AddOption(kAutoNameCustom, kAutoNameCustom);
  frc::SmartDashboard::PutData("Auto Modes", &m_chooser);

  joystick_1 = new frc::Joystick(0);

  std::cout << "Motor Initialization" << std::endl;

  left_motor_1 = new WPI_TalonSRX(1);
  left_motor_2 = new WPI_TalonSRX(4);

  right_motor_1 = new WPI_TalonSRX(2);
  right_motor_2 = new WPI_TalonSRX(6);

  std::cout << "Motors are initialized" << std::endl;
}

void Robot::DreadbotTankDrive(double y_axis, double rot_axis, bool turbo_button, bool turtle_button)
{
  std::cout << "whoa" << std::endl;
  // Remove any possibility of Joystick Deadband.
  // Essentially, if the joystick input is within
  // the range of the considered deadband (-0.2 to 0.2),
  // Consider the input as 0.0
  y_axis = (fabs(y_axis) < kJoystickDeadband) ? 0 : y_axis;
  rot_axis = (fabs(rot_axis) < kJoystickDeadband) ? 0 : rot_axis;

  // Set the speed mode from turbo_button and turtle_button.
  // In the case that both turtle mode and turbo mode are
  // both enabled, turbo mode overrides turtle. 
  // (This can absolutely be changed if needed)
  if(turbo_button)
  {
    current_speed = kTurboSpeed;
  } else if(turtle_button)
  {
    current_speed = kTurtleSpeed;
  } else 
  {
    current_speed = kNormalSpeed;
  }

  // Multiply the axes by the current speed setting
  // the -2 for rotation speed is simply because it
  // takes more force to turn due to friction, so we
  // use twice the speed.
  y_speed = y_axis * current_speed;
  rot_speed = -2 * rot_axis * current_speed;

  // Calculating Final Speed by adding both the
  // Forward/Backward speed (y_speed) and Rotation
  // Speeds (rot_speed)
  left_final_speed = -y_speed + rot_speed;
  right_final_speed = y_speed + rot_speed;

  // Setting the final speed to a max of 100%
  // To prevent any errors if we reach the limit.
  // Essentially, if out of bounds, set it to the
  // most extreme bounds to prevent errors.
  left_final_speed = (left_final_speed > 1.0) ? 1.0 : left_final_speed;
  left_final_speed = (left_final_speed < -1.0) ? -1.0 : left_final_speed;
  right_final_speed = (right_final_speed > 1.0) ? 1.0 : right_final_speed;
  right_final_speed = (right_final_speed < -1.0) ? -1.0 : right_final_speed;
  
  // Set Motor Speeds to the final speeds calculated.
  left_motor_1->Set(ControlMode::PercentOutput, left_final_speed);
  left_motor_2->Set(ControlMode::PercentOutput, left_final_speed);
  right_motor_1->Set(ControlMode::PercentOutput, right_final_speed);
  right_motor_2->Set(ControlMode::PercentOutput, right_final_speed);
}

/**
 * This function is called every robot packet, no matter the mode. Use
 * this for items like diagnostics that you want ran during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void Robot::RobotPeriodic() {}

/**
 * This autonomous (along with the chooser code above) shows how to select
 * between different autonomous modes using the dashboard. The sendable chooser
 * code works with the Java SmartDashboard. If you prefer the LabVIEW Dashboard,
 * remove all of the chooser code and uncomment the GetString line to get the
 * auto name from the text box below the Gyro.
 *
 * You can add additional auto modes by adding additional comparisons to the
 * if-else structure below with additional strings. If using the SendableChooser
 * make sure to add them to the chooser code above as well.
 */
void Robot::AutonomousInit() {
  m_autoSelected = m_chooser.GetSelected();
  // m_autoSelected = SmartDashboard::GetString("Auto Selector",
  //     kAutoNameDefault);
  std::cout << "Auto selected: " << m_autoSelected << std::endl;

  if (m_autoSelected == kAutoNameCustom) {
    // Custom Auto goes here
  } else {
    // Default Auto goes here
  }
}

void Robot::AutonomousPeriodic() {
  if (m_autoSelected == kAutoNameCustom) {
    // Custom Auto goes here
  } else {
    // Default Auto goes here
  }
}

void Robot::TeleopInit() {}

void Robot::TeleopPeriodic() 
{
  std::cout << "prewoah" << std::endl;

  DreadbotTankDrive(
    joystick_1->GetRawAxis(y_axis), 
    joystick_1->GetRawAxis(z_axis), 
    joystick_1->GetRawButton(right_bumper), 
    joystick_1->GetRawButton(left_bumper)
  );
}

void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
