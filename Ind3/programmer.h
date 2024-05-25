#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <map>
using namespace std;

class Programmer {
protected:
	string programmer_name;
	string programmer_level;
	double programmer_hours;

public:
	static const char PROGRAMMER_LABEL = 'P';
	Programmer(string name = " ", string level = " ", double hours = 0.);
	Programmer(const Programmer& C);
	virtual ~Programmer() = default;

	virtual double calculateSalary() const;
	double getHours() const;
	void increaseHours(int quantity);
	bool operator<(const Programmer& P) const;

	virtual void readFrom(istream& in);
	virtual void writeTo(ostream& out) const;
};

istream& operator>>(istream& in, Programmer& P);
ostream& operator<<(ostream& out, const Programmer& P);

class TechLead : public Programmer {
private:
	int people_quantity;

public:
	static const char TECHLEAD_LABEL = 'T';
	TechLead(string name = " ", string level = " ", double hours = 0., int quantity = 0);
	TechLead(const TechLead& C);

	virtual double calculateSalary() const override;
	double sumOfPercentage() const;

	virtual void readFrom(istream& in) override;
	virtual void writeTo(ostream& out) const override;
};

void FillInVector(const string fileName, const string fileName2, vector<Programmer*>& workers);
void printVector(const vector<Programmer*>& workers);

void fillInMap(vector<Programmer*>& workers, map<string, double>& stats);

ostream& operator<<(ostream& out, const pair<string, double>& p);
