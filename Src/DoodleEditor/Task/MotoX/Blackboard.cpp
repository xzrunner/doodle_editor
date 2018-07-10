#include "Blackboard.h"

using namespace deditor::motox;

bool Blackboard::isCameraFocusOnMotobike = false;

const int Blackboard::gravity = 20;

const float Blackboard::wheelFriction = 3.0f;
const float Blackboard::motoDensity = 8.0f;
const float Blackboard::speed = 30.0f;
const float Blackboard::acceleration = 20.0f;
const float Blackboard::motoTorque = 600.0f;

const float Blackboard::playerDensity = 2.0f;
const float Blackboard::playerTorque = 1500.0f;

const float Blackboard::trackFriction = 2.0f;

const float Blackboard::frontWheelSpeedScale = 1.0f;
const float Blackboard::frontWheelTorqueScale = 1.0f;