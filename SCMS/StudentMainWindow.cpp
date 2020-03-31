#include "StudentMainWindow.h"

QString stu;
bool sm;

StudentMainWindow::StudentMainWindow(bool mode, QString student, QMainWindow* parent) :QMainWindow(parent) {
	ui.setupUi(this);
	sm = mode;
	stu = student;
	if (!sm)AssistantExitJudge();
}

void StudentMainWindow::ShowOwnCourse() {
	StudentOwnCourseWidget* socw = new StudentOwnCourseWidget(sm, stu, Q_NULLPTR);
	socw->show();
}

void StudentMainWindow::SelectCourse() {
	StudentCourseListWidget* sclw = new StudentCourseListWidget(sm, stu, Q_NULLPTR);
	sclw->show();
}

void StudentMainWindow::Exit() {
	this->close();
	LoginDialog* ld = new LoginDialog();
	ld->show();
}

void StudentMainWindow::AssistantExitJudge() {
	CourseManage scm;
	CourseManage cm;
	scm.ReadStudentFile(sm, stu);
	cm.ReadFile(sm);
	set<Course>CourseSet = scm.CourseSet;
	set<Course>CourseList_2 = cm.CourseSet;
	for (set<Course>::iterator it = CourseSet.begin();it != CourseSet.end();it++) {
		if (!const_cast<Course&>(*CourseList_2.find(*it)).Assistant.contains(it->PersonalAssistant) && it->PersonalAssistant != QString::fromLocal8Bit("δѡ��")) {
			QMessageBox::information(Q_NULLPTR, QString::fromLocal8Bit("��ʾ"), QString::fromLocal8Bit("����ѡ�γ� ") + it->Name + QString::fromLocal8Bit(" �ĸ����������˿Σ�������ѡ������"));
			scm.SetAssistant(QString::fromLocal8Bit("δѡ��"), *it);
		}
	}
	scm.WriteStudentFile(sm, stu);
}