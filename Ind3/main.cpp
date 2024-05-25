#include "programmer.h"

int main() {
	vector<Programmer*> workers;
	FillInVector("prog.txt", "tech.txt", workers);
	cout << "Filled vector: " << endl;
	printVector(workers);

	sort(workers.begin(), workers.end(), [](const Programmer* First, const Programmer* Second)
		{
			return First->getHours() < Second->getHours();
		});
	cout << "Sorted vector: " << endl;
	printVector(workers);

	for_each(workers.begin(), workers.end(), [](Programmer* P) { P->increaseHours(P->getHours());  });
	sort(workers.begin(), workers.end(), [](const Programmer* First, const Programmer* Second)
		{
			return First->calculateSalary() < Second->calculateSalary();
		});
	cout << "Vector after increased hours and sorted by salary: " << endl;
	printVector(workers);

	map<string, double> statistic;
	fillInMap(workers, statistic);
	cout << "Our map: " << endl;
	for_each(statistic.begin(), statistic.end(), [](const pair<string, double>& p)
		{
			cout << p;
		});
	return 0;
}