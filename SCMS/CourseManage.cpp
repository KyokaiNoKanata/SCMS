#include "CourseManage.h"

void CourseManage::InputCourse(QString path) {
	QFile file(path);
	file.open(QIODevice::ReadOnly | QIODevice::Text);
	QTextStream in(&file);
	while (!in.atEnd()) {
		QStringList qsl = in.readLine().split('\t');
		Course course;
		course.ID = qsl[0].toInt();
		if (qsl.length() > 1)course.Name = qsl[1];
		if (qsl.length() > 2)course.Teacher = qsl[2];
		if (qsl.length() > 3) {
			course.MaxNumber = qsl[3];
			course.MN = qsl[3].toInt();
			course.CurrentNumber = "0";
			course.CN = 0;
		}
		if (qsl.length() > 5)course.Type = qsl[5];
		CourseList.insert(course);
	}
}

void CourseManage::ReadCourse() {
	QFile file("../data/course.txt");
	QFile file_2("../data/assistant.txt");
	QFile file_3("../data/member.txt");
	file.open(QIODevice::ReadOnly | QIODevice::Text);
	file_2.open(QIODevice::ReadOnly | QIODevice::Text);
	file_3.open(QIODevice::ReadOnly | QIODevice::Text);
	QTextStream in(&file);
	QTextStream in_2(&file_2);
	QTextStream in_3(&file_3);
	while (!in.atEnd()) {
		QStringList qsl = in.readLine().split('\t');
		Course course;
		course.ID = qsl[0].toInt();
		course.Name = qsl[1];
		course.Teacher = qsl[2];
		course.MN = (course.MaxNumber = qsl[3]).toInt();
		course.CN = (course.CurrentNumber = qsl[4]).toInt();
		course.Type = qsl[5];
		qsl = in_2.readLine().split('\t');
		course.AssistantQS = qsl[1];
		if (course.AssistantQS != "Null")course.Assistant = course.AssistantQS.split(',');
		if (!in_3.atEnd()) {
			qsl = in_3.readLine().split('\t');
			if (qsl[1] != "Null") {
				QStringList qsl_2 = qsl[1].split(',');
				for (QStringList::iterator it = qsl_2.begin();it != qsl_2.end();it++) {
					course.AddStudent(*it);
				}
			}
		}
		CourseList.insert(course);
	}
	file.close();
	file_2.close();
	file_3.close();
}

void CourseManage::WriteCourse() {
	QFile file("../data/course.txt");
	QFile file_2("../data/assistant.txt");
	QFile file_3("../data/member.txt");
	file.open(QIODevice::WriteOnly | QIODevice::Text);
	file_2.open(QIODevice::WriteOnly | QIODevice::Text);
	file_3.open(QIODevice::WriteOnly | QIODevice::Text);
	QTextStream out(&file);
	QTextStream out_2(&file_2);
	QTextStream out_3(&file_3);
	for (set<Course>::iterator it = CourseList.begin();it != CourseList.end();it++) {
		out << QString("%1").arg(it->ID, 3, 10, QLatin1Char('0')) << '\t' << it->Name << '\t' << it->Teacher << '\t' << (it->MaxNumber.isEmpty() ? it->MaxNumber : QString::number(it->MN)) << '\t' << (it->MaxNumber.isEmpty() ? it->CurrentNumber : QString::number(it->CN)) << '\t' << it->Type << endl;
		out_2 << QString("%1").arg(it->ID, 3, 10, QLatin1Char('0')) << '\t';
		if (!it->Assistant.isEmpty()) {
			out_2 << it->AssistantQS << endl;
		}
		else {
			out_2 << "Null" << endl;
		}
		out_3 << QString("%1").arg(it->ID, 3, 10, QLatin1Char('0')) << '\t' << const_cast<Course&>(*it).getMember() << endl;
	}
	file.close();
	file_2.close();
	file_3.close();
}

void CourseManage::AddCourse(QString Name, QString Teacher, QString MaxNumber, QString Type) {
	Course course;
	set<Course>::iterator it = getNth(CourseList.size());
	it--;
	course.ID = it->ID + 1;
	course.Name = Name;
	course.Teacher = Teacher;
	course.MN = (course.MaxNumber = MaxNumber).toInt();
	if (!MaxNumber.isEmpty())course.CN = (course.CurrentNumber = "0").toInt();
	course.Type = Type;
	CourseList.insert(course);
}

void CourseManage::RemoveNth(int n) {
	set<Course>::iterator it = getNth(n);
	CourseList.erase(it);
}

void CourseManage::ChangeNth(int n, int mode, QString qs) {
	set<Course>::iterator it = getNth(n);
	Change(it, mode, qs);
}

void CourseManage::Change(set<Course>::iterator it, int mode, QString qs) {
	switch (mode) {
	case 2:
		const_cast<Course&>(*it).Teacher = qs;
		break;
	case 3:
		const_cast<Course&>(*it).MN = (const_cast<Course&>(*it).MaxNumber = qs).toInt();
		break;
	}
	WriteCourse();
}

set<Course> CourseManage::getList() {
	return CourseList;
}

set<Course>::iterator CourseManage::getNth(int n) {
	int i = 0;
	set<Course>::iterator it;
	for (it = CourseList.begin();i < n && it != CourseList.end();it++, i++);
	return it;
}

Course CourseManage::getNthCourse(int n) {
	return *getNth(n);
}

void CourseManage::AddToNth(int n, QString student) {
	set<Course>::iterator it = getNth(n);
	const_cast<Course&>(*it).AddStudent(student);
}

void CourseManage::ReadStudentFile(QString ID) {
	QFile file("../data/" + ID + ".txt");
	file.open(QIODevice::ReadOnly | QIODevice::Text);
	QTextStream in(&file);
	while (!in.atEnd()) {
		Course course;
		QStringList qsl = in.readLine().split('\t');
		course.ID = qsl[0].toInt();
		course.Name = qsl[1];
		course.Teacher = qsl[2];
		course.Type = qsl[3];
		course.PersonalAssistant = qsl[4];
		CourseList.insert(course);
	}
	file.close();
}

void CourseManage::WriteStudentFile(QString ID) {
	QFile file("../data/" + ID + ".txt");
	file.open(QIODevice::WriteOnly | QIODevice::Text);
	QTextStream out(&file);
	for (set<Course>::iterator it = CourseList.begin();it != CourseList.end();it++) {
		out << QString("%1").arg(it->ID, 3, 10, QLatin1Char('0')) << '\t' << it->Name << '\t' << it->Teacher << '\t' << it->Type << '\t' << it->PersonalAssistant << endl;
	}
	file.close();
}

void CourseManage::InsertCourse(Course course) {
	CourseList.insert(course);
}

bool CourseManage::Exist(Course course) {
	return CourseList.count(course);
}

bool CourseManage::AddAssistant(QString student, Course course) {
	set<Course>::iterator it = CourseList.find(course);
	if (it->Assistant.count(student)) {
		return 0;
	}
	else {
		if (it->Assistant.isEmpty()) {
			const_cast<Course&>(*it).AssistantQS = student;
		}
		else {
			const_cast<Course&>(*it).AssistantQS += ("," + student);
		}
		const_cast<Course&>(*it).Assistant.push_back(student);
		return 1;
	}
}

void CourseManage::SetAssistant(QString student, Course course) {
	const_cast<Course&>(*CourseList.find(course)).PersonalAssistant = student;
}

int CourseManage::TotalCount() {
	return CourseList.size();
}

int CourseManage::CompulsoryCount() {
	int n = 0;
	for (set<Course>::iterator it = CourseList.begin();it != CourseList.end();it++) {
		if (it->Type == "×¨Òµ¿Î")n++;
	}
	return n;
}

void CourseManage::RemoveFromCourse(QString student, Course course) {
	const_cast<Course&>(*CourseList.find(course)).DeleteStudent(student);
}

bool CourseManage::CourseCheck() {
	return (TotalCount() - CompulsoryCount() >= 2 && CompulsoryCount() >= 2);
}

bool CourseManage::isAssistant(QString student, Course course) {
	return const_cast<Course&>(*CourseList.find(course)).AssistantQS.contains(student);
}

void CourseManage::RemoveAssistant(QString student, Course course) {
	const_cast<Course&>(*CourseList.find(course)).Assistant.removeAll(student);
	QStringList qsl = const_cast<Course&>(*CourseList.find(course)).Assistant;
	QString qs;
	int s = qsl.size();
	for (int i = 0;i < s;i++) {
		if (!i)qs = qsl[i];
		else qs += ("," + qsl[i]);
	}
	const_cast<Course&>(*CourseList.find(course)).AssistantQS = qs;
}

bool CourseManage::NameExist(QString Name) {
	for (set<Course>::iterator it = CourseList.begin();it != CourseList.end();it++) {
		if (it->Name == Name) {
			return 1;
		}
	}
	return 0;
}