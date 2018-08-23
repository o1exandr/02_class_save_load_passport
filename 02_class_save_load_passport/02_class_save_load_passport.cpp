/*
Завдання 2.
До раніше розроблених класів по темі успадкування (Паспорт - Іноземний Паспорт) 
додати можливості збереження(завантаження) екземплярів класів у(з) текстових файлових потоках.

*/

#include "stdafx.h"
#include <iostream> 
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class Passport
{
protected:

	string name;
	string id;

public:

	Passport(string name = "unknown", string id = "XX000000") :name(name), id(id)
	{

	}

	void setName(string n)
	{
		name = n;
	}

	string getName() const
	{
		return name;
	}

	void setId(string i)
	{
		id = i;
	}

	string getId() const
	{
		return id;
	}

	void print()
	{
		cout << "\nName:\t" << getName() << "\t\nID_Ukr:\t\t" << getId() << "\n";
	}

};

struct Visa
{
	string country;
	string date;
};

class ForeignPassport : public Passport
{
	vector<Visa> visas;
	string fId;

public:


	ForeignPassport(Passport p, string fId) :Passport(p), fId(fId)
	{
	}

	ForeignPassport() 
	{
	}

	void setFid(string i)
	{
		fId = i;
	}

	string getFid() const
	{
		return fId;
	}

	int getSize() const
	{
		return visas.size();
	}


	void addVisa(Visa visa)
	{
		visas.push_back(visa);
	}

	void addVisa(string country, string date)
	{
		Visa tmp;
		tmp.country = country;
		tmp.date = date;
		visas.push_back(tmp);
	}

	vector<Visa> getVisas()
	{
		return visas;
	}

	void print()
	{
		Passport::print();
		cout << "ID_Foreign:\t" << id << endl;
		if (visas.size() == 0)
			cout << "Don't have visas\n";
		else
		{
			cout << "Visas:\n";
			int count = 1;
			for (Visa& v : visas)
			{
				cout << "(" << count++ << ") " << v.country << "\t" << v.date << endl;
			}
		}
		//cout << "____________________________\n";
	}


	friend ostream & operator << (ostream &os, const ForeignPassport & fp);
	friend istream & operator >> (istream & is, ForeignPassport & fp);

};

ostream & operator << (ostream &os, const ForeignPassport & fp)
{
	os << fp.name << endl << fp.id << endl << fp.getFid() << endl;
	for (const Visa& v : fp.visas)
	{
		os << v.country << "\t" << v.date << endl;
	}
	return os;
}
istream & operator >> (istream & is, ForeignPassport & fp)
{

	is >> fp.name >> fp.id >> fp.fId;
	for (Visa& v : fp.getVisas())
	{
		is >> v.country >> v.date;
	}
	return is;
}

int main()
{
	fstream file("02_database.txt", ios::out | ios::trunc | ios::in);
	
	if (!file)
	{
		cout << "Error\n";
		return EXIT_FAILURE;
	}

	Passport p1("Viktor Pavlik", "AB123456");
	Passport p2("Sergii Petrik", "AC987654");

	ForeignPassport fp[2]{ForeignPassport(p1, "SF987654") , ForeignPassport(p2, "SR111111") };
	

	fp[0].addVisa("Germany", "02.07.2019");
	fp[0].addVisa("France", "02.07.2020");
	//fp[0].print();
	
	fp[1].addVisa("Egypt", "20.08.2021");
	fp[1].addVisa("OAE", "20.08.2022");
	fp[1].addVisa("Cuba", "20.08.2023");
	//fp[1].print();

	// записуємо у файл
	for (int i = 0; i < 2; ++i)
	{
		file << fp[i]; 
	}
	file.seekg(0);

	// читаємо з файлу
	ForeignPassport fp_;
	int num = 0;
	while (file >> fp_)
	{
		cout << fp_;
	}

	file.close();



	cout << endl;
	system("pause");
	return 0;
}


