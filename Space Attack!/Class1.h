#pragma once
#include "enemy.h"
class Class1 :	public Enemy
{
private:
	lives = 1;
public:
	Class1();

	void Init(ALLEGRO_BITMAP *image,int velX = 6, int velY = 6);
	void Update();
	void Reset();
	void Render();

	ALLEGRO_BITMAP *image;

	void ResetAnimation(int position);
};

