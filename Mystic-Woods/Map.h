#ifndef GAME_MAP_H
#define GAME_MAP_H

#define MAX 300

#include "CommonFunc.h"
#include "BaseObject.h"

class TileMat : public BaseObject
{
    public:
    TileMat(){}
    ~TileMat(){}

};

class GameMap
{
    public:
    GameMap(){}
    ~GameMap(){}

    void LoadMap(std::string name);
    void LoadTile(SDL_Renderer* screen);
    void DrawMap(SDL_Renderer* screen);
    Map getMap() const {return game_map;}
    void SetMap(Map& map_data) {game_map = map_data;}
    private:
    Map game_map;
    TileMat tile_mat[MAX];
};

#endif