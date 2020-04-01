#include "ViewScheduleWidget.h"

QString stu_5;
set<stack<Course>>Solution;
set<stack<Course>>::iterator it;
int Max;

ViewScheduleWidget::ViewScheduleWidget(QString student, QWidget* parent) :QWidget(parent) {
	ui.setupUi(this);
	stu_5 = student;
	CourseManage cm;
	CourseManage scm;
	cm.ReadFile(1);
	scm.ReadStudentFile(1, stu_5);
	scm.CourseSet_2 = cm.CourseSet;
	Solution = scm.getSchedule();
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
			ui.tableWidget->setItem(j, course.DayList[i], new QTableWidgetItem(course.Name + '\n' + course.Teacher));
		}
	}
}