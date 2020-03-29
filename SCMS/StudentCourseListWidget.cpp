#include "StudentCourseListWidget.h"

QString stu_2;

StudentCourseListWidget::StudentCourseListWidget(QString student, QWidget* parent) :QWidget(parent) {
	ui.setupUi(this);
	stu_2 = student;
	TableDisplay();
}

void StudentCourseListWidget::TableDisplay() {
	CourseManage cm;
	cm.ReadCourse();
	set<Course>CourseList = cm.getList();
	ui.tableWidget->setRowCount(CourseList.size());
	int CurrentRow = 0;
	for (set<Course>::iterator it = CourseList.begin();it != CourseList.end();it++, CurrentRow++) {
		ui.tableWidget->setItem(CurrentRow, 0, new QTableWidgetItem(QString("%1").arg(it->ID, 3, 10, QLatin1Char('0'))));
		ui.tableWidget->setItem(CurrentRow, 1, new QTableWidgetItem(it->Name));
		ui.tableWidget->setItem(CurrentRow, 2, new QTableWidgetItem(it->Teacher));
		ui.tableWidget->setItem(CurrentRow, 3, new QTableWidgetItem(it->MaxNumber));
		ui.tableWidget->setItem(CurrentRow, 4, new QTableWidgetItem(it->CurrentNumber));
		ui.tableWidget->setItem(CurrentRow, 5, new QTableWidgetItem(it->Type));
		ui.tableWidget->setItem(CurrentRow, 6, new QTableWidgetItem(it->AssistantQS));
		ui.tableWidget->setItem(CurrentRow, 7, new QTableWidgetItem(it->PersonalAssistant));
	}
	ui.tableWidget->resizeColumnsToContents();
}

void StudentCourseListWidget::SelectCourse(QString student) {
	CourseManage cm;
	cm.ReadCourse();
	int CurrentRow = ui.tableWidget->currentRow();
	Course course = cm.getNthCourse(CurrentRow);
	if (!course.isFull()) {
		CourseManage scm;
		scm.ReadStudentFile(stu_2);
		if (scm.Exist(course)) {
			QMessageBox::information(this, QString::fromLocal8Bit("ѡ��ʧ��"), QString::fromLocal8Bit("�����ظ�ѡ��"));
			return;
		}
		course.PersonalAssistant = QString::fromLocal8Bit("δѡ��");
		scm.InsertCourse(course);
		cm.AddToNth(CurrentRow, stu_2);
		QMessageBox::information(this, QString::fromLocal8Bit("��ʾ"), QString::fromLocal8Bit("ѡ�γɹ�"));
		scm.WriteStudentFile(stu_2);
		cm.WriteCourse();
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