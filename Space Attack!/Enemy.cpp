#include "Enemy.h"


Enemy::Enemy()
{
}

void Enemy::Init(ALLEGRO_BITMAP *image,int velX, int velY)
{
	srand (time(NULL));
	GameObject::Init(25 + rand() % (DisplayWidth-50),rand() % -DisplayHeight,velX,velY,0,0,10,10);
	SetID(ENEMY);
	SetAlive(true);

	if(image != NULL)
		Enemy::image = image;
}
void Enemy::Destroy()
{
	GameObject::Destroy();
}
void Enemy::Update()
{
	GameObject::Update();
	dirY =+ 1;
	if (y > DisplayHeight)
		Enemy::Reset();
}
void Enemy::Render()
{
	GameObject::Render();
	al_draw_bitmap_region(image, 0, 0, frameWidth, frameHeight,
		x- frameWidth/ 2, y - frameHeight / 2, 0);
}
void Enemy::ResetAnimation(int position)
{
}
void Enemy::Collided(int objectID)
{
	if(objectID == PLAYER)
		SetAlive(false);
	else if(objectID == BULLET)
		LoseLife();
	if (lives <= 0)
		SetAlive(false);
}
void Enemy::Fire(int enemyX, int enemyY)
{
	GameObject::Fire(enemyX,enemyY);
}
void Enemy::Reset()
{
	SetAlive(true);
	SetX(rand() % DisplayWidth);
	SetY(-(rand() % DisplayHeight));
}
