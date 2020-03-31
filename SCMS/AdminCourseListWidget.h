#pragma once

#include "qwidget.h"

#include "CourseManage.h"
#include "AddCourseWidget.h"
#include "EditCourseWidget.h"

#include "ui_AdminCourseListWidget.h"

class AdminCourseListWidget :public QWidget {
	Q_OBJECT
public:
	explicit AdminCourseListWidget(bool mode, QWidget* parent = Q_NULLPTR);
	void TableDisplay();
	void NTableDisplay();
	void JWTableDisplay();

private slots:
	void AddCourse();
	void DeleteCourse();
	void InfoEdit();
	void VerifiedInfo();
	void NVerifiedInfo();
	void JWVerifiedInfo();
	void Refresh();
	void Exit();

private:
	Ui::AdminCourseListWidgetClass ui;
};