#include "Map.h"
void GameMap::LoadMap(std::string name)
{
    FILE* fp = NULL;
    fopen_s(&fp, name.c_str(), "rb");
    if(fp == NULL)
    {
        return ;
    }

    game_map.max_x = 0;
    game_map.max_y = 0;
    for(int i = 0; i < MAX_Y; i++)
    {
        for(int j = 0; j < MAX_X; j++)
        {
            fscanf(fp, "%d", &game_map.tile[i][j]);
            int val = game_map.tile[i][j];
            if(val > 0)
            {
                if(j > game_map.max_x)
                {
                    game_map.max_x = j;
                }

                if(i > game_map.max_y)
                {
                    game_map.max_y = i;
                }
            }
        }
    }
    game_map.max_x = (game_map.max_x)*SIZE;
    game_map.max_y = (game_map.max_y)*SIZE;

    game_map.start_x = 0;
    game_map.start_y = 0;

    game_map.file_name = name.c_str();
    fclose(fp);
}

void GameMap::LoadTile(SDL_Renderer* screen)
{
    char file_img[300];
    FILE* fp = NULL;
    for(int i = 1; i <= MAX; i++)
    {
        sprintf_s(file_img, "map/Map2/images/map_%d.png", i+1);

        fopen_s(&fp, file_img, "rb");
        if(fp == NULL)
        {
            continue;
        }

        fclose(fp);

        tile_mat[i].LoadImg(file_img, screen);
    }
}

void GameMap::DrawMap(SDL_Renderer* screen)
{
    int x1 = 0;
    int x2 = 0;

    int y1 = 0;
    int y2 = 0;

    int map_x = 0;
    int map_y = 0;

    map_x = game_map.start_x/SIZE;
    x1 = (game_map.start_x%SIZE)*-1;
    x2 = x1 + SCREEN_WIDTH + (x1 == 0 ? 0 : SIZE);
    
    map_y = game_map.start_y/SIZE;
    y1 = (game_map.start_y%SIZE)*-1;
    y2 = y1 + SCREEN_HEIGHT + (y1 == 0 ? 0 : SIZE);
    
    for (int i = y1; i < y2; i += SIZE)
    {
        map_x = game_map.start_x/SIZE;
        for (int j = x1; j < x2; j += SIZE)
        {
            int val  = game_map.tile[map_y][map_x];
            if(val > 0)
            {
                tile_mat[val].SetRect(j, i);
                tile_mat[val].Render(screen);
            }
            map_x++;
        }
        map_y++;
    }
}