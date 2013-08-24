#include "Application.h"

int main()
{
	int64 delta = 0;

	AppCtrlr *controller = new AppCtrlr();
	controller->init();

	while (!s3eDeviceCheckQuitRequest())
	{
		delta = s3eTimerGetUST();

		s3ePointerUpdate();
		s3eKeyboardUpdate();
		s3eDeviceYield(0);

		if (N2F::Iw3D::s3eExitKeyHit())
		{
			break;
		}

		controller->update(delta);
		s3eDeviceYield(0);

		controller->render(delta);
		s3eDeviceYield(0);
	}

	controller->kill();
	delete controller;

	return(0);
}
