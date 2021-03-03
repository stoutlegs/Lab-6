#include "stdafx.h"
#include "CMissile.h"

CMissile::CMissile(cv::Point2f vel)
{
	//sprite = cv::imread("Missile.jpg");
	_shape.height = 20;
	_shape.width = 3;
	_velocity = vel;
	_tick = cv::getTickCount();
	_lives = 1;
}
