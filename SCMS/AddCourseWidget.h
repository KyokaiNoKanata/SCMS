#pragma once

#include "qwidget.h"
#include "qmessagebox.h"

#include "CourseManage.h"

#include "ui_AddCourseWidget.h"

class AddCourseWidget :public QWidget {
	Q_OBJECT
public:
	explicit AddCourseWidget(QWidget* parent = Q_NULLPTR);

private slots:
	void AddCourse();

private:
	Ui::AddCourseWidgetClass ui;
};