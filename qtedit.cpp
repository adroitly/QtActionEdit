#include "qtedit.h"
#include "Classes/AppDelegate.h"
#include "Classes/CocosQtPort/CCQGLView.h"
#include <QTimer>
#include <QDockWidget>
#include "QTextEdit"
#include "QTextBlock"
#include <QEvent>
#include <qfiledialog.h>
#include "QMessageBox.h"
#include "DrawRectLayer.h"
#include "cocos2d.h"
#include "QTableWidget.h"
#include "QTextStream.h"
#include "string.h"
#include "DES/DES.h"
#include "QTextCodec.h"
#include "json/json.h"
USING_NS_CC;
static QtEdit		* _QtEdit;

QtEdit::QtEdit(QWidget *parent)
	: QMainWindow(parent),
	_appDelegate(NULL),
	_glWidget(NULL),
	is_import(false),
	Ctrl_Is_On(false),
	_lastButton(NULL),
	FPX(-1),
	myVector(NULL),
	Shift_is_ON(false)
{
	QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
	_QtEdit = this;
	ui.setupUi(this);
	ui.SceneWidget->setWindowTitle("Cocos2dx Scene");
	ui.SceneWidget->setFeatures(QDockWidget::NoDockWidgetFeatures);
	ui.OutWiget->setWindowTitle("Out Put");
	//ui.OutWiget->setFeatures(QDockWidget::NoDockWidgetFeatures);
	ui.PerWiget->setWindowTitle("PerCentage");
	ui.PerWiget->setFeatures(QDockWidget::NoDockWidgetFeatures);
	ui.dockWidget->setWindowTitle("");
	ui.dockWidget->setFeatures(QDockWidget::NoDockWidgetFeatures);
	ui.AnimationtreeWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	ui.AnimationtreeWidget->header()->setStretchLastSection(true);
	ui.dockWidgetContents_5->setUpdatesEnabled(TRUE);
	ui.PencentageSlider->setGeometry(81, 0, this->width()-ui.label_5->width(), 20);
	codec = QTextCodec::codecForName("GB18030");
	AddCao();
	AddSliderButton();
}

void QtEdit::AddCao()
{
	//QObject::connect(importaction, SIGNAL(triggered()), QtEditClass, SLOT(import()));
	//QObject::connect(Width, SIGNAL(textEdited(QString)), QtEditClass, SLOT(ChangeInput()));
	//QObject::connect(Height, SIGNAL(textEdited(QString)), QtEditClass, SLOT(ChangeInput()));
	//QObject::connect(ScallX, SIGNAL(textEdited(QString)), QtEditClass, SLOT(ChangeInput()));
	//QObject::connect(ScallY, SIGNAL(textEdited(QString)), QtEditClass, SLOT(ChangeInput()));
	//QObject::connect(PauseButton, SIGNAL(clicked()), QtEditClass, SLOT(pausebuttonclick()));
	//QObject::connect(showmessage, SIGNAL(textChanged()), QtEditClass, SLOT(showmessageChange()));
	//QObject::connect(PencentageSlider, SIGNAL(valueChanged(int)), QtEditClass, SLOT(AnimationSlderChange()));
	//QObject::connect(AnimationtreeWidget, SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)), QtEditClass, SLOT(AnimationTreeWidgetClick(QTreeWidgetItem*, int)));
	//QObject::connect(PencentageSlider, SIGNAL(actionTriggered(int)), QtEditClass, SLOT(AnimationSlderClick(int)));
	//QObject::connect(actionHelp, SIGNAL(triggered()), QtEditClass, SLOT(ActionHelp()));
	//QObject::connect(exportaction, SIGNAL(triggered()), QtEditClass, SLOT(exportData()));
	//QObject::connect(openaction, SIGNAL(triggered()), QtEditClass, SLOT(openData()));
	//QObject::connect(closeaction, SIGNAL(triggered()), QtEditClass, SLOT(close()));
	QObject::connect(ui.importaction, SIGNAL(triggered()), this, SLOT(import()));
	QObject::connect(ui.Width, SIGNAL(textEdited(QString)), this, SLOT(ChangeInput()));
	QObject::connect(ui.Height, SIGNAL(textEdited(QString)), this, SLOT(ChangeInput()));
	QObject::connect(ui.ScallX, SIGNAL(textEdited(QString)), this, SLOT(ChangeInput()));
	QObject::connect(ui.ScallY, SIGNAL(textEdited(QString)), this, SLOT(ChangeInput()));
	QObject::connect(ui.PauseButton, SIGNAL(clicked()), this, SLOT(pausebuttonclick()));
	QObject::connect(ui.showmessage, SIGNAL(textChanged()), this, SLOT(showmessageChange()));
	QObject::connect(ui.PencentageSlider, SIGNAL(valueChanged(int)), this, SLOT(AnimationSlderChange()));
	QObject::connect(ui.AnimationtreeWidget, SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)), this, SLOT(AnimationTreeWidgetClick(QTreeWidgetItem*, int)));
	QObject::connect(ui.PencentageSlider, SIGNAL(actionTriggered(int)), this, SLOT(AnimationSlderClick(int)));
	QObject::connect(ui.actionHelp, SIGNAL(triggered()), this, SLOT(ActionHelp()));
	QObject::connect(ui.exportaction, SIGNAL(triggered()), this, SLOT(exportData()));
	QObject::connect(ui.openaction, SIGNAL(triggered()), this, SLOT(openData()));
	QObject::connect(ui.closeaction, SIGNAL(triggered()), this, SLOT(close()));
}

QtEdit::~QtEdit()
{
	Director::getInstance()->release();
	delete _DrawRectLayer;
	delete _QtEdit;
}

QtEdit * QtEdit::getInstance()
{
	if (_QtEdit == NULL)
	{
		new QtEdit();
	}
	return _QtEdit;
}
void QtEdit::ShowMsg(std::string str)
{
	mymsg = mymsg + str + "\n";
	ui.showmessage->setPlainText((codec->toUnicode(mymsg.c_str())));
	QTextCursor cursor = ui.showmessage->textCursor();
	cursor.movePosition(QTextCursor::End);
	ui.showmessage->setTextCursor(cursor);
	
}
void QtEdit::closeEvent(QCloseEvent *event)
{
	if (this->windowTitle().indexOf("*") != -1)
	{
		std::string showabout = "当前未保存是否退出?";
		//QMessageBox::about(NULL, "About Edit", codec->toUnicode(showabout.c_str()));
		QMessageBox::StandardButton rb = QMessageBox::question(NULL, "information", codec->toUnicode(showabout.c_str()), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
		if (rb == QMessageBox::Yes)
		{
			//import();
			cocos2d::Director::getInstance()->end();
			exit(0);
			qApp->quit();
			event->accept();  //接受退出信号，程序退出
		}
		else
		{
			event->ignore();  //忽略退出信号，程序继续运行
		}
	}
	else
	{
		cocos2d::Director::getInstance()->end();
		exit(0);
		qApp->quit();
		event->accept();  //接受退出信号，程序退出
	}
	//QMessageBox::StandardButton button;
	//button = QMessageBox::question(this, tr("退出程序"),
	//	QString(tr("警告：程序有一个任务正在运行中，是否结束操作退出?")),
	//	QMessageBox::Yes | QMessageBox::No);

	//if (button == QMessageBox::No) {
	//	event->ignore();  //忽略退出信号，程序继续运行
	//}
	//else if (button == QMessageBox::Yes) {
	//	event->accept();  //接受退出信号，程序退出
	//}
}
void QtEdit::setGLView(QWidget *glWidget)
{
	_glWidget = glWidget;

	if (_glWidget)
	{
		this->setParent((HWND)glWidget->winId());
 		ui.SceneWidget->setWidget(_glWidget);
		//ui.SceneWidget->setTitleBarWidget(_glWidget);
 		setCentralWidget(ui.SceneWidget);
	}
}
void QtEdit::exportData()
{
	//ShowMsg("Export");
	if (!is_import)
	{
		QMessageBox::StandardButton rb = QMessageBox::question(NULL, "information", codec->toUnicode("当前没有导入资源，是否先导入资源?"), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
		if (rb == QMessageBox::Yes)
		{
			import();
			
		}
		
	}
	else
	{
		QString fileName = QFileDialog::getSaveFileName(this,
			tr("Open Config"),
			"",
			tr("json Files (*.json);; all files (*)"));

		if (!fileName.isNull())
		{
			//fileName是文件名
			doSaveData(fileName);
		}
		else
		{
			//点的是取消
		}
	}
}

void QtEdit::ActionHelp()
{
	//QMessageBox::aboutQt(NULL, "About Qt");
	std::string showabout = "";
	showabout = "cocos Action Edit是FBX用cocos2dx自带的转换器转换到c3b或c3t中，支持一个model多个Animation的动作编辑器\n";
	showabout += "贴图的名字必须和model的一样，并且贴图文件是.png格式，动作的c3b和c3t必须放在animations文件夹下，";
	showabout += "为了让其在cocos2dx中运行，所有的资源必须在Resources文件夹下，这个编辑器支持保存操作和导出json格式操作。";
	showabout += "\n本编辑器存在很多问题。";
	showabout += "\nCopyRight(©) killer & TimeNew Studios";
	QMessageBox::about(NULL, "About Edit", codec->toUnicode(showabout.c_str()));
}

void QtEdit::openData()
{
	ShowMsg("Open");
}
void QtEdit::import()
{
	QString file_name;
	file_name = QFileDialog::getOpenFileName(this,
		tr("Open Config"), "", tr("c3b Files (*.c3b);; c3t Files (*.c3t);; all Files (*)"));
	if (!file_name.isNull())
	{
		//fileName是文件名
		_DrawRectLayer = DrawRectLayer::getInstence();
		//log("%d", file_name.lastIndexOf("/"));
		//QStringList strlist = file_name.split("Resources/");
		QString Re_File_name = file_name.mid(file_name.lastIndexOf("/") + 1);
		this->setWindowTitle(Re_File_name);
		
		if (_DrawRectLayer->sp)
		{
			_DrawRectLayer->removeChild(_DrawRectLayer->sp, true);
		}

		QFileInfo fi; 
		fi = QFileInfo(file_name);
		saveDataName = fi.path() + "/" +  fi.fileName().split(".").at(0) + tr(".data");
		_filename = fi.fileName().split(".").at(0);
		if (is_import)
		{
			animation_list.clear();
			_DrawRectLayer->removeAllChildrenWithCleanup(true);
			_DrawRectLayer->spritePoints.clear();
		}
		
		AddAnimationList(file_name);
		
		if (animation_list.size() != 0)
		{
			is_import = true;
			_DrawRectLayer->updatemydata(file_name.toStdString(), file_name.split(".").at(0).toStdString() + ".png", animation_list.at(0).toStdString());
			ui.dockWidget->setWindowTitle(animation_list.at(0));
			setSlideEndFPX(_DrawRectLayer->animation->getDuration() * oneFPX);
			//从.data文件中导入数据
			Init();

			btn = sliderButton.at(0);
			btn->Is_Click = true;
			btn->setPalette(QPalette(Qt::green));
			btn->setAutoFillBackground(true);
			showline = sliderFameshow.at((btn->Singl_ID));
			showline->setVisible(true);
			_lastButton = btn;
			SlderAnimationAction();

			MySpriteChange();
			setMyFrame();
			//btn = sliderButton.at(0);
			//btn->Is_Click = true;
			//btn->setPalette(QPalette(Qt::green));
			//btn->setAutoFillBackground(true);
			//showline = sliderFameshow.at((btn->Singl_ID));
			//showline->setVisible(true);
			//_lastButton = btn;
			//SlderAnimationAction();
			//AddSliderButton();
		}
		else
		{
			//QMessageBox::about(this, tr("information"), tr("No animations"));
			QMessageBox::about(this, tr("information"), codec->toUnicode("当前没有animations"));
		}
		
	}
	else{
		//点的是取消
	}
}

void QtEdit::Init()
{
	MyVector * tempVector = new MyVector();
	MySpritePoint * tempSprite = new MySpritePoint();
	spritesPoints.clear();
	_DrawRectLayer->spritePoints.clear();
	QFile file(saveDataName);
	if (!file.exists())
	{
		file.open(QIODevice::ReadWrite);
		file.close();
		return;
	}
	QString _MyData = NULL;
	if (!file.open(QIODevice::ReadOnly))
	{
		QMessageBox::about(this, tr("information"), tr("Read ERROR"));
		return;
	}
	_MyData = QString(QByteArray::fromBase64(file.readAll()));
	file.close();
	if (_MyData == NULL || _MyData.size() <= 0 || _MyData.length() <= 0 || _MyData.isEmpty() || _MyData.isNull())
	{
		return;
	}
	Json::Reader reader;
	Json::Value root;
	if (!reader.parse(_MyData.toStdString(), root, false))
	{
		return;
	}
	int i, j;
	int ex, ey, sx, sy;
	double _wi, _he, _sclx, _scly;
	float rotate;
	if (root.size() <= 0)
	{
		return;
	}
	root = root[_filename.toStdString()];
	Json::Value Anima;
	Json::Value Item;
	Json::Value ObItem;
	Json::Value _data;
	std::string jiedian;
	for (i = 0; i < animation_list.size(); i ++)
	{
		tempVector = new MyVector();
		//jiedian = animation_list.at(i).split("/").at(1).split(".").at(0).toStdString();
		jiedian = animation_list.at(i).mid(animation_list.at(i).lastIndexOf("/") + 1).split(".").at(0).toStdString();
		if (root[jiedian].isNull())
		{
			continue;
		}
		Anima = root[jiedian];
		for (j = 0; j < Anima.size(); j++)
		{
			tempSprite = new MySpritePoint();
			Json::Value temp_value = Anima[j];
			Json::Value Inj = NULL;
			Json::Value Att = NULL;
			Json::Value Act = NULL;
			Json::Value Body = NULL;
			if (!temp_value["att"].isNull())
			{
				Att = temp_value["att"];
			}
			if (!temp_value["inj"].isNull())
			{
				Inj = temp_value["inj"];
			}
			if (!temp_value["act"].isNull())
			{
				Act = temp_value["act"];
			}
			if (!temp_value["body"].isNull())
			{
				Body = temp_value["body"];
			}
			tempSprite->Single_ID = temp_value["fre"].asInt();
			if (Att != NULL)
			{
				sx = Att["sx"].asInt();
				sy = Att["sy"].asInt();
				ex = Att["ex"].asInt();
				ey = Att["ey"].asInt();
				rotate = Att["ro"].asDouble();
				tempSprite->setAttackVertices(Vec2(sx, sy), Vec2(ex, ey));
				tempSprite->RotateAtt = rotate; 
				tempSprite->Is_AttFra = true;
			}
			if (Inj != NULL)
			{
				sx = Inj["sx"].asInt();
				sy = Inj["sy"].asInt();
				ex = Inj["ex"].asInt();
				ey = Inj["ey"].asInt();
				rotate = Inj["ro"].asDouble();
				tempSprite->setInjureVertices(Vec2(sx, sy), Vec2(ex, ey));
				tempSprite->RotateInj = rotate;
				tempSprite->Is_InjFra = true;
			}
			if (Act != NULL)
			{
				_he = Act["he"].asDouble();
				_wi = Act["wi"].asDouble();
				_sclx = Act["scalx"].asDouble();
				_scly = Act["scaly"].asDouble();
				tempSprite->_ScallX = _sclx;
				tempSprite->_ScallY = _scly;
				tempSprite->_width = _wi;
				tempSprite->_height = _he;
				tempSprite->Is_ActFra = true;
			}
			if (Body != NULL)
			{
				sx = Body["sx"].asInt();
				sy = Body["sy"].asInt();
				ex = Body["ex"].asInt();
				ey = Body["ey"].asInt();
				//rotate = Inj["ro"].asDouble();
				tempSprite->setBodyVertices(Vec2(sx, sy), Vec2(ex, ey));
				//tempSprite->RotateInj = rotate;
				tempSprite->Is_BodyFra = true;
			}
			tempVector->Sprites.push_back(tempSprite);
		}
		tempVector->Singl_ID = i;
		spritesPoints.push_back(tempVector);
	}
	//myVector = new MyVector();
	for (i = 0; i < spritesPoints.size(); i ++ )
	{
		if (spritesPoints.at(i)->Singl_ID == 0)
		{
			myVector = new MyVector();
			myVector->Singl_ID = 0;
			myVector->Sprites = spritesPoints.at(i)->Sprites;
			_DrawRectLayer->spritePoints = myVector->Sprites;
			//SetMyUI();
			break;;
		}
	}
	//setSlideEndFPX(_DrawRectLayer->animation->getDuration() * oneFPX);
	//AddSliderButton();
	//btn = sliderButton.at(0);
	//btn->Is_Click = true;
	//btn->setPalette(QPalette(Qt::green));
	//btn->setAutoFillBackground(true);
	//showline = sliderFameshow.at((btn->Singl_ID));
	//showline->setVisible(true);
	//_lastButton = btn;
	//SlderAnimationAction();
	//SetMyUI();
}

void QtEdit::SetMyUI()
{
	ui.Height->setText(QString::number(myVector->_height, 'f', 0));
	ui.Width->setText(QString::number(myVector->_width, 'f', 0));
	ui.ScallX->setText(QString::number(myVector->_ScallX, 'f', 0));
	ui.ScallY->setText(QString::number(myVector->_ScallY, 'f', 0));
	//ChangeInput();
	MySpriteChange();
}
//Slider下的Button响应
void QtEdit::SlderButtonClick()
{
	btn = dynamic_cast<QtButton*>(sender());
	if (is_import && btn->Singl_ID <= FPX)
	{
		//_DrawRectLayer->unscheduleUpdate();
		_DrawRectLayer->EndUpdate();
		ui.PauseButton->setText("Start");
		pu = -1;
		//_DrawRectLayer->drawPositionEdit(btn->Singl_ID);
	}
	SlderAnimationAction();

	
}
void  QtEdit::SlderAnimationAction()
{
	if (is_import)
	{
		if (btn->Singl_ID > FPX)
		{
			return;
		}
		//if (btn->Singl_ID == FPX)
		//{
		//	if (is_import)
		//	{
		//		//std::sprintf(myshowstr, "%d", 100);
		//		_DrawRectLayer->animate->updateOnPercentage(0.01 * btn->Singl_ID * (100.0 / FPX));
		//		return;
		//	}
		//}
	}
	if (_lastButton != NULL)
	{
		if (_lastButton->Singl_ID % 5 != 0)
		{
			showline = sliderFameshow.at((_lastButton->Singl_ID ));
			showline->setVisible(false);
		}
		_lastButton->Is_Click = false;
		//_lastButton->setAutoFillBackground(true);
		_lastButton->setStyleSheet("background:transparent");
		//_endButton->setPalette(QPalette(Qt::red));
	}
	if (btn->Singl_ID < FPX || FPX == -1)
	{
		_lastButton = btn;
	}
	btn->Is_Click = true;
	btn->setPalette(QPalette(Qt::green));
	btn->setAutoFillBackground(true);
	showline = sliderFameshow.at((btn->Singl_ID));
	showline->setVisible(true);
	if (is_import)
	{
		_DrawRectLayer->drawPositionEdit(btn->Singl_ID);
		_DrawRectLayer->animate->updateOnPercentage(0.01 * btn->Singl_ID * 100.0 / (FPX -1));
		_endButton->setPalette(QPalette(Qt::red));
	}
	
}
//
void QtEdit::ChangeSliderButton()
{

}

//添加按钮
void QtEdit::AddSliderButton()
{
	int  i;
	_lastButton = NULL;
	buttonWidget = new QWidget(ui.PerWiget);
	buttonWidget->setPalette(QPalette(Qt::gray));
	buttonWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	scrollArea = new QScrollArea(ui.PerWiget);
	//scrollArea->setBackgroundRole(QPalette::Dark);
	scrollArea->setWidget(buttonWidget);
	scrollArea->setGeometry(QRect(0, 40, 1780, 190));
	QScrollBar *scallbar = scrollArea->horizontalScrollBar();
	buttonWidget->setGeometry(QRect(0, 40, 8000, 170));
	sliderFameshow.clear();
	sliderButton.clear();
	//float duratime = _DrawRectLayer->animation->getDuration();
	QFont font;
	font.setPointSize(9);
	int size = 400;
	int wi;
	for (i = 0; i < size; i ++ )
	{
		std::sprintf(myshowstr, "%d", i);
		line = new QFrame(buttonWidget);
		oneButton = new QtButton(buttonWidget);
		//oneButton->setAutoFillBackground(true);
		
		oneButton->Singl_ID = i;
		oneButton->Is_Click = false;
		wi = i * 20;
		oneButton->setGeometry(QRect(wi, 20, 20, 130));
		oneButton->setStyleSheet("background:transparent");
		oneButton->_AttFraButton->setGeometry(QRect(wi, 150, 20, 5));
		oneButton->_AttFraButton->setStyleSheet("background:transparent");
		oneButton->_ActFraButton->setGeometry(QRect(wi, 155, 20, 5));
		oneButton->_ActFraButton->setStyleSheet("background:transparent");
		oneButton->_InjFraButton->setGeometry(QRect(wi, 160, 20, 5));
		oneButton->_InjFraButton->setStyleSheet("background:transparent");
		oneButton->_BodyFraButton->setGeometry(QRect(wi, 165, 20, 5));
		oneButton->_BodyFraButton->setStyleSheet("background:transparent");
		line->setGeometry(QRect(wi, 20, 3, 130));
		line->setFrameShape(QFrame::VLine);
		line->setFrameShadow(QFrame::Sunken);
		QObject::connect(oneButton, SIGNAL(clicked()), this, SLOT(SlderButtonClick()));
		showline = new QLabel(buttonWidget);
		showline->setGeometry(QRect(wi, 7, 20, 15));
		showline->setFont(font);
		showline->setText(myshowstr);
		showline->setAlignment(Qt::AlignCenter);
		showline->setVisible(false);
		if (i % 5 == 0)
		{
			showline->setVisible(true);
		}
		sliderFameshow.push_back(showline);
		sliderButton.push_back(oneButton);
		//sliderButtonList.push_back(oneButton);
	}

}

void QtEdit::AnimationUpdate(float dt)
{
	//_lastButton = btn;
	int sing_id = dt * 100.0 / (100.0 / oneFPX);
	//int sing_id = dt / (0.01 * 100 / (FPX - 1));
	//int i;
	//for (i = 0; i < FPX; i ++)
	//{
	//	btn = sliderButton.at(i);
	//	if (btn->Singl_ID == sing_id)
	//	{
	//		break;
	//	}
	//}
	
	btn = sliderButton.at(sing_id);
	SlderAnimationAction();
}

void QtEdit::showmessageChange()
{
	
	mymsg = ui.showmessage->toPlainText().toStdString();
}
void QtEdit::ChangeInput()
{
	_DrawRectLayer = DrawRectLayer::getInstence();
	_QtEdit->setWindowTitle(_QtEdit->windowTitle().split("*").at(0) + "*");
	if (btn != nullptr && is_import)
	{
		int i = btn->Singl_ID;
		_DrawRectLayer->EndUpdate();
		//for (i = 0; i < FPX; i ++)
		{
			//if (sliderButton.at(i)->Singl_ID == btn->Singl_ID)
			{
				//sliderButton.at(i)->Is_ActFra = true;
				sliderButton.at(i)->_ActFraButton->setPalette(QPalette(Qt::blue));
				sliderButton.at(i)->_ActFraButton->setAutoFillBackground(true);
				sliderButton.at(i)->Is_ActFra = true;
				MySpritePoint * OneSpritePoint = new MySpritePoint();
				OneSpritePoint->Single_ID = _DrawRectLayer->Single_ID;
				OneSpritePoint->attackVertices = _DrawRectLayer->attackNode->Vertices;
				OneSpritePoint->RotateAtt = _DrawRectLayer->attackNode->Rotate;
				OneSpritePoint->injureVertices = _DrawRectLayer->injuredNode->Vertices;
				OneSpritePoint->RotateInj = _DrawRectLayer->injuredNode->Rotate;
				//if (ui.Width->text().toDouble() != _IN_Width || ui.Height->text().toDouble() != _IN_Height || ui.ScallX->text().toDouble() != _IN_SacllX || ui.ScallY->text().toDouble() != _IN_ScallY)
				//{
				//	OneSpritePoint->Is_ActFra = true;
				//}
				//else
				//{
				//	OneSpritePoint->Is_ActFra = false;
				//}
				OneSpritePoint->Is_ActFra = true;
				//新的
				bool Is_Has = false;
				MySpritePoint * _tempSpritePoint;
				for (i = 0; i < _DrawRectLayer->spritePoints.size(); i++)
				{
					_tempSpritePoint = _DrawRectLayer->spritePoints.at(i);
					//showMsg("SIngle_ID", NULL, _tempSpritePoint->Single_ID);
					//showMsg("Size", NULL, spritePoints.size());
					if (_tempSpritePoint->Single_ID == _DrawRectLayer->Single_ID)
					{
						_DrawRectLayer->spritePoints.at(i)->attackVertices = OneSpritePoint->attackVertices;
						_DrawRectLayer->spritePoints.at(i)->injureVertices = OneSpritePoint->injureVertices;
						//if (ui.Width->text().toDouble() != _IN_Width || ui.Height->text().toDouble() != _IN_Height || ui.ScallX->text().toDouble() != _IN_SacllX || ui.ScallY->text().toDouble() != _IN_ScallY)
						//{
						//	_DrawRectLayer->spritePoints.at(i)->Is_ActFra = true;
						//}
						//else
						//{
						//	_DrawRectLayer->spritePoints.at(i)->Is_ActFra = false;
						//	sliderButton.at(btn->Singl_ID)->deleteAct();
						//}
						_DrawRectLayer->spritePoints.at(i)->Is_ActFra = true;
						Is_Has = true;
						break;
					}
				}
				if (!Is_Has)
				{
					MySpritePoint * ss = new MySpritePoint();
					ss->Single_ID = OneSpritePoint->Single_ID;
					ss->Is_ActFra = OneSpritePoint->Is_ActFra;
					ss->attackVertices = OneSpritePoint->attackVertices;
					ss->injureVertices = OneSpritePoint->injureVertices;
					_DrawRectLayer->spritePoints.push_back(ss);
				}
				//break;
			}
		}
	}
	if (is_import)
	{
		
		MySpriteChange();
		SlderAnimationAction();
	}
	else
	{
		//QMessageBox::about(this, tr("information"), tr("NULL Import"));
	}
}

void QtEdit::pausebuttonclick()
{
	QPushButton* btn = dynamic_cast<QPushButton*>(sender());
	//ShowMsg(btn->text().toStdString());
	pu *= -1;
	if (is_import)
	{
		if (-1 == pu)
		{
			ui.PauseButton->setText(tr("Start"));
			_DrawRectLayer->EndUpdate();
			//_DrawRectLayer->unscheduleUpdate();
		}
		else
		{
			ui.PauseButton->setText(tr("Pause") );
			_DrawRectLayer->StartUpdate();
			//_DrawRectLayer->scheduleUpdate();
			
		}
	}
}


void QtEdit::SlderChange(float Percentage)
{
	ui.PencentageSlider->setValue((int)(Percentage * 100));
}

void QtEdit::MySpriteChange()
{
	//由于窗口植入QT中有所变化，所以需要进行一个数值的等宽高缩放，
	_DrawRectLayer->sp->setPosition(Point(ui.Width->text().toDouble(), ui.Height->text().toDouble()));
	if (myVector != NULL)
	{
		myVector->_width = ui.Width->text().toDouble();
		myVector->_height = ui.Height->text().toDouble();
	}
	//if (ui.ScallX->text().toDouble() > 0.0)
	{
		_DrawRectLayer->sp->setScaleX(ui.ScallX->text().toDouble() );
		if (myVector != NULL)
		{
			myVector->_ScallX = ui.ScallX->text().toDouble();
		}
	}
	//if (ui.ScallY->text().toDouble() > 0.0)
	{
		_DrawRectLayer->sp->setScaleY(ui.ScallY->text().toDouble());
		if (myVector != NULL)
		{
			myVector->_ScallY = ui.ScallY->text().toDouble();
		}
	}
	if (btn != nullptr)
	{
		int i;
		for (i = 0; i < _DrawRectLayer->spritePoints.size(); i ++)
		{
			if (_DrawRectLayer->spritePoints.at(i)->Single_ID == btn->Singl_ID)
			{
				_DrawRectLayer->spritePoints.at(i)->_height = ui.Height->text().toDouble();
				_DrawRectLayer->spritePoints.at(i)->_width = ui.Width->text().toDouble();
				_DrawRectLayer->spritePoints.at(i)->_ScallX = ui.ScallX->text().toDouble();
				_DrawRectLayer->spritePoints.at(i)->_ScallY = ui.ScallY->text().toDouble();
				break;
			}
		}
	}
	AnimationSlderChange();
}

//进度条有点击
void QtEdit::AnimationSlderClick(int per)
{
	if (is_import)
	{
		//_DrawRectLayer->unscheduleUpdate();
		_DrawRectLayer->EndUpdate();
		ui.PauseButton->setText("Start");
		pu = -1;
	}
		
}
//进度条值变换了
void QtEdit::AnimationSlderChange()
{
	double a = ui.PencentageSlider->value();
	a *= 0.01;
	ui.PerWiget->setWindowTitle("PerCentage  " + QString::number((int) (a * 100)) + "%");
	if (is_import)
	{
		_DrawRectLayer->animate->updateOnPercentage(a);
	}
}
void QtEdit::yestButtonClick()
{
	auto _DrawRectLayer = DrawRectLayer::getInstence();
	//_DrawRectLayer->updatemydata(ui.lineEdit->text().toStdString());
}



//键盘操作
//Ctrl是否有按下
void QtEdit::keyPressEvent(QKeyEvent *e)
{
	if (e->key() == Qt::Key_Control)
	{
		Ctrl_Is_On = true;
	}
	if (e->key() == Qt::Key_Shift)
	{
		Shift_is_ON = true;
	}
	//if (Ctrl_Is_On == true && e->key() == Qt::Key_Z)
	//{
	//	if (is_import)
	//	{
	//		_DrawRectLayer->CtrlZ();
	//	}

	//}
	//if (Ctrl_Is_On == true && e->key() == Qt::Key_Y)
	//{
	//	if (is_import)
	//	{
	//		_DrawRectLayer->CtrlY();
	//	}

	//}
	//if (Ctrl_Is_On == true && e->key() == Qt::Key_D)
	//{
	//	if (is_import)
	//	{
	//		_DrawRectLayer->CtrlD();
	//	}
	//}
	if (Ctrl_Is_On == true && e->key() == Qt::Key_S)
	{
		if (is_import)
		{
			this->setWindowTitle(this->windowTitle().split("*").at(0));
			doSaveData(saveDataName , true);
		}
	}

}

void QtEdit::doSaveData(QString name , bool istobase)
{

	Json::Value root;
	Json::Value arrayObj;
	Json::Value item;
	Json::Value OnjectItem;
	Json::Value SItem;
	Json::Value _data;
	int i, j, k;
	int attsx, attsy, attex, attey;
	float attrotate;
	int injsx, injsy, injex, injey;
	float injrotate;
	int bodsx, bodsy, bodex, bodey;
	MyVector * _tempVector = new MyVector();
	if (myVector == NULL)
	{
		myVector = new MyVector();
		myVector->Singl_ID = 0;
		myVector->Sprites = _DrawRectLayer->spritePoints;
		spritesPoints.push_back(myVector);
	}
	for (i = 0; i < spritesPoints.size(); i++)
	{
		tempVector = spritesPoints.at(i);
		if (tempVector->Singl_ID == myVector->Singl_ID)
		{
			spritesPoints.at(i)->Sprites = _DrawRectLayer->spritePoints;
			break;
		}
	}
	QFile file(name);
	if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
	{
		QMessageBox::about(this, tr("information"), tr("Save Error"));
		return;
	}
	MySpritePoint * _tempSp;
	QTextStream out(&file);
	arrayObj.clear();
	_tempVector = nullptr;
	for (i = 0; i < spritesPoints.size(); i++)
	{
		_tempVector = spritesPoints.at(i);
		OnjectItem.clear();
		for (j = 0; j < _tempVector->Sprites.size(); j++)
		{
			attsx = -100.0;
			injex = -100.0;
			bodsx = -100.0;
			item.clear();
			_tempSp = _tempVector->Sprites.at(j);
			if (_tempSp->attackVertices != nullptr && _tempSp->Is_AttFra)
			{
				attsx = _tempSp->attackVertices[0].x;
				attsy = _tempSp->attackVertices[0].y;
				attex = _tempSp->attackVertices[2].x;
				attey = _tempSp->attackVertices[2].y;
			}
			attrotate = _tempSp->RotateAtt;

			if (_tempSp->injureVertices != nullptr && _tempSp->Is_InjFra)
			{
				injsx = _tempSp->injureVertices[0].x;
				injsy = _tempSp->injureVertices[0].y;
				injex = _tempSp->injureVertices[2].x;
				injey = _tempSp->injureVertices[2].y;
			}
			injrotate = _tempSp->RotateInj;

			if (_tempSp->bodyVertices != nullptr && _tempSp->Is_BodyFra)
			{
				bodsx = _tempSp->bodyVertices[0].x;
				bodsy = _tempSp->bodyVertices[0].y;
				bodex = _tempSp->bodyVertices[2].x;
				bodey = _tempSp->bodyVertices[2].y;
			}

			if (_tempSp->Is_ActFra)
			{
				SItem.clear();
				SItem["he"] = _tempSp->_height;
				SItem["wi"] = _tempSp->_width;
				SItem["scalx"] = _tempSp->_ScallX;
				SItem["scaly"] = _tempSp->_ScallY;
				item["act"] = SItem;
			}
			if (attsx > 0.0)
			{
				SItem.clear();
				SItem["sx"] = attsx;
				SItem["sy"] = attsy;
				SItem["ex"] = attex;
				SItem["ey"] = attey;
				SItem["ro"] = attrotate;
				item["att"] = SItem;
			}
			if (injex > 0.0)
			{
				SItem.clear();
				SItem["sx"] = injsx;
				SItem["sy"] = injsy;
				SItem["ex"] = injex;
				SItem["ey"] = injey;
				SItem["ro"] = injrotate;
				item["inj"] = SItem;
			}
			if (bodsx > 0.0)
			{
				SItem.clear();
				SItem["sx"] = bodsx;
				SItem["sy"] = bodsy;
				SItem["ex"] = bodex;
				SItem["ey"] = bodey;
				item["body"] = SItem;
			}
			item["fre"] = _tempSp->Single_ID;
			OnjectItem[j] = item;
		}
		//_data["data"] = OnjectItem;
		//_data["scx"] = _tempVector->_ScallX;
		//_data["scy"] = _tempVector->_ScallY;
		//_data["he"] = _tempVector->_height;
		//_data["wi"] = _tempVector->_width;
		//arrayObj[animation_list.at(i).split("/").at(1).split(".").at(0).toStdString()] = OnjectItem;
		arrayObj[animation_list.at(i).mid(animation_list.at(i).lastIndexOf("/") + 1).split(".").at(0).toStdString()] = OnjectItem;
	}
	root[_filename.toStdString()] = arrayObj;
	std::string outfile;
	outfile = root.toStyledString();
	file.resize(0);
	const char * str = outfile.c_str();
	if (istobase)
	{
		out << (QByteArray(str).toBase64());
	}
	else
	{
		out << str;
	}
	file.close();
}
void QtEdit::keyReleaseEvent(QKeyEvent *e)
{
	if (e->key() == Qt::Key_Control)
	{
		Ctrl_Is_On = false;
	}
	if (e->key() == Qt::Key_Shift)
	{
		Shift_is_ON = false;
	}
}

void QtEdit::AddAnimationList(QString full_path_name)
{
	
	QFileInfo fi;
	QString file_name, file_path;
	fi = QFileInfo(full_path_name);
	file_name = fi.fileName();
	file_path = fi.absolutePath(); 
	file_path = file_path + "/animations/";
	re_file_path = file_path;
	//判断路径是否存在
	QDir dir(file_path);
	if (!dir.exists(file_path))
	{
		QMessageBox::about(this, tr("information"), tr("No animations Fold"));
		return;
	}
	//获取所选文件类型过滤器
	QStringList filters;
	filters << QString("*.c3t") << QString("*.c3b");
	//定义迭代器并设置过滤器
	dir.setNameFilters(filters);//设置文件名称过滤器，只为filters格式（后缀为.c3B，c3t等格式）
	int dir_count = dir.count();
	if (dir_count <= 0)
	{
		return;
	}
	animation_list.clear();
	//获取分隔符
	//只写结点的实现
	QList<QTreeWidgetItem *> rootList;
	//先把之前的清除了
	ui.AnimationtreeWidget->clear();
	QTreeWidgetItem *imageItem1 = new QTreeWidgetItem;   //添加第一个父节点
	imageItem1->setText(0, file_name.split(".").at(0));
	rootList.append(imageItem1);

	QTreeWidgetItem *imageItem1_1;
	int i, j;
	QString name, path;
	QString temp;
	int list_size = 0;
	bool is_in_list;
	for (i = 0; i < dir_count ; i ++)
	{
		name = dir[i];  //文件名称
		path = re_file_path + name;   //文件路径
		
		list_size = animation_list.size();
		//查找是否有同名文件
		is_in_list = false;
		for (j = 0; j < list_size; j ++)
		{
			temp = animation_list.at(j).split(".").at(0);//获取到文件名称，无后缀
			//存在同名
			if (path.split(".").at(0) == temp)
			{
				is_in_list = true;
			}
		}
		if (!is_in_list)
		{
			animation_list.append(path);
			ShowMsg("Import animations/" + name.toStdString());
			imageItem1_1 = new QTreeWidgetItem(imageItem1, QStringList(QString(path))); //添加子节点
			imageItem1->addChild(imageItem1_1);
		}
	}
	_mycol = 0;
	ui.AnimationtreeWidget->insertTopLevelItems(0, rootList);  //将结点插入部件中

	ui.AnimationtreeWidget->expandAll(); //全部展开
}



//Tree点击事件
void QtEdit::AnimationTreeWidgetClick(QTreeWidgetItem * item, int column)
{
	int last_rol = -1;
	last_rol = _DrawRectLayer->animation->getDuration() * oneFPX;
	last_rol++;
	QTreeWidgetItem *parent = item->parent();
	if (NULL == parent || !is_import) //注意：最顶端项是没有父节点的，双击这些项时注意(陷阱)
		return;
	int col = parent->indexOfChild(item); //item在父项中的节点行号(从0开始)
	_mycol = col;
	char s[100];
	int i;
	bool Is_Has = false;
	if (myVector == NULL)
	{
		myVector = new MyVector();
		myVector->Singl_ID = 0;
		myVector->Sprites = _DrawRectLayer->spritePoints;
		spritesPoints.push_back(myVector);
	}
	for (i = 0; i < spritesPoints.size(); i ++)
	{
		tempVector = spritesPoints.at(i);
		if (tempVector->Singl_ID == myVector->Singl_ID)
		{
			spritesPoints.at(i)->Sprites = _DrawRectLayer->spritePoints;
			break;
		}
	}
	for (i = 0; i < spritesPoints.size(); i ++)
	{
		myVector = spritesPoints.at(i);
		if (myVector->Singl_ID == col)
		{
			Is_Has = true;
			_DrawRectLayer->spritePoints.clear();
			_DrawRectLayer->spritePoints = myVector->Sprites;
			break;
		}
	}
	if (!Is_Has)
	{
		_DrawRectLayer->spritePoints.clear();
		myVector = new MyVector();
		myVector->Singl_ID = col;
		spritesPoints.push_back(myVector);
	}

	std::sprintf(s, "%s %d", "CL_", col);
	ShowMsg("animations/" + animation_list.at(col).split("animations/").at(1).toStdString());
	_DrawRectLayer->sp->stopAllActions();
	_DrawRectLayer->animation = Animation3D::getOrCreate(animation_list.at(col).toStdString());
	if (_DrawRectLayer->animation != NULL)
	{
		_DrawRectLayer->animate = Animate3D::create(_DrawRectLayer->animation);
		_DrawRectLayer->animate->is_auto_update = false;
		_DrawRectLayer->_RepeatForever = RepeatForever::create(_DrawRectLayer->animate);
		_DrawRectLayer->sp->runAction(_DrawRectLayer->_RepeatForever);
	}
	ui.dockWidget->setWindowTitle(animation_list.at(col));
	setSlideEndFPX(_DrawRectLayer->animation->getDuration() * oneFPX);
	//AddSliderButton();
	btn = sliderButton.at(0);
	btn->Is_Click = true;
	btn->setPalette(QPalette(Qt::green));
	btn->setAutoFillBackground(true);
	showline = sliderFameshow.at((btn->Singl_ID));
	showline->setVisible(true);
	_lastButton = btn;
	SlderAnimationAction();
	SetMyUI();
	setMyFrame(-1, -1, false, last_rol);
}


void QtEdit::setSlideEndFPX(int end)
{
	int i;
	//for (i = 0; i <= FPX; i++)
	//{
	//	try
	//	{
	//		_endButton = sliderButton.at(i);
	//		//_endButton->setAutoFillBackground(true);
	//		_endButton->setStyleSheet("background:transparent");
	//		_endButton->Is_Click = false;
	//	}
	//	catch (...)
	//	{

	//	}
	//}
	if (btn)
	{
		btn->setAutoFillBackground(true);
		btn->Is_Click = false;
		btn->setStyleSheet("background:transparent");
	}
	if (_lastButton)
	{
		_lastButton->setAutoFillBackground(true);
		_lastButton->Is_Click = false;
		_lastButton->setStyleSheet("background:transparent");
	}
	if (FPX >= 0)
	{
		sliderButton.at(FPX)->setAutoFillBackground(true);
		sliderButton.at(FPX)->setStyleSheet("background:transparent");
		sliderButton.at(FPX)->Is_Click = false;
	}
	if (-1 != FPX)
	{
		showline = sliderFameshow.at((_endButton->Singl_ID));
		showline->setVisible(false);
	}
	
	FPX = end + 1;
	_endButton = sliderButton.at(FPX);
	_endButton->setPalette(QPalette(Qt::red));
	_endButton->setAutoFillBackground(true);
	showline = sliderFameshow.at((_endButton->Singl_ID));
	showline->setVisible(true);
}

void QtEdit::mousePressEvent(QMouseEvent *e)
{
	//stPoint = e->pos();
	if (is_import)
	{
		if (e->button() == Qt::RightButton)
		{
			stPoint.setX(e->pos().x() - ui.SceneWidget->pos().x());
			stPoint.setY(ui.SceneWidget->height() - (e->pos().y() - ui.SceneWidget->pos().y()) - (ui.SceneWidget->height() - 640) / 4);
			bool Att_Is_In, Inj_is_In;
			_DrawRectLayer->attackNode->setRelativeVertices(_DrawRectLayer->attackNode->Vertices, Vec2(_QtEdit->ui.Width->text().toFloat(), _QtEdit->ui.Height->text().toFloat()));
			_DrawRectLayer->injuredNode->setRelativeVertices(_DrawRectLayer->injuredNode->Vertices, Vec2(_QtEdit->ui.Width->text().toFloat(), _QtEdit->ui.Height->text().toFloat()));
			//_DrawRectLayer->showMsg("AttFirX=", NULL, _DrawRectLayer->attackNode->Relativevertices[0].x);
			//_DrawRectLayer->showMsg("InjFirX=", NULL, _DrawRectLayer->injuredNode->Relativevertices[0].x);
			Att_Is_In = Is_Point_Into(stPoint, QPoint(_DrawRectLayer->attackNode->Relativevertices[0].x, _DrawRectLayer->attackNode->Relativevertices[0].y), QPoint(_DrawRectLayer->attackNode->Relativevertices[2].x, _DrawRectLayer->attackNode->Relativevertices[2].y));
			Inj_is_In = Is_Point_Into(stPoint, QPoint(_DrawRectLayer->injuredNode->Relativevertices[0].x, _DrawRectLayer->injuredNode->Relativevertices[0].y), QPoint(_DrawRectLayer->injuredNode->Relativevertices[2].x, _DrawRectLayer->injuredNode->Relativevertices[2].y));
			if (Att_Is_In)
			{
				attstPoint = stPoint;
			}
			else
			{
				attstPoint.setX(0);
				attstPoint.setY(0);
			}
			if (Inj_is_In)
			{
				injstPoint = stPoint;
			}
			else
			{
				injstPoint.setX(0);
				injstPoint.setY(0);
			}
		}
		//if (Shift_is_ON == true)
		//{
		//	if (e->button() == Qt::RightButton)
		//	{
		//		deleteAtt = Is_Point_Into(stPoint, QPoint(_DrawRectLayer->attackNode->vertices[0].x, _DrawRectLayer->attackNode->vertices[0].y), QPoint(_DrawRectLayer->attackNode->vertices[2].x, _DrawRectLayer->attackNode->vertices[2].y));
		//		deleteInj = Is_Point_Into(stPoint, QPoint(_DrawRectLayer->injuredNode->vertices[0].x, _DrawRectLayer->injuredNode->vertices[0].y), QPoint(_DrawRectLayer->injuredNode->vertices[2].x, _DrawRectLayer->injuredNode->vertices[2].y));
		//		if (!deleteAtt && !deleteInj)
		//		{
		//			return;
		//		}
		//		QMenu *popMenu = new QMenu(this);
		//		//popMenu->addAction(new QAction(tr("add"), this));
		//		QAction *myAction = new QAction(this);
		//		myAction->setObjectName(QStringLiteral("mydeleteAction"));
		//		myAction->setText("delete");
		//		QObject::connect(myAction, SIGNAL(triggered()), this, SLOT(deleteDrawnode()));
		//		popMenu->addAction(myAction);
		//		popMenu->setStyleSheet("QMenu{background-color:rgb(255,255,255);color:rgb(0, 0, 0);font:10pt ""宋体"";}"
		//			"QMenu::item:selected{background-color:#CCDAE7;}");
		//		popMenu->exec(QCursor::pos());
		//	}
		//}
	}
}

void QtEdit::deleteDrawnode()
{
	_QtEdit->setWindowTitle(_QtEdit->windowTitle().split("*").at(0) + "*");
	int i;
	if (deleteAtt)
	{
		for (i = 0; i < _DrawRectLayer->spritePoints.size(); i++)
		{
			MySpritePoint * _tempSpritePoint = _DrawRectLayer->spritePoints.at(i);
			if (_tempSpritePoint->Single_ID == _DrawRectLayer->Single_ID)
			{
				_DrawRectLayer->spritePoints.at(i)->attackVertices = nullptr;
				_DrawRectLayer->spritePoints.at(i)->RotateAtt = 0;
				_DrawRectLayer->removeChild(_DrawRectLayer->attackNode->drawnode);
				sliderButton.at(btn->Singl_ID)->Is_AttFra = false;
				sliderButton.at(btn->Singl_ID)->deleteAction(false);
				_DrawRectLayer->attackNode = new MyDrawNode();
				if (_DrawRectLayer->spritePoints.at(i)->injureVertices == nullptr && !sliderButton.at(btn->Singl_ID)->Is_ActFra)
				{
					_DrawRectLayer->spritePoints.erase(_DrawRectLayer->spritePoints.begin() + i);
					sliderButton.at(btn->Singl_ID)->Is_AttFra = false;
					sliderButton.at(btn->Singl_ID)->deleteAction(true);
				}
				break;
			}
		}
	}
	else
	{
		for (i = 0; i < _DrawRectLayer->spritePoints.size(); i++)
		{
			MySpritePoint * _tempSpritePoint = _DrawRectLayer->spritePoints.at(i);
			if (_tempSpritePoint->Single_ID == _DrawRectLayer->Single_ID)
			{
				_DrawRectLayer->spritePoints.at(i)->injureVertices = nullptr;
				_DrawRectLayer->spritePoints.at(i)->RotateInj = 0;
				sliderButton.at(btn->Singl_ID)->Is_InjFra = false;
				_DrawRectLayer->removeChild(_DrawRectLayer->injuredNode->drawnode);
				sliderButton.at(btn->Singl_ID)->Is_InjFra = false;
				sliderButton.at(btn->Singl_ID)->deleteAction(false);
				_DrawRectLayer->injuredNode = new MyDrawNode();
				if (_DrawRectLayer->spritePoints.at(i)->attackVertices == nullptr && !sliderButton.at(btn->Singl_ID)->Is_ActFra)
				{
					_DrawRectLayer->spritePoints.erase(_DrawRectLayer->spritePoints.begin() + i);
					sliderButton.at(btn->Singl_ID)->Is_InjFra = false;
					sliderButton.at(btn->Singl_ID)->deleteAction(true);
				}
				break;
			}
		}
	}
}

void QtEdit::mouseReleaseEvent(QMouseEvent *e)
{
	if (is_import)
	{
		if (e->button() == Qt::RightButton && CheckIsFrame())
		{
			enPoint.setX(e->pos().x() - ui.SceneWidget->pos().x());
			enPoint.setY(ui.SceneWidget->height() - (e->pos().y() - ui.SceneWidget->pos().y()) - (ui.SceneWidget->height() - 640) / 4);
			bool Att_Is_In, Inj_is_In;
			_DrawRectLayer->attackNode->setRelativeVertices(_DrawRectLayer->attackNode->Vertices, Vec2(_QtEdit->ui.Width->text().toFloat(), _QtEdit->ui.Height->text().toFloat()));
			_DrawRectLayer->injuredNode->setRelativeVertices(_DrawRectLayer->injuredNode->Vertices, Vec2(_QtEdit->ui.Width->text().toFloat(), _QtEdit->ui.Height->text().toFloat()));
			//_DrawRectLayer->showMsg("AttEndX=", NULL, _DrawRectLayer->attackNode->Relativevertices[0].x);
			//_DrawRectLayer->showMsg("InjEndX=", NULL, _DrawRectLayer->injuredNode->Relativevertices[0].x);
			Att_Is_In = Is_Point_Into(enPoint, QPoint(_DrawRectLayer->attackNode->Relativevertices[0].x, _DrawRectLayer->attackNode->Relativevertices[0].y), QPoint(_DrawRectLayer->attackNode->Relativevertices[2].x, _DrawRectLayer->attackNode->Relativevertices[2].y));
			Inj_is_In = Is_Point_Into(enPoint, QPoint(_DrawRectLayer->injuredNode->Relativevertices[0].x, _DrawRectLayer->injuredNode->Relativevertices[0].y), QPoint(_DrawRectLayer->injuredNode->Relativevertices[2].x, _DrawRectLayer->injuredNode->Relativevertices[2].y));
			MyDrawNode *_tempDraw;
			bool Is_Update = false;
			float rotate, i;
			if (Ctrl_Is_On && Att_Is_In && attstPoint.x() != 0 && attstPoint.y() != 0 && sliderButton.at(btn->Singl_ID)->Is_AttFra)
			{
				rotate = _DrawRectLayer->attackNode->getRotate(Vec2(attstPoint.x(), attstPoint.y()), Vec2(enPoint.x(), enPoint.y()), Vec2((_DrawRectLayer->injuredNode->Relativevertices[0].x + _DrawRectLayer->injuredNode->Relativevertices[2].x) / 2, (_DrawRectLayer->injuredNode->Relativevertices[0].y + _DrawRectLayer->injuredNode->Relativevertices[2].y) / 2));
				if (attstPoint.y() > enPoint.y())
				{
					_DrawRectLayer->attackNode->Rotate = rotate;

				}
				else
				{
					_DrawRectLayer->attackNode->Rotate = rotate;

				}
				_DrawRectLayer->attackNode->setRotateVertices(_DrawRectLayer->attackNode->Vertices[0], _DrawRectLayer->attackNode->Vertices[2], rotate);
				_tempDraw = new MyDrawNode();
				_tempDraw->Rotate = _DrawRectLayer->attackNode->Rotate;
				_tempDraw->RotateVertices = _DrawRectLayer->attackNode->RotateVertices;
				_tempDraw->Singl_ID = _DrawRectLayer->attackNode->Singl_ID;
				_tempDraw->Vertices = _DrawRectLayer->attackNode->Vertices;
				_tempDraw->is_visible = _DrawRectLayer->attackNode->is_visible;
				_DrawRectLayer->removeChild(_DrawRectLayer->attackNode->drawnode);
				_DrawRectLayer->attackNode = _tempDraw;
				_DrawRectLayer->removeChild(_DrawRectLayer->injuredNode->drawnode);
				_tempDraw = new MyDrawNode();
				_tempDraw->Rotate = _DrawRectLayer->injuredNode->Rotate;
				_tempDraw->RotateVertices = _DrawRectLayer->injuredNode->RotateVertices;
				_tempDraw->Singl_ID = _DrawRectLayer->injuredNode->Singl_ID;
				_tempDraw->Vertices = _DrawRectLayer->injuredNode->Vertices;
				_tempDraw->is_visible = _DrawRectLayer->injuredNode->is_visible;
				_DrawRectLayer->injuredNode = _tempDraw;

				_DrawRectLayer->removeChild(_DrawRectLayer->bodyNode->drawnode);
				_tempDraw = new MyDrawNode();
				//_tempDraw->Rotate = _DrawRectLayer->injuredNode->Rotate;
				//_tempDraw->RotateVertices = _DrawRectLayer->bodyNode->RotateVertices;
				_tempDraw->Singl_ID = _DrawRectLayer->bodyNode->Singl_ID;
				_tempDraw->Vertices = _DrawRectLayer->bodyNode->Vertices;
				//_tempDraw->is_visible = _DrawRectLayer->bodyNode->is_visible;
				_DrawRectLayer->bodyNode = _tempDraw;
				Is_Update = true;
				for (i = 0; i < _DrawRectLayer->spritePoints.size(); i++)
				{
					MySpritePoint * _tempSpritePoint = _DrawRectLayer->spritePoints.at(i);
					if (_tempSpritePoint->Single_ID == _DrawRectLayer->Single_ID)
					{
						_DrawRectLayer->spritePoints.at(i)->RotateAtt = _DrawRectLayer->attackNode->Rotate;
						break;
					}
				}
			}
			else if (Inj_is_In && injstPoint.x() != 0 && injstPoint.y() != 0 && !Ctrl_Is_On && sliderButton.at(btn->Singl_ID)->Is_InjFra)
			{
				rotate = _DrawRectLayer->injuredNode->getRotate(Vec2(injstPoint.x(), injstPoint.y()), Vec2(enPoint.x(), enPoint.y()), Vec2((_DrawRectLayer->injuredNode->Relativevertices[0].x + _DrawRectLayer->injuredNode->Relativevertices[2].x) / 2, (_DrawRectLayer->injuredNode->Relativevertices[0].y + _DrawRectLayer->injuredNode->Relativevertices[2].y) / 2));
				//log("B = %f", sin(rotate));
				if (injstPoint.y() > enPoint.y())
				{
					_DrawRectLayer->injuredNode->Rotate = rotate;
					
				}
				else
				{
					_DrawRectLayer->injuredNode->Rotate = rotate;
					
				}	
				_DrawRectLayer->injuredNode->setRotateVertices(_DrawRectLayer->injuredNode->Vertices[0], _DrawRectLayer->injuredNode->Vertices[2], rotate);
				_tempDraw = new MyDrawNode();
				_tempDraw->Rotate = _DrawRectLayer->attackNode->Rotate;
				_tempDraw->RotateVertices = _DrawRectLayer->attackNode->RotateVertices;
				_tempDraw->Singl_ID = _DrawRectLayer->attackNode->Singl_ID;
				_tempDraw->Vertices = _DrawRectLayer->attackNode->Vertices;
				_tempDraw->is_visible = _DrawRectLayer->attackNode->is_visible;
				_DrawRectLayer->removeChild(_DrawRectLayer->attackNode->drawnode);
				_DrawRectLayer->attackNode = _tempDraw;
				_DrawRectLayer->removeChild(_DrawRectLayer->injuredNode->drawnode);
				_tempDraw = new MyDrawNode();
				_tempDraw->Rotate = _DrawRectLayer->injuredNode->Rotate;
				_tempDraw->RotateVertices = _DrawRectLayer->injuredNode->RotateVertices;
				_tempDraw->Singl_ID = _DrawRectLayer->injuredNode->Singl_ID;
				_tempDraw->Vertices = _DrawRectLayer->injuredNode->Vertices;
				_tempDraw->is_visible = _DrawRectLayer->injuredNode->is_visible;
				_DrawRectLayer->injuredNode = _tempDraw;

				_DrawRectLayer->removeChild(_DrawRectLayer->bodyNode->drawnode);
				_tempDraw = new MyDrawNode();
				//_tempDraw->Rotate = _DrawRectLayer->bodyNode->Rotate;
				//_tempDraw->RotateVertices = _DrawRectLayer->injuredNode->RotateVertices;
				_tempDraw->Singl_ID = _DrawRectLayer->bodyNode->Singl_ID;
				_tempDraw->Vertices = _DrawRectLayer->bodyNode->Vertices;
				//_tempDraw->is_visible = _DrawRectLayer->bodyNode->is_visible;
				_DrawRectLayer->bodyNode = _tempDraw;
				for (i = 0; i < _DrawRectLayer->spritePoints.size(); i++)
				{
					MySpritePoint * _tempSpritePoint = _DrawRectLayer->spritePoints.at(i);
					if (_tempSpritePoint->Single_ID == _DrawRectLayer->Single_ID)
					{
						_DrawRectLayer->spritePoints.at(i)->RotateInj = _DrawRectLayer->injuredNode->Rotate;
						break;
					}
				}
				Is_Update = true;
			}
			if (Is_Update)
			{
				_QtEdit->setWindowTitle(_QtEdit->windowTitle().split("*").at(0) + "*");
				_DrawRectLayer->doDraw();
			}
		}
	}
}
bool QtEdit::CheckIsFrame()
{
	return sliderButton.at(btn->Singl_ID)->Is_AttFra || sliderButton.at(btn->Singl_ID)->Is_InjFra;
}

void QtEdit::mouseMoveEvent(QMouseEvent *e)
{
	if (is_import)
	{
		if ((e->buttons() & Qt::RightButton) && CheckIsFrame())
		{
			enPoint.setX(e->pos().x() - ui.SceneWidget->pos().x());
			enPoint.setY(ui.SceneWidget->height() - (e->pos().y() - ui.SceneWidget->pos().y()) - (ui.SceneWidget->height() - 640) / 4);
			bool Att_Is_In, Inj_is_In;
			_DrawRectLayer->attackNode->setRelativeVertices(_DrawRectLayer->attackNode->Vertices, Vec2(_QtEdit->ui.Width->text().toFloat(), _QtEdit->ui.Height->text().toFloat()));
			_DrawRectLayer->injuredNode->setRelativeVertices(_DrawRectLayer->injuredNode->Vertices, Vec2(_QtEdit->ui.Width->text().toFloat(), _QtEdit->ui.Height->text().toFloat()));
			//_DrawRectLayer->showMsg("AttMoveX=", NULL, _DrawRectLayer->attackNode->Relativevertices[0].x);
			//_DrawRectLayer->showMsg("InjMoveX=", NULL, _DrawRectLayer->injuredNode->Relativevertices[0].x);
			Att_Is_In = Is_Point_Into(enPoint, QPoint(_DrawRectLayer->attackNode->Relativevertices[0].x, _DrawRectLayer->attackNode->Relativevertices[0].y), QPoint(_DrawRectLayer->attackNode->Relativevertices[2].x, _DrawRectLayer->attackNode->Relativevertices[2].y));
			Inj_is_In = Is_Point_Into(enPoint, QPoint(_DrawRectLayer->injuredNode->Relativevertices[0].x, _DrawRectLayer->injuredNode->Relativevertices[0].y), QPoint(_DrawRectLayer->injuredNode->Relativevertices[2].x, _DrawRectLayer->injuredNode->Relativevertices[2].y));
			MyDrawNode *_tempDraw;
			bool Is_Update = false;
			float rotate, i;
			if (Ctrl_Is_On && Att_Is_In && attstPoint.x() != 0 && attstPoint.y() != 0 && sliderButton.at(btn->Singl_ID)->Is_AttFra)
			{
				rotate = _DrawRectLayer->attackNode->getRotate(Vec2(attstPoint.x(), attstPoint.y()), Vec2(enPoint.x(), enPoint.y()), Vec2((_DrawRectLayer->injuredNode->Relativevertices[0].x + _DrawRectLayer->injuredNode->Relativevertices[2].x) / 2, (_DrawRectLayer->injuredNode->Relativevertices[0].y + _DrawRectLayer->injuredNode->Relativevertices[2].y) / 2));
				//rotate = rotate / (180 / M_PI);
				if (attstPoint.y() > enPoint.y())
				{
					_DrawRectLayer->attackNode->Rotate = rotate;

				}
				else
				{
					_DrawRectLayer->attackNode->Rotate = rotate;

				}
				_DrawRectLayer->attackNode->setRotateVertices(_DrawRectLayer->attackNode->Vertices[0], _DrawRectLayer->attackNode->Vertices[2], rotate);
				_tempDraw = new MyDrawNode();
				_tempDraw->Rotate = _DrawRectLayer->attackNode->Rotate;
				_tempDraw->RotateVertices = _DrawRectLayer->attackNode->RotateVertices;
				_tempDraw->Singl_ID = _DrawRectLayer->attackNode->Singl_ID;
				_tempDraw->Vertices = _DrawRectLayer->attackNode->Vertices;
				_tempDraw->is_visible = _DrawRectLayer->attackNode->is_visible;
				_DrawRectLayer->removeChild(_DrawRectLayer->attackNode->drawnode);
				_DrawRectLayer->attackNode = _tempDraw;
				_DrawRectLayer->removeChild(_DrawRectLayer->injuredNode->drawnode);
				_tempDraw = new MyDrawNode();
				_tempDraw->Rotate = _DrawRectLayer->injuredNode->Rotate;
				_tempDraw->RotateVertices = _DrawRectLayer->injuredNode->RotateVertices;
				_tempDraw->Singl_ID = _DrawRectLayer->injuredNode->Singl_ID;
				_tempDraw->Vertices = _DrawRectLayer->injuredNode->Vertices;
				_tempDraw->is_visible = _DrawRectLayer->injuredNode->is_visible;
				_DrawRectLayer->injuredNode = _tempDraw;


				_DrawRectLayer->removeChild(_DrawRectLayer->bodyNode->drawnode);
				_tempDraw = new MyDrawNode();
				//_tempDraw->Rotate = _DrawRectLayer->bodyNode->Rotate;
				//_tempDraw->RotateVertices = _DrawRectLayer->injuredNode->RotateVertices;
				_tempDraw->Singl_ID = _DrawRectLayer->bodyNode->Singl_ID;
				_tempDraw->Vertices = _DrawRectLayer->bodyNode->Vertices;
				//_tempDraw->is_visible = _DrawRectLayer->bodyNode->is_visible;
				_DrawRectLayer->bodyNode = _tempDraw;

				Is_Update = true;
				for (i = 0; i < _DrawRectLayer->spritePoints.size(); i++)
				{
					MySpritePoint * _tempSpritePoint = _DrawRectLayer->spritePoints.at(i);
					if (_tempSpritePoint->Single_ID == _DrawRectLayer->Single_ID)
					{
						_DrawRectLayer->spritePoints.at(i)->RotateAtt = _DrawRectLayer->attackNode->Rotate;
						break;
					}
				}
			}
			else if (Inj_is_In && injstPoint.x() != 0 && injstPoint.y() != 0 && !Ctrl_Is_On && sliderButton.at(btn->Singl_ID)->Is_InjFra)
			{
				rotate = _DrawRectLayer->injuredNode->getRotate(Vec2(injstPoint.x(), injstPoint.y()), Vec2(enPoint.x(), enPoint.y()), Vec2((_DrawRectLayer->injuredNode->Relativevertices[0].x + _DrawRectLayer->injuredNode->Relativevertices[2].x) / 2, (_DrawRectLayer->injuredNode->Relativevertices[0].y + _DrawRectLayer->injuredNode->Relativevertices[2].y) / 2));
				//_DrawRectLayer->showMsg("QT", injstPoint.x(), enPoint.x());
				//log("B = %f", sin(rotate));
				//rotate = rotate / (180 / M_PI);
				if (injstPoint.y() > enPoint.y())
				{
					_DrawRectLayer->injuredNode->Rotate = rotate;
					
				}
				else
				{
					_DrawRectLayer->injuredNode->Rotate = rotate;
					
				}	
				_DrawRectLayer->injuredNode->setRotateVertices(_DrawRectLayer->injuredNode->Vertices[0], _DrawRectLayer->injuredNode->Vertices[2], rotate);
				_tempDraw = new MyDrawNode();
				_tempDraw->Rotate = _DrawRectLayer->attackNode->Rotate;
				_tempDraw->RotateVertices = _DrawRectLayer->attackNode->RotateVertices;
				_tempDraw->Singl_ID = _DrawRectLayer->attackNode->Singl_ID;
				_tempDraw->Vertices = _DrawRectLayer->attackNode->Vertices;
				_tempDraw->is_visible = _DrawRectLayer->attackNode->is_visible;
				_DrawRectLayer->removeChild(_DrawRectLayer->attackNode->drawnode);
				_DrawRectLayer->attackNode = _tempDraw;
				_DrawRectLayer->removeChild(_DrawRectLayer->injuredNode->drawnode);
				_tempDraw = new MyDrawNode();
				_tempDraw->Rotate = _DrawRectLayer->injuredNode->Rotate;
				_tempDraw->RotateVertices = _DrawRectLayer->injuredNode->RotateVertices;
				_tempDraw->Singl_ID = _DrawRectLayer->injuredNode->Singl_ID;
				_tempDraw->Vertices = _DrawRectLayer->injuredNode->Vertices;
				_tempDraw->is_visible = _DrawRectLayer->injuredNode->is_visible;
				_DrawRectLayer->injuredNode = _tempDraw;


				_DrawRectLayer->removeChild(_DrawRectLayer->bodyNode->drawnode);
				_tempDraw = new MyDrawNode();
				//_tempDraw->Rotate = _DrawRectLayer->bodyNode->Rotate;
				//_tempDraw->RotateVertices = _DrawRectLayer->injuredNode->RotateVertices;
				_tempDraw->Singl_ID = _DrawRectLayer->bodyNode->Singl_ID;
				_tempDraw->Vertices = _DrawRectLayer->bodyNode->Vertices;
				//_tempDraw->is_visible = _DrawRectLayer->bodyNode->is_visible;
				_DrawRectLayer->bodyNode = _tempDraw;

				for (i = 0; i < _DrawRectLayer->spritePoints.size(); i++)
				{
					MySpritePoint * _tempSpritePoint = _DrawRectLayer->spritePoints.at(i);
					if (_tempSpritePoint->Single_ID == _DrawRectLayer->Single_ID)
					{
						_DrawRectLayer->spritePoints.at(i)->RotateInj = _DrawRectLayer->injuredNode->Rotate;
						break;
					}
				}
				Is_Update = true;
			}
			if (Is_Update)
			{
				_QtEdit->setWindowTitle(_QtEdit->windowTitle().split("*").at(0) + "*");
				_DrawRectLayer->doDraw();
			}
		}
	}
}
bool  QtEdit::Is_Point_Into(QPoint po, QPoint st , QPoint en)
{
	if (po.x() < st.x() && po.x() < en.x())
	{
		return false;
	}
	if (po.x() > st.x() && po.x() > en.x())
	{
		return false;
	}
	if (po.y() < st.y() && po.y() < en.y())
	{
		return false;
	}
	if (po.y() > st.y() && po.y() > en.y())
	{
		return false;
	}
	return true;
}

//关键帧的标识
void QtEdit::setMyFrame(int rol,int posi, bool dele , int last_rol)
{
	int i;
	if (rol == -1)
	{
		int r = last_rol == -1 ? sliderButton.size() : last_rol;
		for (i = 0; i < r; i++)
		{
			try
			{
				//sliderButton.at(i)->_AttFraButton->setAutoFillBackground(true);
				sliderButton.at(i)->_AttFraButton->setStyleSheet("background:transparent");
				sliderButton.at(i)->Is_AttFra = false;

				//sliderButton.at(i)->_InjFraButton->setAutoFillBackground(true;)
				sliderButton.at(i)->_InjFraButton->setStyleSheet("background:transparent");
				sliderButton.at(i)->Is_InjFra = false;

				//sliderButton.at(i)->_ActFraButton->setAutoFillBackground(true);
				sliderButton.at(i)->_ActFraButton->setStyleSheet("background:transparent");
				sliderButton.at(i)->Is_ActFra = false;

				sliderButton.at(i)->_BodyFraButton->setStyleSheet("background:transparent");
				sliderButton.at(i)->Is_BodyFra = false;
			}
			catch (...)
			{
				
			}
		}
		for (i = 0; i < _DrawRectLayer->spritePoints.size(); i++)
		{
			if (_DrawRectLayer->spritePoints.at(i)->Is_ActFra)
			{
				sliderButton.at(_DrawRectLayer->spritePoints.at(i)->Single_ID)->_ActFraButton->setAutoFillBackground(true);
				sliderButton.at(_DrawRectLayer->spritePoints.at(i)->Single_ID)->_ActFraButton->setPalette(QPalette(Qt::blue));
				sliderButton.at(_DrawRectLayer->spritePoints.at(i)->Single_ID)->Is_ActFra = true;
			}
			if (_DrawRectLayer->spritePoints.at(i)->Is_AttFra)
			{
				sliderButton.at(_DrawRectLayer->spritePoints.at(i)->Single_ID)->_AttFraButton->setAutoFillBackground(true);
				sliderButton.at(_DrawRectLayer->spritePoints.at(i)->Single_ID)->_AttFraButton->setPalette(QPalette(Qt::red));
				sliderButton.at(_DrawRectLayer->spritePoints.at(i)->Single_ID)->Is_AttFra = true;
			}
			if (_DrawRectLayer->spritePoints.at(i)->Is_InjFra)
			{
				sliderButton.at(_DrawRectLayer->spritePoints.at(i)->Single_ID)->_InjFraButton->setAutoFillBackground(true);
				sliderButton.at(_DrawRectLayer->spritePoints.at(i)->Single_ID)->_InjFraButton->setPalette(QPalette(Qt::yellow));
				sliderButton.at(_DrawRectLayer->spritePoints.at(i)->Single_ID)->Is_InjFra = true;
			}
			if (_DrawRectLayer->spritePoints.at(i)->Is_BodyFra)
			{
				sliderButton.at(_DrawRectLayer->spritePoints.at(i)->Single_ID)->_BodyFraButton->setAutoFillBackground(true);
				sliderButton.at(_DrawRectLayer->spritePoints.at(i)->Single_ID)->_BodyFraButton->setPalette(QPalette(Qt::green));
				sliderButton.at(_DrawRectLayer->spritePoints.at(i)->Single_ID)->Is_BodyFra = true;
			}
			
		}
		return;
	}
	if (!dele)
	{
		if (posi == 1)
		{
			sliderButton.at(rol)->_AttFraButton->setPalette(QPalette(Qt::red));
			sliderButton.at(rol)->_AttFraButton->setAutoFillBackground(true);
			sliderButton.at(rol)->Is_AttFra = true;
		}
		else if (posi == 2)
		{
			sliderButton.at(rol)->_InjFraButton->setPalette(QPalette(Qt::yellow));
			sliderButton.at(rol)->_InjFraButton->setAutoFillBackground(true);
			sliderButton.at(rol)->Is_InjFra = true;
		}
		else if (posi == 3)
		{
			sliderButton.at(rol)->_ActFraButton->setPalette(QPalette(Qt::blue));
			sliderButton.at(rol)->_ActFraButton->setAutoFillBackground(true);
			sliderButton.at(rol)->Is_ActFra = true;
		}
		else if (posi == 4)
		{
			sliderButton.at(rol)->_BodyFraButton->setPalette(QPalette(Qt::green));
			sliderButton.at(rol)->_BodyFraButton->setAutoFillBackground(true);
			sliderButton.at(rol)->Is_BodyFra = true;
		}

		return;
	}
	//if (dele)
	//{
	//	sliderButton.at(rol)->_AttFraButton->setStyleSheet("background:transparent");
	//	sliderButton.at(rol)->Is_AttFra = false;
	//}
	
}

void QtEdit::setParent(HWND parent)
{
	m_Parent = parent;
}
void QtEdit::SetFraDe(MySpritePoint * _temp_sprite_point)
{
	ui.Height->setText(QString("%1").arg(_temp_sprite_point->_height));
	ui.Width->setText(QString("%1").arg(_temp_sprite_point->_width));
	ui.ScallX->setText(QString("%1").arg(_temp_sprite_point->_ScallX));
	ui.ScallY->setText(QString("%1").arg(_temp_sprite_point->_ScallY));
	//ChangeInput();
	MySpriteChange();
}