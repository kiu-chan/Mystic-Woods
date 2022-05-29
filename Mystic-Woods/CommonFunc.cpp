
#include "CommonFunc.h"

bool SDLCommonFunc::CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2)
{
    int left_a = object1.x;
  int right_a = object1.x + object1.w;
  int top_a = object1.y;
  int bottom_a = object1.y + object1.h;
 
  int left_b = object2.x;
  int right_b = object2.x + object2.w;
  int top_b = object2.y;
  int bottom_b = object2.y + object2.h;
 
  // Case 1: size object 1 < size object 2
  if (left_a > left_b && left_a < right_b)
  {
    if (top_a > top_b && top_a < bottom_b)
    {
      return true;
    }
  }
 
  if (left_a > left_b && left_a < right_b)
  {
    if (bottom_a > top_b && bottom_a < bottom_b)
    {
      return true;
    }
  }
 
  if (right_a > left_b && right_a < right_b)
  {
    if (top_a > top_b && top_a < bottom_b)
    {
      return true;
    }
  }
 
  if (right_a > left_b && right_a < right_b)
  {
    if (bottom_a > top_b && bottom_a < bottom_b)
    {
      return true;
    }
  }
  
  // Case 2: size object 1 < size object 2
  if (left_b > left_a && left_b < right_a)
  {
    if (top_b > top_a && top_b < bottom_a)
    {
      return true;
    }
  }
 
  if (left_b > left_a && left_b < right_a)
  {
    if (bottom_b > top_a && bottom_b < bottom_a)
    {
      return true;
    }
  }
 
  if (right_b > left_a && right_b < right_a)
  {
    if (top_b > top_a && top_b < bottom_a)
    {
      return true;
    }
  }
 
  if (right_b > left_a && right_b < right_a)
  {
    if (bottom_b > top_a && bottom_b < bottom_a)
    {
      return true;
    }
  }
 
   // Case 3: size object 1 = size object 2
  if (top_a == top_b && right_a == right_b && bottom_a == bottom_b)
  {
    return true;
  }
 
  return false; 
}

bool SDLCommonFunc::CheckMove(const SDL_Rect& object1, const SDL_Rect& object2)
{
  int x = abs(object1.x - object2.x);
  int y = abs(object1.y - object2.y);//std::cout << object1.x << " " << object1.y << std::endl;
  float vector_to_player = sqrt(x*x + y*y);//std::cout << vector_to_player << std::endl;

  if (vector_to_player < MIN_ATTACK_DISTANCE*SIZE)
    return true;
  else
    return false;
}

int SDLCommonFunc::CheckDirection(const SDL_Rect& object1, const SDL_Rect& object2)
{
  int x = object2.x - object1.x;
  int y = object2.y - object1.y;

  int direction = 0;
  
  if(x == 0)
  {
    if(y > 0)
    {
      direction = 3;
    }
    else if(y < 0)
    {
      direction = 6;
    }
  }

  if (y == 0)
  {
    if(x > 0)
    {
      direction = 2;
    }
    else if(x < 0)
    {
      direction = 1;
    }
  }

  if(x > 0)
  {
    if(y > 0)
    {
      direction = 4;
    }
    else if(y < 0)
    {
      direction = 8;
    }
  }

  if(x < 0)
  {
    if(y > 0)
    {
      direction = 5;
    }
    else if(y < 0)
    {
      direction = 7;
    }
  }
  
  return direction;
}

/*
*/