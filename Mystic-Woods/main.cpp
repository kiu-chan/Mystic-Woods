#include "CommonFunc.h"
#include "Map.h"
#include "MainObject.h"
#include "Time.h"
#include "Monster.h"
#include "TextObject.h"
#include "Menu.h"

#undef main


//BaseObject g_background;
TTF_Font* font_hp = NULL;
TTF_Font* font_menu = NULL;
SoundsEffect Sounds;

bool InitData()
{
    bool success = true;
    int ret = SDL_Init(SDL_INIT_VIDEO);
    if(ret < 0)
        return false;

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

    g_window = SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if(g_window == NULL)
    {
        success = false;
    }
    else
    {
        g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
        if(g_screen == NULL)
            success = false;
        else
        {
            SDL_SetRenderDrawColor(g_screen, 255, 255, 255, 255);
            int imgFlags = IMG_INIT_PNG;
            if(!(IMG_Init(imgFlags) && imgFlags))
                success = false;

        }

        if(TTF_Init() == -1)
        {
            success = false;
        }

        font_hp = TTF_OpenFont("font//hlfants1.ttf", 15);
        font_menu = TTF_OpenFont("font//hlfants1.ttf", 50);
        if(font_hp == NULL && font_menu == NULL)
        {
            success = false;
        }



        if(Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
        {
            success = false;
        }
         //g_sound_player[0] = Mix_LoadWAV("audio/player-attack.wav");
        Sounds.addSound("player_attack", "audio/player-attack.wav");
        Sounds.addSound("slime_attack", "audio/slime-attack.wav");
        Sounds.addSound("music", "audio/music-game.wav");
        // if(g_sound_player[0] == 0)
        // {
        //     success = false;
        // }
    }
    return success;
}

/*
bool LoadBackground()
{
    bool ret = g_background.LoadImg("assets/background.png", g_screen);
    if( ret == false )
        return false;
    else 
        return true;
}
*/

void close()
{
    //g_background.Free();

    SDL_DestroyRenderer(g_screen);
    g_screen = NULL;

    SDL_DestroyWindow(g_window);
    g_window = NULL;

    IMG_Quit();
    SDL_Quit();
}

std::vector<Monster*> MakeMonsterList(Map monster_data)
{
    std::vector<Monster*> list_monster;

    Monster* moster = new Monster[MAX_MONSTER];

    for(int i = 0; i < MAX_MONSTER; i++)
    {
        Monster* p_monsters = (moster + i);
        if(p_monsters != NULL)
        {
            if(monster_data.types[i] == 1)
                p_monsters -> LoadImg("img/slime.png", g_screen, 1);
             if(monster_data.types[i] == 2)
                 p_monsters -> LoadImg("img/skeleton.png", g_screen, 2);
             p_monsters -> Set_clip();
             p_monsters -> set_x_pos(monster_data.x[i]*SIZE);
             p_monsters -> set_y_pos(monster_data.y[i]*SIZE);;

            list_monster.push_back(p_monsters);
        }
    }
    return list_monster;
}

int main(int argc, char* argv[])
{
    Time fps;
    srand((int)time(0));
    if(InitData() == false)
        return -1;
    /*if(LoadBackground() == false)
        return -1;*/
    

    GameMap game_map;
    game_map.LoadMap("map/Map2/map1.txt");
    game_map.LoadTile(g_screen);

    GameMap game_map1;
    game_map1.LoadMap("map/Map2/map2.txt");
    game_map1.LoadTile(g_screen);


    GameMap collision_map;
    collision_map.LoadMap("map/Map2/collision.txt");
    collision_map.LoadTile(g_screen);



    MainObject p_player;

    
    Monster monster_map;
    monster_map.LoadMap("map/Map2/monster.txt");
    Map monster_data = monster_map.getMap();

    std::vector<Monster*> monster_list = MakeMonsterList(monster_data);
    //text
    TextObject HP;
    TextObject Point;

    bool attack = false;
    Menu p_menu;

    //Sounds.PlaySound("music");

    int point = 0;

    int ret_menu = p_menu.ShowMenu(g_screen, font_menu);
    bool is_quit = false;
    if (ret_menu == 1)
    {
        is_quit = false;
    }
    else
        is_quit = true;

    bool start_game = true;
    while(!is_quit)
    {
        
        if (start_game)
        {
            is_quit = !p_menu.ShowMenu(g_screen, font_menu);
            if(!is_quit)
            {
                start_game = false;
            }
            else
            continue;
            p_player.RevivalPlayer();
            point = 0;
        }
        else
        {
            bool check_dead_player = p_player.GetDeadPlayer();
            if (check_dead_player)
                start_game = p_player.GetMenuDead();
        }

        fps.start();
        while (SDL_PollEvent(&g_event)!= 0)
        {
            if(g_event.type == SDL_QUIT)
            {
                is_quit = true;
            }
            p_player.HandelInputActive(g_event, g_screen);
        }

        SDL_RenderClear(g_screen);


        //g_background.Render(g_screen, NULL);
        Map map_data = game_map.getMap();
        Map map_data1 = game_map1.getMap();
        Map collision_data = collision_map.getMap();

        p_player.SetMapXY(map_data.start_x, map_data.start_y);
        p_player.SetMapXY(collision_data.start_x, collision_data.start_y);
        p_player.SetMapXY(map_data1.start_x, map_data1.start_y);

        p_player.DoPlayer(map_data);
        p_player.DoPlayer(collision_data);
        p_player.DoPlayer(map_data1);
        p_player.CheckToMap(collision_data);

        game_map.SetMap(map_data);
        game_map.DrawMap(g_screen);

        collision_map.SetMap(collision_data);
        collision_map.DrawMap(g_screen);

        game_map1.SetMap(map_data1);
        game_map1.DrawMap(g_screen);

        for(int i = 0; i < monster_list.size(); i++)
            {
                Monster* p_monster = monster_list.at(i);
                int move_value =  rand()%9;
                if(p_monster != NULL)
                {
                    bool check_dead = p_monster ->Get_Dead();
                    if(!check_dead)
                    {
                        std::string hp_monster = "HP: ";
                        int hp = p_monster ->GetHP();
                        if(hp > HP_MONSTER/2)
                        {
                            HP.SetColor(TextObject::WHILE_TEXT);
                        }
                        else
                        {
                            HP.SetColor(TextObject::RED_TEXT);
                        }
                        int x = p_monster ->GetRect().x;
                        int y = p_monster ->GetRect().y;
                        hp_monster += std::to_string(hp);
                        HP.SetText(hp_monster);
                        HP.LoadFromRenderText(font_hp, g_screen);
                        if(monster_data.types[i] ==1)
                        {
                            HP.RenderText(g_screen, x , y + 10);
                        }else if(monster_data.types[i] == 2)
                        {
                            HP.RenderText(g_screen, x + 30, y + 60);
                        }
                    }
                    p_monster -> SetMapXY(collision_data.start_x, collision_data.start_y);
                    p_monster -> DoMonster(collision_data);
                    p_monster -> AutoMove(move_value);
                    p_monster -> Set_clip();
                    p_monster -> Show(g_screen, monster_data.types[i]);
                }
            }

            //danh quai
        if(p_player.GetStatus() == 5)
        {
            for(int i = 0; i < monster_list.size(); i++)
            {
                Monster* p_monster = monster_list.at(i);
                if(p_monster != NULL)
                {
                    SDL_Rect monster_xy;
                    monster_xy.x = p_monster -> GetRect().x;
                    monster_xy.y = p_monster -> GetRect().y;
                    monster_xy.w = p_monster -> get_width_frame();
                    monster_xy.h = p_monster -> get_height_frame();

                    SDL_Rect player_attack = p_player.GetAttackMonster();

                    bool check_attack = SDLCommonFunc::CheckCollision(player_attack, monster_xy);

                    if(check_attack)
                    {
                        p_monster -> MonsterDead();
                        // Mix_PlayChannel(-1, g_sound_player[0], 0);
                        Sounds.PlaySound("player_attack");
                        attack = true;
                        if(p_monster -> Get_Dead() && p_monster -> GetTime())
                        {
                            point ++;
                        }
                    }

                }
            }
        }


        //tự động tấn công
        for(int i = 0; i < monster_list.size(); i++)
        {
            Monster* p_monster = monster_list.at(i);
            if(p_monster != NULL)
            {
                SDL_Rect monster_xy;
                monster_xy.x = p_monster-> get_x_pos();     //lay toa do
                monster_xy.y = p_monster-> get_y_pos();
                monster_xy.w = p_monster -> get_width_frame();
                monster_xy.h = p_monster -> get_height_frame();

                SDL_Rect player_move;
                player_move.x = p_player.Get_x_pos();
                player_move.y = p_player.Get_y_pos();
                player_move.w = p_player.get_width_frame();
                player_move.h = p_player.get_height_frame();

                bool check_move = SDLCommonFunc::CheckMove(player_move, monster_xy);

                if(check_move)
                    {
                        int move_value;
                        bool check_collision = p_player.GetDeadPlayer();
                        if (!check_collision)
                            check_collision = SDLCommonFunc::CheckCollision(player_move, monster_xy);
                        else
                            check_collision = false;
                        if(check_collision)
                        {
                            move_value = 0;
                            bool check_dead_monster = p_monster -> Get_Dead();      //tranh xung dot dead voi attack
                            if(!check_dead_monster)
                            {
                                p_monster -> AttackPlayer();
                                bool check_dead_player =  p_monster -> Get_Attack();        //sat thuong player nhan vao
                                if(check_dead_player)
                                    p_player.PlayerDead();
                                if(p_monster->Get_Audio())
                                    Sounds.PlaySound("slime_attack");
                            }
                        }
                        else
                        {
                            move_value = SDLCommonFunc::CheckDirection(player_move, monster_xy);
                            p_monster -> RunToPlayer(move_value);
                        }
                    }
            }
        }

        p_player.set_clips();
        p_player.Show(g_screen);

        //show hp player
         std::string str_hp = "HP: ";
         int hp = p_player.GetHP();
         if(hp > HP_PLAYER/3)
            {
                HP.SetColor(TextObject::WHILE_TEXT);
            }
            else
            {
                HP.SetColor(TextObject::RED_TEXT);
            }
         int val_hp = hp;
         int x =  p_player.GetRect().x;
        int y = p_player.GetRect().y;

        str_hp += std::to_string(val_hp);
        HP.SetText(str_hp);
        HP.LoadFromRenderText(font_hp, g_screen);
        HP.RenderText(g_screen, x + 20, y + 20);

        std::string str_point = "";
        Point.SetColor(TextObject::RED_TEXT);
        str_point += std::to_string(point);
        Point.SetText(str_point);
        Point.LoadFromRenderText(font_hp, g_screen);
        Point.RenderText(g_screen, SCREEN_WIDTH/2, 20);


        SDL_RenderPresent(g_screen);
        int real_time =fps.getTicks();
        int one_frame = 1000/FPS;

        if(real_time < one_frame)
        {
            int delay_time = one_frame - real_time;
            if(delay_time >= 0)
            SDL_Delay(delay_time);
        }
    }
    close();
    return 0;
}