#include "Course.h"

bool Course::isFull() {
	return CN >= MN;
}

bool Course::operator<(const Course& course)const {
	return ID < course.ID;
}

bool Course::isCompulsory() {
	return Type == "×¨Òµ¿Î";
}

void Course::AddStudent(QString student) {
	MemberList.insert(student);
	Refresh();
}

void Course::DeleteStudent(QString student) {
	MemberList.erase(student);
	Refresh();
}

void Course::Refresh() {
	CN = MemberList.size();
	CurrentNumber = QString::number(CN);
}

QString Course::getMember() {
	if (!MemberList.size())return "Null";
	QStringList qsl;
	for (set<QString>::iterator it = MemberList.begin();it != MemberList.end();it++) {
		qsl.push_back(*it);
	}
	QString qs = qsl[0];
	int s = qsl.size();
	for (int i = 1;i < s;i++) {
		qs += ("," + qsl[i]);
	}
	return qs;
}