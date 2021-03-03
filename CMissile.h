#pragma once

#include "CGameObject.h"

/**
*
* @brief This is the game missile class
*
* The game missile class with its own unique constructor to set the size, sprite, and lives.
*
* @author Michael Andrews
*
*/
class CMissile:
	public CGameObject
{
public:
    /** @brief The class constructor
    *
    * @details This method will take a velocity in and create a new missile
    *
    *  @param vel This variable will determine the velocity of the missile. If an invader is shooting the y portion will be positive and if the ship shoots it will be negative.
    *  @return Nothing to return
    */
	CMissile(cv::Point2f vel);
};

