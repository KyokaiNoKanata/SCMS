#pragma once

#include "qwidget.h"
#include "qmessagebox.h"
#include "qtablewidget.h"

#include "CourseManage.h"

#include "ui_ViewScheduleWidget.h"

class ViewScheduleWidget :public QWidget {
	Q_OBJECT
public:
	explicit ViewScheduleWidget(QString student, QWidget* parent = Q_NULLPTR);
	void Display(Course course);

private slots:
	void Next();

private:
	Ui::ViewScheduleWidgetClass ui;
};