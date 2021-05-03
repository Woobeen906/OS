#include<fstream>
#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;

ifstream inp("rr.inp");
ofstream out("rr.out");

int totaltime = 0, cnt = 0;
int n, q;


typedef struct Process {
	int PID;//���μ��� ��ȣ
	int turnaroundTime;
	bool finish = false; //�߰��� ����� true�� �ٲ���
	bool run = true;//���μ����� run�� �� �ִ��� Ȯ��
	int burstCount;
	int burstMove = 0;
	int burst[100] = { -1, };//cpu burst , i/o burst ����
	int waitingtime = 0;//���μ��� wating time�� ����
	bool statement = false;//ť�ȿ� �ȵ������� falseť�ȿ� �� ������ true
	bool read = false;//time slice���� ū cpu burst���� üũ
};

bool comparePID(const Process& a, const Process& b) {
	return (a.PID < b.PID);
}
bool compare(const Process& a, const Process& b) {
	if (a.turnaroundTime < b.turnaroundTime) return true;
	else if (a.turnaroundTime == b.turnaroundTime) {
		if (a.finish == false && b.finish == true) return true;
		else if (a.finish == b.finish) {
			return a.PID < b.PID;
		}
		else return false;
	}
	else return false;
}


void init(vector<Process>& p, queue<int>& q, int totaltime, int num) {
	int temp_index = -1;
	sort(p.begin(), p.end(), compare);

	for (int i = 0; i < p.size(); i++) {
		if (p[i].PID == num) {
			temp_index = i;
			continue;
		}
		if (p[i].finish == false && totaltime >= p[i].turnaroundTime && p[i].run != false && p[i].statement != true) {
			p[i].finish = true;
			q.push(p[i].PID);
			p[i].statement = true;
		}
		else if (totaltime >= p[i].turnaroundTime && p[i].run != false && p[i].statement != true) {
			q.push(p[i].PID);
			p[i].statement = true;
		}
	}

	if (temp_index != -1) {
		if (p[temp_index].read) {
			q.push(p[temp_index].PID);
			p[temp_index].statement = true;
		}
	}
}

int Total(vector<Process>& p, queue<int>& q, int totaltime) {
	sort(p.begin(), p.end(), compare);

	for (int i = 0; i < p.size(); i++) {
		if (p[i].run != false) {
			totaltime = p[i].turnaroundTime;
			p[i].statement = true;
			p[i].read = false;
			if (p[i].finish == false) {
				p[i].finish = true;
			}
			q.push(p[i].PID);
			break;
		}
	}
	return totaltime;
}

int main() {

	vector<Process>v;
	queue<int>Q;


	inp >> n >> q;

	for (int i = 0; i < n; i++) {
		Process temp;
		temp.PID = i;
		inp >> temp.turnaroundTime >> temp.burstCount;
		for (int j = 0; j < temp.burstCount; j++) {
			inp >> temp.burst[j];
		}
		v.push_back(temp);
	}

	for (int i = 0; i < n; i++) {
		if (v[i].turnaroundTime == 0) {
			Q.push(v[i].PID);
			v[i].statement = true;
			v[i].finish = true;
			v[i].read = false;
		}
	}

	while (1) {
		if (Q.empty()) {
			if (cnt == v.size()) break;
			else totaltime = Total(v, Q, totaltime);
		}
		else {

			int num = Q.front();
			Q.pop();
			sort(v.begin(), v.end(), comparePID);
			v[num].statement = false;
			if (totaltime > v[num].turnaroundTime) {
				int temp = totaltime - v[num].turnaroundTime;
				v[num].waitingtime += temp;
			}

			if (v[num].burst[v[num].burstMove] > q && v[num].burstMove % 2 == 0) {
				totaltime += q;
				v[num].turnaroundTime = totaltime;
				v[num].read = true;
				v[num].burst[v[num].burstMove] -= q;
			}
			else if (v[num].burst[v[num].burstMove] <= q && v[num].burstMove % 2 == 0) {
				v[num].read = false;
				totaltime += v[num].burst[v[num].burstMove];
				v[num].turnaroundTime = totaltime;
				v[num].burst[v[num].burstMove] = 0;
				v[num].burstMove++;
				v[num].turnaroundTime += v[num].burst[v[num].burstMove];
				v[num].burstMove++;

				if (v[num].burstMove > v[num].burstCount && v[num].run == true) {
					v[num].run = false;
					cnt++;
				}
			}
			init(v, Q, totaltime, num);
		}

	}
	sort(v.begin(), v.end(), comparePID);

	for (int u = 0; u < v.size(); u++) {
		out << v[u].PID + 1 << " " << v[u].waitingtime << endl;
	}
}