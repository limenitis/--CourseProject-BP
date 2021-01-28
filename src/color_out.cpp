#pragma once
#include ".\..\include\color_out.h"
#include <iostream>
#include <string>
#include <fcntl.h>
#include <io.h>

// using namespace colors;
using namespace std;

int front2int (string front_color)
{
    if (front_color[0] == 'b')
    {
        if (front_color[2] == 'a') // black
        {
            return 0;
        }
        else if (front_color[2] == 'u') // blue
        {
            return 4;
        }
        else
        {
            return -1;
        }
    }
    else if (front_color[0] == 'r') // red
    {
        return 1;
    }
    else if (front_color[0] == 'g') // green
    {
        return 2;
    }
    else if (front_color[0] == 'y') // yellow
    {
        return 3;
    }
    else if (front_color[0] == 'm') // magenda
    {
        return 5;
    }
    else if (front_color[0] == 'c') // cyan
    {
        return 6;
    }
    else if (front_color[0] == 'w') // white
    {
        return 7;
    }
    else
    {
        return -1;
    }
}

int back2int (string back_color)
{
    if (back_color[3] == 'b')
    {
        if (back_color[5] == 'a') // on_black
        {
            return 0;
        }
        else if (back_color[5] == 'u') // on_blue
        {
            return 4;
        }
        else
        {
            return -1;
        }
    }
    else if (back_color[3] == 'r') // on_red
    {
        return 1;
    }
    else if (back_color[3] == 'g') // on_green
    {
        return 2;
    }
    else if (back_color[3] == 'y') // on_yellow
    {
        return 3;
    }
    else if (back_color[3] == 'm') // on_magenda
    {
        return 5;
    }
    else if (back_color[3] == 'c') // on_cyan
    {
        return 6;
    }
    else if (back_color[3] == 'w') // on_white
    {
        return 7;
    }
    else
    {
        return -1;
    }
}
