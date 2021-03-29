#include <fstream>
#include <vector>
using namespace std;

#define ll long long

vector<pair<int, int>>v;

int main() {
	ifstream inp("fcfs.inp");
	ofstream out("fcfs.out");
	int n;
	inp >> n;
	for (int i = 0; i < n; i++) {
		int time, cpu;
		inp >> time >> cpu;
		v.push_back(make_pair(time, cpu)); //�־��� 
	}

	ll sum = 0,saveTime = v[0].first,temp = v[0].second;
	/*
	* sum�� wating time�� ��
	* saveTime�� ���� �����ð�
	* temp�� ���� �۾��ð�
	*/

	ll k = v[0].first;
	for (int i = 1; i < n; i++) {
		if ((v[i].first-k) < temp) {//*�۾� �ð� ���� �����ð��� ���Ե� ���
			sum += (temp - (v[i].first-k));
			//�տ� �ִ� �۾��ð��� (temp)���� ���絵�� �ð��� ���ش�
			//�� �� k�� �۾��ð��� ��ġ�� �ʴ� (���� �۾��� ���� ť�� ���� �ȵ� ��) ���� ���ִ� ����
		}
		else {//�ƴ� ���
			temp = 0;
			k = v[i].first;
			//�տ� ������ �۾��ð� �ʱ�ȭ
		}
		temp += v[i].second; //�۾��ð��� ����ؼ� �������ش�.
	}
	
	out << sum;
}