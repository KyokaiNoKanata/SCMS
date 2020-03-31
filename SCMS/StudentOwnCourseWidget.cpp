#include "StudentOwnCourseWidget.h"

QString stu_3;
bool sm_3;

StudentOwnCourseWidget::StudentOwnCourseWidget(bool mode, QString student, QWidget* parent) :QWidget(parent) {
	ui.setupUi(this);
	stu_3 = student;
	sm_3 = mode;
	TableDisplay();
}


void StudentOwnCourseWidget::TableDisplay() {
	if (!sm_3) {
		NTableDisplay();
	}
	else {
		JWTableDisplay();
	}
}

void StudentOwnCourseWidget::NTableDisplay() {
	CourseManage cm;
	cm.ReadStudentFile(sm_3, stu_3);
	set<Course>CourseSet = cm.CourseSet;
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
	CourseManage cm;
	cm.ReadStudentFile(sm_3, stu_3);
	set<Course>CourseSet = cm.CourseSet;
	ui.tableWidget->setColumnCount(10);
	ui.tableWidget->setRowCount(CourseSet.size());
	QStringList qsl;
	qsl << QString::fromLocal8Bit("�γ̱��") << QString::fromLocal8Bit("�γ�����") << QString::fromLocal8Bit("����") << QString::fromLocal8Bit("����Ժϵ") << QString::fromLocal8Bit("ѧ��") << QString::fromLocal8Bit("ѧʱ") << QString::fromLocal8Bit("У��") << QString::fromLocal8Bit("��ʦ") << QString::fromLocal8Bit("�Ͽ�ʱ�估�ص�") << QString::fromLocal8Bit("��������");
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
		ui.tableWidget->setItem(CurrentRow, 8, new QTableWidgetItem(it->PersonalAssistant));
	}
	ui.tableWidget->resizeColumnsToContents();
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
	TableDisplay();
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
	TableDisplay();
}