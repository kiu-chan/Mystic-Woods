#include "Menu.h"
Menu::Menu()
{

}

Menu::~Menu()
{

}

bool Menu::LoadMenu(std::string path, SDL_Renderer* des)
{
    // bool ret = g_background.LoadImg(path, g_screen);
    // if( ret == false )
    //     return false;
    // else 
    //     return true;
    return BaseObject::LoadImg(path, des);
}

int Menu::ShowMenu(SDL_Renderer* des, TTF_Font* font)
{
  bool img_menu = LoadMenu("assets/menu.png", des);
  if(img_menu == false)
  {
    return 1;
  }

  const int kMenuItemNum = 2;
  SDL_Rect pos_arr[kMenuItemNum];
  pos_arr[1].x = 150;
  pos_arr[1].y = 200;
  
  pos_arr[0].x = 150;
  pos_arr[0].y = 250;

  


  TextObject text_menu[kMenuItemNum];


  text_menu[0].SetText("Exit");
  text_menu[0].SetColor(TextObject::BLACK_TEXT);

  text_menu[1].SetText("Play Game");
  text_menu[1].SetColor(TextObject::BLACK_TEXT);

  for(int i = 0; i < kMenuItemNum; ++i)
  {
      text_menu[i].LoadFromRenderText(font, des);
  }

  pos_arr[1].w = text_menu[1].GetWidth();
  pos_arr[1].h = text_menu[1].GetHeight();

  pos_arr[0].w = text_menu[0].GetWidth();
  pos_arr[0].h = text_menu[0].GetHeight();

  bool selected[kMenuItemNum] = {0, 0};
  int xm = 0;
  int ym = 0;

  SDL_Event m_event;
  
  while(true)
  {
    SDL_RenderClear(des);
    SDL_RenderCopy(des, this->p_object_, NULL, NULL);
    for(int i = 0; i < kMenuItemNum; ++i)
    {
      text_menu[i].LoadFromRenderText(font, des);
      text_menu[i].RenderText(des, pos_arr[i].x, pos_arr[i].y);
    }

    
    SDL_RenderPresent(des);
    while(SDL_PollEvent(&m_event))
    {
      
      switch(m_event.type)
      {
        case SDL_QUIT:
        {
          return 1;
        }
        break;
        
        case SDL_MOUSEMOTION:
        {
          
          xm = m_event.motion.x;
          ym = m_event.motion.y;

          for(int i = 0; i < kMenuItemNum; i++)
            {
              if(CheckFousWithRect(xm, ym, pos_arr[i]))
              {
                if(selected[i] == false)
                {
                  selected[i] = 1;
                  text_menu[i].SetColor(TextObject::RED_TEXT);
                }
                
                
              }else
                {
                  if(selected[i] == true)
                {
                  selected[i] = 0;
                  text_menu[i].SetColor(TextObject::BLACK_TEXT);
                }
                }
            }
        }
        break; 

        case SDL_MOUSEBUTTONDOWN:
        {
          
          xm = m_event.button.x;
          ym = m_event.button.y;
          for(int i = 0; i < kMenuItemNum; i++)
        {
          if(CheckFousWithRect(xm, ym, pos_arr[i]))
          {
            return i;
          }
        }
        }
        break;

        case SDL_KEYDOWN:
        if(m_event.key.keysym.sym == SDLK_ESCAPE)
        {
          return 1;
        }
        break;
      }
    }
  }
  return 0;
}

void Menu::Show(SDL_Renderer* des)
{
  SDL_Rect renderQuad = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
  SDL_Rect bg = {0, 0, width_frame, height_frame};
  SDL_RenderCopy(des, p_object_, &bg, &renderQuad);
}


bool Menu::CheckFousWithRect(const int& x, const int& y, const SDL_Rect& rect)
{
  if(x > rect.x && x <= rect.x + rect.w
    && y> rect.y && y <= rect.y + rect.h)
    {
      return true;
    }
    else
    return false;
}