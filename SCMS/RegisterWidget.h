#pragma once

#include "qwidget.h"
#include "qstring.h"
#include "qmessagebox.h"
#include "qfile.h"

#include "Keyring.h"

#include "ui_RegisterWidget.h"

class RegisterWidget :public QWidget {
	Q_OBJECT
public:
	RegisterWidget(QWidget* parent = Q_NULLPTR);
	bool isLegal();
	bool StringCheck(QString qs);

private slots:
	void Register();

private:
	Ui::RegisterWidgetClass ui;
};