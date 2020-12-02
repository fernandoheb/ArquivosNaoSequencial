#include <fstream>
#include <cstring>
#include <iostream>

#include "personal.h"
#include "student.h"
#include "database.h"

template<class T>
Database<T>::Database() {
}

template<class T>
void Database<T>::add( T& d) {	
	database.open(fName, ios::in | ios::out | ios::binary);
	if (!database) {
		cout << " -> Erro ao abrir arquivo." << endl;
		return;
	}
	database.seekg(0, ios::end);
	d.writeToFile(database);
	database.close();
}

template<class T>
void Database<T>::modify(const T& d) {
	T tmp;
	database.open(fName, ios::in | ios::out | ios::binary);
	if (!database) {
		cout << " -> Erro ao abrir arquivo." << endl;
		return ;
	}
	while (!database.eof()) {
		tmp.readFromFile(database);
		if (tmp == d) {  //sobrecarregado ==
			cin >> tmp; //sobrecarregado >>
			database.seekp(-d.size(), ios::cur);
			tmp.writeToFile(database);
			database.close();
			return;
		}
	}
	database.close();
	cout << "O registro a ser modificado não está no banco de dados \n";
}

template<class T>
bool Database<T>::find(const T& d) {
	T tmp;
	database.open(fName, ios::in | ios::out | ios::binary);//ios:: in |
	if (!database) {
		cout << " -> Erro ao abrir arquivo." << endl;
		return false;
	}
	while (!database.eof()) {
		tmp.readFromFile(database);
		if (tmp == d) { // sobrecarregado == 
			database.close();
			return true;
		}
	}
	database.close();
	return false;
}

template<class T>
bool Database<T>::fileExists(char* fName)
{
	fstream fs;
	fs.open(fName, std::fstream::in | std::fstream::out | std::fstream::app);
	if(fs)
		return true;
	return false;
}


template<class T>
ostream& Database<T>::print(ostream& out) {
	T tmp;
	database.open(fName, ios::in | ios::out | ios::binary);
	while (true) {
		tmp.readFromFile(database);
		if (database.eof())
			break;
			out << tmp << endl; //sobrecarregado <<
	}
	database.close();
	return out;
}

template<class T>
void Database<T>::run(){
	cout << " Nome do arquivo: ";
	cin >> fName;
	fileExists(fName);

	char option[5];
	T rec;
	cout << "1. Adicionar  2. Procurar 3. Modificar Registro; 4 Sair\n";
	cout << "Entre uma opcao";
	cin.getline(option, 4); //obtem o '\n';
	while (cin.getline(option, 4)) {
		if (*option == '1') {
			cin >> rec;
			add(rec);
		}
		else if (*option == '2') {
			rec.readKey();
			cout << "o registro ";
			if (find(rec) == false)
				cout << "nao ";
			cout << "esta no banco de dados\n";
		}
		else if (*option == '3') {
			rec.readKey();
			modify(rec);
		}
		else if (*option != '4')
			cout << "Opcao nao reconhecida\n";
		else return;
		cout << *this;
		cout << "Entre com uma opcao";
	}
}



int main() {
	Database<Personal>().run();
	//Database<Student>().run();
	return 0;
}



