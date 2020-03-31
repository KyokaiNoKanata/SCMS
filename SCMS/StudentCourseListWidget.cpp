#include "StudentCourseListWidget.h"

QString stu_2;
bool sm_2;

StudentCourseListWidget::StudentCourseListWidget(bool mode, QString student, QWidget* parent) :QWidget(parent) {
	ui.setupUi(this);
	stu_2 = student;
	sm_2 = mode;
	TableDisplay();
}

void StudentCourseListWidget::TableDisplay() {
	if (!sm_2) {
		NTableDisplay();
	}
	else {
		JWTableDisplay();
	}
}

void StudentCourseListWidget::NTableDisplay() {
	CourseManage cm;
	cm.ReadFile(sm_2);
	set<Course>CourseSet = cm.CourseSet;
	ui.tableWidget->setRowCount(CourseSet.size());
	int CurrentRow = 0;
	for (set<Course>::iterator it = CourseSet.begin();it != CourseSet.end();it++, CurrentRow++) {
		ui.tableWidget->setItem(CurrentRow, 0, new QTableWidgetItem(QString("%1").arg(it->ID, 3, 10, QLatin1Char('0'))));
		ui.tableWidget->setItem(CurrentRow, 1, new QTableWidgetItem(it->Name));
		ui.tableWidget->setItem(CurrentRow, 2, new QTableWidgetItem(it->Teacher));
		ui.tableWidget->setItem(CurrentRow, 3, new QTableWidgetItem(it->MaxNumber));
		ui.tableWidget->setItem(CurrentRow, 4, new QTableWidgetItem(it->CurrentNumber));
		ui.tableWidget->setItem(CurrentRow, 5, new QTableWidgetItem(it->Type));
		ui.tableWidget->setItem(CurrentRow, 6, new QTableWidgetItem(it->AssistantQS));
	}
	ui.tableWidget->resizeColumnsToContents();
}

void StudentCourseListWidget::JWTableDisplay() {
	CourseManage cm;
	cm.ReadFile(sm_2);
	set<Course>CourseSet = cm.CourseSet;
	ui.tableWidget->setColumnCount(9);
	ui.tableWidget->setRowCount(CourseSet.size());
	QStringList qsl;
	qsl << QString::fromLocal8Bit("�γ̱��") << QString::fromLocal8Bit("�γ�����") << QString::fromLocal8Bit("����") << QString::fromLocal8Bit("����Ժϵ") << QString::fromLocal8Bit("ѧ��") << QString::fromLocal8Bit("ѧʱ") << QString::fromLocal8Bit("У��") << QString::fromLocal8Bit("��ʦ") << QString::fromLocal8Bit("�Ͽ�ʱ�估�ص�");
	ui.tableWidget->setHorizontalHeaderLabels(qsl);
	int CurrentRow = 0;
	for (set<Course>::iterator it = CourseSet.begin();it != CourseSet.end();it++, CurrentRow++) {
		ui.tableWidget->setItem(CurrentRow, 0, new QTableWidgetItem(it->JWID));
		ui.tableWidget->setItem(CurrentRow, 1, new QTableWidgetItem(it->Name));
		ui.tableWidget->setItem(CurrentRow, 2, new QTableWidgetItem(it->Type));
		ui.tableWidget->setItem(CurrentRow, 3, new QTableWidgetItem(it->College));
		ui.tableWidget->setItem(CurrentRow, 4, new QTableWidgetItem(it->Score));
		ui.tableWidget->setItem(CurrentRow, 5, new QTableWidgetItem(it->Hour));
		ui.tableWidget->setItem(CurrentRow, 6, new QTableWidgetItem(it->Campus));
		ui.tableWidget->setItem(CurrentRow, 7, new QTableWidgetItem(it->Teacher));
		ui.tableWidget->setItem(CurrentRow, 8, new QTableWidgetItem(it->TPWQS));
	}
	ui.tableWidget->resizeColumnsToContents();
}

void StudentCourseListWidget::SelectCourse(QString student) {
	CourseManage cm;
	cm.ReadFile(sm_2);
	int CurrentRow = ui.tableWidget->currentRow();
	Course course = cm.getNthCourse(CurrentRow);
	if (!course.isFull() || sm_2) {
		CourseManage scm;
		scm.ReadStudentFile(sm_2, stu_2);
		if (scm.CourseSet.count(course)) {
			QMessageBox::information(this, QString::fromLocal8Bit("ѡ��ʧ��"), QString::fromLocal8Bit("�����ظ�ѡ��"));
			return;
		}
		course.PersonalAssistant = QString::fromLocal8Bit("δѡ��");
		scm.InsertCourse(course);
		cm.AddToNth(CurrentRow, stu_2);
		QMessageBox::information(this, QString::fromLocal8Bit("��ʾ"), QString::fromLocal8Bit("ѡ�γɹ�"));
		scm.WriteStudentFile(sm_2, stu_2);
		cm.WriteFile(sm_2);
		TableDisplay();
	}
	else {
		QMessageBox::warning(this, QString::fromLocal8Bit("ѡ��ʧ��"), QString::fromLocal8Bit("�γ�����"));
	}
}

void StudentCourseListWidget::sc() {
	SelectCourse(stu_2);
}

void StudentCourseListWidget::Exit() {
	this->close();
}