#include "AdminCourseListWidget.h"

bool am_2;

AdminCourseListWidget::AdminCourseListWidget(bool mode, QWidget* parent) :QWidget(parent) {
	am_2 = mode;
	ui.setupUi(this);
	TableDisplay();
}

void AdminCourseListWidget::TableDisplay() {
	if (!am_2) {
		NTableDisplay();
	}
	else {
		JWTableDisplay();
	}
}

void AdminCourseListWidget::NTableDisplay() {
	CourseManage cm;
	cm.ReadFile(am_2);
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

void AdminCourseListWidget::JWTableDisplay() {
	CourseManage cm;
	cm.ReadFile(am_2);
	set<Course>CourseSet = cm.CourseSet;
	ui.tableWidget->setColumnCount(9);
	ui.tableWidget->setRowCount(CourseSet.size());
	QStringList qsl;
	qsl << QString::fromLocal8Bit("课程编号") << QString::fromLocal8Bit("课程名称") << QString::fromLocal8Bit("性质") << QString::fromLocal8Bit("开课院系") << QString::fromLocal8Bit("学分") << QString::fromLocal8Bit("学时") << QString::fromLocal8Bit("校区") << QString::fromLocal8Bit("教师") << QString::fromLocal8Bit("上课时间及地点");
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

void AdminCourseListWidget::AddCourse() {
	if (am_2) {
		QMessageBox::information(this, QString::fromLocal8Bit("操作失败"), QString::fromLocal8Bit("该模式下不可用"));
	}
	AddCourseWidget* adw = new AddCourseWidget;
	adw->show();
}

void AdminCourseListWidget::DeleteCourse() {
	if (am_2) {
		QMessageBox::warning(this, QString::fromLocal8Bit("操作失败"), QString::fromLocal8Bit("该模式下不可用"));
	}
	CourseManage cm;
	cm.ReadFile(am_2);
	int CurrentRow = ui.tableWidget->currentRow();
	Course course = cm.getNthCourse(CurrentRow);
	if (!course.CN) {
		cm.RemoveNth(CurrentRow);
		cm.WriteFile(am_2);
		TableDisplay();
	}
	else {
		QMessageBox::information(this, QString::fromLocal8Bit("删除失败"), QString::fromLocal8Bit("有学生选中该课程"));
	}
}

void AdminCourseListWidget::InfoEdit() {
	if (am_2) {
		QMessageBox::information(this, QString::fromLocal8Bit("操作失败"), QString::fromLocal8Bit("该模式下不可用"));
	}
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
	if (!am_2) {
		NVerifiedInfo();
	}
	else {
		JWVerifiedInfo();
	}
}

void AdminCourseListWidget::NVerifiedInfo() {
	CourseManage cm;
	cm.ReadFile(am_2);
	Course course = cm.getNthCourse(ui.tableWidget->currentRow());
	ui.tableWidget_2->setItem(0, 0, new QTableWidgetItem(QString("%1").arg(course.ID, 3, 10, QLatin1Char('0'))));
	ui.tableWidget_2->setItem(1, 0, new QTableWidgetItem(course.Name));
	ui.tableWidget_2->setItem(2, 0, new QTableWidgetItem(course.Teacher));
	ui.tableWidget_2->setItem(3, 0, new QTableWidgetItem(course.MaxNumber));
	ui.tableWidget_2->setItem(4, 0, new QTableWidgetItem(course.CurrentNumber));
	ui.tableWidget_2->setItem(5, 0, new QTableWidgetItem(course.Type));
	ui.tableWidget_2->setItem(6, 0, new QTableWidgetItem(course.AssistantQS.replace(',', '\n')));
	ui.tableWidget_2->setItem(7, 0, new QTableWidgetItem(course.getMember().replace(',', '\n')));
	ui.tableWidget_2->resizeColumnsToContents();
	ui.tableWidget_2->resizeRowsToContents();
}

void AdminCourseListWidget::JWVerifiedInfo() {
	CourseManage cm;
	cm.ReadFile(am_2);
	Course course = cm.getNthCourse(ui.tableWidget->currentRow());
	ui.tableWidget_2->setRowCount(11);
	QStringList qsl;
	qsl << QString::fromLocal8Bit("课程编号") << QString::fromLocal8Bit("课程名称") << QString::fromLocal8Bit("性质") << QString::fromLocal8Bit("开课院系") << QString::fromLocal8Bit("学分") << QString::fromLocal8Bit("学时") << QString::fromLocal8Bit("校区") << QString::fromLocal8Bit("教师") << QString::fromLocal8Bit("上课时间及地点") << QString::fromLocal8Bit("助教") << QString::fromLocal8Bit("已选学生");
	ui.tableWidget_2->setVerticalHeaderLabels(qsl);
	ui.tableWidget_2->setItem(0, 0, new QTableWidgetItem(course.JWID));
	ui.tableWidget_2->setItem(1, 0, new QTableWidgetItem(course.Name));
	ui.tableWidget_2->setItem(2, 0, new QTableWidgetItem(course.Type));
	ui.tableWidget_2->setItem(3, 0, new QTableWidgetItem(course.College));
	ui.tableWidget_2->setItem(4, 0, new QTableWidgetItem(course.Score));
	ui.tableWidget_2->setItem(5, 0, new QTableWidgetItem(course.Hour));
	ui.tableWidget_2->setItem(6, 0, new QTableWidgetItem(course.Campus));
	ui.tableWidget_2->setItem(7, 0, new QTableWidgetItem(course.Teacher));
	ui.tableWidget_2->setItem(8, 0, new QTableWidgetItem(course.TPWQS.mid(0, course.TPWQS.size() - 1).replace(';', '\n')));
	ui.tableWidget_2->setItem(9, 0, new QTableWidgetItem(course.AssistantQS.replace(',', '\n')));
	ui.tableWidget_2->setItem(10, 0, new QTableWidgetItem(course.getMember().replace(',', '\n')));
	ui.tableWidget_2->resizeColumnsToContents();
	ui.tableWidget_2->resizeRowsToContents();
}

void AdminCourseListWidget::AddConnect() {
	if (!am_2) {
		QMessageBox::information(this, QString::fromLocal8Bit("操作失败"), QString::fromLocal8Bit("该模式下不可用"));
	}
	AddConnectionWidget* acw = new AddConnectionWidget;
	acw->show();
}