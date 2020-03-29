#pragma once

#include<set>
#include<map>
#include<string>

#include "qfile.h"
#include "qtextcodec.h"
#include "qtextstream.h"
#include "qfiledialog.h"
#include "qstring.h"
#include "qstringlist.h"

#include "Course.h"

using namespace std;

class CourseManage {
public:
	int TotalCount();
	int CompulsoryCount();
	void InputCourse(QString path);
	void ReadCourse();
	void WriteCourse();
	void ReadStudentFile(QString ID);
	void WriteStudentFile(QString ID);
	void InsertCourse(Course course);
	void AddToNth(int n, QString student);
	void RemoveNth(int n);
	void ChangeNth(int n, int mode, QString qs);
	void Change(set<Course>::iterator it, int mode, QString qs);
	void AddCourse(QString Name, QString Teacher, QString MaxNumber, QString Type);
	void SetAssistant(QString student, Course course);
	void RemoveFromCourse(QString student, Course course);
	void RemoveAssistant(QString student, Course course);
	bool AddAssistant(QString student, Course course);
	bool isAssistant(QString student, Course course);
	bool NameExist(QString Name);
	bool Exist(Course course);
	bool ApplyCheck(QString student);
	bool CourseCheck();
	Course getNthCourse(int n);
	set<Course>getList();
	set<Course>::iterator getNth(int n);

private:
	set<Course>CourseList;
	map<QString, int>ApplyCount;
};