#include "AddCourseWidget.h"

AddCourseWidget::AddCourseWidget(QWidget* parent) :QWidget(parent) {
	ui.setupUi(this);
}

void AddCourseWidget::AddCourse() {
	CourseManage cm;
	cm.ReadFile(0);
	if (!cm.NameExist(ui.lineEdit_2->text())) {
		cm.AddCourse(ui.lineEdit_2->text(), ui.lineEdit_3->text(), ui.lineEdit_4->text(), ui.lineEdit_5->text());
		cm.WriteFile(0);
		QMessageBox::information(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("添加成功"));
	}
	else {
		QMessageBox::information(this, QString::fromLocal8Bit("添加失败"), QString::fromLocal8Bit("课程已存在"));
	}
	this->close();
}