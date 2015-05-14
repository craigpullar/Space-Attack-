#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <list>
#include <array>

#include "globals.h"
#include "GameObject.h"
#include "SpaceShip.h"
#include "Bullet.h"
#include "Class2.h"
#include "Class1.h"
 
//*MAIN VARIABLES*//
enum KEY{UP,DOWN,LEFT,RIGHT,SPACE,CLOSE};
bool key[6] = {false, false, false, false, false, false};
const int noBullets = 3;
const int noClass1 = 5;
const int noClass2 = 3;

//globls
SpaceShip *ship;
Bullet *bullet[noBullets];
Class1 *class1[noClass1];
Class2 *class2[noClass2];
std::list<GameObject *> objects;
std::list<GameObject *>::iterator iter;
std::list<GameObject *>::iterator iter2;

int main(int argc, char **argv)
{
	//*PROJECT VARIABLES*//
	bool done = false;
	bool render = false;

	float GameTime = 0;
	int frames = 0;
	int GameFPS = 0;


	//*INITIALIZE ALLEGRO ADDONS*//
	al_init();
	al_install_keyboard();
	al_install_audio();
	al_init_image_addon();
	al_init_acodec_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_primitives_addon();

	//*ALLEGRO OBJECTS*//
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer;
	ALLEGRO_FONT *font18;
	ALLEGRO_BITMAP *shipImage;

	//*INIT ALLEGRO OBJECTS*//
    display = al_create_display(DisplayWidth, DisplayHeight);
	event_queue = al_create_event_queue();
	timer = al_create_timer(1.0/60);
	font18 = al_load_font("fonts/default.ttf",18,0);

	al_set_window_title(display,"Space Attack!");

	al_register_event_source(event_queue,al_get_timer_event_source(timer));
	al_register_event_source(event_queue,al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_display_event_source(display));

	al_start_timer(timer);
	GameTime = al_current_time();
	

	//*INIT IMAGES*//
	shipImage = al_load_bitmap("images/ship.bmp");
	al_convert_mask_to_alpha(shipImage,al_map_rgb(255,0,255));

	//*INIT PROJECT OBJECTS*//
	ship = new SpaceShip();
	ship->Init(shipImage);
	objects.push_back(ship);
	for (int i = 0; i < noBullets; i++)
	{
		bullet[i] = new Bullet();
		bullet[i]->Init(al_load_bitmap("images/bullet.png"));
		al_convert_mask_to_alpha(bullet[i]->image,al_map_rgb(255,0,255));
		objects.push_back(bullet[i]);
	}
	for (int i = 0; i < noClass1; i++)
	{
		class1[i] = new Class1();
		class1[i]->Init(al_load_bitmap("images/class1.png"),6,6);
		al_convert_mask_to_alpha(class1[i]->image,al_map_rgb(255,0,255));
		objects.push_back(class1[i]);
	}
	/*for (int i = 0; i < noClass2; i++) **SECOND LEVEL SHIPS**
	{
		class2[i] = new Class2();
		class2[i]->Init(al_load_bitmap("images/class2.png"));
		al_convert_mask_to_alpha(class2[i]->image,al_map_rgb(255,0,255));
		objects.push_back(class2[i]);
	}*/
	//*ERROR CHECKING*//
	if(!al_init())
		return -1;
	if(!display)
	   return -1;

   //*GAME LOOP*//
	while(!done)
   {
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			done = true;
			break;
		}

		//*INPUT*//
		if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch(ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;
			case ALLEGRO_KEY_RIGHT:
				key[RIGHT] = true;
				break;
			case ALLEGRO_KEY_LEFT:
				key[LEFT] = true;
				break;
			case ALLEGRO_KEY_UP:
				key[UP] = true;
				break;
			case ALLEGRO_KEY_DOWN:
				key[DOWN] = true;
				break;
			case ALLEGRO_KEY_SPACE:
				key[SPACE] = true;
				break;
			}
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_UP)
		{
			switch(ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;
			case ALLEGRO_KEY_RIGHT:
				key[RIGHT] = false;
				break;
			case ALLEGRO_KEY_LEFT:
				key[LEFT] = false;
				break;
			case ALLEGRO_KEY_UP:
				key[UP] = false;
				break;
			case ALLEGRO_KEY_DOWN:
				key[DOWN] = false;
				break;
			case ALLEGRO_KEY_SPACE:
				key[SPACE] = false;
				break;
			}
		}
		//*GAME UPDATE*//
		else if(ev.type == ALLEGRO_EVENT_TIMER)
		{
			render = true;

			//*UPDATE FPS*//
			frames++;
			if(al_current_time() - GameTime >= 1)
			{
				GameTime = al_current_time();
				GameFPS = frames;
				frames = 0;
			}

			if(key[UP])
				ship->MoveUp();
			else if(key[DOWN])
				ship->MoveDown();
			else
				ship->ResetAnimation(1);

			if (key[LEFT])
				ship->MoveLeft();
			else if (key[RIGHT])
				ship->MoveRight();
			else
				ship->ResetAnimation(0);

			if (key[SPACE])
				for (iter = objects.begin(); iter != objects.end(); ++iter)
					if(!(*iter)->GetAlive() & (*iter)->GetID() == BULLET)
					{
						(*iter)->Fire(ship->GetX(),ship->GetY());
						key[SPACE] = false;
						break;
					}

			//update
			for (iter = objects.begin(); iter != objects.end(); ++iter)
			{
				if(!(*iter)->GetAlive())
					(*iter)->Reset();
				else
					(*iter)->Update();
			}

			//collisions
			for(iter = objects.begin(); iter != objects.end(); ++iter)
			{
				if(!(*iter)->Collidable()) continue;

				for(iter2 = iter; iter2 != objects.end(); ++iter2)
				{
					if (!(*iter2)->Collidable()) continue;
					if (((*iter)->GetID() == (*iter2)->GetID())) continue;

					if ((*iter)->checkCollisions((*iter2)))
					{
						(*iter)->Collided((*iter2)->GetID());
						(*iter2)->Collided((*iter)->GetID());
					}
				}
			}

			//cull the dead
		}
		//*RENDER*//
		if (render && al_is_event_queue_empty(event_queue))
		{
			render = false;
			
			al_draw_textf(font18,al_map_rgb(255,0,0),5,5,0,"FPS:  %i",GameFPS);//Display FPS

			for(iter = objects.begin(); iter != objects.end(); ++iter)
				if((*iter)->GetAlive())
					(*iter)->Render();

			//*FLIP BUFFERS*//
			al_flip_display();
			al_clear_to_color(al_map_rgb(0,0,0));
		}
   }

	//*DESTROY OBJECTS*//

   for(iter = objects.begin(); iter != objects.end(); ++iter)
   {
	   (*iter)->Destroy();
	   delete (*iter);
   }
   al_destroy_display(display);
   al_destroy_event_queue(event_queue);
   al_destroy_timer(timer);
   al_destroy_font(font18);
   return 0;
}