#include "Input.h"

Input::Input(Joystick* newStick, OctocanumDrive* newDrive)
{
	stick = newStick;
	drive = newDrive;
}

void Input::Update()
{
	drive->Drive(
		stick->GetRawAxis(STRAFE_X),
		stick->GetRawAxis(STRAFE_Y),
		stick->GetRawAxis(ROTATE)
	);
	
	
	SmartDashboard::PutNumber("Stafe_x: ", stick->GetRawAxis(STRAFE_X));
	SmartDashboard::PutNumber("Stafe_y: ", stick->GetRawAxis(STRAFE_Y));
	SmartDashboard::PutNumber("rot: ", stick->GetRawAxis(ROTATE));
	SmartDashboard::PutBoolean("button: ", stick->GetRawButton(MODE_TOGGLE));
	
	//if (stick->GetRawButton(MODE_TOGGLE))
		//drive->Toggle();
if (stick->GetRawButton(MODE_MEC))
drive->Raise();
if (stick->GetRawButton(MODE_TRAC))
drive->Drop();
}
