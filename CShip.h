#pragma once

#include "CGameObject.h"

#define SHIP_WIDTH 37
#define SHIP_HEIGHT 47

/**
*
* @brief This is the game ship class
*
* The game ship class with its own unique constructor to set the size, sprite, and lives.
*
* @author Michael Andrews
*
*/
class CShip :
	public CGameObject
{
public:
    /** @brief The class constructor
    *
    * @details This method will set the parameters for the ship object
    *
    *  @param None
    *  @return Nothing to return
    */
	CShip();
};

