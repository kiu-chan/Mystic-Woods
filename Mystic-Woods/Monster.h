#ifndef MONSTER_H
#define MONSTER_H


#include "CommonFunc.h"

#define MONSTER_MAX_SPEED 8

class Monster : public BaseObject
{
    public:
    Monster();
    ~Monster();

    enum Walktype
    {
        WALK_STOP = 0,
        WALK_RIGHT = 1,
        WALK_LEFT = 2,
        WALK_UP = 3,
        WALK_UP_LEFT = 4,
        WALK_UP_RIGHT = 5,
        WALK_DOWN = 6,
        WALK_DOWN_RIGHT = 7,
        WALK_DOWN_LEFT = 8,
        ATTACK = 9,
        HP = 10,
        DEAD = 11,
        REVIVAL = 12,
    };

    void LoadMap(std::string name);
    Map getMap() const {return monster_map;}
    void SetMap(Map& map_data) {monster_map = map_data;}

    void set_x_val(const float& xVal) {x_val = xVal;}
    void set_y_val(const float& yVal) {y_val = yVal;}

    void set_x_pos(const float& xPos) {start_monster_x = xPos; x_pos = xPos;}
    void set_y_pos(const float& yPos) {start_monster_y = yPos; y_pos = yPos;}

    float get_x_pos() const {return x_pos;}
    float get_y_pos() const {return y_pos;}
    void SetMapXY(const int& mp_x, const int& mp_y) {map_x = mp_x; map_y = mp_y;}

    void Set_clip();
    bool LoadImg(std::string path, SDL_Renderer* screen, int types_);
    void Show(SDL_Renderer* des, int types_);
    int get_width_frame() const {return width_frame;}
    int get_height_frame() const {return height_frame;}
    void DoMonster(Map& gMap);
    void CheckToMap(Map& gMap);
    void AutoMove(int move_value);
    void RunToPlayer(int move_value);
    void AttackPlayer();
    void MonsterDead();
    void RevivalMonster();

    bool Get_Attack() const {return check_damage_monster;}
    bool Get_Dead() const {return check_monster_dead;}
    int GetHP() const {return hp_monster;}
    bool Get_Audio() const {return check_attack;}

private:

    int map_x;
    int map_y;
    float x_val;
    float y_val;
    float x_pos;
    float y_pos;
    int combacktime;
    SDL_Rect frameClip[8];
    int width_frame;
    int height_frame;
    int start_frame;
    int short_frame;
    int frame;
    int max_frame;
    int max_slime_frame;
    int max_skeleton_frame;

    float start_monster_x;
    float start_monster_y;;

    int move_;
    int status_time;
    int time_move;
    int revival_time;
    int delay_attack;

    int stop_slime_frame;
    int stop_skeleton_frame;
    int move_slime_frame;
    int move_skeleton_frame;
    int attack_slime_frame;
    int attack_skeleton_frame;
    int hp_slime_frame;
    int hp_skeleton_frame;
    int dead_slime_frame;
    int dead_skeleton_frame;
    int dead_monster_frame;

    bool check_monster_dead;
    bool check_hp_monster;
    bool check_hp_frame;
    bool check_run;     //chay ve phia nguoi choi
    bool check_attack;
    bool check_damage_monster;
    int hp_monster;

    Map monster_map;
    Input input_type;

    int types_monster;  //luu loai quai

    SDL_RendererFlip flip_ = SDL_FLIP_NONE;

};



#endif