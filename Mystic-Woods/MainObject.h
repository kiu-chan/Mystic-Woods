#ifndef MAIN_OBJECT_H
#define MAIN_OBJECT_H


#include "CommonFunc.h"


class MainObject : public BaseObject
{
    public:
    MainObject();
    ~MainObject();

    enum Walktype
    {
        WALK_STOP = 0,
        WALK_RIGHT = 1,
        WALK_LEFT = 2,
        WALK_UP = 3,
        WALK_DOWN = 4,
        ATTACK = 5,
        HP = 6,
        DEAD = 7,
    };

    bool LoadImg(std::string path, SDL_Renderer* screen);
    void Show(SDL_Renderer* des);
    void HandelInputActive(SDL_Event events, SDL_Renderer* screen);
    void set_clips();

    void DoPlayer(Map& map_data);
    void CheckToMap(Map& map_data);
    void SetMapXY(const int map_x, const int map_y) {map_x_ = map_x; map_y_ = map_y;};
    void SetMenu();
    void CenterEntityOnMap(Map& map_data);
    void PlayerDead();
    void RevivalPlayer();

    SDL_Rect GetAttackMonster() const {return attack_monster;}
    int GetStatus() const {return status_;}
    float Get_x_pos() const {return x_pos;}
    float Get_y_pos() const {return y_pos;}
    int get_width_frame() const {return width_frame;}
    int get_height_frame() const {return height_frame;}
    int GetHP() const {return hp_player;}
    bool GetMenuDead() const {return check_menu_dead;}
    bool GetDeadPlayer() const {return check_dead_player;}
    
private:
    float x_val;
    float y_val;

    float x_pos;
    float y_pos;

    int width_frame;
    int height_frame;
    int start_frame;
    int attack_frame;
    int start_attack;
    bool check_attack;
    int dead_frame;
    int short_frame;
    int delay_frame;

    int hp_player;

    bool check_hp_player;
    bool check_dead_player;
    bool check_menu_dead;

    SDL_Rect frame_clip[MAX_FRAME];
    SDL_Rect attack_monster;
    Input input_type_;
    int frame_;
    int status_;

    int map_x_;
    int map_y_;


    SDL_RendererFlip flip_ = SDL_FLIP_NONE;
};



#endif