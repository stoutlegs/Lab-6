#pragma once
#include "stdafx.h"
#include "CControl.h"

#define BLUE 0
#define RED 1
#define GREEN 2
#define BLUE_CH 37
#define GREEN_CH 38
#define RED_CH 39
#define DIGITAL 0
#define ANALOG 1
#define SERVO 2
#define ON 1
#define OFF 0

/**
*
* @brief The base class for labs in ELEX 4618
*
* This class is meant to be a shell class for the
* rest of the labs in ELEX 4618. It has a run
* function that will call the update and draw
* methods which will be written in the children classes.
*
* @author Michael Andrews
*
*/
class CBase4618
{
protected:

	CControl _ctrl; ///< Object for calling and using the serial interface

	cv::Mat _canvas; ///< Object for all OpenCV fucntions and the Mat

	bool _thread_exit; ///< Flag to tell the threads to stop

public:

	/** @brief This is the default class constructor
	*
	*  @param None
	*  @return Nothing to return
	*/
	CBase4618();

	/** @brief This is the default class destructor
	*
	*  @param None
	*  @return Nothing to return
	*/
	~CBase4618();
	
	/** @brief This is the virtual update function to be inherited by a child class
	*
	*  @param None
	*  @return Nothing to return
	*/
	virtual void update() = 0;

	/** @brief This is the virtual draw function to be inherited by a child class
	*
	*  @param None
	*  @return Nothing to return
	*/
	virtual void draw() = 0;

	/** @brief This is the run function which will call update and draw continuously 
	*
	*  @param None
	*  @return Nothing to return
	*/
	void run();

	/** @brief This is the vitrual start function to be inherited by a child class
	*
	*  @param None
	*  @return Nothing to return
	*/
	virtual void start() = 0;
};

