#include <Math/vector2.h>
#include <Sprite/sprite.h>

struct QuadTreeObject
{
	Vector2f position;
	float halfWidth;

	SpriteSharedData* spriteSharedData;
	Sprite2DInstanceData spriteInstanceData;
};