#pragma once

#include "qwidget.h"
#include "qmessagebox.h"

#include "Course.h"
#include "CourseManage.h"

#include "ui_StudentCourseListWidget.h"

class StudentCourseListWidget :public QWidget {
	Q_OBJECT
public:
	explicit StudentCourseListWidget(QString student, QWidget* parent = Q_NULLPTR);
	void TableDisplay();

private slots:
	void SelectCourse(QString student);
	void sc();
	void Exit();

private:
	Ui::StudentCourseListWidgetClass ui;
};