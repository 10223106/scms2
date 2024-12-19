#ifndef MENU_H
#define MENU_H  
#pragma once
#include "olcPixelGameEngine.h"

#include "olcPixelGameEngine.h"
#include <vector>
#include <string>

using namespace std; 
struct MenuOption {
    string text;
    olc::vf2d position;
    olc::Pixel color;
};

class Menu {
public:
    void AddOption(const std::string& text, const olc::vf2d& position, olc::Pixel color = olc::WHITE);
    void Draw(olc::PixelGameEngine* pge);
    void HandleInput(olc::PixelGameEngine* pge);
    int GetSelectedOption() const;

private:
    vector<MenuOption> options;
    int selectedOption = 0;
};
#endif