#include "DrawRectLayer.h"
#include "qtedit.h"
static DrawRectLayer * _DrawRectLayer;
static QtEdit *_QtEdit;
DrawRectLayer::DrawRectLayer()
{
}


DrawRectLayer::~DrawRectLayer()
{
}

DrawRectLayer * DrawRectLayer::getInstence()
{
	if (!_DrawRectLayer)
	{
		createLayer();
	}
	return _DrawRectLayer;
}
DrawRectLayer * DrawRectLayer::createLayer()
{
	_DrawRectLayer = DrawRectLayer::create();
	return _DrawRectLayer;
}

bool DrawRectLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	Is_Moveto_Add = false;
	injuredNode = new MyDrawNode();
	this->addChild(injuredNode->drawnode, 100);
	attackNode = new MyDrawNode();
	this->addChild(attackNode->drawnode, 100);
	bodyNode = new MyDrawNode();
	this->addChild(bodyNode->drawnode, 100);
	OneSpritePoint = nullptr;
	_QtEdit = QtEdit::getInstance();
	this->setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(DrawRectLayer::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(DrawRectLayer::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(DrawRectLayer::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	animation = NULL;
	return true;
}


bool DrawRectLayer::onTouchBegan(Touch *touch, Event *unused_event)
{
	Point touchpoint = touch->getLocation();
	Startpoint = Vec2((int)touchpoint.x, (int)touchpoint.y);
	this->EndUpdate();
	if (_QtEdit)
	{
		_QtEdit->ui.PauseButton->setText("Start");
		_QtEdit->pu = -1;
	}
	return true;
}
void DrawRectLayer::onTouchMoved(Touch* touch, Event  *event)
{
	Point touchpoint = touch->getLocation();
	Endpoint = Vec2((int)touchpoint.x, (int)touchpoint.y);
	if (std::abs(Endpoint.x - Startpoint.x) >= 15 && std::abs(Endpoint.y - Startpoint.y) >= 15)
	{
		_QtEdit->setWindowTitle(_QtEdit->windowTitle().split("*").at(0) + "*");
		this->myupdate();
	}
	
}
void DrawRectLayer::onTouchEnded(Touch *touch, Event *unused_event)
{
	Point touchpoint = touch->getLocation();
	Endpoint = Vec2((int)touchpoint.x, (int)touchpoint.y);
	if (std::abs(Endpoint.x - Startpoint.x) >= 15 && std::abs(Endpoint.y - Startpoint.y) >= 15)
	{
		_QtEdit->setWindowTitle(_QtEdit->windowTitle().split("*").at(0) + "*");
		this->myupdate();
	}

}
void DrawRectLayer::setDrawPosition()
{
	if (_QtEdit->Ctrl_Is_On && attackNode != nullptr)
	{
		attackNode->setVertices(Startpoint, Endpoint);
	}
	else if (injuredNode != nullptr)
	{
		injuredNode->setVertices(Startpoint, Endpoint);
	}
}

void DrawRectLayer::updatemydata(std::string filename, std::string texture, std::string file_animation)
{
	mydt = 0.0;
	sp = Sprite3D::create(filename, texture);
	//sp->setAnchorPoint(ccp(0.5, 0.5));
	sp->setCullFaceEnabled(false);
	this->addChild(sp);
	animation = Animation3D::getOrCreate(file_animation);
	if (animation != NULL)
	{
		animate = Animate3D::create(animation);
		animate->is_auto_update = false;
		_RepeatForever = RepeatForever::create(animate);
		sp->runAction(_RepeatForever);
	}
}
void DrawRectLayer::actioncallback(Node* pSender)
{
	//this->unscheduleUpdate();
}
void DrawRectLayer::showMsg(char * charstr = NULL, float dt = 0.0, int num = 0)
{
	char str[100];
	_QtEdit = QtEdit::getInstance();
	std::sprintf(str, " %s %f %d", charstr == NULL ? "" : charstr, dt == 0.0 ? NULL : dt, num == NULL ? NULL : num);
	_QtEdit->ShowMsg(str);
}
void DrawRectLayer::doDraw()
{
	if (!_QtEdit->is_import)
	{
		return;
	}
	if (attackNode->Rotate == 0.0)
	{
		if (attackNode != nullptr && attackNode->Vertices != nullptr && attackNode->Vertices[0].x != 0)
		{
			
			if (Is_Moveto_Add && _QtEdit->Ctrl_Is_On)
			{
				//attackNode->Relativevertices = attackNode->Vertices;
				attackNode->setVerticesScallX(sp->getPosition().x, _QtEdit->ui.ScallX->text().toFloat(), _IN_ScallX);
				attackNode->setVerticesScallY(sp->getPosition().y, _QtEdit->ui.ScallY->text().toFloat(), _IN_ScallX);
				attackNode->setVerticeFromRelative(attackNode->Vertices, Vec2(_QtEdit->ui.Width->text().toFloat(), _QtEdit->ui.Height->text().toFloat()));
				
			}
			attackNode->setRelativeVertices(attackNode->Vertices, Vec2(_QtEdit->ui.Width->text().toFloat(), _QtEdit->ui.Height->text().toFloat()));
			//attackNode->drawnode->drawPoly(attackNode->Vertices, 5, false, Color4F(1, 0, 0, 1));
			attackNode->setRelativeScallX(sp->getPosition().x, _IN_ScallX, _QtEdit->ui.ScallX->text().toFloat());
			attackNode->setRelativeScallY(sp->getPosition().y, _IN_ScallY, _QtEdit->ui.ScallY->text().toFloat());
			attackNode->drawnode->drawPoly(attackNode->Relativevertices, 5, false, Color4F(1, 0, 0, 1));
			this->addChild(attackNode->drawnode, 100);
		}
	}
	else
	{
		if (attackNode != nullptr && attackNode->RotateVertices != nullptr)
		{
			//attackNode->drawnode->drawPoly(attackNode->RotateVertices, 5, false, Color4F(1, 0, 0, 1));
			if (Is_Moveto_Add && _QtEdit->Ctrl_Is_On)
			{
				//attackNode->RelativeRotateVertices = attackNode->RotateVertices;
				attackNode->setVerticesScallX(sp->getPosition().x, _QtEdit->ui.ScallX->text().toFloat(), _IN_ScallX);
				attackNode->setVerticesScallY(sp->getPosition().y, _QtEdit->ui.ScallY->text().toFloat(), _IN_ScallX);
				attackNode->setRotateFromRelativeRotate(attackNode->RotateVertices, Vec2(_QtEdit->ui.Width->text().toFloat(), _QtEdit->ui.Height->text().toFloat()));
				
			}
			attackNode->setRelativeRotateVertices(attackNode->RotateVertices, Vec2(_QtEdit->ui.Width->text().toFloat(), _QtEdit->ui.Height->text().toFloat()));
			attackNode->setRelativeScallX(sp->getPosition().x, _IN_ScallX, _QtEdit->ui.ScallX->text().toFloat());
			attackNode->setRelativeScallY(sp->getPosition().y, _IN_ScallY, _QtEdit->ui.ScallY->text().toFloat());
			attackNode->drawnode->drawPoly(attackNode->RelativeRotateVertices, 5, false, Color4F(1, 0, 0, 1));
			this->addChild(attackNode->drawnode, 100);
		}
	}
	if (injuredNode->Rotate == 0.0)
	{
		if (injuredNode != nullptr && injuredNode->Vertices != nullptr && injuredNode->Vertices[0].x != 0)
		{
			//injuredNode->drawnode->drawPoly(injuredNode->Vertices, 5, false, Color4F(1, 1, 0, 1));
			if (Is_Moveto_Add && !_QtEdit->Ctrl_Is_On && !_QtEdit->Shift_is_ON)//如果是现在绘制的则先进行转换成一般情况的坐标，之后就和普通一样绘制了
			{
				//injuredNode->Relativevertices = injuredNode->Vertices;
				//先进行原版放大
				injuredNode->setVerticesScallX(sp->getPosition().x, _QtEdit->ui.ScallX->text().toFloat(), _IN_ScallX);
				injuredNode->setVerticesScallY(sp->getPosition().y, _QtEdit->ui.ScallY->text().toFloat(), _IN_ScallX);
				//再进行位移偏差计算
				injuredNode->setVerticeFromRelative(injuredNode->Vertices, Vec2(_QtEdit->ui.Width->text().toFloat(), _QtEdit->ui.Height->text().toFloat()));
				
			}
			injuredNode->setRelativeVertices(injuredNode->Vertices, Vec2(_QtEdit->ui.Width->text().toFloat(), _QtEdit->ui.Height->text().toFloat()));
			injuredNode->setRelativeScallX(sp->getPosition().x, _IN_ScallX, _QtEdit->ui.ScallX->text().toFloat());
			injuredNode->setRelativeScallY(sp->getPosition().y, _IN_ScallY, _QtEdit->ui.ScallY->text().toFloat());
			injuredNode->drawnode->drawPoly(injuredNode->Relativevertices, 5, false, Color4F(1, 1, 0, 1));
			this->addChild(injuredNode->drawnode, 100);
		}
	}
	else
	{
		if (injuredNode != nullptr && injuredNode->RotateVertices != nullptr)
		{
			//injuredNode->drawnode->drawPoly(injuredNode->RotateVertices, 5, false, Color4F(1, 1, 0, 1));
			if (Is_Moveto_Add && !_QtEdit->Ctrl_Is_On && !_QtEdit->Shift_is_ON)
			{
				injuredNode->setVerticesScallX(sp->getPosition().x, _QtEdit->ui.ScallX->text().toFloat(), _IN_ScallX);
				injuredNode->setVerticesScallY(sp->getPosition().y, _QtEdit->ui.ScallY->text().toFloat(), _IN_ScallX);
				injuredNode->setRotateFromRelativeRotate(injuredNode->RotateVertices, Vec2(_QtEdit->ui.Width->text().toFloat(), _QtEdit->ui.Height->text().toFloat()));
				
			}
			injuredNode->setRelativeRotateVertices(injuredNode->RotateVertices, Vec2(_QtEdit->ui.Width->text().toFloat(), _QtEdit->ui.Height->text().toFloat()));
			injuredNode->setRelativeScallX(sp->getPosition().x, _IN_ScallX, _QtEdit->ui.ScallX->text().toFloat());
			injuredNode->setRelativeScallY(sp->getPosition().y, _IN_ScallY, _QtEdit->ui.ScallY->text().toFloat());
			injuredNode->drawnode->drawPoly(injuredNode->RelativeRotateVertices, 5, false, Color4F(1, 1, 0, 1));
			this->addChild(injuredNode->drawnode, 100);
		}
	}
	if (bodyNode != nullptr && bodyNode->Vertices != nullptr)
	{
		if (Is_Moveto_Add && _QtEdit->Shift_is_ON)//如果是现在绘制的，则先进行转换
		{
			bodyNode->setVerticesScallX(sp->getPosition().x, _QtEdit->ui.ScallX->text().toFloat(), _IN_ScallX);
			bodyNode->setVerticesScallY(sp->getPosition().y, _QtEdit->ui.ScallY->text().toFloat(), _IN_ScallX);
			bodyNode->setVerticeFromRelative(bodyNode->Vertices, Vec2(_QtEdit->ui.Width->text().toFloat(), _QtEdit->ui.Height->text().toFloat()));
		
		}
		bodyNode->setRelativeVertices(bodyNode->Vertices, Vec2(_QtEdit->ui.Width->text().toFloat(), _QtEdit->ui.Height->text().toFloat()));
		bodyNode->setRelativeScallX(sp->getPosition().x, _IN_ScallX, _QtEdit->ui.ScallX->text().toFloat());
		bodyNode->setRelativeScallY(sp->getPosition().y, _IN_ScallY, _QtEdit->ui.ScallY->text().toFloat());
		bodyNode->drawnode->drawPoly(bodyNode->Relativevertices, 5, false, Color4F(0, 1, 0, 1));
		this->addChild(bodyNode->drawnode, 100);
	}
	Is_Moveto_Add = false;
}
//void DrawRectLayer::update(float dt)
//{
//
//	//if (NULL != animation)
//	{
//		mydt += dt / animate->getDuration();
//		if (!Is_run_update)
//		{
//			Is_run_update = true;
//			_QtEdit->SlderChange(mydt);
//			_QtEdit->AnimationUpdate(mydt);
//			//mydt += 0.01;
//			//animate->updateOnPercentage(mydt);
//			//showMsg("dt", mydt, 0);
//			if (mydt > 1)
//			{
//				mydt = 0.0;
//			}
//			Is_run_update = false;
//		}
//
//	}
//}
int  i = 0;
void DrawRectLayer::myupdate()
{
	char str[100];

	if (std::abs(Endpoint.x - Startpoint.x) >= 5 && std::abs(Endpoint.y - Startpoint.y) >= 5)
	{
		float _ROTATE;
		if (_QtEdit->Ctrl_Is_On)
		{
			this->removeChild(attackNode->drawnode);
			attackNode = new MyDrawNode();
			attackNode->setVertices(Startpoint, Endpoint);
			injurepoints = injuredNode->Vertices;
			this->removeChild(injuredNode->drawnode);
			_ROTATE = injuredNode->Rotate;
			injuredNode = new MyDrawNode();
			injuredNode->Rotate = _ROTATE;
			injuredNode->setVertices(injurepoints[0], injurepoints[2]);

			bodypoints = bodyNode->Vertices;
			this->removeChild(bodyNode->drawnode);
			_ROTATE = bodyNode->Rotate;
			bodyNode = new MyDrawNode();
			bodyNode->Rotate = _ROTATE;
			bodyNode->setVertices(bodypoints[0], bodypoints[2]);

		}
		else if (_QtEdit->Shift_is_ON)
		{
			this->removeChild(bodyNode->drawnode);
			bodyNode = new MyDrawNode();
			bodyNode->setVertices(Startpoint, Endpoint);
			attpoints = attackNode->Vertices;
			_ROTATE = attackNode->Rotate;
			this->removeChild(attackNode->drawnode);
			attackNode = new MyDrawNode();
			attackNode->Rotate = _ROTATE;
			attackNode->setVertices(attpoints[0], attpoints[2]);
			injurepoints = injuredNode->Vertices;
			this->removeChild(injuredNode->drawnode);
			_ROTATE = injuredNode->Rotate;
			injuredNode = new MyDrawNode();
			injuredNode->Rotate = _ROTATE;
			injuredNode->setVertices(injurepoints[0], injurepoints[2]);
		}
		else
		{
			this->removeChild(injuredNode->drawnode);
			injuredNode = new MyDrawNode();
			injuredNode->setVertices(Startpoint, Endpoint);
			attpoints = attackNode->Vertices;
			_ROTATE = attackNode->Rotate;
			this->removeChild(attackNode->drawnode);
			attackNode = new MyDrawNode();
			attackNode->Rotate = _ROTATE;
			attackNode->setVertices(attpoints[0], attpoints[2]);

			bodypoints = bodyNode->Vertices;
			this->removeChild(bodyNode->drawnode);
			_ROTATE = bodyNode->Rotate;
			bodyNode = new MyDrawNode();
			bodyNode->Rotate = _ROTATE;
			bodyNode->setVertices(bodypoints[0], bodypoints[2]);
		}

		//injuredNode->drawnode->setAnchorPoint(Vec2((injuredNode->Vertices[0].x + injuredNode->Vertices[2].x), (injuredNode->Vertices[0].y + injuredNode->Vertices[2].y) / 2));
		//attackNode->drawnode->setAnchorPoint(Vec2((attackNode->Vertices[0].x + attackNode->Vertices[2].x), (attackNode->Vertices[0].y + attackNode->Vertices[2].y) / 2));
		//bodyNode->drawnode->setAnchorPoint(Vec2((bodyNode->Vertices[0].x + bodyNode->Vertices[2].x), (bodyNode->Vertices[0].y + bodyNode->Vertices[2].y) / 2));
		updataOrInsertFra();
	}
}

void DrawRectLayer::removeDrawNode()
{
	float _ROTATE;
	injurepoints = injuredNode->Vertices;
	this->removeChild(injuredNode->drawnode);
	_ROTATE = injuredNode->Rotate;
	injuredNode = new MyDrawNode();
	injuredNode->Rotate = _ROTATE;
	injuredNode->setVertices(injurepoints[0], injurepoints[2]);

	attpoints = attackNode->Vertices;
	_ROTATE = attackNode->Rotate;
	this->removeChild(attackNode->drawnode);
	attackNode = new MyDrawNode();
	attackNode->Rotate = _ROTATE;
	attackNode->setVertices(attpoints[0], attpoints[2]);

	bodypoints = bodyNode->Vertices;
	this->removeChild(bodyNode->drawnode);
	_ROTATE = bodyNode->Rotate;
	bodyNode = new MyDrawNode();
	bodyNode->Rotate = _ROTATE;
	bodyNode->setVertices(bodypoints[0], bodypoints[2]);
}

void DrawRectLayer::updataOrInsertFra()
{
	_tempSpritePoint = nullptr;
	int posi;
	if (OneSpritePoint != nullptr)
	{
		OneSpritePoint->attackVertices = attackNode->Vertices;
		OneSpritePoint->RotateAtt = attackNode->Rotate;
		OneSpritePoint->injureVertices = injuredNode->Vertices;
		OneSpritePoint->RotateInj = injuredNode->Rotate;
		OneSpritePoint->bodyVertices = bodyNode->Vertices;
		//新的
		bool Is_Has = false;
		for (i = 0; i < spritePoints.size(); i++)
		{
			_tempSpritePoint = spritePoints.at(i);
			//showMsg("SIngle_ID", NULL, _tempSpritePoint->Single_ID);
			//showMsg("Size", NULL, spritePoints.size());
			if (_tempSpritePoint->Single_ID == Single_ID)
			{
				spritePoints.at(i) = OneSpritePoint;
				if (_QtEdit->Ctrl_Is_On)
				{
					OneSpritePoint->Is_AttFra = true;
					spritePoints.at(i)->Is_AttFra = true;
					posi = 1;
				}
				else if (_QtEdit->Shift_is_ON)
				{
					OneSpritePoint->Is_BodyFra = true;
					spritePoints.at(i)->Is_BodyFra = true;
					posi = 4;
				}
				else
				{
					OneSpritePoint->Is_InjFra = true;
					spritePoints.at(i)->Is_InjFra = true;
					posi = 2;
				}
				Is_Has = true;
				//break;
			}
		}
		if (!Is_Has)
		{
			MySpritePoint * ss = new MySpritePoint();
			ss->Single_ID = OneSpritePoint->Single_ID;
			ss->attackVertices = OneSpritePoint->attackVertices;
			ss->injureVertices = OneSpritePoint->injureVertices;
			ss->bodyVertices = OneSpritePoint->bodyVertices;
			if (_QtEdit->Ctrl_Is_On)
			{
				ss->Is_AttFra = true;
				posi = 1;
			}
			else if (_QtEdit->Shift_is_ON)
			{
				ss->Is_BodyFra = true;
				posi = 4;
			}
			else
			{
				ss->Is_InjFra = true;
				posi = 2;
			}

			spritePoints.push_back(ss);
		}
	}
	//标识
	if (_QtEdit->is_import)
	{
		_QtEdit->setMyFrame(Single_ID, posi);
	}
	//记录是现在绘制的，待会要先转换成绝对坐标再转换成相对坐标
	Is_Moveto_Add = true;
	this->doDraw();
}

void DrawRectLayer::CtrlZ()
{

}
void DrawRectLayer::CtrlY()
{


}
void DrawRectLayer::CtrlD()
{
	if (injuredNode != nullptr)
	{
		this->removeChild(injuredNode->drawnode);
	}
	if (attackNode != nullptr)
	{
		this->removeChild(attackNode->drawnode);
	}
}

void DrawRectLayer::drawPositionEdit(int n)
{
	bool FPX_has = false;
	//记录Single_ID
	Single_ID = n;
	//for (i = 0; i < spritePoints.size(); i++)
	//{
	//	_myOnePoint = spritePoints.at(i);
	//	if (_myOnePoint->Single_ID == n)
	//	{
	//		FPX_has = true;
	//		break;
	//	}
	//}
	this->removeChild(attackNode->drawnode);
	this->removeChild(injuredNode->drawnode);
	this->removeChild(bodyNode->drawnode);
	injuredNode = new MyDrawNode();
	attackNode = new MyDrawNode();
	bodyNode = new MyDrawNode();
	bool Ac_La = false;
	bool At_La = false;
	bool In_La = false;
	bool Bo_La = false;
	//之前没有存在编辑过
	//if (!FPX_has)
	{
		OneSpritePoint = new MySpritePoint();
		OneSpritePoint->Single_ID = n;
		//spritePoints.push_back(OneSpritePoint);
		//新的
		_lastSpritePoint = nullptr;
		_nextSpritePoint = nullptr;
		int _lcha = 100000;
		int _ncha = 100000;
		for (i = 0; i < spritePoints.size(); i ++)
		{
			_tempSpritePoint = spritePoints.at(i);
			if (_tempSpritePoint->Single_ID <= n && (n - _tempSpritePoint->Single_ID) <= _lcha && _tempSpritePoint->Is_AttFra)
			{
				_lcha = n - _tempSpritePoint->Single_ID;
				_lastSpritePoint = _tempSpritePoint;
			}
			if (_tempSpritePoint->Single_ID >= n && (_tempSpritePoint->Single_ID - n) <= _ncha && _tempSpritePoint->Is_AttFra)
			{
				_ncha = _tempSpritePoint->Single_ID - n;
				_nextSpritePoint = _tempSpritePoint;
			}
		}
		if (_lcha == 0)
		{
			//OneSpritePoint = _lastSpritePoint;
			OneSpritePoint->attackVertices = _lastSpritePoint->attackVertices;
			OneSpritePoint->RotateAtt = _lastSpritePoint->RotateAtt;
			OneSpritePoint->RotateAtt = _lastSpritePoint->RotateAtt;
			OneSpritePoint->Is_AttFra = _lastSpritePoint->Is_AttFra;
			//OneSpritePoint->_height = _lastSpritePoint->_height;
			//OneSpritePoint->_width = _lastSpritePoint->_width;
			//OneSpritePoint->_ScallX = _lastSpritePoint->_ScallX;
			//OneSpritePoint->_ScallY = _lastSpritePoint->_ScallY;
			At_La = true;
		}
		else if (_lastSpritePoint != nullptr && _nextSpritePoint != nullptr )
		{
			//OneSpritePoint = getChaZhi(_lastSpritePoint, _nextSpritePoint, n);
			OneSpritePoint->attackVertices = getChaAtt(_lastSpritePoint, _nextSpritePoint, n);
			At_La = true;
		}
		else if (_lastSpritePoint != nullptr)
		{
			OneSpritePoint->attackVertices = _lastSpritePoint->attackVertices;
			//OneSpritePoint->RotateAtt = _lastSpritePoint->RotateAtt;
			//OneSpritePoint->RotateAtt = _lastSpritePoint->RotateAtt;
			//OneSpritePoint->injureVertices = _lastSpritePoint->injureVertices;
			//OneSpritePoint->_height = _lastSpritePoint->_height;
			//OneSpritePoint->_width = _lastSpritePoint->_width;
			//OneSpritePoint->_ScallX = _lastSpritePoint->_ScallX;
			//OneSpritePoint->_ScallY = _lastSpritePoint->_ScallY;
			At_La = true;
		}



		_lastSpritePoint = nullptr;
		_nextSpritePoint = nullptr;
		_lcha = 100000;
		_ncha = 100000;
		for (i = 0; i < spritePoints.size(); i++)
		{
			_tempSpritePoint = spritePoints.at(i);
			if (_tempSpritePoint->Single_ID <= n && (n - _tempSpritePoint->Single_ID) <= _lcha && _tempSpritePoint->Is_InjFra)
			{
				_lcha = n - _tempSpritePoint->Single_ID;
				_lastSpritePoint = _tempSpritePoint;
			}
			if (_tempSpritePoint->Single_ID >= n && (_tempSpritePoint->Single_ID - n) <= _ncha && _tempSpritePoint->Is_InjFra)
			{
				_ncha = _tempSpritePoint->Single_ID - n;
				_nextSpritePoint = _tempSpritePoint;
			}
		}
		if (_lcha == 0)
		{
			OneSpritePoint->injureVertices = _lastSpritePoint->injureVertices;
			OneSpritePoint->Is_InjFra = _lastSpritePoint->Is_InjFra;
			//OneSpritePoint->injureVertices = _lastSpritePoint->injureVertices;
			OneSpritePoint->RotateInj = _lastSpritePoint->RotateInj;
			OneSpritePoint->RotateInj = _lastSpritePoint->RotateInj;
			//OneSpritePoint->_height = _lastSpritePoint->_height;
			//OneSpritePoint->_width = _lastSpritePoint->_width;
			//OneSpritePoint->_ScallX = _lastSpritePoint->_ScallX;
			//OneSpritePoint->_ScallY = _lastSpritePoint->_ScallY;
		}
		else if (_lastSpritePoint != nullptr && _nextSpritePoint != nullptr)
		{
			//OneSpritePoint = getChaZhi(_lastSpritePoint, _nextSpritePoint, n);
			OneSpritePoint->injureVertices = getChaInj(_lastSpritePoint, _nextSpritePoint, n);
		}
		else if (_lastSpritePoint != nullptr)
		{
			OneSpritePoint->injureVertices = _lastSpritePoint->injureVertices;
			//OneSpritePoint->RotateInj = _lastSpritePoint->RotateInj;
			//OneSpritePoint->RotateInj = _lastSpritePoint->RotateInj;
			//OneSpritePoint->_height = _lastSpritePoint->_height;
			//OneSpritePoint->_width = _lastSpritePoint->_width;
			//OneSpritePoint->_ScallX = _lastSpritePoint->_ScallX;
			//OneSpritePoint->_ScallY = _lastSpritePoint->_ScallY;
		}



		_lastSpritePoint = nullptr;
		_nextSpritePoint = nullptr;
		_lcha = 100000;
		_ncha = 100000;
		for (i = 0; i < spritePoints.size(); i++)
		{
			_tempSpritePoint = spritePoints.at(i);
			if (_tempSpritePoint->Single_ID <= n && (n - _tempSpritePoint->Single_ID) <= _lcha && _tempSpritePoint->Is_ActFra)
			{
				_lcha = n - _tempSpritePoint->Single_ID;
				_lastSpritePoint = _tempSpritePoint;
			}
			if (_tempSpritePoint->Single_ID >= n && (_tempSpritePoint->Single_ID - n) <= _ncha && _tempSpritePoint->Is_ActFra)
			{
				_ncha = _tempSpritePoint->Single_ID - n;
				_nextSpritePoint = _tempSpritePoint;
			}
		}
		if (_lcha == 0)
		{
			//OneSpritePoint->attackVertices = _lastSpritePoint->attackVertices;
			//OneSpritePoint->injureVertices = _lastSpritePoint->injureVertices;
			OneSpritePoint->Is_ActFra = _lastSpritePoint->Is_ActFra;
			OneSpritePoint->_height = _lastSpritePoint->_height;
			OneSpritePoint->_width = _lastSpritePoint->_width;
			OneSpritePoint->_ScallX = _lastSpritePoint->_ScallX;
			OneSpritePoint->_ScallY = _lastSpritePoint->_ScallY;
		}
		else if (_lastSpritePoint != nullptr && _nextSpritePoint != nullptr)
		{
			//OneSpritePoint = getChaZhi(_lastSpritePoint, _nextSpritePoint, n);
			//OneSpritePoint->injureVertices = getChaInj(_lastSpritePoint, _nextSpritePoint, n);
			_nextSpritePoint = getChaAct(_lastSpritePoint, _nextSpritePoint, n);
			OneSpritePoint->_height = _nextSpritePoint->_height;
			OneSpritePoint->_width = _nextSpritePoint->_width;
			OneSpritePoint->_ScallX = _nextSpritePoint->_ScallX;
			OneSpritePoint->_ScallY = _nextSpritePoint->_ScallY;
		}
		else if (_lastSpritePoint != nullptr)
		{
			//OneSpritePoint->injureVertices = _lastSpritePoint->injureVertices;
			OneSpritePoint->_height = _lastSpritePoint->_height;
			OneSpritePoint->_width = _lastSpritePoint->_width;
			OneSpritePoint->_ScallX = _lastSpritePoint->_ScallX;
			OneSpritePoint->_ScallY = _lastSpritePoint->_ScallY;
		}



		_lastSpritePoint = nullptr;
		//_nextSpritePoint = nullptr;
		_lcha = 100000;
		//_ncha = 100000;
		for (i = 0; i < spritePoints.size(); i++)
		{
			_tempSpritePoint = spritePoints.at(i);
			if (_tempSpritePoint->Single_ID <= n && (n - _tempSpritePoint->Single_ID) <= _lcha && _tempSpritePoint->Is_BodyFra)
			{
				_lcha = n - _tempSpritePoint->Single_ID;
				_lastSpritePoint = _tempSpritePoint;
			}
		}
		if (_lcha == 0)
		{
			//OneSpritePoint->attackVertices = _lastSpritePoint->attackVertices;
			//OneSpritePoint->injureVertices = _lastSpritePoint->injureVertices;
			OneSpritePoint->bodyVertices = _lastSpritePoint->bodyVertices;
			OneSpritePoint->Is_BodyFra = _lastSpritePoint->Is_BodyFra;
		}
		else if (_lastSpritePoint != nullptr)
		{
			//OneSpritePoint->injureVertices = _lastSpritePoint->injureVertices;
			OneSpritePoint->bodyVertices = _lastSpritePoint->bodyVertices;
		}
	}
	//else
	//{
	//	OneSpritePoint = _myOnePoint;
	//}
	
	if (OneSpritePoint->injureVertices != nullptr)
	{
		injuredNode->setVertices(OneSpritePoint->injureVertices[0], OneSpritePoint->injureVertices[2]);
		injuredNode->Rotate = OneSpritePoint->RotateInj;
		injuredNode->setRotateVertices(OneSpritePoint->injureVertices[0], OneSpritePoint->injureVertices[2]);
	}

	if (OneSpritePoint->attackVertices != nullptr)
	{
		attackNode->setVertices(OneSpritePoint->attackVertices[0], OneSpritePoint->attackVertices[2]);
		attackNode->Rotate = OneSpritePoint->RotateAtt;
		attackNode->setRotateVertices(OneSpritePoint->attackVertices[0], OneSpritePoint->attackVertices[2]);
	}
	if (OneSpritePoint->bodyVertices != nullptr)
	{
		bodyNode->setVertices(OneSpritePoint->bodyVertices[0], OneSpritePoint->bodyVertices[2]);
		//bodyNode->Rotate = OneSpritePoint->RotateAtt;
		bodyNode->setRotateVertices(OneSpritePoint->bodyVertices[0], OneSpritePoint->bodyVertices[2]);
	}
	_QtEdit->SetFraDe(OneSpritePoint);
	_tempSpritePoint = nullptr;
	this->doDraw();

}

Vec2 * DrawRectLayer::getChaAtt(MySpritePoint *la, MySpritePoint *en, int n)
{
	Vec2 * tempatt = new Vec2[5];
	float one, two;
	one = la->attackVertices[0].x + (en->attackVertices[0].x - la->attackVertices[0].x) / (en->Single_ID - la->Single_ID) * (n - la->Single_ID);
	two = la->attackVertices[0].y + (en->attackVertices[0].y - la->attackVertices[0].y) / (en->Single_ID - la->Single_ID) * (n - la->Single_ID);
	tempatt[0] = Vec2(one, two);
	tempatt[1] = Vec2(0, 0);
	one = la->attackVertices[2].x + (en->attackVertices[2].x - la->attackVertices[2].x) / (en->Single_ID - la->Single_ID) * (n - la->Single_ID);
	two = la->attackVertices[2].y + (en->attackVertices[2].y - la->attackVertices[2].y) / (en->Single_ID - la->Single_ID) * (n - la->Single_ID);
	tempatt[2] = Vec2(one, two);
	tempatt[1] = Vec2(tempatt[2].x, tempatt[0].y);
	tempatt[3] = Vec2(tempatt[0].x, tempatt[2].y);
	tempatt[4] = tempatt[0];
	return tempatt;
}
Vec2 *DrawRectLayer::getChaInj(MySpritePoint *la, MySpritePoint *en, int n)
{
	float one, two;
	Vec2 * tempinj = new Vec2[5];
	one = la->injureVertices[0].x + (en->injureVertices[0].x - la->injureVertices[0].x) / (en->Single_ID - la->Single_ID) * (n - la->Single_ID);
	two = la->injureVertices[0].y + (en->injureVertices[0].y - la->injureVertices[0].y) / (en->Single_ID - la->Single_ID) * (n - la->Single_ID);
	tempinj[0] = Vec2(one, two);
	tempinj[1] = Vec2(0, 0);
	one = la->injureVertices[2].x + (en->injureVertices[2].x - la->injureVertices[2].x) / (en->Single_ID - la->Single_ID) * (n - la->Single_ID);
	two = la->injureVertices[2].y + (en->injureVertices[2].y - la->injureVertices[2].y) / (en->Single_ID - la->Single_ID) * (n - la->Single_ID);
	tempinj[2] = Vec2(one, two);
	tempinj[1] = Vec2(tempinj[2].x, tempinj[0].y);
	tempinj[3] = Vec2(tempinj[0].x, tempinj[2].y);
	tempinj[4] = tempinj[0];
	return tempinj;

}
MySpritePoint * DrawRectLayer::getChaAct(MySpritePoint *la, MySpritePoint *en, int n)
{
	float _Cha;
	_tempSpritePoint = new MySpritePoint();
	_Cha = la->_height + (en->_height - la->_height) / (en->Single_ID - la->Single_ID) * (n - la->Single_ID);
	_tempSpritePoint->_height = _Cha;
	_Cha = la->_width + (en->_width - la->_width) / (en->Single_ID - la->Single_ID) * (n - la->Single_ID);
	_tempSpritePoint->_width = _Cha;
	_Cha = la->_ScallX + (en->_ScallX - la->_ScallX) / (en->Single_ID - la->Single_ID) * (n - la->Single_ID);
	_tempSpritePoint->_ScallX = _Cha;
	_Cha = la->_ScallY + (en->_ScallY - la->_ScallY) / (en->Single_ID - la->Single_ID) * (n - la->Single_ID);
	_tempSpritePoint->_ScallY = _Cha;
	return _tempSpritePoint;
}

MySpritePoint * DrawRectLayer::getChaZhi(MySpritePoint *la, MySpritePoint *en, int n)
{
	Vec2 * tempatt = new Vec2[5];
	Vec2 * tempinj = new Vec2[5];
	float one, two;
	if (la->attackVertices != nullptr && en->attackVertices != nullptr && en->Is_AttFra)
	{
		one = la->attackVertices[0].x + (en->attackVertices[0].x - la->attackVertices[0].x) / (en->Single_ID - la->Single_ID) * (n - la->Single_ID);
		two = la->attackVertices[0].y + (en->attackVertices[0].y - la->attackVertices[0].y) / (en->Single_ID - la->Single_ID) * (n - la->Single_ID);
		tempatt[0] = Vec2(one, two);
		tempatt[1] = Vec2(0, 0);
		one = la->attackVertices[2].x + (en->attackVertices[2].x - la->attackVertices[2].x) / (en->Single_ID - la->Single_ID) * (n - la->Single_ID);
		two = la->attackVertices[2].y + (en->attackVertices[2].y - la->attackVertices[2].y) / (en->Single_ID - la->Single_ID) * (n - la->Single_ID);
		tempatt[2] = Vec2(one, two);
		tempatt[1] = Vec2(tempatt[2].x, tempatt[0].y);
		tempatt[3] = Vec2(tempatt[0].x, tempatt[2].y);
		tempatt[4] = tempatt[0];
	}
	else if (la->attackVertices != nullptr)
	{
		tempatt = la->attackVertices;
	}

	if (la->injureVertices != nullptr && en->injureVertices != nullptr && en->Is_InjFra)
	{
		one = la->injureVertices[0].x + (en->injureVertices[0].x - la->injureVertices[0].x) / (en->Single_ID - la->Single_ID) * (n - la->Single_ID);
		two = la->injureVertices[0].y + (en->injureVertices[0].y - la->injureVertices[0].y) / (en->Single_ID - la->Single_ID) * (n - la->Single_ID);
		tempinj[0] = Vec2(one, two);
		tempinj[1] = Vec2(0, 0);
		one = la->injureVertices[2].x + (en->injureVertices[2].x - la->injureVertices[2].x) / (en->Single_ID - la->Single_ID) * (n - la->Single_ID);
		two = la->injureVertices[2].y + (en->injureVertices[2].y - la->injureVertices[2].y) / (en->Single_ID - la->Single_ID) * (n - la->Single_ID);
		tempinj[2] = Vec2(one, two);
		tempinj[1] = Vec2(tempinj[2].x, tempinj[0].y);
		tempinj[3] = Vec2(tempinj[0].x, tempinj[2].y);
		tempinj[4] = tempinj[0];
	}
	else if (la->injureVertices != nullptr)
	{
		tempinj = la->injureVertices;
	}

	float _Cha;
	_tempSpritePoint = new MySpritePoint();
	_tempSpritePoint->Single_ID = Single_ID;
	_tempSpritePoint->attackVertices = tempatt;
	_tempSpritePoint->injureVertices = tempinj;
	_Cha = la->_height + (en->_height - la->_height) / (en->Single_ID - la->Single_ID) * (n - la->Single_ID);
	_tempSpritePoint->_height = _Cha;
	_Cha = la->_width + (en->_width - la->_width) / (en->Single_ID - la->Single_ID) * (n - la->Single_ID);
	_tempSpritePoint->_width = _Cha;
	_Cha = la->_ScallX + (en->_ScallX - la->_ScallX) / (en->Single_ID - la->Single_ID) * (n - la->Single_ID);
	_tempSpritePoint->_ScallX = _Cha;
	_Cha = la->_ScallY + (en->_ScallY - la->_ScallY) / (en->Single_ID - la->Single_ID) * (n - la->Single_ID);
	_tempSpritePoint->_ScallY = _Cha;
	return _tempSpritePoint;
}


void DrawRectLayer::deleteFrame()
{
	//删除Frame
	for (i = 0; i < spritePoints.size(); i ++)
	{
		if (spritePoints.at(i)->Single_ID == Single_ID)
		{
			spritePoints.erase(spritePoints.begin() + i);
			break;
		}
	}
	_QtEdit->setWindowTitle(_QtEdit->windowTitle().split("*").at(0) + "*");
	//重新绘制
	drawPositionEdit(Single_ID);
}
//int a = 0;
void DrawRectLayer::ScheduMyUpdate(float dt)
{
	//showMsg(NULL, dt);
	mydt += oneDt;
	//showMsg(NULL, mydt , a);
	_QtEdit->SlderChange(mydt);
	_QtEdit->AnimationUpdate(mydt);
	if (mydt > animate->getDuration())
	{
		mydt = 0.0;
		//a = 0;
	}
	//showMsg(NULL, mydt ,a ++);
	//mydt += 0.01;
	//animate->updateOnPercentage(mydt);
	//showMsg("dt", mydt, 0);
}
/************************************************************************/
/*开启自动                                                              */
/************************************************************************/
void DrawRectLayer::StartUpdate()
{
	mydt = 0.0;
	oneDt = animate->getDuration() / (animate->getDuration() * oneFPX);
	float pe = animate->getDuration() / oneFPX;
	this->schedule(schedule_selector(DrawRectLayer::ScheduMyUpdate), pe);
}
/************************************************************************/
/* 关闭自动                                                             */
/************************************************************************/
void DrawRectLayer::EndUpdate()
{
	this->unschedule(schedule_selector(DrawRectLayer::ScheduMyUpdate));
}