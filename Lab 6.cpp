#include "stdafx.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <thread>
#include "Client.h"
#include "Server.h"
#include "Serial.h"
#include "CSpaceInvaderGame.h"
#include "CBase4618.h"

#define PORT 6
#define CANVAS_HORI 1000
#define CANVAS_VERT 800

int main(int argc, char* argv[])
{
    cv::Size matSize = cv::Size(CANVAS_HORI, CANVAS_VERT);
    int comport = PORT;

    CSpaceInvaderGame spaceGame(matSize, comport);

    int value;

    spaceGame.run();
}
