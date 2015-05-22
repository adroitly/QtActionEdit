#include "qtedit.h"
#include <QtWidgets/QApplication>

#include "Classes/AppDelegate.h"
#include "Classes/CocosQtPort/CCQGLView.h"
#include "cocos2d.h"
//#define M_PI        3.14159265358979323846;
//#define M_FU		57.3;
USING_NS_CC;
#if _MSC_VER >= 1600  
#pragma execution_character_set("utf-8")  
#endif  
int main(int argc, char *argv[])
{
	//QApplication a(argc, argv);
	//QtEdit w;
	//w.show();
	//return a.exec();
	AppDelegate app(argc, argv);
	return cocos2d::CCQApplication::getInstance()->run();
}
