#include<fstream>
#include<algorithm>
#include<vector>

using namespace std;

struct HRRN {
	int PID;
	int arrive;
	double cpu;
	double watting = 0;
};

vector<HRRN>v;
ifstream inp("hrrn.inp");
ofstream out("hrrn.out");


int alltime = 0, wait = 0, number = 0;

void init(int n) {
	for (int i = 0; i < n; i++) {
		HRRN temp;
		temp.PID = i;
		inp >> temp.arrive >> temp.cpu;
		v.push_back(temp);
	}
}


bool priority_compare(const HRRN& a, const HRRN& b) {
	double temp1, temp2;
	temp1 = (a.watting / a.cpu);
	temp2 = (b.watting / b.cpu);
	if (temp1 < temp2) return false;

	else if (temp1 == temp2) {
		if (a.PID < b.PID) return true;
		else return false;
	}
	else return true;

}

void wait_sum(vector<HRRN>& v) {
	int i;
	for (i = 1; i < v.size(); i++) {
		if (v[i].arrive < alltime) {
			v[i].watting++;
		}
		else break;
	}
}


int main() {

	int n;
	inp >> n;

	init(n);

	if (v[0].arrive != 0) {
		int temp = v[0].arrive;
		for (int i = 0; i < v.size(); i++) {
			v[i].arrive -= temp;
		}
	}


	while (true) {
		if (v.size() == 1) {
			wait += v[0].watting;
			break;
		}
		if (alltime < v[0].arrive) alltime = v[0].arrive;

		alltime++;
		v[0].cpu--;
		v[0].arrive++;

		wait_sum(v);


		if (v[0].cpu == 0) {
			wait += v[0].watting;
			v.erase(v.begin());
			int num, j;
			for (j = 1; j < v.size(); j++) {
				if (alltime >= v[j].arrive) {
					num = j;
				}
				else break;
			}
			sort(v.begin(), v.begin() + j, priority_compare);
		}

	}
	out << wait;

}