#define _CRT_SECURE_NO_WARNINGS

#include "personal.h"
#include <iostream>
#include <cstring>





Personal::Personal() : nameLen(10), cityLen(10) {
	name = new char[nameLen + 1];
	city = new char[cityLen + 1];
}

//SSN, Name, City, Year, Salary
Personal::Personal(char* ssn, char* n, char* c, int y, long s) : nameLen(10), cityLen(10) {
	name = new char[nameLen + 1];
	city = new char[cityLen + 1];
	strcpy(SSN, ssn);
	strcpy(name, n);
	strcpy(city, c);
	year = y;
	salary = s;
}


void Personal::writeToFile(fstream& out)  {
	
	out.write(SSN, 9);
	out.write(name, nameLen);
	out.write(city, cityLen);
	out.write(reinterpret_cast <char*>(&year), sizeof(int));
	out.write(reinterpret_cast <char*>(&salary), sizeof(long));
}

void Personal::readFromFile(fstream& in) {
	
	in.read(SSN, 9);
	in.read(name, nameLen);
	in.read(city, cityLen);
	in.read(reinterpret_cast<char*>(&year), sizeof(int));
	in.read(reinterpret_cast<char*>(&salary), sizeof(long));
}

void Personal::readKey() {
	char s[80];
	cout << "Digite o SSN (9)";
	cin.getline(s, 80);
	strncpy_s(SSN, s, 9);
}

ostream& Personal::writeLegibly(ostream& out) {
	SSN[9] = name[nameLen] = city[cityLen] = '\0';
	out << "SSN = " << SSN << ", Nome = " << name << ", Cidade = " << city << ", Ano = " << year << ", Salario = " << salary;
	return out;
}

istream& Personal::readFromConsole(istream& in) {
	SSN[9] = name[nameLen] = city[cityLen] = '\0';
	char s[80];
	cout << "SSN: ";
	in.getline(s, 80);
	strncpy(SSN, s, 9);
	cout << "Nome: ";
	in.getline(s, 80);
	strncpy(name, s, nameLen);
	cout << "Cidade: ";
	in.getline(s, 80);
	strncpy(city, s, cityLen);
	cout << "Ano Nascimento: ";
	in >> year;
	cout << "Salario: ";
	in >> salary;
	in.ignore();
	return in;
}
		 
