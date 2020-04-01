#include "ViewScheduleWidget.h"

QString stu_5;
set<stack<Course>>Solution;
set<stack<Course>>::iterator it;
int Max;

ViewScheduleWidget::ViewScheduleWidget(bool mode, QString student, QWidget* parent) :QWidget(parent) {
	ui.setupUi(this);
	stu_5 = student;
	CourseManage cm;
	CourseManage scm;
	cm.ReadFile(1);
	scm.ReadStudentFile(1, stu_5);
	scm.CourseSet_2 = cm.CourseSet;
	Solution = scm.getSchedule(mode);
	Max = scm.MaxCount;
	it = Solution.begin();
	Next();
}

void ViewScheduleWidget::Next() {
	while (it != Solution.end() && it->size() < Max) {
		it++;
	}
	if (it == Solution.end()) {
		QMessageBox::information(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("已是最后一个"));
	}
	else {
		ui.tableWidget->clear();
		QStringList qsl;
		qsl << QString::fromLocal8Bit("周一") << QString::fromLocal8Bit("周二") << QString::fromLocal8Bit("周三") << QString::fromLocal8Bit("周四") << QString::fromLocal8Bit("周五") << QString::fromLocal8Bit("周六") << QString::fromLocal8Bit("周日");
		ui.tableWidget->setHorizontalHeaderLabels(qsl);
		stack<Course>sc = *it;
		while (!sc.empty()) {
			Course course = sc.top();
			Display(course);
			sc.pop();
		}
		ui.tableWidget->resizeColumnsToContents();
		ui.tableWidget->resizeRowsToContents();
		it++;
	}
}

void ViewScheduleWidget::Display(Course course) {
	for (int i = 0;i < course.DayList.size();i++) {
		for (int j = course.SList[i];j <= course.EList[i];j++) {
			ui.tableWidget->setItem(j, course.DayList[i], new QTableWidgetItem(course.Name + '\n' + course.Teacher + ' ' + course.PList[i]));
		}
	}
}