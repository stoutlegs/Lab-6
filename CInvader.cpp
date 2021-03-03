#include "stdafx.h"
#include "CInvader.h"

CInvader::CInvader(cv::Point2f pos)
{
	sprite = cv::imread("Alien 1.jpg");
	set_pos(pos);
	set_lives(1);
	_shape.height = 37;
	_shape.width = 37;
}
