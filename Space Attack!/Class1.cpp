#include "Class1.h"


Class1::Class1()
{
}
void Class1::Init(ALLEGRO_BITMAP *image = NULL,int velX, int velY)
{
	Enemy::Init(image,4,4);
}
void Class1::Update()
{
}
void Class1::Render()
{
	Enemy::Render();
}
void Class1::Reset()
{
}
void Class1::ResetAnimation(int position)
{
}
