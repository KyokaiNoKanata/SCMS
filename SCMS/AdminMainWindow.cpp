#include "AdminMainWindow.h"

AdminMainWindow::AdminMainWindow(QMainWindow* parent) :
	QMainWindow(parent) {
	ui.setupUi(this);
}

void AdminMainWindow::Exit() {
	this->close();
	LoginDialog* ld = new LoginDialog;
	ld->show();
}

void AdminMainWindow::ViewCourseList() {
	AdminCourseListWidget* clw = new AdminCourseListWidget;
	clw->show();
}

void AdminMainWindow::InputCourse() {
	CourseManage cm;
	QString path = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("请选择课程文件"), "../data", QString::fromLocal8Bit("文本文件(*.txt)"));
	cm.InputCourse(path);
	cm.WriteCourse();
	QMessageBox::information(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("录入成功"));
}

bool CourseManage::ApplyCheck(QString student) {
	for (set<Course>::iterator it = CourseList.begin();it != CourseList.end();it++) {
		if (it->AssistantQS.contains(student)) {
			if (!ApplyCount.count(student)) {
				ApplyCount[student] = 1;
			}
			else {
				ApplyCount[student]++;
			}
		}
	}
	return ApplyCount[student] < 2;
}