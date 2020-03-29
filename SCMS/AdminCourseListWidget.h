#pragma once

#include "qwidget.h"

#include "CourseManage.h"
#include "AddCourseWidget.h"
#include "EditCourseWidget.h"

#include "ui_AdminCourseListWidget.h"

class AdminCourseListWidget :public QWidget {
	Q_OBJECT
public:
	explicit AdminCourseListWidget(QWidget* parent = Q_NULLPTR);
	void TableDisplay();

private slots:
	void AddCourse();
	void DeleteCourse();
	void InfoEdit();
	void VerifiedInfo();
	void Refresh();
	void Exit();

private:
	Ui::AdminCourseListWidgetClass ui;
};