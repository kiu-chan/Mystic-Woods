#ifndef MENU_H
#define MENU_H

#include "CommonFunc.h"

class Menu : public BaseObject
{
public:
    Menu();
    ~Menu();

    int ShowMenu(SDL_Renderer* screen, TTF_Font* font);
    bool LoadMenu(std::string path, SDL_Renderer* des);
    void Show(SDL_Renderer* des);
    bool CheckFousWithRect(const int& x, const int& y, const SDL_Rect& rect);

private:

    SDL_Rect offset;
    SDL_Texture* m_object;
    int width_frame;
    int height_frame;
};




#endif