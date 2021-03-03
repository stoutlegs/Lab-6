#pragma once

#include "CBase4618.h"
#include "CGameObject.h"
#include "CInvader.h"
#include "CShip.h"
#include "CMissile.h"

#define SHOOT 33
#define RESET 32
#define RIGHT 0
#define LEFT 1
#define DOWN 2
#define WAIT_STATE 3
#define X_SPEED 2   
#define Y_SPEED 20

/**
*
* @brief The class responsible for actually running the Space invaders game.
*
* This class is responsible for running and drawing all aspects of the space
* invaders game. It will update all game objects and check for user input
* from the MSP432R.
*
* @author Michael Andrews
*
*/
class CSpaceInvaderGame:
	public CBase4618
{
private:

    std::vector<CInvader> invaders; ///< Vector to hold the enemies for the game

    std::vector<CMissile> missiles; ///< Vector to hold the missiles in the game

    CShip ship; ///< Ship game object

    int _score; ///< Player score for the game

    bool _reset; ///< flag to see if the rest button has been pressed

    double last_tick; ///< Variable to hold when update last finished to calculate the physics

    float _speed_mod; ///< Variable to hold the current speed modifyer for when the player advances to the next round

    cv::Point2f _movement; ///< Variable to hold the movement vector of the invaders

    int last_state, state; ///< Holds the last movement and current movement directions of the invaders

    int count; ///< Variable to change how often an invader shoots at the player

    int _move_count; ///< Variable to hold how many times the invaders have moved

    /** @brief Update will get information from the joystick, calculate ball physics, and check for collisions.
    *
    *  @param None
    *  @return Nothing to return
    */
    void update();

    /** @brief Draw will draw the images to the mat with the information gathered by the Update method.
    *
    *  @param None
    *  @return Nothing to return
    */
    void draw();

    /** @brief Will call update continuously on its own thread
    *
    *  @param ptr A pointer to the current class
    *  @return Nothing to return
    */
    static void update_thread(CSpaceInvaderGame* ptr);

    /** @brief Will call draw continuously on its own thread
    *
    *  @param ptr A pointer to the current class
    *  @return Nothing to return
    */
    static void draw_thread(CSpaceInvaderGame* ptr);

    /** @brief Will reset all game elements
    *
    *  @param None
    *  @return Nothing to return
    */
    void reset();

    /** @brief Will recreate the enemies for the next level
    *
    *  @param None
    *  @return Nothing to return
    */
    void next_level();

public:
    /** @brief The class constructor
    *
    * @details This method will take a mat size and a com port and initialize everything required to begin the game.
    *
    *  @param size This variable is of type cv::Size and will determine the size of canvas that is created and show on screen.
    *  @param port This is the COM port number to be initialized.
    *  @return Nothing to return
    */
    CSpaceInvaderGame(cv::Size size, int port);

    /** @brief Will create and detach the threads to run independantly
    *
    *  @param None
    *  @return Nothing to return
    */
    void start();
};

