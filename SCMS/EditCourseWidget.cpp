#include "EditCourseWidget.h"

int row;

void EditCourseWidget::CourseEdit(int mode, QString qs) {
	CourseManage cm;
	cm.ReadCourse();
	cm.ChangeNth(row, mode, qs);
}

EditCourseWidget::EditCourseWidget(int n, QWidget* parent) :QWidget(parent) {
	ui.setupUi(this);
	row = n;
}

void EditCourseWidget::ChangeTeacher() {
	CourseEdit(2, ui.lineEdit_2->text());
}

void EditCourseWidget::ChangeMaxNumber() {
	CourseEdit(3, ui.lineEdit_3->text());
}