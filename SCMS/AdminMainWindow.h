#pragma once

#include<stack>
#include<vector>

#include "qmainwindow.h"
#include "qwidget.h"
#include "qmessagebox.h"
#include "qstring.h"
#include "qfiledialog.h"
#include "LoginDialog.h"

#include "Course.h"
#include "AdminCourseListWidget.h"
#include "CourseManage.h"
#include "AddCourseWidget.h"

#include"ui_AdminMainWindow.h"

using namespace std;

class AdminMainWindow :public QMainWindow {
	Q_OBJECT
public:
	explicit AdminMainWindow(QMainWindow* parent = Q_NULLPTR);

private slots:
	void InputCourse();
	void Exit();
	void ViewCourseList();

private:
	Ui::AdminMainWindowClass ui;
};