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
	QString path = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("��ѡ��γ��ļ�"), "../data", QString::fromLocal8Bit("�ı��ļ�(*.txt)"));
	cm.InputCourse(path);
	cm.WriteCourse();
	QMessageBox::information(this, QString::fromLocal8Bit("��ʾ"), QString::fromLocal8Bit("¼��ɹ�"));
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