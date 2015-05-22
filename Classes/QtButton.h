#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_qtedit.h"
#include "DrawRectLayer.h"
#include "qpushbutton.h"
#include "QTableWidget.h"
#include "qframe.h"
#include "QScrollArea.h"
#include "MyConfig.h"

class QtButton : public QPushButton
{
	Q_OBJECT
public:
	QtButton(QWidget *parent = 0) :QPushButton(parent){
		_AttFraButton = new QPushButton(parent);
		Is_AttFra = false;
		_InjFraButton = new QPushButton(parent);
		Is_InjFra = false;
		_ActFraButton = new QPushButton(parent);
		Is_ActFra = false;
		_BodyFraButton = new QPushButton(parent);
		Is_BodyFra = false;
	};
	QtButton(const QString &text, QWidget *parent = 0) :QPushButton(text, parent){};
	QtButton(const QIcon& icon, const QString &text, QWidget *parent = 0) :QPushButton(icon, text, parent){};

	void deleteAction(bool Is_Update = false);

	private slots:
	void keyPressEvent(QKeyEvent *e);
	void mousePressEvent(QMouseEvent *e);
	void DoDelete();

public:

	QPushButton * _AttFraButton;
	QPushButton * _InjFraButton;
	QPushButton * _ActFraButton;
	QPushButton * _BodyFraButton;
	bool Is_AttFra;
	bool Is_InjFra;
	bool Is_ActFra;
	bool Is_BodyFra;
	QMenu* popMenu;
	QAction * DeleteActAction;
	QAction * DeleteInjAction;
	QAction * DeleteAttAction;
	QAction * DeleteBodyAction;
	QAction * DeleteAllAction;

	QAction * AddActAction;
	QAction * AddInjAction;
	QAction * AddAttAction;
	QAction * AddBodyAction;
	QAction * AddAllAction;
private:
	void CheckButton(int);
	int size ;
	int i;
	QtButton *_QtButton;


Q_SIGNALS :
public slots :
	void deleteFra();
	void deleteAct();
	void deleteInj();
	void deleteAtt();
	void deleteBody();
	void addAct();
	void addInj();
	void addAtt();
	void addBody();
	void addFra();
public:
	int Singl_ID;
	bool Is_Click;
	bool te_sh;
	bool te_ct;
};

