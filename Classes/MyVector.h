#pragma once
#include "iostream"
#include "MySpritePoint.h"
using namespace std;
class MyVector
{
public:
	MyVector();
	~MyVector();
	vector<MySpritePoint * > Sprites;
	double _ScallX;
	double _ScallY;
	double _height;
	double _width;
	int Singl_ID;
};

