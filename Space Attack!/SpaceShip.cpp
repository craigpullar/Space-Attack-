#include "SpaceShip.h"

SpaceShip::SpaceShip()
{}

void SpaceShip::Destroy()
{
	GameObject::Destroy();
}

void SpaceShip::Init(ALLEGRO_BITMAP *image)
{
	GameObject::Init(20,200,6,6,0,0,10,10);
	SetID(PLAYER);
	SetAlive(true);

	lives = 3;
	score = 0;

	frameWidth = 50;
	frameHeight= 50;

	if(image != NULL)
		SpaceShip::image = image;
}

void SpaceShip::Update()
{
	GameObject::Update();

	if (x < 0)
		x = 0;
	else if(x > DisplayWidth)
		x = DisplayWidth;

	if (y < 0)
		y = 0;
	else if (y > DisplayHeight)
		y = DisplayHeight;

	if (lives <= 0)
		SetAlive(false);
}

void SpaceShip::Render()
{
	GameObject::Render();
	al_draw_bitmap_region(image, 0, 0, frameWidth, frameHeight,
		x- frameWidth/ 2, y - frameHeight / 2, 0);
}

void SpaceShip::MoveUp()
{
	dirY = -1;
}
void SpaceShip::MoveDown()
{

	dirY = 1;
}
void SpaceShip::MoveLeft()
{
	curFrame = 3;
	dirX =-1;
}
void SpaceShip::MoveRight()
{
	curFrame= 2;
	dirX = 1;
}

void SpaceShip::ResetAnimation(int position)
{
	if(position == 1)
	{
		dirY = 0;
	}
	else
	{
		curFrame = 1;
		dirX= 0;
	}
}

void SpaceShip::Collided(int objectID)
{
	GameObject::Collided(objectID);
	if(objectID == ENEMY)
		LoseLife();
}