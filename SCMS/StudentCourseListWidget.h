#pragma once

#include "qwidget.h"
#include "qmessagebox.h"
#include "qtablewidget.h"

#include "Course.h"
#include "CourseManage.h"

#include "ui_StudentCourseListWidget.h"

class StudentCourseListWidget :public QWidget {
	Q_OBJECT
public:
	explicit StudentCourseListWidget(bool mode, QString student, QWidget* parent = Q_NULLPTR);
	void TableDisplay();
	void NTableDisplay();
	void JWTableDisplay();

private slots:
	void SelectCourse(QString student);
	void sc();
	void Exit();

private:
	Ui::StudentCourseListWidgetClass ui;
};