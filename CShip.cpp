#include "stdafx.h"
#include "CShip.h"

CShip::CShip()
{
	sprite = cv::imread("Ship.jpg");
	_shape.height = SHIP_HEIGHT;
	_shape.width = SHIP_WIDTH;
	_lives = 3;
}
