#include "LoginDialog.h"

LoginDialog::LoginDialog(QWidget* parent) :QDialog(parent) {
	ui.setupUi(this);
}

void LoginDialog::Login() {
	if (ui.radioButton->isChecked()) {
		if (ui.radioButton_3->isChecked()) {
			StudentLogin(0);
		}
		else if (ui.radioButton_4->isChecked()) {
			StudentLogin(1);
		}
		else {
			QMessageBox::warning(this, QString::fromLocal8Bit("µÇÂ¼Ê§°Ü"), QString::fromLocal8Bit("ÇëÑ¡ÔñÄ£Ê½£¡"));
		}
	}
	else if (ui.radioButton_2->isChecked()) {
		if (ui.radioButton_3->isChecked()) {
			AdminLogin(0);
		}
		else if (ui.radioButton_4->isChecked()) {
			AdminLogin(1);
		}
		else {
			QMessageBox::warning(this, QString::fromLocal8Bit("µÇÂ¼Ê§°Ü"), QString::fromLocal8Bit("ÇëÑ¡ÔñÄ£Ê½£¡"));
		}
	}
	else {
		QMessageBox::warning(this, QString::fromLocal8Bit("µÇÂ¼Ê§°Ü"), QString::fromLocal8Bit("ÇëÑ¡ÔñÉí·Ý£¡"));
	}
}

void LoginDialog::AdminLogin(bool mode) {
	if (ui.lineEdit->text() == "Admin" && ui.lineEdit_2->text() == "admin") {
		this->close();
		AdminMainWindow* amw = new AdminMainWindow(mode, Q_NULLPTR);
		amw->show();
	}
	else {
		QMessageBox::warning(this, QString::fromLocal8Bit("µÇÂ¼Ê§°Ü"), QString::fromLocal8Bit("ÓÃ»§Ãû»òÃÜÂë´íÎó!"));
		ui.lineEdit->clear();
		ui.lineEdit_2->clear();
	}
}

void LoginDialog::StudentLogin(bool mode) {
	Keyring k;
	k.ReadFile();
	if (k.PasswordCheck(ui.lineEdit->text(), ui.lineEdit_2->text())) {
		this->close();
		QString student = ui.lineEdit->text();
		StudentMainWindow* smw = new StudentMainWindow(mode, student, Q_NULLPTR);
		smw->show();
	}
	else {
		QMessageBox::warning(this, QString::fromLocal8Bit("µÇÂ¼Ê§°Ü"), QString::fromLocal8Bit("ÓÃ»§Ãû»òÃÜÂë´íÎó!"));
		ui.lineEdit->clear();
		ui.lineEdit_2->clear();
	}
}

void LoginDialog::Register() {
	RegisterWidget* rw = new RegisterWidget;
	rw->show();
}