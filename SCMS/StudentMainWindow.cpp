#include "StudentMainWindow.h"

QString stu;

StudentMainWindow::StudentMainWindow(QString student, QMainWindow* parent) :QMainWindow(parent){
	ui.setupUi(this);
	stu = student;
	AssistantExitJudge();
}

void StudentMainWindow::ShowOwnCourse() {
	StudentOwnCourseWidget* socw = new StudentOwnCourseWidget(stu, Q_NULLPTR);
	socw->show();
}

void StudentMainWindow::SelectCourse() {
	StudentCourseListWidget* sclw = new StudentCourseListWidget(stu, Q_NULLPTR);
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
	scm.ReadStudentFile(stu);
	cm.ReadCourse();
	set<Course>CourseList = scm.getList();
	set<Course>CourseList_2 = cm.getList();
	for (set<Course>::iterator it = CourseList.begin();it != CourseList.end();it++) {
		if (!const_cast<Course&>(*CourseList_2.find(*it)).Assistant.contains(it->PersonalAssistant) && it->PersonalAssistant != QString::fromLocal8Bit("δѡ��")) {
			QMessageBox::information(Q_NULLPTR, QString::fromLocal8Bit("��ʾ"), QString::fromLocal8Bit("����ѡ�γ� ") + it->Name + QString::fromLocal8Bit(" �ĸ����������˿Σ�������ѡ������"));
			scm.SetAssistant(QString::fromLocal8Bit("δѡ��"), *it);
		}
	}
	scm.WriteStudentFile(stu);
}