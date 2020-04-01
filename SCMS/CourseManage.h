#pragma once

#include<set>
#include<map>
#include<string>
#include<stack>
#include<algorithm>

#include "qfile.h"
#include "qtextcodec.h"
#include "qtextstream.h"
#include "qfiledialog.h"
#include "qstring.h"
#include "qstringlist.h"
#include "qdebug.h"

#include "Course.h"

using namespace std;

class CourseManage {
public:
	int TotalCount();
	int CompulsoryCount();
	int TypeCount(int mode);
	int MaxCount;
	void InputCourse(bool mode, QString path);
	void ReadFile(bool mode);
	void WriteFile(bool mode);
	void ReadStudentFile(bool mode, QString ID);
	void WriteStudentFile(bool mode, QString ID);
	void InsertCourse(Course course);
	void AddToNth(int n, QString student);
	void RemoveNth(int n);
	void ChangeNth(int n, bool mode, QString qs);
	void AddCourse(QString Name, QString Teacher, QString MaxNumber, QString Type);
	void SetAssistant(QString student, Course course);
	void Connect(QString qs, QString qs_2);
	void RemoveFromCourse(QString student, Course course);
	void RemoveAssistant(QString student, Course course);
	bool AddAssistant(QString student, Course course);
	void NewConnect(QString qs, QString qs_2);
	bool NameExist(QString Name);
	bool ApplyCheck(QString student);
	bool CourseCheck();
	void ReadConnection();
	void WriteConnection();
	Course getNthCourse(int n);
	set<Course>CourseSet;
	set<Course>CourseSet_2;
	set<stack<Course>>getSchedule();
	map<QString, QString>Father;

private:
	void NInputCourse(QString path);
	void JWInputCourse(QString path);
	void NWriteFile();
	void JWWriteFile();
	void NReadFile();
	void JWReadFile();
	void NWriteStudentFile(QString ID);
	void JWWriteStudentFile(QString ID);
	void NReadStudentFile(QString ID);
	void JWReadStudentFile(QString ID);
	void Change(set<Course>::iterator it, bool mode, QString qs);
	void Search(set<Course>::iterator it);
	void Init();
	void AddToSchedule(Course course, bool mode);
	bool ScheduleCheck(Course course);
	bool isType(QString qs);
	bool isCampus(QString qs);
	bool isTPW(QString qs);
	bool Table[5][13];
	QString getFather(QString qs);
	QString ConnectList;
	map<QString, int>ApplyCount;
	map<QString, set<QString>>Connection;
	set<Course>getSubstance(QString qs);
	set<Course>getCourseJWID(QString qs);
	set<stack<Course>>TimeTable;
	set<QString>getConnection(QString qs);
	set<Course>::iterator getNth(int n);
	stack<Course>Temp;
};