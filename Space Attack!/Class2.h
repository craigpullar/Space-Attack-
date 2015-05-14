#pragma once
#include "enemy.h"
class Class2 : public Enemy
{
private:
	int lives;

public:
	Class2();

	void Init(ALLEGRO_BITMAP *image = NULL);
	void Update();
	void Reset();
	void Render();
	void Fire(int enemyX, int enemyY);
	void Collided(int objectID);

	ALLEGRO_BITMAP *image;

	void ResetAnimation(int position);
	void LoseLife() {lives--;}
};

