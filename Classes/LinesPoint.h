#pragma once
#include "cocos2d.h"
USING_NS_CC;
class LinesPoint
{
public:
	LinesPoint();
	~LinesPoint();
	void setVec(double width, double height);
	double width;
	double height;
	Vec2 mypoint;
};

