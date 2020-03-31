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
	void RemoveFromCourse(QString student, Course course);
	void RemoveAssistant(QString student, Course course);
	bool AddAssistant(QString student, Course course);
	bool NameExist(QString Name);
	bool ApplyCheck(QString student);
	bool CourseCheck();
	Course getNthCourse(int n);
	set<Course>CourseSet;

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
	bool isType(QString qs);
	bool isCampus(QString qs);
	bool isTPW(QString qs);
	map<QString, int>ApplyCount;
	set<Course>::iterator getNth(int n);
};