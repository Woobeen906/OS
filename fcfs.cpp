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
		v.push_back(make_pair(time, cpu)); 
	}

	ll sum = 0,saveTime = v[0].first,temp = v[0].second;
	/*
	* sum은 wating time에 합
	* saveTime은 최초 도착시간
	* temp는 최초 작업시간
	*/

	ll k = v[0].first;
	for (int i = 1; i < n; i++) {
		if ((v[i].first-k) < temp) {//*작업 시간 내에 도착시간이 포함된 경우
			sum += (temp - (v[i].first-k));
			//앞에 있던 작업시간들 (temp)에서 현재도착 시간을 弧娩
			//이 때 k는 작업시간에 겹치지 않는 (다음 작업이 레디 큐에 포함 안될 때) 값을 빼주는 역할
		}
		else {//아닐 경우
			temp = 0;
			k = v[i].first;
			//앞에 누적된 작업시간 초기화
		}
		temp += v[i].second; //작업시간은 계속해서 누적해준다.
	}
	
	out << sum;
}
