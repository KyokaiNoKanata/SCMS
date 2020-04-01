#pragma once

#include "qwidget.h"
#include "qmessagebox.h"

#include "CourseManage.h"

#include "ui_AddConnectionWidget.h"

class AddConnectionWidget :public QWidget {
	Q_OBJECT
public:
	explicit AddConnectionWidget(QWidget* parent = Q_NULLPTR);

private slots:
	void AddConnection();

private:
	Ui::AddConnectionWidgetClass ui;
};