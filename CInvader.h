#pragma once

#include "CGameObject.h"

/**
*
* @brief This is the game invader class
*
* The game invader class with its own unique constructor to set the size, sprite, and lives.
*
* @author Michael Andrews
*
*/
class CInvader:
	public CGameObject
{
public:
    /** @brief The class constructor
    *
    * @details This method will take a velocity in and create a new invader
    *
    *  @param pos The starting position for the new invader
    *  @return Nothing to return
    */
	CInvader(cv::Point2f);
};

