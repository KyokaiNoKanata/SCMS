#pragma once

#include<vector>
#include<set>
#include<map>

#include "qstring.h"
#include  "qstringlist.h"

#include "qstring.h"

using namespace std;

class Course {
public:
	int ID;
	QString Name;
	QString Teacher;
	QString Type;
	QString CurrentNumber;
	QString MaxNumber;
	QString AssistantQS;
	QString PersonalAssistant;
	QStringList Assistant;
	int CN;
	int MN;
	bool isFull();
	bool isCompulsory();
	void Refresh();
	void DeleteStudent(QString student);
	void AddStudent(QString student);
	bool operator<(const Course& course)const;
	QString getMember();

private:
	set<QString>MemberList;
};