#pragma once

#include "qwidget.h"

#include "CourseManage.h"

#include "ui_EditCourseWidget.h"

class EditCourseWidget :public QWidget {
	Q_OBJECT
public:
	explicit EditCourseWidget(int n, QWidget* parent = Q_NULLPTR);

private slots:
	void ChangeTeacher();
	void ChangeMaxNumber();;
	void CourseEdit(bool cmode, QString qs);

private:
	Ui::EditCourseWidgetClass ui;
};