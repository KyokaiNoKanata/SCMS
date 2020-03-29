#pragma once

#include "qdialog.h"

#include "AdminMainWindow.h"
#include "StudentMainWindow.h"
#include "Keyring.h"
#include "RegisterWidget.h"

#include "ui_LoginDialog.h"

class LoginDialog : public QDialog {
	Q_OBJECT
public:
	LoginDialog(QWidget *parent = Q_NULLPTR);

public slots:
	void Login();
	void StudentLogin(bool mode);
	void Register();
	void AdminLogin(bool mode);

protected:
	Ui::LoginDialogClass ui;
};