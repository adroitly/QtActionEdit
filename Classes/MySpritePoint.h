#pragma once
#include "cocos2d.h"
#include "MyConfig.h"
USING_NS_CC;
class MySpritePoint
{
public:
	MySpritePoint();
	~MySpritePoint();
	void setAttackVertices(Vec2, Vec2);
	void setInjureVertices(Vec2, Vec2);
	void setBodyVertices(Vec2, Vec2);

public:
	int Single_ID;
	Vec2 *attackVertices = nullptr;
	Vec2 *injureVertices = nullptr;
	Vec2 *bodyVertices = nullptr;
	float RotateAtt;
	float RotateInj;
	double _ScallX;
	double _ScallY;
	double _height;
	double _width;
	bool Is_AttFra;
	bool Is_InjFra;
	bool Is_ActFra;
	bool Is_BodyFra;
};

