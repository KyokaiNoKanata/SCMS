#include "StudentCourseListWidget.h"

QString stu_2;
bool sm_2;

StudentCourseListWidget::StudentCourseListWidget(bool mode, QString student, QWidget* parent) :QWidget(parent) {
	ui.setupUi(this);
	stu_2 = student;
	sm_2 = mode;
	TableDisplay(sm_2);
}

void StudentCourseListWidget::TableDisplay(bool mode) {
	if (!mode) {
		NTableDisplay();
	}
	else {
		JWTableDisplay();
	}
}

void StudentCourseListWidget::NTableDisplay() {
	CourseManage scm;
	scm.ReadStudentFile(sm_2, stu_2);
	set<Course>CourseSet = scm.CourseSet;
	ui.tableWidget->setRowCount(CourseSet.size());
	int CurrentRow = 0;
	for (set<Course>::iterator it = CourseSet.begin();it != CourseSet.end();it++, CurrentRow++) {
		ui.tableWidget->setItem(CurrentRow, 0, new QTableWidgetItem(QString("%1").arg(it->ID, 3, 10, QLatin1Char('0'))));
		ui.tableWidget->setItem(CurrentRow, 1, new QTableWidgetItem(it->Name));
		ui.tableWidget->setItem(CurrentRow, 2, new QTableWidgetItem(it->Teacher));
		ui.tableWidget->setItem(CurrentRow, 3, new QTableWidgetItem(it->Type));
		ui.tableWidget->setItem(CurrentRow, 4, new QTableWidgetItem(it->PersonalAssistant));
	}
	ui.tableWidget->resizeColumnsToContents();
}

void StudentCourseListWidget::JWTableDisplay() {

}

void StudentCourseListWidget::SelectCourse(QString student) {
	CourseManage cm;
	cm.ReadFile(sm_2);
	int CurrentRow = ui.tableWidget->currentRow();
	Course course = cm.getNthCourse(CurrentRow);
	if (!course.isFull()) {
		CourseManage scm;
		scm.ReadStudentFile(sm_2, stu_2);
		if (scm.CourseSet.count(course)) {
			QMessageBox::information(this, QString::fromLocal8Bit("选课失败"), QString::fromLocal8Bit("请勿重复选课"));
			return;
		}
		course.PersonalAssistant = QString::fromLocal8Bit("未选择");
		scm.InsertCourse(course);
		cm.AddToNth(CurrentRow, stu_2);
		QMessageBox::information(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("选课成功"));
		scm.WriteStudentFile(sm_2, stu_2);
		cm.WriteFile(sm_2);
		TableDisplay(sm_2);
	}
	else {
		QMessageBox::warning(this, QString::fromLocal8Bit("选课失败"), QString::fromLocal8Bit("课程已满"));
	}
}

void StudentCourseListWidget::sc() {
	SelectCourse(stu_2);
}

void StudentCourseListWidget::Exit() {
	this->close();
}