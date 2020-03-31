#include "CourseManage.h"

void CourseManage::InputCourse(bool mode, QString path) {
	if (!mode) {
		NInputCourse(path);
	}
	else {
		JWInputCourse(path);
	}
}

void CourseManage::NInputCourse(QString path) {
	QFile file(path);
	file.open(QIODevice::ReadOnly | QIODevice::Text);
	QTextStream in(&file);
	in.setCodec("UTF-8");
	while (!in.atEnd()) {
		QStringList qsl = in.readLine().split('\t');
		Course course;
		course.ID = qsl[0].toInt();
		course.Name = qsl[1];
		course.Teacher = qsl[2];
		course.MaxNumber = qsl[3];
		course.MN = qsl[3].toInt();
		course.CurrentNumber = "0";
		course.CN = 0;
		if (qsl.length() > 5)course.Type = qsl[5];
		CourseSet.insert(course);
	}
	file.close();
}

void CourseManage::JWInputCourse(QString path) {
	QFile file(path);
	file.open(QIODevice::ReadOnly | QIODevice::Text);
	QTextStream in(&file);
	in.setCodec("UTF-8");
	Course course;
	bool flag = 0;
	while (!in.atEnd()) {
		QStringList qsl = in.readLine().split('\t');
		if (qsl[0][0].isNumber()) {
			if (flag) {
				CourseSet.insert(course);
				Course course_1;
				course = course_1;
			}
			course.ID = CourseSet.size() + 1;
			course.JWID = qsl[0];
			int i = 1;
			course.Name = qsl[i++];
			course.Type = isType(qsl[i]) ? qsl[i++] : "Null";
			course.Type = course.Type.isEmpty() ? "Null" : course.Type;
			course.College = qsl[i][0].isNumber() ? "Null" : qsl[i++];
			course.College = course.College.isEmpty() ? "Null" : course.College;
			course.Score = qsl[i++];
			course.Hour = qsl[i++];
			if (i == qsl.size()) {
				flag = 1;
				course.Campus = course.Teacher = course.TPWQS = "Null";
				continue;
			}
			course.Campus = (isCampus(qsl[i]) && !qsl[i].isEmpty()) ? qsl[i++] : "Null";
			course.Campus = course.Campus.isEmpty() ? "Null" : course.Campus;
			if (i == qsl.size()) {
				flag = 1;
				course.Teacher = course.TPWQS = "Null";
				continue;
			}
			course.Teacher = isTPW(qsl[i]) ? "Null" : qsl[i++];
			course.Teacher = course.Teacher.isEmpty() ? "Null" : course.Teacher;
			if (i == qsl.size()) {
				flag = 1;
				course.TPWQS = "Null";
				continue;
			}
			if (!qsl[i].isEmpty()) {
				course.TPWList.push_back(qsl[i]);
				course.TPWQS += (qsl[i] + ';');
			}
			flag = 1;
		}
		else {
			course.TPWList.push_back(qsl[0]);
			course.TPWQS += (qsl[0] + ';');
		}
	}
	file.close();
}

bool CourseManage::isType(QString qs) {
	return qs == QString::fromLocal8Bit("通修") || qs == QString::fromLocal8Bit("核心") || qs == QString::fromLocal8Bit("选修") || qs == QString::fromLocal8Bit("通识") || qs == QString::fromLocal8Bit("平台") || qs == QString::fromLocal8Bit("共通");
}

void CourseManage::WriteFile(bool mode) {
	if (!mode) {
		NWriteFile();
	}
	else {
		JWWriteFile();
	}
}

void CourseManage::ReadFile(bool mode) {
	if (!mode) {
		NReadFile();
	}
	else {
		JWReadFile();
	}
}

void CourseManage::NReadFile() {
	QFile file("../data/course.txt");
	QFile file_2("../data/assistant.txt");
	QFile file_3("../data/member.txt");
	file.open(QIODevice::ReadOnly | QIODevice::Text);
	file_2.open(QIODevice::ReadOnly | QIODevice::Text);
	file_3.open(QIODevice::ReadOnly | QIODevice::Text);
	QTextStream in(&file);
	QTextStream in_2(&file_2);
	QTextStream in_3(&file_3);
	in.setCodec("UTF-8");
	in_2.setCodec("UTF-8");
	in_3.setCodec("UTF-8");
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
		CourseSet.insert(course);
	}
	file.close();
	file_2.close();
	file_3.close();
}

void CourseManage::JWReadFile() {
	QFile file("../data/jwcourse.txt");
	QFile file_2("../data/jwassistant.txt");
	QFile file_3("../data/jwmember.txt");
	file.open(QIODevice::ReadOnly | QIODevice::Text);
	file_2.open(QIODevice::ReadOnly | QIODevice::Text);
	file_3.open(QIODevice::ReadOnly | QIODevice::Text);
	QTextStream in(&file);
	QTextStream in_2(&file_2);
	QTextStream in_3(&file_3);
	in.setCodec("UTF-8");
	in_2.setCodec("UTF-8");
	in_3.setCodec("UTF-8");
	while (!in.atEnd()) {
		QStringList qsl = in.readLine().split('\t');
		QTextStream in(&file);
		Course course;
		int i = 0;
		course.ID = qsl[i++].toInt();
		course.JWID = qsl[i++];
		course.Name = qsl[i++];
		course.Type = qsl[i++];
		course.College = qsl[i++];
		course.Score = qsl[i++];
		course.Hour = qsl[i++];
		course.Campus = qsl[i++];
		course.Teacher = qsl[i++];
		course.TPWQS = qsl[i];
		if (qsl[i] != "Null") {
			course.TPWList = qsl[i].split(';');
		}
		qsl = in_2.readLine().split('\t');
		course.AssistantQS = qsl[1];
		if (course.AssistantQS != "Null") {
			course.Assistant = course.AssistantQS.split(',');
		}
		if (!in_3.atEnd()) {
			qsl = in_3.readLine().split('\t');
			if (qsl[1] != "Null") {
				QStringList qsl_2 = qsl[1].split(',');
				for (QStringList::iterator it = qsl_2.begin();it != qsl_2.end();it++) {
					course.AddStudent(*it);
				}
			}
		}
		CourseSet.insert(course);
	}
	file.close();
	file_2.close();
	file_3.close();
}

void CourseManage::NWriteFile() {
	QFile file("../data/course.txt");
	QFile file_2("../data/assistant.txt");
	QFile file_3("../data/member.txt");
	file.open(QIODevice::WriteOnly | QIODevice::Text);
	file_2.open(QIODevice::WriteOnly | QIODevice::Text);
	file_3.open(QIODevice::WriteOnly | QIODevice::Text);
	QTextStream out(&file);
	QTextStream out_2(&file_2);
	QTextStream out_3(&file_3);
	out.setCodec("UTF-8");
	out_2.setCodec("UTF-8");
	out_3.setCodec("UTF-8");
	for (set<Course>::iterator it = CourseSet.begin();it != CourseSet.end();it++) {
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

void CourseManage::JWWriteFile() {
	QFile file("../data/jwcourse.txt");
	QFile file_2("../data/jwassistant.txt");
	QFile file_3("../data/jwmember.txt");
	file.open(QIODevice::WriteOnly | QIODevice::Text);
	file_2.open(QIODevice::WriteOnly | QIODevice::Text);
	file_3.open(QIODevice::WriteOnly | QIODevice::Text);
	QTextStream out(&file);
	QTextStream out_2(&file_2);
	QTextStream out_3(&file_3);
	out.setCodec("UTF-8");
	out_2.setCodec("UTF-8");
	out_3.setCodec("UTF-8");
	for (set<Course>::iterator it = CourseSet.begin();it != CourseSet.end();it++) {
		out << QString("%1").arg(it->ID, 3, 10, QLatin1Char('0')) << '\t' << it->JWID << '\t' << it->Name << '\t' << it->Type << '\t' << it->College << "\t" << it->Score << '\t' << it->Hour << '\t' << it->Campus << '\t' << it->Teacher << '\t';
		if (!it->TPWList.isEmpty()) {
			out << it->TPWQS << endl;
		}
		else {
			out << "Null" << endl;
		}
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
	set<Course>::iterator it = getNth(CourseSet.size());
	it--;
	course.ID = it->ID + 1;
	course.Name = Name;
	course.Teacher = Teacher;
	course.MN = (course.MaxNumber = MaxNumber).toInt();
	if (!MaxNumber.isEmpty())course.CN = (course.CurrentNumber = "0").toInt();
	course.Type = Type;
	CourseSet.insert(course);
}

void CourseManage::RemoveNth(int n) {
	set<Course>::iterator it = getNth(n);
	CourseSet.erase(it);
}

void CourseManage::ChangeNth(int n, bool cmode, QString qs) {
	set<Course>::iterator it = getNth(n);
	Change(it, cmode, qs);
}

void CourseManage::Change(set<Course>::iterator it, bool cmode, QString qs) {
	switch (cmode) {
	case 0:
		const_cast<Course&>(*it).Teacher = qs;
		break;
	case 1:
		const_cast<Course&>(*it).MN = (const_cast<Course&>(*it).MaxNumber = qs).toInt();
		break;
	}
}

set<Course>::iterator CourseManage::getNth(int n) {
	int i = 0;
	set<Course>::iterator it;
	for (it = CourseSet.begin();i < n && it != CourseSet.end();it++, i++);
	return it;
}

Course CourseManage::getNthCourse(int n) {
	return *getNth(n);
}

void CourseManage::AddToNth(int n, QString student) {
	set<Course>::iterator it = getNth(n);
	const_cast<Course&>(*it).AddStudent(student);
}

void CourseManage::ReadStudentFile(bool mode, QString student) {
	if (!mode) {
		NReadStudentFile(student);
	}
	else {
		JWReadStudentFile(student);
	}
}

void CourseManage::WriteStudentFile(bool mode, QString student) {
	if (!mode) {
		NWriteStudentFile(student);
	}
	else {
		JWWriteStudentFile(student);
	}
}

void CourseManage::NReadStudentFile(QString ID) {
	QFile file("../data/" + ID + ".txt");
	file.open(QIODevice::ReadOnly | QIODevice::Text);
	QTextStream in(&file);
	in.setCodec("UTF-8");
	while (!in.atEnd()) {
		Course course;
		QStringList qsl = in.readLine().split('\t');
		course.ID = qsl[0].toInt();
		course.Name = qsl[1];
		course.Teacher = qsl[2];
		course.Type = qsl[3];
		course.PersonalAssistant = qsl[4];
		CourseSet.insert(course);
	}
	file.close();
}

void CourseManage::JWReadStudentFile(QString ID) {
	QFile file("../data/jw" + ID + ".txt");
	file.open(QIODevice::ReadOnly | QIODevice::Text);
	QTextStream in(&file);
	in.setCodec("UTF-8");
	while (!in.atEnd()) {
		QStringList qsl = in.readLine().split('\t');
		QTextStream in(&file);
		Course course;
		int i = 0;
		course.ID = qsl[i++].toInt();
		course.JWID = qsl[i++];
		course.Name = qsl[i++];
		course.Type = qsl[i++];
		course.College = qsl[i++];
		course.Score = qsl[i++];
		course.Hour = qsl[i++];
		course.Campus = qsl[i++];
		course.Teacher = qsl[i++];
		course.TPWQS = qsl[i];
		if (qsl[i] != "Null") {
			course.TPWList = qsl[i].split(';');
		}
		course.PersonalAssistant = qsl[++i];
		CourseSet.insert(course);
	}
	file.close();
}

void CourseManage::NWriteStudentFile(QString ID) {
	QFile file("../data/" + ID + ".txt");
	file.open(QIODevice::WriteOnly | QIODevice::Text);
	QTextStream out(&file);
	out.setCodec("UTF-8");
	for (set<Course>::iterator it = CourseSet.begin();it != CourseSet.end();it++) {
		out << QString("%1").arg(it->ID, 3, 10, QLatin1Char('0')) << '\t' << it->Name << '\t' << it->Teacher << '\t' << it->Type << '\t' << it->PersonalAssistant << endl;
	}
	file.close();
}

void CourseManage::JWWriteStudentFile(QString ID) {
	QFile file("../data/jw" + ID + ".txt");
	file.open(QIODevice::WriteOnly | QIODevice::Text);
	QTextStream out(&file);
	out.setCodec("UTF-8");
	for (set<Course>::iterator it = CourseSet.begin();it != CourseSet.end();it++) {
		out << QString("%1").arg(it->ID, 3, 10, QLatin1Char('0')) << '\t' << it->JWID << '\t' << it->Name << '\t' << it->Type << '\t' << it->College << "\t" << it->Score << '\t' << it->Hour << '\t' << it->Campus << '\t' << it->Teacher << '\t';
		if (!it->TPWList.isEmpty()) {
			out << it->TPWQS << '\t';
		}
		else {
			out << "Null" << '\t';
		}
		out << it->PersonalAssistant << endl;
	}
	file.close();
}

void CourseManage::InsertCourse(Course course) {
	CourseSet.insert(course);
}

bool CourseManage::AddAssistant(QString student, Course course) {
	set<Course>::iterator it = CourseSet.find(course);
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
	const_cast<Course&>(*CourseSet.find(course)).PersonalAssistant = student;
}

int CourseManage::TotalCount() {
	return CourseSet.size();
}

int CourseManage::CompulsoryCount() {
	int n = 0;
	for (set<Course>::iterator it = CourseSet.begin();it != CourseSet.end();it++) {
		if (it->Type == "专业课")n++;
	}
	return n;
}

void CourseManage::RemoveFromCourse(QString student, Course course) {
	const_cast<Course&>(*CourseSet.find(course)).DeleteStudent(student);
}

bool CourseManage::CourseCheck() {
	return (TotalCount() - CompulsoryCount() >= 2 && CompulsoryCount() >= 2);
}

void CourseManage::RemoveAssistant(QString student, Course course) {
	const_cast<Course&>(*CourseSet.find(course)).Assistant.removeAll(student);
	QStringList qsl = const_cast<Course&>(*CourseSet.find(course)).Assistant;
	QString qs;
	int s = qsl.size();
	for (int i = 0;i < s;i++) {
		if (!i)qs = qsl[i];
		else qs += ("," + qsl[i]);
	}
	const_cast<Course&>(*CourseSet.find(course)).AssistantQS = qs;
}

bool CourseManage::NameExist(QString Name) {
	for (set<Course>::iterator it = CourseSet.begin();it != CourseSet.end();it++) {
		if (it->Name == Name) {
			return 1;
		}
	}
	return 0;
}

bool CourseManage::ApplyCheck(QString student) {
	for (set<Course>::iterator it = CourseSet.begin();it != CourseSet.end();it++) {
		if (it->AssistantQS.contains(student)) {
			if (!ApplyCount.count(student)) {
				ApplyCount[student] = 1;
			}
			else {
				ApplyCount[student]++;
			}
		}
	}
	return ApplyCount[student] < 2;
}

bool CourseManage::isCampus(QString qs) {
	return qs == QString::fromLocal8Bit("仙林校区") || qs == QString::fromLocal8Bit("鼓楼校区");
}

bool CourseManage::isTPW(QString qs) {
	return qs.mid(0, 1) == QString::fromLocal8Bit("第");
}