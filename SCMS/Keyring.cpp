#include "Keyring.h"

void Keyring::ReadFile() {
	QFile file("../data/student.txt");
	file.open(QIODevice::ReadOnly | QIODevice::Text);
	QTextStream in(&file);
	in.setCodec("UTF-8");
	while (!in.atEnd()) {
		QStringList qsl = in.readLine().split(',');
		AddToKeyring(qsl[0], qsl[1]);
	}
	file.close();
}

void Keyring::WriteFile() {
	QFile file("../data/student.txt");
	file.open(QIODevice::WriteOnly | QIODevice::Text);
	QTextStream out(&file);
	out.setCodec("UTF-8");
	for (map<QString, QString>::iterator it = Key.begin();it != Key.end();it++) {
		out << it->first << ',' << it->second << endl;
	}
	file.close();
}

void Keyring::AddToKeyring(QString ID, QString Password) {
	Key[ID] = Password;
}

bool Keyring::PasswordCheck(QString ID, QString Password) {
	return Key[ID] == Password;
}

bool Keyring::Exist(QString ID) {
	return Key.count(ID);
}