#include "MySprites.h"

static MySprites * _MySprites;

MySprites::MySprites()
{
	
}


MySprites::~MySprites()
{
}
MySprites * MySprites::getInstence()
{
	if (!_MySprites)
	{
		_MySprites = new MySprites();
	}
	return _MySprites;
}