#pragma once

#include "qwidget.h"

#include "Course.h"
#include "CourseManage.h"
#include "SetAssistantDialog.h"

#include "ui_StudentOwnCourseWidget.h"

class StudentOwnCourseWidget :public QWidget {
	Q_OBJECT
public:
	explicit StudentOwnCourseWidget(bool mode, QString student, QWidget* parent = Q_NULLPTR);
	void TableDisplay(bool n);
	void NTableDisplay();
	void JWTableDisplay();

private slots:
	void Refresh();
	void DeleteCourse();
	void SelectAssistant();
	void AssistantApply();
	void Exit();

private:
	Ui::StudentOwnCourseWidgetClass ui;
};