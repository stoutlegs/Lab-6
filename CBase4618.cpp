#include "stdafx.h"
#include "CBase4618.h"
#include <thread>


CBase4618::CBase4618()
{
}

CBase4618::~CBase4618()
{
}

void CBase4618::run()
{
	char key;
	//start();

	do
	{

		update();
		draw();

		key = cv::waitKey(10);
	} while (key != 'q');

	//_thread_exit = true;
	//Sleep(250);
}

