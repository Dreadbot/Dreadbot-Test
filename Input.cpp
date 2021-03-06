#include "Input.h"

Input::Input(Joystick* _drivestick, 
	Joystick* _shootStick,
	OctocanumDrive* _drive,
	ArmControl* _arms,
	Shooter* _shooter)
{
	driveStick = _drivestick;
	shootStick = _shootStick;
	drive = _drive;
	arms = _arms;
	shooter = _shooter;
}


void Input::Update()
{
	float x = driveStick->GetRawAxis(MEC_X);
	float y = driveStick->GetRawAxis(MEC_Y);
	float r = driveStick->GetRawAxis(MEC_R);

	bool drop = driveStick->GetRawButton(DROP);
	bool dance = driveStick->GetRawButton(DANCE_ENABLE);

	SmartDashboard::PutBoolean("Traction Mode: ", drop); 
	SmartDashboard::PutNumber("Flipper Value: ", arms->GetFlipPot()); //TEST

	if (x < 0.1 && x > -0.1) x = 0.0;
	if (y < 0.1 && y > -0.1) y = 0.0;
	if (r < 0.1 && r > -0.1) r = 0.0;
	
	drive->Drive(x, y, r);

	if (dance)
	{
		drive->valve0->Set(driveStick->GetRawButton(DANCE_RIGHT));
		drive->valve1->Set(driveStick->GetRawButton(DANCE_LEFT));
	}
	else
	{
		if (!drop) drive->Drop();
		else drive->Raise();
	}
	shooter->update();
	if (driveStick->GetRawButton(TRIGGER) || shootStick->GetRawButton(TRIGGER)) shooter->shoot();

	// Shooter Controls
	float flipAxis = shootStick->GetRawAxis(FLIPPER);
	float armAxis = shootStick->GetRawAxis(ARMS);
	float rollerAxis = shootStick->GetRawAxis(ARM_MECS);
	//DEBUG
	SmartDashboard::PutNumber("flipAxis:", flipAxis);
	
	// Dead zone
	if (flipAxis <= 0.1 && flipAxis >= -0.1) flipAxis = 0.0;
	if (armAxis <= 0.1 && flipAxis >= -0.1) armAxis = 0.0;
	if (rollerAxis <= 0.1 && rollerAxis >= -0.1) rollerAxis = DriverStation::GetInstance()->GetAnalogIn(2);
	// Set controls
	arms->MoveFlipper(flipAxis);
	
	if (armAxis > 0.5) 
		arms->MoveArms(DoubleSolenoid::kForward);
	if (armAxis < -0.5) 
		arms->MoveArms(DoubleSolenoid::kReverse);
	if (armAxis < -0.5 && armAxis > 0.5) 
		arms->MoveArms(DoubleSolenoid::kOff);
	if (shootStick->GetRawButton(SHOOTER_RESET)) 
		shooter->setReset();
	arms->MoveWheels(rollerAxis);

}
