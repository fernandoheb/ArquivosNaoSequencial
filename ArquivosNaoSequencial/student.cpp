#define _CRT_SECURE_NO_WARNINGS

#include "student.h"

Student::Student() :majorLen(10) {
	Personal();
	major = new char[majorLen + 1];
}

Student::Student(char* ssn, char* n, char* c, int y, long s, char* m) : majorLen(11) {
	Personal(ssn, n, c, y, s);
	major = new char[majorLen + 1];
	strcpy(major, m);
}

void Student::writeToFile(fstream& out)  {
	Personal::writeToFile(out);
	out.write(major, majorLen);
}

void Student::readFromFile(fstream& in) {
	Personal::readFromFile(in);
	in.read(major, majorLen);
}

ostream& Student::writeLegibly(ostream& out) {
	Personal::writeLegibly(out);
	major[majorLen] = '\0';
	out << ", especialidade = " << major;
	return out;
}

istream& Student::readFromConsole(istream& in) {
	Personal::readFromConsole(in);
	char s[80];
	cout << "Especialidade: ";
	in.getline(s, 80);
	strncpy(major, s, 9);
	return in;
}

