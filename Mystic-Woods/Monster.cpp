#include "Monster.h"

#define MONSTER_SPEED 5
Monster::Monster()
{
    width_frame = 0;
    height_frame = 0;
    x_val = 0;
    y_val = 0;
    x_pos = 0;
    y_pos = 0;

    combacktime = 0;

    frame = 0;
    start_frame = 0;
    short_frame = 0;
    max_frame = 0;
    max_slime_frame = 7;
    max_skeleton_frame = 6;

        //thoi gian hoi cac trang thai
    status_time = 10;
    time_move = TIME_MOVE;
    revival_time = 0;
    delay_attack = DELAY_ATTACK;

        //gia tri cac trang thai
    stop_slime_frame = 3;
    stop_skeleton_frame = 0;
    move_slime_frame = 1;
    move_skeleton_frame = 0;
    attack_slime_frame = 0;
    attack_skeleton_frame = 1;
    hp_slime_frame = 4;
    hp_skeleton_frame = 3;
    dead_slime_frame = 2;
    dead_skeleton_frame = 1;
    dead_monster_frame = 2;

        //kiem tra cac trang thai
    check_monster_dead = false;
    check_hp_monster = false;
    check_hp_frame = false;
    check_run = false;
    check_attack = false;
    check_damage_monster = false;
    hp_monster = HP_MONSTER;
    check_time = false;
}

Monster::~Monster()
{

}

void Monster::LoadMap(std::string name)
{
    FILE* fp = NULL;
    fopen_s(&fp, name.c_str(), "rb");
    if(fp == NULL)
    {
        return ;
    }
    monster_map.max_x = 0;
    monster_map.max_y = 0;
    int num = 0;
    for(int i = 0; i < MAX_Y; i++)
    {
        for(int j = 0; j < MAX_X; j++)
        {
            fscanf(fp, "%d", &monster_map.tile[i][j]);
            int val = monster_map.tile[i][j];
            if(val > 0)
            {
                monster_map.types[num] = val;
                monster_map.y[num] = i;
                monster_map.x[num] = j;
                num++;
                if(j > monster_map.max_x)
                {
                    monster_map.max_x = j;
                }

                if(i > monster_map.max_y)
                {
                    monster_map.max_y = i;
                }
            }
        }
    }
    monster_map.max_x = (monster_map.max_x)*SIZE;
    monster_map.max_y = (monster_map.max_y)*SIZE;

    monster_map.start_x = 0;
    monster_map.start_y = 0;

    monster_map.file_name = name.c_str();
    fclose(fp);

}

bool Monster::LoadImg(std::string path, SDL_Renderer * screen, int types_)
{
    if(types_ == 1)
    {
        short_frame = stop_slime_frame;
        max_frame = MAX_FRAME_SLIME;
        short_frame = stop_slime_frame;
        dead_monster_frame = dead_slime_frame;
        types_monster = 1;
    }
    if(types_ == 2)
    {
        short_frame = stop_skeleton_frame;
        max_frame = MAX_FRAME_SKELETON;
        short_frame = stop_skeleton_frame;
        dead_monster_frame = dead_skeleton_frame;
        types_monster = 2;
    }
    bool ret = BaseObject::LoadImg(path, screen);
    if(ret)
    {
        width_frame = rect_.w/max_frame;
        height_frame = rect_.h/MAX_FRAME_H;
    }
    return ret;
}

void Monster::Set_clip()
{
    if(width_frame > 0 && height_frame > 0)
    {
    frameClip[0].x = 0;
    frameClip[0].y = start_frame * height_frame;
    frameClip[0].w = width_frame;
    frameClip[0].h = height_frame;

    for(int i = 1; i < max_frame - short_frame; i++)
    {
        frameClip[i].x = i*width_frame;
        frameClip[i].y = start_frame * height_frame;
        frameClip[i].w = width_frame;
        frameClip[i].h = height_frame;
    }
    }
}

void Monster::Show(SDL_Renderer* des, int types_)
{
    if(combacktime == 0)
    {
        switch(move_)
        {
            case WALK_LEFT:
            {
                flip_ = SDL_FLIP_HORIZONTAL;
            }
            break;

            case WALK_RIGHT:
            {
                if(flip_ == SDL_FLIP_HORIZONTAL)
                    flip_ = SDL_FLIP_NONE;
            }
            break;
        
            case WALK_UP:
            {
                if(input_type.direction_)
                {
                    flip_ = SDL_FLIP_HORIZONTAL;
                }
                else
                {
                  if(flip_ == SDL_FLIP_HORIZONTAL)
                        flip_ = SDL_FLIP_NONE;
                }
            }
            break;

            case WALK_UP_LEFT:
            {
                if(input_type.direction_)
                {
                    flip_ = SDL_FLIP_HORIZONTAL;
                }
                else
                {
                  if(flip_ == SDL_FLIP_HORIZONTAL)
                        flip_ = SDL_FLIP_NONE;
                }
            }
            break;

            case WALK_UP_RIGHT:
            {
                if(input_type.direction_)
                {
                    flip_ = SDL_FLIP_HORIZONTAL;
                }
                else
                {
                  if(flip_ == SDL_FLIP_HORIZONTAL)
                        flip_ = SDL_FLIP_NONE;
                }
            }
            break;

            case WALK_DOWN:
            {
                if(input_type.direction_)
                {
                    flip_ = SDL_FLIP_HORIZONTAL;
                }
                else
                {
                    if(flip_ == SDL_FLIP_HORIZONTAL)
                        flip_ = SDL_FLIP_NONE;
                }
            } 
            break;

            case WALK_DOWN_LEFT:
            {
                if(input_type.direction_)
                {
                    flip_ = SDL_FLIP_HORIZONTAL;
                }
                else
                {
                    if(flip_ == SDL_FLIP_HORIZONTAL)
                        flip_ = SDL_FLIP_NONE;
                }
            }
            break;

            case WALK_DOWN_RIGHT:
            {
                if(input_type.direction_)
                {
                    flip_ = SDL_FLIP_HORIZONTAL;
                }
                else
                {
                    if(flip_ == SDL_FLIP_HORIZONTAL)
                        flip_ = SDL_FLIP_NONE;
                }
            }
            break;

            case WALK_STOP:
            {
                if(input_type.direction_)
                {
                    flip_ = SDL_FLIP_HORIZONTAL;
                }
                else
                {
                    if(flip_ == SDL_FLIP_HORIZONTAL)
                        flip_ = SDL_FLIP_NONE;
                }
            }
            break;
        }

        rect_.x = x_pos - map_x;
        rect_.y = y_pos - map_y;

        frame ++;

        

        if(frame >= max_frame - short_frame)
        {
            if(check_hp_monster)
            {
                move_ = 0;
                frame = 0;
                check_hp_monster = false;
            }else if(check_monster_dead)
            {
                if(types_ == 1)
                    {
                        frame = 4;
                    }
                    else if(types_ == 2)
                    {
                        frame = 3;
                    }
                move_ = DEAD;
                delay_attack = DELAY_ATTACK;
                start_frame = 4;
                //check_attack  = false;
            }
            else if(check_attack)
            {
                delay_attack = DELAY_ATTACK;
                check_attack = false;
                frame = 0;
            }
            else
            {
                frame = 0;
            }
        }
        SDL_Rect* currentClip = &frameClip[frame];
        SDL_Rect rendQuad = {rect_.x, rect_.y, width_frame*RATIO_PLAYER, height_frame*RATIO_PLAYER};
        SDL_RenderCopyEx(des, p_object_, currentClip, &rendQuad, 0, NULL, flip_);
    }
}


void Monster::AutoMove(int move_value)
{
    check_damage_monster = false;

    if(check_hp_monster)
    {
        move_ = HP;
    }

    if(check_monster_dead)
    {
        move_ = DEAD;
    } else{
        if(!check_run && !check_attack)      //neu player khong vao pham vi va bi tan cong -> di chuyen tu do
        {
            if(status_time <= 0)
            {
                move_ =  move_value;
                status_time = STATUS_TIME;
            }
            else
            {
                if(move_ != 0 && time_move <= 0)
                {
                    move_ = 0;
                    time_move = TIME_MOVE;
                }
                else
                {
                    time_move --;
                }
                status_time --;
            }

        }
    }

    if(move_ == WALK_RIGHT || move_ == WALK_UP_RIGHT || move_ == WALK_DOWN_RIGHT)
    {
        input_type.direction_ = false;
    }
    else
    {
        if(move_ == WALK_LEFT || move_ == WALK_UP_LEFT || move_ == WALK_DOWN_LEFT)
            input_type.direction_ = true;
    }

    switch (move_)
    {
    case WALK_STOP:
    {
        input_type.right_ = 0;
        input_type.left_ = 0;
        input_type.down_ = 0;
        input_type.up_ = 0;
        start_frame = 0;
        if(types_monster == 1)
        {
            short_frame = stop_slime_frame;
        }
        else if(types_monster == 2)
        {
            short_frame = stop_skeleton_frame;
        }
        //short_frame = 0;
    }
    break;

    case WALK_RIGHT:
        {
            input_type.right_ = 1;
            input_type.left_ = 0;
            input_type.down_ = 0;
            input_type.up_ = 0;
            start_frame = 1;
            if(types_monster == 1)
            {
                short_frame = move_slime_frame;
            }
            else if(types_monster == 2)
            {
                short_frame = move_skeleton_frame;
            }
            //short_frame = 0;
        }
    break;

    case WALK_LEFT:
        {
            input_type.left_ = 1;
            input_type.right_ = 0;
            input_type.down_ = 0;
            input_type.up_ = 0;
            start_frame = 1;
            if(types_monster == 1)
            {
                short_frame = move_slime_frame;
            }
            else if(types_monster == 2)
            {
                short_frame = move_skeleton_frame;
            }
            //short_frame = 0;
        }
    break;

    case WALK_UP:
    {
        input_type.up_ = 1;
        input_type.down_ = 0;
        input_type.left_ = 0;
        input_type.right_ = 0;
        start_frame = 1;
        if(types_monster == 1)
        {
            short_frame = move_slime_frame;
        }
        else if(types_monster == 2)
        {
            short_frame = move_skeleton_frame;
        }
        //short_frame = 0;
    }
    break;

    case WALK_UP_LEFT:
    {
        input_type.up_ = 1;
        input_type.down_ = 0;
        input_type.left_ = 1;
        input_type.right_ = 0;
        start_frame = 1;
        if(types_monster == 1)
        {
            short_frame = move_slime_frame;
        }
        else if(types_monster == 2)
        {
            short_frame = move_skeleton_frame;
        }
    }
    break;

    case WALK_UP_RIGHT:
    {
        input_type.up_ = 1;
        input_type.down_ = 0;
        input_type.left_ = 0;
        input_type.right_ = 1;
        start_frame = 1;
        if(types_monster == 1)
        {
            short_frame = move_slime_frame;
        }
        else if(types_monster == 2)
        {
            short_frame = move_skeleton_frame;
        }
    }
    break;

    case WALK_DOWN:
    {
        input_type.down_ = 1;
        input_type.up_ = 0;
        input_type.left_ = 0;
        input_type.right_ = 0;
        start_frame = 1;
        if(types_monster == 1)
        {
            short_frame = move_slime_frame;
        }
        else if(types_monster == 2)
        {
            short_frame = move_skeleton_frame;
        }
        //short_frame = 0;
    }
    break;

    case WALK_DOWN_LEFT:
    {
        input_type.down_ = 1;
        input_type.up_ = 0;
        input_type.left_ = 1;
        input_type.right_ = 0;
        start_frame = 1;
        if(types_monster == 1)
        {
            short_frame = move_slime_frame;
        }
        else if(types_monster == 2)
        {
            short_frame = move_skeleton_frame;
        }
    }
    break;

    case WALK_DOWN_RIGHT:
    {
        input_type.down_ = 1;
        input_type.up_ = 0;
        input_type.left_ = 0;
        input_type.right_ = 1;
        start_frame = 1;
        if(types_monster == 1)
        {
            short_frame = move_slime_frame;
        }
        else if(types_monster == 2)
        {
            short_frame = move_skeleton_frame;
        }
    }
    break;

    case ATTACK:
    {
        start_frame = 2;
        if(types_monster = 1)
        {
            short_frame = attack_slime_frame;
        }
        else if(types_monster = 2)
        {
            short_frame = attack_skeleton_frame;
        }
        check_damage_monster = true;
    }
    break;

    case HP:
    {
        input_type.right_ = 0;
        input_type.left_ = 0;
        input_type.down_ = 0;
        input_type.up_ = 0;
        start_frame =  3;
        if(types_monster == 1)
        {
            short_frame = hp_slime_frame;
        }
        else if(types_monster == 2)
        {
            short_frame = hp_skeleton_frame;
        }
    }
    break;

    case DEAD:
    {
        input_type.right_ = 0;
        input_type.left_ = 0;
        input_type.down_ = 0;
        input_type.up_ = 0;
        start_frame = 4;
        if(types_monster == 1)
        {
            short_frame = dead_slime_frame;
        }else if(types_monster == 2)
        {
            short_frame = dead_skeleton_frame;
        }
        if(revival_time == 0)
        {
            revival_time = REVIVAL_TIME;
            check_time = true;
        }
        else
        {
            revival_time--;
            check_time = false;
        }
    }
    break;
    }

    if(revival_time > 0)
        revival_time --;
    else if(check_monster_dead && revival_time <= 0)
    {
        move_ = WALK_STOP;
        check_monster_dead = false;
        revival_time = 0;
        hp_monster = HP_MONSTER;
    }

}

void Monster::DoMonster(Map& gMap)
{
    if(combacktime == 0)
    {
        x_val = 0;
        y_val = 0;
        if(input_type.left_ == 1)
        {
          x_val -= MONSTER_SPEED;
        }
        else
        {
            if(input_type.right_ == 1)
            {
                x_val += MONSTER_SPEED;
            }
        }

        if(input_type.up_ == 1)
        {
            y_val -= MONSTER_SPEED;
        }
        else
        {
            if(input_type.down_ == 1)
            {
                y_val += MONSTER_SPEED;
            }
        }
        CheckToMap(gMap);
    }
    else if(combacktime > 0)
    {
        combacktime --;
        if(combacktime == 0)
        {
            x_val = 0;
            y_val = 0;
            x_pos = 0;
            y_pos = 0;
            combacktime = STATUS_TIME;
        }
    }
}

void Monster::CheckToMap(Map& gMap)
{
     int x1 = 0;
     int x2 = 0;

     int y1 = 0;
     int y2 = 0;

     int move_limit_check;

     //ngang
     int height_min = height_frame < SIZE ? height_frame : SIZE;
     x1 = (x_pos + x_val)/SIZE + SIZE_BACK;
     x2 = (x_pos + x_val + width_frame*RATIO_PLAYER - 1)/SIZE - SIZE_BACK;

     y1 = (y_pos)/SIZE;
     y2 = (y_pos + height_min*RATIO_PLAYER - 1) /SIZE;

     move_limit_check = sqrt(abs(x1*x1) + abs(y1*y1));
     if(move_limit_check > MOVE_LIMIT)
     {
         x_val = 0;
         y_val = 0;
     }
     if(x1 >= 0 && x2 < MAX_X && y1 >= 0 && y2 < MAX_Y)
     {
         if(x_val > 0) //sang phai
         {
             for(int i = y1 + SIZE_BACK*2; i <= y2; i++)
                if(gMap.tile[i][x2] != BLANK_TILE)
                {
                    x_pos = (x2 + SIZE_BACK)*SIZE;
                    x_pos -= (width_frame*RATIO_PLAYER + 1);
                    x_val = 0;
                    move_ = 0;         //ngung di chuyen khi va cham
                }
         }
        else if(x_val < 0) //sang trai
             {
                for(int i = y1 + SIZE_BACK*2; i <= y2; i++)
                    if(gMap.tile[i][x1] != BLANK_TILE)
                    {
                        x_pos = (x1 - SIZE_BACK + 1)*SIZE;
                        x_val = 0;
                        move_ = 0;         //ngung di chuyen khi va cham
                    }
             }
     }

     //doc

     int width_min = width_frame < SIZE ? width_frame : SIZE;
     x1 = (x_pos)/SIZE;
     x2 = (x_pos + width_min*RATIO_PLAYER)/SIZE;

     y1 = (y_pos + y_val)/SIZE + SIZE_BACK;
     y2 = (y_pos + y_val + height_frame*RATIO_PLAYER - 1)/SIZE;

     if(x1 >= 0 && x2 < MAX_X && y1 >= 0 && y2 < MAX_Y)
     {
         if(y_val > 0)   // xuong
         {
             for(int i = x1 + SIZE_BACK*2; i <= x2 - SIZE_BACK; i++)
                if(gMap.tile[y2][i] != BLANK_TILE)
                {
                    y_pos = y2*SIZE;
                    y_pos -= (height_frame*RATIO_PLAYER + 1);
                    y_val = 0;
                    move_ = 0;         //ngung di chuyen khi va cham
                }
         }
         else if(y_val < 0)   // len
         {
             for(int i = x1 + SIZE_BACK*2; i <= x2 - SIZE_BACK; i++)
                if(gMap.tile[y1][i] != BLANK_TILE)
                {
                    y_pos = (y1 - SIZE_BACK  + 1)*SIZE;
                    y_val = 0;
                    move_ = 0;         //ngung di chuyen khi va cham
                }
         }
     }

     x_pos += x_val;
     y_pos += y_val;

     if(x_pos < 0)
     {
         x_pos = 0;
     }
     else if(x_pos + width_frame > gMap.max_x)
     {
         x_pos = gMap.max_x - width_frame - 1;
     }

     
    if(y_pos + SIZE_BACK*SIZE < 0)
    {
        y_pos = 0 - SIZE_BACK*SIZE;
    }
    else if(y_pos + height_frame + SIZE > gMap.max_y)
    {
        y_pos = gMap.max_y -SIZE - height_frame - 1;
    }

}

void Monster::MonsterDead()
{
    if(hp_monster - DAMAGE_TO_MONSTER > 0)
    {
        hp_monster -= DAMAGE_TO_MONSTER;
        check_hp_monster = true;
        check_monster_dead = false;
    }
    else
    {
        check_monster_dead = true;
        hp_monster = 0;
        check_hp_monster = false;
        move_ = DEAD;
        check_attack = false;
    }
}

void Monster::RunToPlayer(int Move_value)
{
    check_run = true;
    move_ = Move_value;     //duoi theo player
    delay_attack = START_ATTACK;
}

void Monster::AttackPlayer()
{
    if(delay_attack <= 0)
    {
        check_attack = true;
        move_ = ATTACK;
    }
    else
    {
        delay_attack--;
        move_ = WALK_STOP;
        check_attack = false;
    }
}

void Monster::RevivalMonster()
{
    width_frame = 0;
    height_frame = 0;
    x_val = 0;
    y_val = 0;
    x_pos = 0;
    y_pos = 0;

    combacktime = 0;

    frame = 0;
    start_frame = 0;
    short_frame = 0;
    max_frame = 0;
    max_slime_frame = 7;
    max_skeleton_frame = 6;

    // thoi gian hoi cac trang thai
    status_time = 10;
    time_move = TIME_MOVE;
    revival_time = 0;
    delay_attack = DELAY_ATTACK;

    // gia tri cac trang thai
    stop_slime_frame = 3;
    stop_skeleton_frame = 0;
    move_slime_frame = 1;
    move_skeleton_frame = 0;
    attack_slime_frame = 0;
    attack_skeleton_frame = 1;
    hp_slime_frame = 4;
    hp_skeleton_frame = 3;
    dead_slime_frame = 2;
    dead_skeleton_frame = 1;
    dead_monster_frame = 2;

    // kiem tra cac trang thai
    check_monster_dead = false;
    check_hp_monster = false;
    check_hp_frame = false;
    check_run = false;
    check_attack = false;
    check_damage_monster = false;
    hp_monster = HP_MONSTER;
}