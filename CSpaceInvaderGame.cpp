#include "stdafx.h"
#include "CSpaceInvaderGame.h"

using namespace cv;

CSpaceInvaderGame::CSpaceInvaderGame(cv::Size size, int port)
{
	_canvas = Mat::zeros(size, CV_8UC3);
	_ctrl.init_com(port);

	reset();
}

void CSpaceInvaderGame::update()
{
	bool _collide_flag = false;
	int value;

	srand((unsigned)time(NULL));

	//Gets the reset button to set the flag
	if (_ctrl.get_button(RESET))
	{
		_reset = true;
		std::cout << "\nReset Pressed!";
	}

	if ((invaders.size() == 0) && (ship.get_lives() > 0))
	{
		next_level();
	}
	else if ((ship.get_lives()) > 0 && (_reset != true))
	{
		if (invaders.size() > 0)
		{
			int rand_num = rand() % invaders.size();
			count++;

			if (count >= 50 / _speed_mod)
			{
				count = 0;

				CMissile enemy_missile(cv::Point2f(0, 80));
				missiles.push_back(enemy_missile);
				missiles[missiles.size() - 1].set_pos(cv::Point2f(invaders[rand_num].get_pos().x + 20, invaders[rand_num].get_pos().y + 40));
			}
		}

		//Gets the button press to generate a new missile
		if (_ctrl.get_button(SHOOT))
		{
			std::cout << "\nShoot Pressed!";
			CMissile ship_missile(cv::Point2f(0, -80));
			missiles.push_back(ship_missile);
			missiles[missiles.size() - 1].set_pos(cv::Point2f(ship.get_pos().x + (SHIP_WIDTH / 2), ship.get_pos().y));
		}

		for (int i = 0; i < missiles.size(); i++)
		{
			if (missiles[i].collide_wall(_canvas.size()))
			{
				missiles[i].hit();
			}
			if (missiles[i].get_velocity().y > 0)
			{
				if (missiles[i].collide(ship))
				{
					ship.hit();
					missiles[i].hit();
				}
			}
			for (int o = 0; o < invaders.size(); o++)
			{
				if (missiles[i].get_velocity().y < 0)
				{
					if (missiles[i].collide(invaders[o]))
					{
						if (invaders[o].get_lives() > 0)
						{
							_score += 10;
						}
						invaders[o].hit();
						missiles[i].hit();
					}
				}
			}
		}

		for (int i = 0; i < missiles.size(); i++)
		{
			if (missiles[i].get_lives() <= 0)
			{
				missiles.erase(missiles.begin() + i);
			}
			else
			{
				missiles[i].move();
			}
		}

		//Ship joystick control
		_ctrl.get_analog(JS_HORI, value);
		if (value < 35)
		{
			if (ship.get_pos().x <= 10)
			{
				ship.set_pos(cv::Point2f(10, ship.get_pos().y));
			}
			else
			{
				ship.set_pos(cv::Point2f(ship.get_pos().x - 15, ship.get_pos().y));
			}
		}
		else if (value > 55)
		{
			if (ship.get_pos().x >= _canvas.size().width - 50)
			{
				ship.set_pos(cv::Point2f(_canvas.size().width - 50, ship.get_pos().y));
			}
			else
			{
				ship.set_pos(cv::Point2f(ship.get_pos().x + 15, ship.get_pos().y));
			}
		}

		//Checks wall collision and what the previous and current state of movement is
		//to determine the next movemonet for the invaders.
		if ((state == DOWN) && (last_state == RIGHT))
		{
			_movement = cv::Point2f(-1 * X_SPEED, 0) * _speed_mod;
			last_state = state;
			state = LEFT;
			_move_count = 0;
		}
		else if ((state == DOWN) && (last_state == LEFT))
		{
			_movement = cv::Point2f(X_SPEED, 0) * _speed_mod;
			last_state = state;
			state = RIGHT;
			_move_count = 0;
		}
		else
		{
			//check for collision with walls and the ship
			for (int i = 0; i < invaders.size(); i++)
			{
				if (invaders[i].collide(ship))
				{
					ship.set_lives(ship.get_lives() - 1);
				}
				if (invaders[i].collide_wall(_canvas.size()))
				{
					_collide_flag = true;
					break;
				}
			}
			_move_count++;
		}

		//Sets the new movement if there has been a collision.
		if ((_collide_flag == true) && (_move_count >= 20))
		{
			_movement = cv::Point2f(0, Y_SPEED);
			last_state = state;
			state = DOWN;
		}
		else
		{
			_collide_flag = false;
		}

		for (int i = 0; i < invaders.size(); i++)
		{
			if (invaders[i].get_lives() <= 0)
			{
				invaders.erase(invaders.begin() + i);
			}
		}

		//sets the new posistion for each invader
		for (int i = 0; i < invaders.size(); i++)
		{
				invaders[i].set_pos(invaders[i].get_pos() + _movement);
		}
	}
	else if (_reset == true)
	{
		reset();
		_reset = false;
	}
}

void CSpaceInvaderGame::draw()
{
	_canvas = Mat::zeros(_canvas.size(), CV_8UC3);
	
	//draws all the invaders
	for (int i = 0; i < invaders.size(); i++)
	{
		invaders[i].draw(_canvas, cv::Scalar(0, 0, 0));
	}

	ship.draw(_canvas, cv::Scalar(0, 0, 0));

	//draws all the missiles
	for (int i = 0; i < missiles.size(); i++)
	{
		missiles[i].draw(_canvas, cv::Scalar(0, 140, 255));
	}

	cv::putText(_canvas, "Score: " + std::to_string(_score), Point(10, 30), cv::FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 255, 0), 1, cv::LINE_AA);
	cv::putText(_canvas, "Lives: " + std::to_string(ship.get_lives()), Point(865, 30), cv::FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 0, 255), 1, cv::LINE_AA);
	cv::putText(_canvas, "Enemies: " + std::to_string(invaders.size()), Point(200, 30), cv::FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 255, 255), 1, cv::LINE_AA);
	cv::putText(_canvas, "Missiles: " + std::to_string(missiles.size()), Point(650, 30), cv::FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 255, 255), 1, cv::LINE_AA);
	cv::putText(_canvas, "Level: " + std::to_string(std::stoi(std::to_string(((_speed_mod - 1)/0.3) + 1))), Point(450, 30), cv::FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 255, 255), 1, cv::LINE_AA);

	if (ship.get_lives() == 0)
	{
		cv::putText(_canvas, "YOU LOSE", Point(150, 300), cv::FONT_HERSHEY_SIMPLEX, 5, Scalar(0, 140, 255), 3, cv::LINE_AA);
	}

  	imshow("Space Invaders", _canvas);

	last_tick = getTickCount();
}

void CSpaceInvaderGame::reset()
{

	invaders.clear();
	missiles.clear();

	_canvas = Mat::zeros(_canvas.size(), CV_8UC3);

	_score = 0;
	ship.set_lives(3);
	ship.set_pos(cv::Point2f(_canvas.size().width / 2, _canvas.size().height - 60));

	int row = 100;

	for (int i = 0; i < 5; i++)
	{
		for (int i = 0; i < 12; i++)
		{
			CInvader newInvader((Point2f(160, row) + Point2f(60, 0) * i));
			invaders.push_back(newInvader);
		}
		row += 60;
	}

	draw();
	state = RIGHT;
	last_state = RIGHT;
	_movement = cv::Point2f(X_SPEED, 0);
	_speed_mod = 1;

	//_thread_exit = false;

	count = 0;

	_move_count = 0;
}

void CSpaceInvaderGame::next_level()
{
	invaders.clear();
	missiles.clear();

	_canvas = Mat::zeros(_canvas.size(), CV_8UC3);

	int row = 100;

	for (int i = 0; i < 5; i++)
	{
		for (int i = 0; i < 12; i++)
		{
			CInvader newInvader((Point2f(160, row) + Point2f(60, 0) * i));
			invaders.push_back(newInvader);
		}
		row += 60;
	}

	draw();
	state = RIGHT;
	last_state = RIGHT;
	
	_speed_mod += 0.30;
	_movement = cv::Point2f(X_SPEED, 0) * _speed_mod;

	count = 0;
}

void CSpaceInvaderGame::update_thread(CSpaceInvaderGame* ptr)
{
	while (ptr->_thread_exit == false)
	{
		ptr->update();
	}
}

void CSpaceInvaderGame::draw_thread(CSpaceInvaderGame* ptr)
{
	while (ptr->_thread_exit == false)
	{
		ptr->draw();
	}
}

void CSpaceInvaderGame::start()
{
	std::thread t1(&CSpaceInvaderGame::update_thread, this);
	std::thread t2(&CSpaceInvaderGame::draw_thread, this);

	t2.detach();
	t1.detach();
}
