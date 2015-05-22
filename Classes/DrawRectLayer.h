#pragma once
#include "cocos2d.h"
#include "MyDrawNode.h"
#include "MySpritePoint.h"
USING_NS_CC;
class DrawRectLayer :public Layer
{
public:
	DrawRectLayer();
	~DrawRectLayer();
	CREATE_FUNC(DrawRectLayer);
	virtual bool init();
	static DrawRectLayer * createLayer();
	virtual bool onTouchBegan(Touch *touch, Event *unused_event);
	virtual void onTouchMoved(Touch* touch, Event  *event);
	virtual void onTouchEnded(Touch *touch, Event *unused_event);
	void showMsg(char * , float , int);
	void doDraw();
	MyDrawNode * injuredNode = NULL;
	MyDrawNode * attackNode = NULL;
	MyDrawNode * bodyNode = NULL;
	//std::vector <MyDrawNode *> listDrawNode;
	//std::vector <MyDrawNode *> backNode;
	std::vector <MySpritePoint *> spritePoints;
	void myupdate();
	static DrawRectLayer * getInstence();
	void updatemydata(std::string filename , std::string texture , std::string file_animation);
	Sprite3D *sp;
	//void update(float);
	//
	void CtrlZ();
	void CtrlY();
	void CtrlD();
	//设置画的区域
	void setDrawPosition();
	//根据帧数设定
	void drawPositionEdit(int);

	MySpritePoint *getChaZhi(MySpritePoint *, MySpritePoint * , int);

	Vec2 * getChaAtt(MySpritePoint *, MySpritePoint *, int);
	Vec2 * getChaInj(MySpritePoint *, MySpritePoint *, int);
	MySpritePoint * getChaAct(MySpritePoint *, MySpritePoint *, int);
	//删除当前关键帧
	void deleteFrame();

	void ScheduMyUpdate(float dt);
	void StartUpdate();
	void EndUpdate();
	void updataOrInsertFra();
	void removeDrawNode();
public:

	Animation3D  *animation;
	Animate3D * animate;
	RepeatForever * _RepeatForever;
	MySpritePoint * _myOnePoint;
	MySpritePoint * OneSpritePoint;
	MySpritePoint * _lastSpritePoint;
	MySpritePoint * _nextSpritePoint;
	MySpritePoint * _tempSpritePoint;
	void actioncallback(Node* pSender);
	int				Single_ID;
	float			mydt;
	double			oneDt;
	bool			Is_Moveto_Add;
private:
	Vec2 Startpoint;
	Vec2 Endpoint;
	Vec2 _LastPoint;
	Vec2 *attpoints;
	Vec2 *injurepoints;
	Vec2 *bodypoints;
	
};

