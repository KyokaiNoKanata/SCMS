#include "AddConnectionWidget.h"

AddConnectionWidget::AddConnectionWidget(QWidget* parent) :QWidget(parent) {
	ui.setupUi(this);
}

void AddConnectionWidget::AddConnection() {
	CourseManage cm;
	cm.ReadConnection();
	cm.NewConnect(ui.lineEdit->text(), ui.lineEdit->text());
	cm.WriteConnection();
	QMessageBox::information(this, QString::fromUtf8("提示"), QString::fromLocal8Bit("操作成功"));
}