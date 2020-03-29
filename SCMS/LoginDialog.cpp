#include "LoginDialog.h"

LoginDialog::LoginDialog(QWidget* parent) :QDialog(parent) {
	ui.setupUi(this);
}

void LoginDialog::Login() {
	if (ui.radioButton->isChecked()) {
		StudentLogin();
	}
	else if (ui.radioButton_2->isChecked()) {
		AdminLogin();
	}
	else {
		QMessageBox::warning(this, QString::fromLocal8Bit("µÇÂ¼Ê§°Ü"), QString::fromLocal8Bit("ÇëÑ¡ÔñÉí·Ý£¡"));
	}
}

void LoginDialog::AdminLogin() {
	if (ui.lineEdit->text() == "Admin" && ui.lineEdit_2->text() == "admin") {
		this->close();
		AdminMainWindow* amw = new AdminMainWindow;
		amw->show();
	}
	else {
		QMessageBox::warning(this, QString::fromLocal8Bit("µÇÂ¼Ê§°Ü"), QString::fromLocal8Bit("ÓÃ»§Ãû»òÃÜÂë´íÎó!"));
		ui.lineEdit->clear();
		ui.lineEdit_2->clear();
	}
}

void LoginDialog::StudentLogin() {
	Keyring k;
	k.ReadFile();
	if (k.PasswordCheck(ui.lineEdit->text(), ui.lineEdit_2->text())) {
		this->close();
		QString student = ui.lineEdit->text();
		StudentMainWindow* smw = new StudentMainWindow(student, Q_NULLPTR);
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