#pragma once
#include "gameobject.h"
class Enemy : public GameObject
{
	public:
		Enemy();
		void Destroy();

		void Init(ALLEGRO_BITMAP *image = NULL, int velX = 6, int velY = 6);
		void Update();
		void Render();
		void Reset();
		void Fire(int enemyX, int enemyY);

		ALLEGRO_BITMAP *image;

		void ResetAnimation(int position);
		void Collided(int objectID);

		
};

