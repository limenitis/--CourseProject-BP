#pragma once
#include <iostream>
#include <string>
#include <cassert>
#include <fcntl.h>
#include <io.h>
#include ".\..\include\linked-list.h"

namespace colors
{
    using std::cout;
    using std::wcout;
    using std::wcerr;
    using std::cerr;
    using std::endl;
    using std::string;
    using std::to_string;
    using std::wstring;
    using std::to_wstring;
}
using namespace colors;

int front2int(string front_color);

int back2int(string back_color);

// -------------
// front colors:
// black, red, green, yellow, blue, magenda, cyan, white
// -------------
// back colors: 
// on_black, on_red, on_green, on_yellow, on_blue, on_magenda, on_cyan, on_white
// -------------
template <typename T>
inline void color_out(const T &str, string front_color, string back_color = "default")
{
    int front = front2int(front_color);
    int back = back2int(back_color);

    if(front != -1) { cout  << "\x1b[3" << front << "m"; }
    if(back  != -1) { cout  << "\x1b[4" << back  << "m"; }
    cout << str << "\x1b[0m";
}

// -------------
// front colors:
// black, red, green, yellow, blue, magenda, cyan, white
// -------------
// back colors: 
// on_black, on_red, on_green, on_yellow, on_blue, on_magenda, on_cyan, on_white
// -------------
template <typename T>
inline void wcolor_out(const T &str, string front_color, string back_color = "default")
{
    int front = front2int(front_color);
    int back = back2int(back_color);

    if(front != -1) wcout << L"\x1b[3" << front << L"m"; 
    if(back  != -1) wcout << L"\x1b[4" << back  << L"m";
    wcout << str << L"\x1b[0m";
}

// const string BLACK   = "\x1b[30m";
// const string RED     = "\x1b[31m";
// const string GREEN   = "\x1b[32m";
// const string YELLOW  = "\x1b[33m";
// const string BLUE    = "\x1b[34m";
// const string MAGENDA = "\x1b[35m";
// const string CYAN    = "\x1b[36m";
// const string WHITE   = "\x1b[37m";
// const string ON_BLACK   = "\x1b[40m";  // background
// const string ON_RED     = "\x1b[41m";  // background
// const string ON_GREEN   = "\x1b[42m";  // background
// const string ON_YELLOW  = "\x1b[43m";  // background
// const string ON_BLUE    = "\x1b[44m";  // background
// const string ON_MAGENDA = "\x1b[45m";  // background
// const string ON_CYAN    = "\x1b[46m";  // background
// const string ON_WHITE   = "\x1b[47m";  // background
// const string RESET_COLOR = "\x1b[0m";

// const wstring wBLACK   = L"\x1b[30m";
// const wstring wRED     = L"\x1b[31m";
// const wstring wGREEN   = L"\x1b[32m";
// const wstring wYELLOW  = L"\x1b[33m";
// const wstring wBLUE    = L"\x1b[34m";
// const wstring wMAGENDA = L"\x1b[35m";
// const wstring wCYAN    = L"\x1b[36m";
// const wstring wWHITE   = L"\x1b[37m";
// const wstring wON_BLACK   = L"\x1b[40m";  // background
// const wstring wON_RED     = L"\x1b[41m";  // background
// const wstring wON_GREEN   = L"\x1b[42m";  // background
// const wstring wON_YELLOW  = L"\x1b[43m";  // background
// const wstring wON_BLUE    = L"\x1b[44m";  // background
// const wstring wON_MAGENDA = L"\x1b[45m";  // background
// const wstring wON_CYAN    = L"\x1b[46m";  // background
// const wstring wON_WHITE   = L"\x1b[47m";  // background
// const wstring wRESET_COLOR = L"\x1b[0m";

// static const char* chBLACK   = "\x1b[30m";
// static const char* chRED     = "\x1b[31m";
// static const char* chGREEN   = "\x1b[32m";
// static const char* chYELLOW  = "\x1b[33m";
// static const char* chBLUE    = "\x1b[34m";
// static const char* chMAGENDA = "\x1b[35m";
// static const char* chCYAN    = "\x1b[36m";
// static const char* chWHITE   = "\x1b[37m";
// static const char* chON_BLACK   = "\x1b[40m";  // background
// static const char* chON_RED     = "\x1b[41m";  // background
// static const char* chON_GREEN   = "\x1b[42m";  // background
// static const char* chON_YELLOW  = "\x1b[43m";  // background
// static const char* chON_BLUE    = "\x1b[44m";  // background
// static const char* chON_MAGENDA = "\x1b[45m";  // background
// static const char* chON_CYAN    = "\x1b[46m";  // background
// static const char* chON_WHITE   = "\x1b[47m";  // background
// static const char* chRESET_COLOR = "\x1b[0m";

