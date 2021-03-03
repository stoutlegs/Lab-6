#include "stdafx.h"
#include "CGameObject.h"

void CGameObject::move()
{
	_position = _position + _velocity *((cv::getTickCount() - _tick) / getTickFrequency());

	_tick = cv::getTickCount();
}

bool CGameObject::collide(CGameObject& obj)
{
	obj._shape.x = obj._position.x;
	obj._shape.y = obj._position.y;
	if (obj._shape.contains(_position))
	{
		return true;
	}
	return false;
}

bool CGameObject::collide_wall(Size board)
{
	if (_position.x > board.width - 100)
	{
		return true;
	}
	else if (_position.x < 60)
	{
		return true;
	}
	else if (_position.y > board.height)
	{
		return true;
	}
	else if (_position.y < 0)
	{
		return true;
	}
	return false;
}

void CGameObject::hit()
{
	_lives--;
}

void CGameObject::draw(Mat& im, cv::Scalar color)
{
	cv::rectangle(im, _position, cv::Point2f(_position.x + _shape.width, _position.y + _shape.height), color, 1, LINE_AA, 0);
	if (sprite.empty() == false)
	{
		sprite.copyTo(im(cv::Rect(_position.x - 1, _position.y - 1, sprite.cols, sprite.rows)));
	}
}