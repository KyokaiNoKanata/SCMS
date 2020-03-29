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
		QMessageBox::information(this, QString::fromLocal8Bit("��ʾ"), QString::fromLocal8Bit("��ӳɹ�"));
	}
	else {
		QMessageBox::information(this, QString::fromLocal8Bit("���ʧ��"), QString::fromLocal8Bit("�γ��Ѵ���"));
	}
	this->close();
}