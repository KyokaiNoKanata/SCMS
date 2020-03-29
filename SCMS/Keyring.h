#pragma once

#include<map>
#include<vector>

#include "qstring.h"
#include "qstringlist.h"
#include "qfile.h"
#include "qiodevice.h"
#include "qtextstream.h"
#include "qtextcodec.h"

using namespace std;

class Keyring {
public:
	void ReadFile();
	void WriteFile();
	void AddToKeyring(QString ID, QString Password);
	bool PasswordCheck(QString ID, QString Password);
	bool Exist(QString ID);

private:
	map<QString, QString>Key;
};