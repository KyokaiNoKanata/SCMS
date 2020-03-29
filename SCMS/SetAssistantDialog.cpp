#include "SetAssistantDialog.h"

QString stu_4;
Course c;

SetAssistantDialog::SetAssistantDialog(QString student, Course course, QDialog* parent) :QDialog(parent) {
	ui.setupUi(this);
	stu_4 = student;
	c = course;
	TableDisplay();
}

void SetAssistantDialog::TableDisplay() {
	CourseManage cm;
	cm.ReadCourse();
	set<Course>CourseList = cm.getList();
	QStringList qsl = CourseList.find(c)->Assistant;
	ui.tableWidget->setRowCount(qsl.count());
	int row = 0;
	for (QStringList::iterator it = qsl.begin();it != qsl.end();it++, row++) {
		ui.tableWidget->setItem(row, 0, new QTableWidgetItem(*it));
	}
}

void SetAssistantDialog::SetAssistant() {
	CourseManage scm;
	CourseManage cm;
	cm.ReadCourse();
	set<Course>CourseList = cm.getList();
	scm.ReadStudentFile(stu_4);
	scm.SetAssistant(CourseList.find(c)->Assistant[ui.tableWidget->currentRow()], c);
	scm.WriteStudentFile(stu_4);
	QMessageBox::information(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("设定成功"));
	this->close();
}

void SetAssistantDialog::Exit() {
	this->close();
}