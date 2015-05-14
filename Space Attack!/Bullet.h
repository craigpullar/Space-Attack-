#pragma once
#include "gameobject.h"
class Bullet : public GameObject
{
	private:

	public:
		Bullet();
		void Destroy();

		void Init(ALLEGRO_BITMAP *image = NULL);
		void Update();
		void Render();

		ALLEGRO_BITMAP *image;

		void ResetAnimation(int position);
		void Collided(int objectID);
		void Fire(int shipX, int shipY);

};

