#include "RegisterWidget.h"

RegisterWidget::RegisterWidget(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

void RegisterWidget::Register() {
	if (isLegal()) {
		Keyring key;
		key.ReadFile();
		if (!key.Exist(ui.lineEdit->text())) {
			key.AddToKeyring(ui.lineEdit->text(), ui.lineEdit_2->text());
			key.WriteFile();
			QFile file("../data/" + ui.lineEdit->text() + ".txt");
			file.open(QIODevice::WriteOnly | QIODevice::Text);
			file.close();
			QMessageBox::information(this, QString::fromLocal8Bit("��ʾ"), QString::fromLocal8Bit("ע��ɹ�"));
			this->close();
		}
		else {
			QMessageBox::information(this, QString::fromLocal8Bit("ע��ʧ�ܣ�"), QString::fromLocal8Bit("�û��Ѵ���"));
		}
	}
}

bool RegisterWidget::isLegal() {
	if (ui.lineEdit->text().isEmpty()) {
		QMessageBox::information(this, QString::fromLocal8Bit("ע��ʧ�ܣ�"), QString::fromLocal8Bit("�û�������Ϊ��"));
		return 0;
	}
	else if (ui.lineEdit_2->text().isEmpty()) {
		QMessageBox::information(this, QString::fromLocal8Bit("ע��ʧ�ܣ�"), QString::fromLocal8Bit("����������"));
		return 0;
	}
	else if (ui.lineEdit_3->text().isEmpty()) {
		QMessageBox::information(this, QString::fromLocal8Bit("ע��ʧ�ܣ�"), QString::fromLocal8Bit("���ظ�����"));
		return 0;
	}
	else if (ui.lineEdit->text().length() > 20) {
		QMessageBox::information(this, QString::fromLocal8Bit("ע��ʧ�ܣ�"), QString::fromLocal8Bit("�û�������"));
		return 0;
	}
	else if (ui.lineEdit_2->text().length() > 20) {
		QMessageBox::information(this, QString::fromLocal8Bit("ע��ʧ�ܣ�"), QString::fromLocal8Bit("�������"));
		return 0;
	}
	else if (ui.lineEdit_2->text() != ui.lineEdit_3->text()) {
		QMessageBox::information(this, QString::fromLocal8Bit("ע��ʧ�ܣ�"), QString::fromLocal8Bit("�������벻һ��"));
		return 0;
	}
	else if (!StringCheck(ui.lineEdit->text()) || !StringCheck(ui.lineEdit_2->text())) {
		QMessageBox::information(this, QString::fromLocal8Bit("ע��ʧ�ܣ�"), QString::fromLocal8Bit("�û���������ֻ����Сд��ĸ���������"));
	}
}

bool RegisterWidget::StringCheck(QString qs) {
	for (QString::iterator it = qs.begin();it != qs.end();it++) {
		if (!it->isLetterOrNumber() || it->isUpper()) {
			return 0;
		}
	}
	return 1;
}