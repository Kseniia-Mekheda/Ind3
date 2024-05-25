#include "programmer.h"

Programmer::Programmer(string name, string level, double hours)
	:programmer_name(name),
	programmer_level(level),
	programmer_hours(hours)
{}

Programmer::Programmer(const Programmer& C)
	:programmer_name(C.programmer_name),
	programmer_level(C.programmer_level),
	programmer_hours(C.programmer_hours)
{}

double Programmer::calculateSalary() const
{
	if (programmer_level == "Junior")
	{
		return programmer_hours * 1.1;
	}
	else if (programmer_level == "Middle")
	{
		return programmer_hours * 2.;
	}
	else if (programmer_level == "Senior")
	{
		return programmer_hours * 2.5;
	}

	return 0;
}

double Programmer::getHours() const
{
	return programmer_hours;
}

void Programmer::increaseHours(int quantity)
{
	programmer_hours += quantity;
}

bool Programmer::operator<(const Programmer& P) const
{
	return programmer_hours < P.programmer_hours;
}

void Programmer::readFrom(istream& in)
{
	in >> programmer_name >> programmer_level >> programmer_hours;
}

void Programmer::writeTo(ostream& out) const
{
	out << "Name: " << programmer_name << ". Level: " << programmer_level << ". Salary: "
		<< calculateSalary() << " (" << programmer_hours << " hours)";
}

istream& operator>>(istream& in, Programmer& P)
{
	P.readFrom(in);
	return in;
}

ostream& operator<<(ostream& out, const Programmer& P)
{
	P.writeTo(out);
	return out;
}

TechLead::TechLead(string name, string level, double hours, int quantity)
	:Programmer(name, level, hours),
	people_quantity(quantity)
{}

TechLead::TechLead(const TechLead& C)
	:Programmer(C),
	people_quantity(C.people_quantity)
{}

double TechLead::calculateSalary() const
{
	double bonus = Programmer::calculateSalary() * sumOfPercentage();
	return Programmer::calculateSalary() + bonus;
}
double TechLead::sumOfPercentage() const
{
	return people_quantity * 0.1;
}

void TechLead::readFrom(istream& in)
{
	Programmer::readFrom(in);
	in >> people_quantity;
}
void TechLead::writeTo(ostream& out) const
{
	Programmer::writeTo(out);
	out << ". People in goup: " << people_quantity << "(" << sumOfPercentage() <<
		"% bonus to salary)";
}

void FillInVector(const string fileName, const string fileName2, vector<Programmer*>& workers)
{
	ifstream fin(fileName);
	char label;
	fin >> label;
	// Check the first file and decide objects of which class should be created
	if (label == Programmer::PROGRAMMER_LABEL)
	{
		while (!fin.eof())
		{
			Programmer newWorker;
			fin >> newWorker;
			workers.push_back(new Programmer(newWorker));
		}
	}
	else if (label == TechLead::TECHLEAD_LABEL)
	{
		while (!fin.eof())
		{
			TechLead newWorker;
			fin >> newWorker;
			workers.push_back(new TechLead(newWorker));
		}
	}
	fin.close();

	ifstream fin2(fileName2);
	fin2 >> label;
	// Check the second file and decide objects of which class should be created
	if (label == Programmer::PROGRAMMER_LABEL)
	{
		Programmer newWorker;
		while (!fin2.eof())
		{
			fin2 >> newWorker;
			workers.push_back(new Programmer(newWorker));
		}
	}
	else if (label == TechLead::TECHLEAD_LABEL)
	{
		TechLead newWorker;
		while (!fin2.eof())
		{
			fin2 >> newWorker;
			workers.push_back(new TechLead(newWorker));
		}
	}
	fin2.close();
}

void printVector(const vector<Programmer*>& workers)
{
	for_each(workers.cbegin(), workers.cend(), [](const auto& Worker) {cout << *Worker << endl; });
	cout << endl;
}

void fillInMap(vector<Programmer*>& workers, map<string, double>& stats)
{
	double salaryProg = 0;
	double salaryLead = 0;
	for_each(workers.begin(), workers.end(), [&salaryProg, &salaryLead](const Programmer* P)
		{
			if (typeid(*P) == typeid(Programmer))
			{
				salaryProg += P->calculateSalary();
			}
			else
			{
				salaryLead += P->calculateSalary();
			}
		});

	stats.emplace("Programmer", salaryProg);
	stats.emplace("Tech Lead", salaryLead);
}

ostream& operator<<(ostream& out, const pair<string, double>& p)
{
	out << '[' << p.first << " - " << p.second << ']' << endl;
	return out;
}