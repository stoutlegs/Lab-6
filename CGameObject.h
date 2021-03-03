#pragma once

#include "stdafx.h"

using namespace cv;

/**
*
* @brief This is the base game object class that all other game objects will inherit from
*
* This class holds all the information the game objects such as the ship, missiles, and 
* enemies will need to function within the game.
*
* @author Michael Andrews
*
*/
class CGameObject
{
protected:
	Point2f _position; ///< The object position vector. The point will be the top right of the object
	Point2f _velocity; ///< tTe velocity of the object.
	Rect _shape; ///< The Objects rectangular shape information
	int _lives; ///< The objects lives
	double _tick; ///< The last tick the object was drawn
	cv::Mat sprite; ///< The object's sprite to be drawn on screen
public:
	/** @brief Will update the objects current position by calculating the velocity and time
	*
	*  @param None
	*  @return Nothing to return
	*/
	void move();

	/** @brief Will check if a given game object has collided with the object
	*
	*  @param obj A game object to check collision with
	*  @return Returns a bool
	*/
	bool collide(CGameObject& obj);

	/** @brief Will check if the object has collided with any walls
	*
	*  @param board The size of the game window
	*  @return Returns a bool
	*/
	bool collide_wall(Size board);

	/** @brief will subtract one form the object's lives
	*
	*  @param None
	*  @return Nothing to return
	*/
	void hit();

	/** @brief Gets the objects current lives
	*
	*  @param None
	*  @return Returns an int
	*/
	int get_lives() { return _lives; }

	/** @brief Set the objects lives to the given value
	*
	*  @param lives The value to set the lives to
	*  @return Nothing to return
	*/
	void set_lives(int lives) {	_lives = lives; }

	/** @brief Sets the objects position
	*
	*  @param pos A point2f type varaible to set the objects position to
	*  @return Nothing to return
	*/
	void set_pos(Point2f pos) { _position = pos; }

	/** @brief gets the objects current position
	*
	*  @param None
	*  @return Returns a Point2f value
	*/
	Point2f get_pos() { return _position; }

	/** @brief Draws the object onto the game window
	*
	*  @param None
	*  @return Nothing to return
	*/
	void draw(Mat& im, cv::Scalar color);

	/** @brief Gets the object's current velocity
	*
	*  @param None
	*  @return Returns a Point2f value
	*/
	Point2f get_velocity() { return _velocity; }
};

