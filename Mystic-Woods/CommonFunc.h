#ifndef COMMON_FUNCTION_H_
#define COMMON_FUNCTION_H_

#include <windows.h>
#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include "BaseObject.h"
#include "TextObject.h"
#include "SoundsEffect.h"

static SDL_Window * g_window = NULL;
static SDL_Renderer * g_screen = NULL;
static SDL_Event g_event;

static Mix_Chunk* g_sound_player[2];
static Mix_Chunk* g_sound_slime[2];
static Mix_Chunk* g_sound_skeleton[2];

const int FPS = 18;
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 640;
const int SCREEN_BPP = 32;

#define BLANK_TILE 0
#define SIZE 32
#define RATIO_PLAYER 2
#define RATIO_MAP 2
#define SIZE_BACK 0.75


#define MAX_X 80
#define MAX_Y 40

#define START_PLAYER 7

#define MAX_FRAME 6
#define MAX_FRAME_SLIME 7
#define MAX_FRAME_SKELETON 6
#define MAX_FRAME_H 5

#define MAX_MONSTER 7
#define MOVE_LIMIT 30

#define STATUS_TIME 100
#define TIME_MOVE 120
#define REVIVAL_TIME 1000
#define DELAY_ATTACK 20
#define START_ATTACK 5      //thoi gian quai danh player khi va cham
#define DELAY_FRAME 50      //giam toc do ra frame khi chet cho tu nhien hon

#define ATTACK_RANGE 35
#define HP_MONSTER 100
#define HP_PLAYER 100
#define DAMAGE_TO_MONSTER 5
#define DAMAGE_TO_PLAYER 10

#define MIN_ATTACK_DISTANCE 5
#define ATTACK_DISTANCE 1


struct Input
{
    int left_;
    int right_;
    int up_;
    int down_;
    int stop_;
    int attack_;
    bool direction_ = false;
};


struct Map
{
    int start_x;
    int start_y;

    int max_x;
    int max_y;

    int tile[MAX_Y][MAX_X];
    int x[MAX_MONSTER];
    int y[MAX_MONSTER];
    int types[MAX_MONSTER];
    std::string file_name;
};

namespace SDLCommonFunc
{
    bool CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2);
    bool CheckMove(const SDL_Rect& object1, const SDL_Rect& object2);
    int CheckDirection(const SDL_Rect& object1, const SDL_Rect& object2);
}

#endif