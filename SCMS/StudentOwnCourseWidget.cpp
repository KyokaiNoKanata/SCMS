#include "StudentOwnCourseWidget.h"

QString stu_3;
bool sm_3;

StudentOwnCourseWidget::StudentOwnCourseWidget(bool mode, QString student, QWidget* parent) :QWidget(parent) {
	ui.setupUi(this);
	stu_3 = student;
	TableDisplay(mode);
}

void StudentOwnCourseWidget::TableDisplay(bool mode) {
	if (!mode) {
		NTableDisplay();
	}
	else {
		JWTableDisplay();
	}
}

void StudentOwnCourseWidget::NTableDisplay() {
	CourseManage scm;
	scm.ReadStudentFile(sm_3, stu_3);
	set<Course>CourseSet = scm.CourseSet;
	ui.tableWidget->setRowCount(CourseSet.size());
	int CurrentRow = 0;
	for (set<Course>::iterator it = CourseSet.begin();it != CourseSet.end();it++, CurrentRow++) {
		ui.tableWidget->setItem(CurrentRow, 0, new QTableWidgetItem(QString("%1").arg(it->ID, 3, 10, QLatin1Char('0'))));
		ui.tableWidget->setItem(CurrentRow, 1, new QTableWidgetItem(it->Name));
		ui.tableWidget->setItem(CurrentRow, 2, new QTableWidgetItem(it->Teacher));
		ui.tableWidget->setItem(CurrentRow, 3, new QTableWidgetItem(it->Type));
		ui.tableWidget->setItem(CurrentRow, 4, new QTableWidgetItem(it->PersonalAssistant));
	}
	ui.tableWidget->resizeColumnsToContents();
}

void StudentOwnCourseWidget::JWTableDisplay() {

}

void StudentOwnCourseWidget::DeleteCourse() {
	CourseManage scm;
	CourseManage cm;
	scm.ReadStudentFile(sm_3, stu_3);
	cm.ReadFile(sm_3);
	int n = ui.tableWidget->currentRow();
	Course course = scm.getNthCourse(n);
	scm.RemoveNth(n);
	cm.RemoveFromCourse(stu_3, course);
	cm.RemoveAssistant(stu_3, course);
	scm.WriteStudentFile(sm_3, stu_3);
	cm.WriteFile(sm_3);
	QMessageBox::information(this, QString::fromLocal8Bit("��ʾ"), QString::fromLocal8Bit("�˿γɹ�"));
	if (!scm.CourseCheck())QMessageBox::warning(this, QString::fromLocal8Bit("�γ̲���"), QString::fromLocal8Bit("�뱣֤����ѡ��4��רҵ����2�ŷ�רҵ��"));
	TableDisplay(sm_3);
}

void StudentOwnCourseWidget::SelectAssistant() {
	CourseManage scm;
	scm.ReadStudentFile(sm_3, stu_3);
	SetAssistantDialog* sad = new SetAssistantDialog(sm_3, stu_3, scm.getNthCourse(ui.tableWidget->currentRow()), Q_NULLPTR);
	sad->show();
}

void StudentOwnCourseWidget::AssistantApply() {
	CourseManage scm;
	CourseManage cm;
	scm.ReadStudentFile(sm_3, stu_3);
	cm.ReadFile(sm_3);
	if (!cm.ApplyCheck(stu_3)) {
		QMessageBox::information(this, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("�����γ���������"));
	}
	else if (!cm.AddAssistant(stu_3, scm.getNthCourse(ui.tableWidget->currentRow()))) {
		QMessageBox::information(this, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("�����ظ�����"));
	}
	else {
		cm.WriteFile(sm_3);
		QMessageBox::information(this, QString::fromLocal8Bit("��ʾ"), QString::fromLocal8Bit("�����ɹ�"));
	}
}

void StudentOwnCourseWidget::Exit() {
	this->close();
}

void StudentOwnCourseWidget::Refresh() {
	TableDisplay(sm_3);
}