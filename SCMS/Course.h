#pragma once

#include<vector>
#include<set>
#include<map>

#include "qchar.h"
#include "qstring.h"
#include  "qstringlist.h"

#include "qstring.h"

using namespace std;

class Course {
public:
	int ID;
	QString JWID;
	QString Name;
	QString Type;
	QString CurrentNumber;
	QString MaxNumber;
	QString AssistantQS;
	QString PersonalAssistant;
	QString TimeQS;
	QString WeekQS;
	QString Place;
	QString College;
	QString Score;
	QString Hour;
	QString Campus;
	QString Teacher;
	QString JWTeacherQS;
	QStringList JWTeacher;
	QStringList TPWList;
	QStringList JWName;
	QStringList Assistant;
	QStringList Time;
	QStringList Week;
	int CN;
	int MN;
	bool isFull();
	void AddStudent(QString student);
	void DeleteStudent(QString student);
	bool operator<(const Course& course)const;
	QString getMember();
	set<QString>MemberSet;

private:
	void Refresh();
	bool isCompulsory();
};