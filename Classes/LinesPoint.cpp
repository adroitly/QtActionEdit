#include "LinesPoint.h"


LinesPoint::LinesPoint()
{
}


LinesPoint::~LinesPoint()
{
	delete this;
}

void LinesPoint::setVec(double width, double height)
{
	this->width = width;
	this->height = height;
	mypoint = Vec2(width, height);
}