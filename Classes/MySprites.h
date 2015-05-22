
#include "cocos2d.h"
#include "mythisSprite.h"
USING_NS_CC;
class MySprites
{
public:
	MySprites();
	~MySprites();
	static MySprites *getInstence();
	std::vector<mythisSprite * > _sprites;
};