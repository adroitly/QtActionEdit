#pragma once
#include "cocos2d.h"
#include "MyConfig.h"
USING_NS_CC;
class MyDrawNode 
{
public:
	MyDrawNode();
	~MyDrawNode();
	DrawNode * drawnode;
	void setVertices(Vec2, Vec2);
	void setRotateVertices(Vec2 startPoint, Vec2 EndPoint , float rotate = -720);
	Vec2 getMidPoint();
	float getRotate(Vec2 StartPoint, Vec2 EndPoint, Vec2 minPoint = Vec2( -1000, -1000));
	void setRelativeVertices(Vec2 *points, Vec2 relativeposi);
	void setRelativeRotateVertices(Vec2 *points, Vec2 relativeposi);
	void setVerticeFromRelative(Vec2 * MyRelativeVertices, Vec2 relativeposi);
	void setRotateFromRelativeRotate(Vec2  MyRelativeRotate[5], Vec2 relativeposi);
	void setRelativeScallX(float PosiX , float InitX, float SX);
	void setRelativeScallY(float PosiY , float InitY , float SY);
	void setVerticesScallX(float PosiX, float InitX, float SX);
	void setVerticesScallY(float PosiY, float InitY, float SY);
	float myabs(float);
public:
	int Singl_ID;
	bool is_visible;
	Vec2 *Vertices;
	Vec2 *RotateVertices;
	float Rotate;
	float SinB;
	float CosB;
	Vec2 * Relativevertices;
	Vec2 * RelativeRotateVertices;
	Vec2 RelativePosition = Vec2(_IN_Width, _IN_Height);
	Vec2 _temp;
	float RelativeScallX;
	float RelativeScallY;

};

