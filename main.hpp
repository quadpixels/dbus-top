#pragma once

#include "bargraph.hpp"

#include <ncurses.h>

#include <string>

const int INVALID = -999; // Constant indicating invalid indices

struct Rect
{
    int x, y, w, h; // X, Y, Width, Height
    Rect(int _x, int _y, int _w, int _h) : x(_x), y(_y), w(_w), h(_h)
    {}
    Rect() : x(0), y(0), w(1), h(1)
    {}
};

int DrawTextWithWidthLimit(WINDOW* win, std::string txt, int y, int x,
                           int width, const std::string& delimiters);
std::string FloatToString(float value);
template <typename T>
void HistoryBarGraph(WINDOW* win, const Rect& rect, BarGraph<T>* bargraph);