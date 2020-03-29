#pragma once

#include "qdialog.h"

#include "Course.h"
#include "CourseManage.h"
#include "qmessagebox.h"

#include "ui_SetAssistantDialog.h"

class SetAssistantDialog :public QDialog {
	Q_OBJECT
public:
	explicit SetAssistantDialog(QString student, Course course, QDialog* parent = Q_NULLPTR);
	void TableDisplay();

private slots:
	void SetAssistant();
	void Exit();

private:
	Ui::SetAssistantDialogClass ui;
};