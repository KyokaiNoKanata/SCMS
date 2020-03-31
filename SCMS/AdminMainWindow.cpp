#include "AdminMainWindow.h"

bool am;

AdminMainWindow::AdminMainWindow(bool mode, QMainWindow* parent) :QMainWindow(parent) {
	am = mode;
	ui.setupUi(this);
}

void AdminMainWindow::Exit() {
	this->close();
	LoginDialog* ld = new LoginDialog;
	ld->show();
}

void AdminMainWindow::ViewCourseList() {
	AdminCourseListWidget* aclw = new AdminCourseListWidget(am, Q_NULLPTR);
	aclw->show();
}

void AdminMainWindow::InputCourse() {
	CourseManage cm;
	QString path = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("请选择课程文件"), "../data", QString::fromLocal8Bit("文本文件(*.txt)"));
	cm.InputCourse(am, path);
	cm.WriteFile(am);
	QMessageBox::information(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("录入成功"));
}