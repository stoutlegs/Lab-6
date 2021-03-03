#pragma once

#include <iostream>
#include "Serial.h"

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
#define SPEED 4
#define JS_HORI 2
#define JS_VERT 26

/**
*
* @brief Used to communicate with the embedded system
*
* This class is meant to contain all information and
* functions related to serial communication with the
* embedded system.
*
* @author Michael Andrews
*
*/
class CControl {
private:
    Serial _com; ///< Serial COM Control object
public:

    /** @brief This is the class constructor
    *
    * @param None
    * @return Nothing to return
    */
    CControl();

    /** @brief This is the class destructor
    *
    * @param None
    * @return Nothing to return
    */
    ~CControl();

    /** @brief This method will initialize the com port
    *
    * @param comport The number of the port to be initialized (COM10)
    * @return Nothing to return
    */
    void init_com(int comport);

    /** @brief This method will get data from the serial port
    *
    * @param type This is the type of data being sent
    * @param channel This is the channel of the microcontroller to be used
    * @param result This will store the result
    * @return Returns if it was successful or not
    */
    bool get_data(int type, int channel, int& result);

    /** @brief This method will set the data from the serial port
    *
    * @param type This is the type of data being sent
    * @param channel This is the channel of the microcontroller to be used
    * @param result This will store the result
    * @return Returns if it was successful or not
    */
    bool set_data(int type, int channel, int val);

    /** @brief This method will call the get data function for analog only then convert it to a percent
    *
    * @param channel This is the channel of the microcontroller to be used
    * @param result This will store the result
    * @return Returns if it was successful or not
    */
    bool get_analog(int channel, int& result);

    bool get_button(int channel);
};
