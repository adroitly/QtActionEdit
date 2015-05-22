#include "ActionLayer.h"


ActionLayer::ActionLayer()
{
}


ActionLayer::~ActionLayer()
{
}

ActionLayer * ActionLayer::createLayer()
{
	ActionLayer *layer = ActionLayer::create();
	return layer;
}
bool ActionLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	visibleSize = Director::getInstance()->getVisibleSize();
	orginSize = Director::getInstance()->getVisibleOrigin();
	auto draw = DrawNode::create();
	Vec2 vertices[] = { Vec2(50, 100), Vec2(150, 100), Vec2(200, 200), Vec2(100, 200), Vec2(50, 100)};
	draw->drawPoly(vertices, 5, false, Color4F(CCRANDOM_0_1(), CCRANDOM_0_1(), CCRANDOM_0_1(), 1));
	this->addChild(draw, 10);
	return true;
}
