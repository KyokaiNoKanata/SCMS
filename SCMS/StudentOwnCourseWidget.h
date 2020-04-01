#pragma once

#include "qwidget.h"
#include "qtablewidget.h"

#include "Course.h"
#include "CourseManage.h"
#include "SetAssistantDialog.h"
#include "ViewScheduleWidget.h"
#include "AddConnectionWidget.h"

#include "ui_StudentOwnCourseWidget.h"

class StudentOwnCourseWidget :public QWidget {
	Q_OBJECT
public:
	explicit StudentOwnCourseWidget(bool mode, QString student, QWidget* parent = Q_NULLPTR);
	void TableDisplay();
	void NTableDisplay();
	void JWTableDisplay();
	void NStatus();
	void JWStatus();

private slots:
	void Refresh();
	void DeleteCourse();
	void SelectAssistant();
	void AssistantApply();
	void ViewSchedule();
	void AddConnection();
	void Exit();

private:
	Ui::StudentOwnCourseWidgetClass ui;
};