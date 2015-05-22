#include "MyDrawNode.h"


MyDrawNode::MyDrawNode()
{
	drawnode = DrawNode::create();
	drawnode->ignoreAnchorPointForPosition(false);
	drawnode->setAnchorPoint(ccp(0.5, 0.5));
	is_visible = true;
	Rotate = 0.0;
	Vertices = new Vec2[5];
	RotateVertices = new Vec2[5];
	Relativevertices = new Vec2[5];
	RelativeRotateVertices = new Vec2[5];
}

MyDrawNode::~MyDrawNode()
{
	drawnode->autorelease();
	delete this;
}

void MyDrawNode::setRotateFromRelativeRotate(Vec2 * MyRelativeRotate, Vec2 relativeposi)
{
	
	float x = relativeposi.x - RelativePosition.x;
	float y = relativeposi.y - RelativePosition.y;
	_temp = Vec2(x, y);
	RotateVertices[0] = MyRelativeRotate[0] - _temp;
	RotateVertices[1] = MyRelativeRotate[1] - _temp;
	RotateVertices[2] = MyRelativeRotate[2] - _temp;
	RotateVertices[3] = MyRelativeRotate[3] - _temp;
	RotateVertices[4] = MyRelativeRotate[4] - _temp;
	//RelativeRotateVertices = MyRelativeRotate;
}
void MyDrawNode::setVerticeFromRelative(Vec2 * MyRelativeVertices, Vec2 relativeposi)
{
	
	float x = relativeposi.x - RelativePosition.x;
	float y = relativeposi.y - RelativePosition.y;
	_temp = Vec2(x, y);
	Relativevertices[0];
	Vertices[0] = MyRelativeVertices[0] - _temp;
	Vertices[1] = MyRelativeVertices[1] - _temp;
	Vertices[2] = MyRelativeVertices[2] - _temp;
	Vertices[3] = MyRelativeVertices[3] - _temp;
	Vertices[4] = MyRelativeVertices[4] - _temp;
	//Relativevertices = MyRelativeVertices;
}

void MyDrawNode::setRelativeRotateVertices(Vec2 *points, Vec2 relativeposi)
{
	float x = relativeposi.x - RelativePosition.x;
	float y = relativeposi.y - RelativePosition.y;
	_temp = Vec2(x, y);
	RelativeRotateVertices[0] = points[0] + _temp;
	RelativeRotateVertices[1] = points[1] + _temp;
	RelativeRotateVertices[2] = points[2] + _temp;
	RelativeRotateVertices[3] = points[3] + _temp;
	RelativeRotateVertices[4] = points[4] + _temp;
}
void MyDrawNode::setRelativeVertices(Vec2 *points, Vec2 relativeposi)
{

	float x = relativeposi.x - RelativePosition.x;
	float y = relativeposi.y - RelativePosition.y;
	_temp = Vec2(x, y);
	Relativevertices[0] = points[0] + _temp;
	Relativevertices[1] = points[1] + _temp;
	Relativevertices[2] = points[2] + _temp;
	Relativevertices[3] = points[3] + _temp;
	Relativevertices[4] = points[4] + _temp;
	//Vertices = Relativevertices;
}


void MyDrawNode::setVertices(Vec2 Startpoint, Vec2 Endpoint)
{
	Vertices[0] = Startpoint;
	Vertices[1] = Vec2(Endpoint.x, Startpoint.y);
	Vertices[2] = Endpoint;
	Vertices[3] = Vec2(Startpoint.x, Endpoint.y);
	Vertices[4] = Startpoint;
	setRotateVertices(Startpoint, Endpoint,Rotate);

}
void MyDrawNode::setVerticesScallX(float PosiX, float InitX, float SX)
{
	RelativeScallX = SX / InitX;
	float _allX = PosiX - Vertices[0].x;
	Vertices[0].x = PosiX - (_allX * SX / InitX);

	_allX = PosiX - Vertices[1].x;
	Vertices[1].x = PosiX - (_allX * SX / InitX);

	_allX = PosiX - Vertices[2].x;
	Vertices[2].x = PosiX - (_allX * SX / InitX);

	_allX = PosiX - Vertices[3].x;
	Vertices[3].x = PosiX - (_allX * SX / InitX);

	_allX = PosiX - Vertices[4].x;
	Vertices[4].x = PosiX - (_allX * SX / InitX);


	_allX = PosiX - RotateVertices[0].x;
	RotateVertices[0].x = PosiX - (_allX * SX / InitX);

	_allX = PosiX - RotateVertices[1].x;
	RotateVertices[1].x = PosiX - (_allX * SX / InitX);

	_allX = PosiX - RotateVertices[2].x;
	RotateVertices[2].x = PosiX - (_allX * SX / InitX);

	_allX = PosiX - RotateVertices[3].x;
	RotateVertices[3].x = PosiX - (_allX * SX / InitX);

	_allX = PosiX - RotateVertices[4].x;
	RotateVertices[4].x = PosiX - (_allX * SX / InitX);
}
void MyDrawNode::setVerticesScallY(float PosiY, float InitY, float SY)
{
	RelativeScallY = SY / InitY;
	//Relativevertices[0].y = Relativevertices[0].y * SY / InitY;
	//Relativevertices[1].y = Relativevertices[1].y * SY / InitY;
	//Relativevertices[2].y = Relativevertices[2].y * SY / InitY;
	//Relativevertices[3].y = Relativevertices[3].y * SY / InitY;
	//Relativevertices[4].y = Relativevertices[4].y * SY / InitY;

	float _allY = PosiY - Vertices[0].y;
	Vertices[0].y = PosiY - (_allY * SY / InitY);

	_allY = PosiY - Vertices[1].y;
	Vertices[1].y = PosiY - (_allY * SY / InitY);

	_allY = PosiY - Vertices[2].y;
	Vertices[2].y = PosiY - (_allY * SY / InitY);

	_allY = PosiY - Vertices[3].y;
	Vertices[3].y = PosiY - (_allY * SY / InitY);

	_allY = PosiY - Vertices[4].y;
	Vertices[4].y = PosiY - (_allY * SY / InitY);




	_allY = PosiY - RotateVertices[0].y;
	RotateVertices[0].y = PosiY - (_allY * SY / InitY);

	_allY = PosiY - RotateVertices[1].y;
	RotateVertices[1].y = PosiY - (_allY * SY / InitY);

	_allY = PosiY - RotateVertices[2].y;
	RotateVertices[2].y = PosiY - (_allY * SY / InitY);

	_allY = PosiY - RotateVertices[3].y;
	RotateVertices[3].y = PosiY - (_allY * SY / InitY);

	_allY = PosiY - RotateVertices[4].y;
	RotateVertices[4].y = PosiY - (_allY * SY / InitY);
}
void MyDrawNode::setRelativeScallX(float PosiX, float InitX, float SX)
{
	RelativeScallX = SX / InitX;
	float _allX = PosiX - Relativevertices[0].x;
	Relativevertices[0].x = PosiX - (_allX * SX / InitX);

	_allX = PosiX - Relativevertices[1].x;
	Relativevertices[1].x = PosiX - (_allX * SX / InitX);

	_allX = PosiX - Relativevertices[2].x;
	Relativevertices[2].x = PosiX - (_allX * SX / InitX);

	_allX = PosiX - Relativevertices[3].x;
	Relativevertices[3].x = PosiX - (_allX * SX / InitX);

	_allX = PosiX - Relativevertices[4].x;
	Relativevertices[4].x = PosiX - (_allX * SX / InitX);

	//Relativevertices[0].x = Relativevertices[0].x * SX / InitX;
	//Relativevertices[1].x = Relativevertices[1].x * SX / InitX;
	//Relativevertices[2].x = Relativevertices[2].x * SX / InitX;
	//Relativevertices[3].x = Relativevertices[3].x * SX / InitX;
	//Relativevertices[4].x = Relativevertices[4].x * SX / InitX;


	_allX = PosiX - RelativeRotateVertices[0].x;
	RelativeRotateVertices[0].x = PosiX - (_allX * SX / InitX);

	_allX = PosiX - RelativeRotateVertices[1].x;
	RelativeRotateVertices[1].x = PosiX - (_allX * SX / InitX);

	_allX = PosiX - RelativeRotateVertices[2].x;
	RelativeRotateVertices[2].x = PosiX - (_allX * SX / InitX);

	_allX = PosiX - RelativeRotateVertices[3].x;
	RelativeRotateVertices[3].x = PosiX - (_allX * SX / InitX);

	_allX = PosiX - RelativeRotateVertices[4].x;
	RelativeRotateVertices[4].x = PosiX - (_allX * SX / InitX);
}
void MyDrawNode::setRelativeScallY(float PosiY , float InitY , float SY)
{
	RelativeScallY = SY / InitY;
	//Relativevertices[0].y = Relativevertices[0].y * SY / InitY;
	//Relativevertices[1].y = Relativevertices[1].y * SY / InitY;
	//Relativevertices[2].y = Relativevertices[2].y * SY / InitY;
	//Relativevertices[3].y = Relativevertices[3].y * SY / InitY;
	//Relativevertices[4].y = Relativevertices[4].y * SY / InitY;

	float _allY = PosiY - Relativevertices[0].y;
	Relativevertices[0].y = PosiY - (_allY * SY / InitY);

	_allY = PosiY - Relativevertices[1].y;
	Relativevertices[1].y = PosiY - (_allY * SY / InitY);

	_allY = PosiY - Relativevertices[2].y;
	Relativevertices[2].y = PosiY - (_allY * SY / InitY);

	_allY = PosiY - Relativevertices[3].y;
	Relativevertices[3].y = PosiY - (_allY * SY / InitY);

	_allY = PosiY - Relativevertices[4].y;
	Relativevertices[4].y = PosiY - (_allY * SY / InitY);




	_allY = PosiY - RelativeRotateVertices[0].y;
	RelativeRotateVertices[0].y = PosiY - (_allY * SY / InitY);

	_allY = PosiY - RelativeRotateVertices[1].y;
	RelativeRotateVertices[1].y = PosiY - (_allY * SY / InitY);

	_allY = PosiY - RelativeRotateVertices[2].y;
	RelativeRotateVertices[2].y = PosiY - (_allY * SY / InitY);

	_allY = PosiY - RelativeRotateVertices[3].y;
	RelativeRotateVertices[3].y = PosiY - (_allY * SY / InitY);

	_allY = PosiY - RelativeRotateVertices[4].y;
	RelativeRotateVertices[4].y = PosiY - (_allY * SY / InitY);



}
void MyDrawNode::setRotateVertices(Vec2 startPoint, Vec2 EndPoint, float _temp)
{
	//x=(x1-x2)cos¦È-(y1-y2)sin¦È+x2
	//y=(y1-y2)cos¦È+(x1-x2)sin¦È+y2
	//x = (one.x - two.x) * cos(rotate) - (one.y - two.y) * sin(rotate) + two.x;
	//y = (one.y - two.y) * cos(rotate) + (one.x - two.x) * sin(rotate) + two.y;

	//x2 = (y1 - y0)*sina¡ã + (x1 - x0)*cosa¡ã
	//y2 = (y1 - y0)*cosa¡ã - (x1 - x0)*sina¡ã
	//x = (one.y - two.y) * sin(rotate) + (one.x - two.x) * cos(rotate);
	//y = (one.y - two.y) * cos(rotate) - (one.x - two.x) * sin(rotate);

	//xA`=x + (ax - x)cosk - (ay - y)sinK
	//yA`=y + (ax - x)sink + (ay - y)cosk
	//x = (one.x - two.x) * cos(rotate) - (one.y - two.y) * sin(rotate) + two.x;
	//y = (one.x - two.x) * sin(rotate) + (one.y - two.y) * cos(rotate) + two.y;

	//x0 = (x - rx0)*cos(a) - (y - ry0)*sin(a) + rx0;

	//y0 = (x - rx0)*sin(a) + (y - ry0)*cos(a) + ry0;

	if (_temp == -720)
	{
		_temp = Rotate;
	}
	//_temp = 90 - _temp;
	//float rotate = M_PI / 180.0 * (_temp * 1.0);
	float rotate = _temp;
	//rotate = _temp * 57.3;
	//log("%f", rotate);
	float x, y;
	Vec2 one = startPoint;
	Vec2 two = getMidPoint();
	x = (one.x - two.x) * cos(rotate) - (one.y - two.y) * sin(rotate) + two.x;
	y = (one.x - two.x) * sin(rotate) + (one.y - two.y) * cos(rotate) + two.y;
	RotateVertices[0] = Vec2(x, y);

	one = Vec2(EndPoint.x, startPoint.y);
	x = (one.x - two.x) * cos(rotate) - (one.y - two.y) * sin(rotate) + two.x;
	y = (one.x - two.x) * sin(rotate) + (one.y - two.y) * cos(rotate) + two.y;
	RotateVertices[1] = Vec2(x, y);

	one = EndPoint;
	x = (one.x - two.x) * cos(rotate) - (one.y - two.y) * sin(rotate) + two.x;
	y = (one.x - two.x) * sin(rotate) + (one.y - two.y) * cos(rotate) + two.y;
	RotateVertices[2] = Vec2(x, y);

	one = Vec2(startPoint.x, EndPoint.y);
	x = (one.x - two.x) * cos(rotate) - (one.y - two.y) * sin(rotate) + two.x;
	y = (one.x - two.x) * sin(rotate) + (one.y - two.y) * cos(rotate) + two.y;
	RotateVertices[3] = Vec2(x, y);

	RotateVertices[4] = RotateVertices[0];

}

Vec2 MyDrawNode::getMidPoint()
{
	return Vec2((Vertices[0].x + Vertices[2].x) / 2, (Vertices[0].y + Vertices[2].y) / 2);
}

float MyDrawNode::getRotate(Vec2 StartPoint, Vec2 EndPoint, Vec2 midPoint)
{
	if (midPoint == Vec2(-1000 , -1000))
	{
		midPoint = getMidPoint();
	}
	int ro;
	float len_a, len_b, len_c;
	len_a = sqrt(((StartPoint.x - midPoint.x)) * ((StartPoint.x - midPoint.x)) + ((StartPoint.y - midPoint.y)) * ((StartPoint.y - midPoint.y)));
	len_b = sqrt(((StartPoint.x - EndPoint.x)) * ((StartPoint.x - EndPoint.x)) + ((StartPoint.y - EndPoint.y)) * ((StartPoint.y - EndPoint.y)));
	len_c = sqrt(((midPoint.x - EndPoint.x)) * ((midPoint.x - EndPoint.x)) + ((midPoint.y - EndPoint.y)) * ((midPoint.y - EndPoint.y) ));
	CosB = (len_a * len_a + len_c * len_c - len_b * len_b) / (2 * len_a * len_c);
	SinB = sqrt(1 - CosB * CosB);

	return CosB;

}
float MyDrawNode::myabs(float dt)
{
	return dt < 0 ? -dt : dt;
}