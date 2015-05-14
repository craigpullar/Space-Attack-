#include "Class2.h"


Class2::Class2()
{
}
void Class2::Init(ALLEGRO_BITMAP *image)
{
	Enemy::Init(image,4,4);
	frameWidth = 50;
	frameHeight = 50;

	if(image != NULL)
		Class2::image = image;
	lives = 3;

}
void Class2::Update()
{
	Enemy::Update();

}
void Class2::Reset()
{
	Enemy::Reset();
	lives = 3;
}
void Class2::Render()
{
		al_draw_bitmap_region(image, 0, 0, frameWidth, frameHeight,
		x- frameWidth/ 2, y - frameHeight / 2, ALLEGRO_FLIP_VERTICAL);
}
void Class2::Fire(int enemyX, int enemyY)
{

}
void Class2::ResetAnimation(int position)
{
}
void Class2::Collided(int objectID)
{
	Enemy::Collided(objectID);
}