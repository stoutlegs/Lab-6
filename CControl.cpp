///////////////////////////////////////////////////////////////////////////////////////////
// CControl.cpp Header file for Lab 3 - ELEX 4618
// Author: Michael Andrews
// Last Edited: 23/01/2021
///////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include "stdafx.h"
#include "CControl.h"
#include "CControl.h"
#include <string.h>

#define ANALOG 1
#define DIGITAL 0

/** @brief This is the class constructor
*
* @param None
* @return Nothing to return
*/
CControl::CControl() {

}

/** @brief This is the class destructor
*
* @param None
* @return Nothing to return
*/
CControl::~CControl() {
	
}

/** @brief This method will initialize the com port
*
* @param comport The number of the port to be initialized (COM10)
* @return Nothing to return
*/
void CControl::init_com(int comport) {
	std::string port = std::to_string(comport);
	port = "COM" + port;
	_com.open(port.c_str());
}

/** @brief This method will get data from the serial port
*
* @param type This is the type of data being sent
* @param channel This is the channel the data is being sent on
* @param result This will store the result
* @return Returns if it was successful or not
*/
bool CControl::get_data(int type, int channel, int& result) {
	std::string tx_str = "G " + std::to_string(type) + " " + std::to_string(channel) + '\n';
	std::string rx_str;
	std::string value;

	char buff[2];

	if (_com.is_open())
	{
		_com.write(tx_str.c_str(), tx_str.length());
		Sleep(10);

		rx_str = "";
		// start timeout count
		double start_time = cv::getTickCount();

		buff[0] = 0;

		// Read 1 byte and if an End Of Line then exit loop
		// Timeout after 1 second, if debugging step by step this will cause you to exit the loop
		while (buff[0] != '\n' && (cv::getTickCount() - start_time) / cv::getTickFrequency() < 1.0)
		{
			if (_com.read(buff, 1) > 0)
			{
				rx_str = rx_str + buff[0];
			}
		}


		int spaceCount = 0;

		for (int i = 0; i < rx_str.size(); i++)
		{
			if (rx_str[i] == ' ')
			{
				spaceCount++;
				if (spaceCount == 3)
				{
					value = rx_str.substr(i + 1, ((rx_str.size() - 1) - (i + 1)));
				}
			}
		}


		if (rx_str.size() > 0)
		{
			result = std::stoi(value);

			if (rx_str.substr(0, 1) == "A")
			{
				return true;
			}
			else
			{
				result = 0;
				return false;
			}
		}
	}
	return false;
}

/** @brief This method will set the data from the serial port
*
* @param type This is the type of data being sent
* @param channel This is the channel the data is being sent on
* @param result This will store the result
* @return Returns if it was successful or not
*/
bool CControl::set_data(int type, int channel, int val) {
	std::string tx_str = "S " + std::to_string(type) + " " + std::to_string(channel) + " " + std::to_string(val) + '\n';
	std::string rx_str;

	char buff[2];

	if (_com.is_open())
	{
		_com.write(tx_str.c_str(), tx_str.length());
		Sleep(10);

		rx_str = "";
		// start timeout count
		double start_time = cv::getTickCount();

		buff[0] = 0;

		// Read 1 byte and if an End Of Line then exit loop
		// Timeout after 1 second, if debugging step by step this will cause you to exit the loop
		while (buff[0] != '\n' && (cv::getTickCount() - start_time) / cv::getTickFrequency() < 1.0)
		{
			if (_com.read(buff, 1) > 0)
			{
				rx_str = rx_str + buff[0];
			}
		}

		if (rx_str.substr(0, 1) == "A")
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	return false;
}

bool CControl::get_analog(int channel, int& result)
{
	int value;

	if (get_data(ANALOG, channel, value))
	{
		result = value * 100 / 1024;
		return true;
	}

	return false;
}

bool CControl::get_button(int channel)
{
	DWORD lastTime;
	DWORD currentTime;

	int result;

	get_data(DIGITAL, channel, result);

	if (result == 0)
	{
		lastTime = GetTickCount();
		do
		{
			currentTime = GetTickCount();
		} while (currentTime - lastTime < 25);

		if (result == 0)
		{
			return true;
		}
	}

	return false;
}