// dllmain.cpp : Определяет точку входа для приложения DLL.
#include "pch.h"
enum name { HAT, BOOK, BALL };
class Subject {
public:
	name _name;
	int cost;
	int count;
};

int SumSubj(vector< Subject> subj) {
	int su = 0;
	for (int i = 0; i < subj.size(); i++) su += subj[i].cost * subj[i].count;
	return su;
}
bool CompareClass(const Subject& a, const Subject& b) {
	return a.cost < b.cost;
}
int GiveLowCostSubject(vector< Subject> subj, int count_of_subject) {
	int anser = 0;
	int count = 0;
	for (int i = 0; i < subj.size(); i++) {
		while (subj[i].count != 0)
		{
			if (count == count_of_subject) return anser;
			if (subj[i]._name == HAT) {
				anser += subj[i].cost * 100;
				subj[i].count--;
			}
			else if (subj[i]._name == BOOK) {
				anser += subj[i].cost * 10;
				subj[i].count--;
			}
			else {
				anser += subj[i].cost;
				subj[i].count--;
			}
			++count;
		}
	}
	return anser;
}
__declspec(dllexport) int __cdecl decide(
	int turn,
	int hatCost,
	int bookCost,
	int ballCost,
	int hatCount,
	int bookCount,
	int ballCount) {
	int exchange_hat = 0;
	int exchange_book = 0;
	int exchange_balls = 0;

	if (hatCost == 0) exchange_hat = 1;
	if (bookCost == 0) exchange_book = 2;
	else if (ballCost == 0) exchange_balls = 3;
	vector< Subject> subj = { {HAT,hatCost, hatCount},{BOOK, bookCost,bookCount },{BALL,ballCost, ballCount } };
	vector< Subject> full_subj = { {HAT,hatCost, 1},{BOOK, bookCost,2 },{BALL,ballCost, 3 } };
	sort(subj.begin(), subj.end(), CompareClass);

	if (SumSubj(subj) == 10) return 1;

	if (turn == 0) {
		if (exchange_balls + exchange_book + exchange_hat != 0)
			return exchange_hat * 100 + exchange_book * 10 + exchange_balls;
		return GiveLowCostSubject(full_subj, 2);
	}
	else if (turn == 1) {
		if (exchange_balls + exchange_book + exchange_hat != 0)
			return exchange_hat * 100 + exchange_book * 10 + exchange_balls;
		if (SumSubj(subj) >= 6) return 1;
		return GiveLowCostSubject(full_subj, 3);
	}
	else if (turn == 2) {
		if (SumSubj(subj) >= 7) return 1;
		return GiveLowCostSubject(full_subj, 2);
	}
	else if (turn == 3) {
		if (SumSubj(subj) >= 6) return 1;
		return GiveLowCostSubject(full_subj, 4);
	}
	else if (turn == 4) {
		return GiveLowCostSubject(full_subj, 1);
	}
	else if (turn == 5 && SumSubj(subj) != 0) return 1;
	else if (turn == 5) return 100;


}
