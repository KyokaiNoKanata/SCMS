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
		if (!const_cast<Course&>(*CourseList_2.find(*it)).Assistant.contains(it->PersonalAssistant) && it->PersonalAssistant != QString::fromLocal8Bit("未选择")) {
			QMessageBox::information(Q_NULLPTR, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("你所选课程 ") + it->Name + QString::fromLocal8Bit(" 的个人助教已退课，请重新选择助教"));
			scm.SetAssistant(QString::fromLocal8Bit("未选择"), *it);
		}
	}
	scm.WriteStudentFile(stu);
}