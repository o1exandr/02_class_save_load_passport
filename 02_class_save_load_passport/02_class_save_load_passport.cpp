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
	string id;

public:


	ForeignPassport(Passport p, string id) :Passport(p), id(id)
	{
	}

	void setId(string i)
	{
		id = i;
	}

	string getId() const
	{
		return id;
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
	}

	void save(const ForeignPassport & fp)
	{
		ofstream save;
		save.open("database.txt", ios::app);\

			if (!save.is_open())
			{
				cerr << "Error read\n";
				return;
			}

		save << fp;

		/*	ofstream save; 
			save.open("database.txt", ios::app);

			if (!save.is_open())
			{
				cerr << "Error read\n";
				return;
			}
			else
			{
				save << Passport::getName() << endl << Passport::getId() << endl << getId() << endl;
				for (Visa& v : visas)
				{
					save << v.country << "\t" << v.date << endl;
				}
			}

			save.close();*/

	}

	void load(const ForeignPassport & fp)
	{

		ifstream load;
		load.open("database.txt", ios::out);
		string str;
		if (!load.is_open())
		{
	
			cerr << "Error read\n";
			return;
		}
			while (load)
			{ }

				//load >> fp;
		
	/*	ifstream load; 
		load.open("database.txt", ios::out);
		string str;
		if (!load.is_open())
		{
			cerr << "Error read\n";
			return;
		}
		else
			while (getline(load, str))
			{
				cout << str << endl;
			}
	

		load.close();*/

	}

	friend ostream & operator << (ostream &os, const ForeignPassport & fp);
	friend istream & operator >> (istream & is, ForeignPassport & fp);

};

ostream & operator << (ostream &os, const ForeignPassport & fp)
{
	os << fp.id << endl << fp.name << endl;
	vector<Visa> visas;
	for (Visa& v : visas)
	{
		os << v.country << "\t" << v.date << endl;
	}
	return os;
}
istream & operator >> (istream & is, ForeignPassport & fp)
{

	is >> fp.id >> fp.name;
	vector<Visa> visas;
	for (Visa& v : visas)
	{
		is >> v.country >> v.date;
	}
	return is;
}

int main()
{

	Passport p[2]{ Passport ("Viktor Pavlik", "AB123456"), Passport ("Sergii Petrik", "AC987654") };
	

	Visa v;
	v.country = "Germany";
	v.date = "02.07.2019";

	ForeignPassport fp1(p[0], "SF987654");
	fp1.addVisa(v);
	fp1.addVisa("France", "02.07.2020");
	fp1.print();
	fp1.save(fp1);
	fp1.load(fp1);

	ForeignPassport fp2(p[1], "SR111111");
	fp2.addVisa("Egypt", "20.08.2021");
	fp2.addVisa("OAE", "20.08.2022");
	fp2.addVisa("Cuba", "20.08.2023");
	fp2.print();



	cout << endl;
	system("pause");
	return 0;
}


