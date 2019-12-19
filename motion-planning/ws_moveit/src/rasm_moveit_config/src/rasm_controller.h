#include <hardware_interface/joint_command_interface.h>
#include <hardware_interface/joint_state_interface.h>
#include <hardware_interface/robot_hw.h>
#include "ros/ros.h"
#include <std_msgs/Float64.h>
#include <iostream>
#pragma once
class MyRobot : public hardware_interface::RobotHW
{
public:
  virtual ~MyRobot(){}
  MyRobot() 
 { 
   // connect and register the joint state interface
   hardware_interface::JointStateHandle state_handle_a("A", &pos[0], &vel[0], &eff[0]);
   jnt_state_interface.registerHandle(state_handle_a);

   hardware_interface::JointStateHandle state_handle_b("B", &pos[1], &vel[1], &eff[1]);
   jnt_state_interface.registerHandle(state_handle_b);

   registerInterface(&jnt_state_interface);

   // connect and register the joint position interface
   hardware_interface::JointHandle pos_handle_a(jnt_state_interface.getHandle("A"), &cmd[0]);
   jnt_pos_interface.registerHandle(pos_handle_a);

   hardware_interface::JointHandle pos_handle_b(jnt_state_interface.getHandle("B"), &cmd[1]);
   jnt_pos_interface.registerHandle(pos_handle_b);

   registerInterface(&jnt_pos_interface);
  }
  

  class Reader
  {
  private:
    double value;
  public:
    void read(const std_msgs::Float64& msg)
    {
      value = msg.data;
    }
    double getValue()
    {
      return value;
    }
  };

  Reader shoulder;
  Reader elbow;

  void read()
  {
    this->pos[0] = shoulder.getValue();
    this->pos[1] = elbow.getValue();
  }

  friend void write();

private:
  hardware_interface::JointStateInterface jnt_state_interface;
  hardware_interface::PositionJointInterface jnt_pos_interface;
  double cmd[2];
  double pos[2];
  double vel[2];
  double eff[2];
};

