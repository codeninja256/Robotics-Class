#pragma config(UserModel, "base_code.h")
#include "base_code.h"

//This code uses the VexNet joystick for movement. You need to have the Vex Communication mode set to VexNet or USB for this to work.

task main()
{
	  while(true)
	  {
		    joystickMove();
	  }
}
