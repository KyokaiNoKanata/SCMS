#include "EditCourseWidget.h"

int row;

void EditCourseWidget::CourseEdit(bool cmode, QString qs) {
	CourseManage cm;
	cm.ReadFile(0);
	cm.ChangeNth(row, cmode, qs);
}

EditCourseWidget::EditCourseWidget(int n, QWidget* parent) :QWidget(parent) {
	ui.setupUi(this);
	row = n;
}

void EditCourseWidget::ChangeTeacher() {
	CourseEdit(0, ui.lineEdit_2->text());
}

void EditCourseWidget::ChangeMaxNumber() {
	CourseEdit(1, ui.lineEdit_3->text());
}