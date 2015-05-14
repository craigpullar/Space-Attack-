#include "Bullet.h"


Bullet::Bullet()
{
}

void Bullet::Destroy()
{
	GameObject::Destroy();
}

void Bullet::Init(ALLEGRO_BITMAP *image)
{
	GameObject::Init(200,200,10,10,0,0,10,10);
	SetID(BULLET);
	SetAlive(false);

	frameWidth = 10;
	frameHeight = 10;

	if(image != NULL)
		Bullet::image = image;
}

void Bullet::Update()
{
	GameObject::Update();
	dirY =- 1;
	if (GetY() < frameHeight)
		SetAlive(false);
}

void Bullet::Render() 
{
	GameObject::Render();
	al_draw_bitmap_region(image, 0, 0, frameWidth, frameHeight,
		x- frameWidth/ 2, y - frameHeight / 2, 0);
}

void Bullet::ResetAnimation(int position)
{
}

void Bullet::Collided(int objectID)
{
	if(objectID == ENEMY)
		SetAlive(false);
}

void Bullet::Fire(int shipX, int shipY)
{
	GameObject::Fire(shipX,shipY);
	SetX(shipX);
	SetY(shipY);
	SetAlive(true);
}

