#include "SetAssistantDialog.h"

QString stu_4;
Course c;
bool sm_4;

SetAssistantDialog::SetAssistantDialog(bool mode, QString student, Course course, QDialog* parent) :QDialog(parent) {
	ui.setupUi(this);
	stu_4 = student;
	c = course;
	sm_4 = mode;
	TableDisplay();
}

void SetAssistantDialog::TableDisplay() {
	CourseManage cm;
	cm.ReadFile(sm_4);
	set<Course>CourseSet = cm.CourseSet;
	QStringList qsl = CourseSet.find(c)->Assistant;
	ui.tableWidget->setRowCount(qsl.count());
	int row = 0;
	for (QStringList::iterator it = qsl.begin();it != qsl.end();it++, row++) {
		ui.tableWidget->setItem(row, 0, new QTableWidgetItem(*it));
	}
}

void SetAssistantDialog::SetAssistant() {
	CourseManage scm;
	CourseManage cm;
	cm.ReadFile(sm_4);
	set<Course>CourseSet = cm.CourseSet;
	scm.ReadStudentFile(sm_4, stu_4);
	scm.SetAssistant(CourseSet.find(c)->Assistant[ui.tableWidget->currentRow()], c);
	scm.WriteStudentFile(sm_4, stu_4);
	QMessageBox::information(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("设定成功"));
	this->close();
}

void SetAssistantDialog::Exit() {
	this->close();
}