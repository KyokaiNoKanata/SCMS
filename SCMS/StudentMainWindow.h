#pragma once

#include "qmainwindow.h"

#include "Course.h"
#include "StudentCourseListWidget.h"
#include "StudentOwnCourseWidget.h"
#include "LoginDialog.h"
#include "qmessagebox.h"

#include "ui_StudentMainWindow.h"

class StudentMainWindow :public QMainWindow {
	Q_OBJECT
public:
	StudentMainWindow(QString student, QMainWindow* parent = Q_NULLPTR);
	void AssistantExitJudge();

private slots:
	void ShowOwnCourse();
	void SelectCourse();
	void Exit();

private:
	Ui::StudentMainWindowClass ui;
};