#include "AdminCourseListWidget.h"

AdminCourseListWidget::AdminCourseListWidget(QWidget* parent) :QWidget(parent) {
	ui.setupUi(this);
	TableDisplay();
}

void AdminCourseListWidget::TableDisplay() {
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
	}
	ui.tableWidget->resizeColumnsToContents();
}

void AdminCourseListWidget::AddCourse() {
	AddCourseWidget* adw = new AddCourseWidget;
	adw->show();
}

void AdminCourseListWidget::DeleteCourse() {
	CourseManage cm;
	cm.ReadCourse();
	int CurrentRow = ui.tableWidget->currentRow();
	Course course = cm.getNthCourse(CurrentRow);
	if (!course.CN) {
		cm.RemoveNth(CurrentRow);
		cm.WriteCourse();
		TableDisplay();
	}
	else {
		QMessageBox::information(this, QString::fromLocal8Bit("删除失败"), QString::fromLocal8Bit("有学生选中该课程"));
	}
}

void AdminCourseListWidget::InfoEdit() {
	EditCourseWidget* ecw = new EditCourseWidget(ui.tableWidget->currentItem()->row(), Q_NULLPTR);
	ecw->show();
}

void AdminCourseListWidget::Refresh() {
	TableDisplay();
}

void AdminCourseListWidget::Exit() {
	this->close();
}

void AdminCourseListWidget::VerifiedInfo() {
	CourseManage cm;
	cm.ReadCourse();
	Course course = cm.getNthCourse(ui.tableWidget->currentRow());
	ui.tableWidget_2->setItem(0, 0, new QTableWidgetItem(QString("%1").arg(course.ID, 3, 10, QLatin1Char('0'))));
	ui.tableWidget_2->setItem(1, 0, new QTableWidgetItem(course.Name));
	ui.tableWidget_2->setItem(2, 0, new QTableWidgetItem(course.Teacher));
	ui.tableWidget_2->setItem(3, 0, new QTableWidgetItem(course.MaxNumber));
	ui.tableWidget_2->setItem(4, 0, new QTableWidgetItem(course.CurrentNumber));
	ui.tableWidget_2->setItem(5, 0, new QTableWidgetItem(course.Type));
	ui.tableWidget_2->setItem(6, 0, new QTableWidgetItem(course.AssistantQS));
	ui.tableWidget_2->setItem(7, 0, new QTableWidgetItem(course.getMember()));
	ui.tableWidget_2->resizeColumnsToContents();
}