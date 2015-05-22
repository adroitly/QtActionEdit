#include "MySpritePoint.h"


MySpritePoint::MySpritePoint()
{
	Single_ID = -1;
	RotateAtt = 0.0;
	RotateInj = 0.0;
	_height = _IN_Height;
	_width = _IN_Width;
	_ScallX = _IN_ScallX;
	_ScallY = _IN_ScallY;
	Is_InjFra = false;
	Is_AttFra = false;
	Is_ActFra = false;
	Is_BodyFra = false;
}


MySpritePoint::~MySpritePoint()
{
	delete this;
	delete bodyVertices;
	delete attackVertices;
	delete injureVertices;
}
void MySpritePoint::setAttackVertices(Vec2 st, Vec2 en)
{
	if (attackVertices == nullptr)
	{
		attackVertices = new Vec2();
	}
	attackVertices[0] = st;
	attackVertices[1] = Vec2(st.x, en.y);
	attackVertices[2] = en;
	attackVertices[3] = Vec2(st.x, en.y);
	attackVertices[4] = st;
}
void MySpritePoint::setInjureVertices(Vec2 st, Vec2 en)
{
	if (injureVertices == nullptr)
	{
		injureVertices = new Vec2();
	}
	injureVertices[0] = st;
	injureVertices[1] = Vec2(st.x, en.y);
	injureVertices[2] = en;
	injureVertices[3] = Vec2(st.x, en.y);
	injureVertices[4] = st;
}

void MySpritePoint::setBodyVertices(Vec2 st, Vec2 en)
{
	if (bodyVertices == nullptr)
	{
		bodyVertices = new Vec2();
	}
	bodyVertices[0] = st;
	bodyVertices[1] = Vec2(st.x, en.y);
	bodyVertices[2] = en;
	bodyVertices[3] = Vec2(st.x, en.y);
	bodyVertices[4] = st;
}