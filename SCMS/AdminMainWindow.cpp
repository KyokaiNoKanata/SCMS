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
	QString path = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("��ѡ��γ��ļ�"), "../data", QString::fromLocal8Bit("�ı��ļ�(*.txt)"));
	cm.InputCourse(am, path);
	cm.WriteFile(am);
	QMessageBox::information(this, QString::fromLocal8Bit("��ʾ"), QString::fromLocal8Bit("¼��ɹ�"));
}