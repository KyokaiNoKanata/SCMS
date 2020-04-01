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
				for (int i = 0;i < course.TPWList.size();i++) {
					int w;
					int s;
					int e;
					QStringList qsl_2 = course.TPWList[i].split(' ');
					if (qsl_2[0] == QString::fromLocal8Bit("周一")) {
						w = 0;
					}
					else if (qsl_2[0] == QString::fromLocal8Bit("周二")) {
						w = 1;
					}
					else if (qsl_2[0] == QString::fromLocal8Bit("周三")) {
						w = 2;
					}
					else if (qsl_2[0] == QString::fromLocal8Bit("周四")) {
						w = 3;
					}
					else if (qsl_2[0] == QString::fromLocal8Bit("周五")) {
						w = 4;
					}
					else if (qsl_2[0] == QString::fromLocal8Bit("周六")) {
						w = 5;
					}
					else if (qsl_2[0] == QString::fromLocal8Bit("周日")) {
						w = 6;
					}
					course.DayList.push_back(w);
					course.PList.push_back(qsl_2[2]);
					QStringList qsl_3 = qsl_2[1].mid(1, qsl_2[1].size() - 2).split('-');
					s = qsl_3[0].toInt();
					course.SList.push_back(s);
					e = qsl_3[1].toInt();
					course.EList.push_back(e);
				}
				CourseSet.insert(course);
				Course course_1;
				course = course_1;
			}
			course.ID = CourseSet.size() + 1;
			int i = 0;
			course.JWID = qsl[i++];
			Father[course.JWID] = course.JWID;
			Connection[course.JWID].insert(course.JWID);
			course.Name = qsl[i++];
			course.Type = qsl[i].isEmpty() ? "Null" : qsl[i];
			i++;
			course.College = qsl[i].isEmpty() ? "Null" : qsl[i];
			i++;
			course.Score = qsl[i++];
			course.Hour = qsl[i++];
			course.Campus = qsl[i].isEmpty() ? "Null" : qsl[i];
			i++;
			course.Teacher = qsl[i].isEmpty() ? "Null" : qsl[i];
			i++;
			if (i == qsl.size()) {
				course.TPWQS = "NULL";
				flag = 1;
				continue;
			}
			if (!qsl[i].isEmpty()) {
				course.TPWList.push_back(qsl[i]);
				course.TPWQS += (qsl[i] + ';');
			}
			else {
				course.TPWQS = "Null";
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
		Course course;
		int i = 0;
		course.ID = qsl[i++].toInt();
		course.JWID = qsl[i++];
		Father[course.JWID] = course.JWID;
		Connection[course.JWID].insert(course.JWID);
		course.Name = qsl[i++];
		course.Type = qsl[i++];
		course.College = qsl[i++];
		course.Score = qsl[i++];
		course.Hour = qsl[i++];
		course.Campus = qsl[i++];
		course.Teacher = qsl[i++];
		course.TPWQS = qsl[i];
		if (qsl[i] != "Null") {
			course.TPWList = qsl[i].mid(0, qsl[i].size() - 1).split(';');
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
		for (int i = 0;i < course.TPWList.size();i++) {
			int w;
			int s;
			int e;
			QStringList qsl_2 = course.TPWList[i].split(' ');
			if (qsl_2[0] == QString::fromLocal8Bit("周一")) {
				w = 0;
			}
			else if (qsl_2[0] == QString::fromLocal8Bit("周二")) {
				w = 1;
			}
			else if (qsl_2[0] == QString::fromLocal8Bit("周三")) {
				w = 2;
			}
			else if (qsl_2[0] == QString::fromLocal8Bit("周四")) {
				w = 3;
			}
			else if (qsl_2[0] == QString::fromLocal8Bit("周五")) {
				w = 4;
			}
			else if (qsl_2[0] == QString::fromLocal8Bit("周六")) {
				w = 5;
			}
			else if (qsl_2[0] == QString::fromLocal8Bit("周日")) {
				w = 6;
			}
			course.DayList.push_back(w);
			course.PList.push_back(qsl_2[2]);
			QStringList qsl_3 = qsl_2[1].mid(1, qsl_2[1].size() - 2).split('-');
			s = qsl_3[0].toInt();
			course.SList.push_back(s);
			e = qsl_3[1].toInt();
			course.EList.push_back(e);
		}
		CourseSet.insert(course);
	}
	file.close();
	file_2.close();
	file_3.close();
	ReadConnection();
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
	WriteConnection();
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
		Father[course.JWID] = course.JWID;
		Connection[course.JWID].insert(course.JWID);
		course.Name = qsl[i++];
		course.Type = qsl[i++];
		course.College = qsl[i++];
		course.Score = qsl[i++];
		course.Hour = qsl[i++];
		course.Campus = qsl[i++];
		course.Teacher = qsl[i++];
		course.TPWQS = qsl[i];
		if (qsl[i] != "Null") {
			course.TPWList = qsl[i].mid(0, qsl[i].size() - 1).split(';');
		}
		course.PersonalAssistant = qsl[++i];
		for (int i = 0;i < course.TPWList.size();i++) {
			int w;
			int s;
			int e;
			QStringList qsl_2 = course.TPWList[i].split(' ');
			if (qsl_2[0] == QString::fromLocal8Bit("周一")) {
				w = 0;
			}
			else if (qsl_2[0] == QString::fromLocal8Bit("周二")) {
				w = 1;
			}
			else if (qsl_2[0] == QString::fromLocal8Bit("周三")) {
				w = 2;
			}
			else if (qsl_2[0] == QString::fromLocal8Bit("周四")) {
				w = 3;
			}
			else if (qsl_2[0] == QString::fromLocal8Bit("周五")) {
				w = 4;
			}
			else if (qsl_2[0] == QString::fromLocal8Bit("周六")) {
				w = 5;
			}
			else if (qsl_2[0] == QString::fromLocal8Bit("周日")) {
				w = 6;
			}
			course.DayList.push_back(w);
			course.PList.push_back(qsl_2[2]);
			QStringList qsl_3 = qsl_2[1].mid(1, qsl_2[1].size() - 2).split('-');
			s = qsl_3[0].toInt();
			course.SList.push_back(s);
			e = qsl_3[1].toInt();
			course.EList.push_back(e);
		}
		CourseSet.insert(course);
	}
	file.close();
	ReadConnection();
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
	WriteConnection();
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
	return qs.mid(0, 1) == QString::fromLocal8Bit("周");
}

int CourseManage::TypeCount(int mode) {
	int n = 0;
	QString qs;
	switch (mode)
	{
	case 1:
		qs = QString::fromLocal8Bit("核心");
		break;
	case 2:
		qs = QString::fromLocal8Bit("共通");
		break;
	case 3:
		qs = QString::fromLocal8Bit("平台");
		break;
	case 4:
		qs = QString::fromLocal8Bit("通识");
		break;
	case 5:
		qs = QString::fromLocal8Bit("通修");
		break;
	case 6:
		qs = QString::fromLocal8Bit("选修");
	}
	for (set<Course>::iterator it = CourseSet.begin();it != CourseSet.end();it++) {
		if (it->Type == qs) {
			n++;
		}
	}
	return n;
}

void CourseManage::Init() {
	for (int i = 0;i <= 4;i++) {
		for (int j = 0;j <= 12;j++) {
			Table[i][j] = 0;
		}
	}
}

set<stack<Course>>CourseManage::getSchedule(bool mode) {
	Init();
	TimeTable.clear();
	MaxCount = 0;
	set<Course>::iterator it = CourseSet.begin();
	Search(mode, it);
	return TimeTable;
}

void CourseManage::AddToSchedule(Course course, bool mode) {
	for (int i = 0;i < course.DayList.size();i++) {
		for (int j = course.SList[i] - 1;j < course.EList[i];j++) {
			Table[course.DayList[i]][j] = mode;
		}
	}
}

bool CourseManage::ScheduleCheck(Course course) {
	for (int i = 0;i < course.DayList.size();i++) {
		for (int j = course.SList[i] - 1;j < course.EList[i];j++) {
			if (Table[course.DayList[i]][j]) {
				return 0;
			}
		}
	}
	return 1;
}

QString CourseManage::getFather(QString qs) {
	if (Father[qs] == qs) {
		return qs;
	}
	else {
		Father[qs] = getFather(Father[qs]);
		for (set<QString>::iterator it = Connection[qs].begin();it != Connection[qs].end();it++) {
			Connection[Father[qs]].insert(*it);
		}
		return Father[qs];
	}
}

void CourseManage::Connect(QString qs, QString qs_2) {
	Father[qs_2] = getFather(qs);
	for (set<QString>::iterator it = Connection[qs_2].begin();it != Connection[qs_2].end();it++) {
		Connection[Father[qs]].insert(*it);
	}
}

void CourseManage::Search(bool mode, set<Course>::iterator it) {

	if (it == CourseSet.end()) {
		TimeTable.insert(Temp);
		int s = Temp.size();
		MaxCount = max(MaxCount, s);
		return;
	}
	else {
		if (mode) {
			set<Course>sc = getSubstance(it->JWID);
			it++;
			Search(1, it);
			for (set<Course>::iterator it_2 = sc.begin();it_2 != sc.end();it_2++) {
				if (ScheduleCheck(*it_2) && it_2->TPWQS != "Null") {
					AddToSchedule(*it_2, 1);
					Temp.push(*it_2);
					Search(1, it);
					Temp.pop();
					AddToSchedule(*it_2, 0);
				}
			}
		}
		else {
			set<Course>::iterator it_2 = it;
			if (ScheduleCheck(*it)) {
				AddToSchedule(*it, 1);
				Temp.push(*it);
				it++;
				Search(0, it);
				Temp.pop();
				AddToSchedule(*it_2, 0);
				Search(0, it);
			}
			else {
				it++;
				Search(0, it);
			}
		}
	}
}

set<QString>CourseManage::getConnection(QString qs) {
	set<QString>sqs;
	for (set<QString>::iterator it = Connection[getFather(qs)].begin();it != Connection[getFather(qs)].end();it++) {
		sqs.insert(*it);
	}
	return sqs;
}

set<Course>CourseManage::getSubstance(QString qs) {
	set<Course>sc;
	set<QString>sqs = getConnection(qs);
	for (set<QString>::iterator it = sqs.begin();it != sqs.end();it++) {
		set<Course>sc_2 = getCourseJWID(*it);
		sc.insert(sc_2.begin(), sc_2.end());
	}
	return sc;
}

set<Course>CourseManage::getCourseJWID(QString qs) {
	set<Course>sc;
	for (set<Course>::iterator it = CourseSet_2.begin();it != CourseSet_2.end();it++) {
		if (it->JWID == qs) {
			sc.insert(*it);
		}
	}
	return sc;
}

void CourseManage::ReadConnection() {
	QFile file("../data/jwconnection.txt");
	file.open(QIODevice::ReadOnly | QIODevice::Text);
	QTextStream in(&file);
	in.setCodec("UTF-8");
	ConnectList = in.readAll();
	QStringList qsl = ConnectList.split(' ');
	for (int i = 0;i < ConnectList.size() - 1;i++) {
		Connect(qsl[i], qsl[i++]);
	}
	file.close();
}

void CourseManage::WriteConnection() {
	QFile file("../data/jwconnection.txt");
	file.open(QIODevice::WriteOnly | QIODevice::Text);
	QTextStream out(&file);
	out.setCodec("UTF-8");
	out << ConnectList;
	file.close();
}

void CourseManage::NewConnect(QString qs, QString qs_2) {
	Connect(qs, qs_2);
	if (ConnectList.isEmpty()) {
		ConnectList = qs + ' ' + qs_2;
	}
	else {
		ConnectList += (' ' + qs + ' ' + qs_2);
	}
}