#include<fstream>
#include<vector>
#include<queue>
#include<string>
using namespace std;

struct Sequence {
	string odd;
	int process_number;
	vector <int>arr;
};

bool deadlock(vector<int>& v, vector<vector<int>>& n, vector<vector<int>>& v1, vector<vector<int>>& v2, Sequence& v3) {
	for (int i = 0; i < v3.arr.size(); i++) {
		v[i] -= v3.arr[i];
		n[v3.process_number][i] -= v3.arr[i];
		v1[v3.process_number][i] += v3.arr[i];
		if (v[i] < 0 || n[v3.process_number][i]<0 || v1[v3.process_number][i]>v2[v3.process_number][i]) {
			return false;
		}
	}
	return true;
}
void deadlock1(vector<int>& v, vector<vector<int>>& N, vector<vector<int>>& A, vector<vector<int>>& M, vector<int>& L, Sequence& R) {

	bool check3 = true;
	for (int j = 0; j < v.size(); j++) {
		if (v[j] < N[R.process_number][j]) {
			check3 = false;
			break;
		}
	}
	if (check3) {
		L[R.process_number] = -1;
		for (int k = 0; k < v.size(); k++) {
			v[k] += R.arr[k];
			A[R.process_number][k] -= R.arr[k];
			N[R.process_number][k] = 0;
			if (v[k]<0 || A[R.process_number][k]>M[R.process_number][k]) {
				L[R.process_number] = 0;
			}
		}
	}

}
void deadlock2(vector<int>& v, vector<vector<int>>& n, vector<vector<int>>& v2, vector<vector<int>>& v3, vector<int>& v4) {
	for (int i = 0; i < n.size(); i++) {
		if (v4[i] != -1) {
			bool check3 = true;
			for (int j = 0; j < v.size(); j++) {
				if (v[j] < n[i][j]) {
					check3 = false;
					break;
				}
			}
			if (check3) {
				v4[i] = -1;
				for (int k = 0; k < v.size(); k++) {
					v[k] += v2[i][k];
					n[i][k] -= v2[i][k];
					v2[i][k] = 0;
					if (v[k]<0 || v2[i][k]>v3[i][k]) {
						v4[i] = 0;
					}
				}
			}
		}
	}
}

bool request(vector<int>& v, Sequence& s) {
	for (int i = 0; i < v.size(); i++) {
		if (s.arr[i] > v[i]) {
			return false;
		}
	}
	return true;
}
bool needSpare(Sequence& s, vector<vector<int>>& v) {
	for (int i = 0; i < s.arr.size(); i++) {
		if (s.arr[i] > v[s.process_number][i])
			return false;
	}
	return true;
}

int main() {
	ifstream inp("banker.inp");
	ofstream out("banker.out");

	int n, m;
	inp >> n >> m;
	vector <int>max_v;
	vector <int> vv;

	for (int i = 0; i < m; i++) {
		int a;
		inp >> a;
		max_v.push_back(a);
	}

	vector < vector<int> > MAX(n, vector<int>(m, 0));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			inp >> MAX[i][j];
		}
	}


	vector< vector<int> > ALLOCATION(n, vector<int>(m, 0));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			inp >> ALLOCATION[i][j];
		}
	}

	for (int i = 0; i < m; i++) {
		int sum = 0;
		for (int j = 0; j < n; j++) {
			sum += ALLOCATION[j][i];
		}
		int value = max_v[i] - sum;
		vv.push_back(value);
	}
	vector<vector<int> >NEED(n, vector<int>(m, 0));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			NEED[i][j] = MAX[i][j] - ALLOCATION[i][j];
		}
	}

	queue<Sequence> ready;

	while (1) {
		vector <int> emporaryV = vv;
		vector<vector<int>> temporaryNeed = NEED;
		vector<vector<int>> temporaryAllocation = ALLOCATION;

		Sequence TEMP;
		bool NEED_check = true, request_check = true, deadlock_check = true;
		inp >> TEMP.odd;
		if (TEMP.odd == "quit") {
			break;
		}
		inp >> TEMP.process_number;

		for (int i = 0; i < m; i++) {
			int a;
			inp >> a;
			TEMP.arr.push_back(a);
		}



		if (TEMP.odd.compare("request") == 0) {
			NEED_check = needSpare(TEMP, NEED);
			if (NEED_check) {

				request_check = request(vv, TEMP);
				if (request_check) {

					deadlock_check = deadlock(emporaryV, temporaryNeed, temporaryAllocation, MAX, TEMP);
					if (deadlock_check) {
						vector <int>Lock;
						for (int i = 0; i < n; i++) {
							Lock.push_back(0);
						}
						deadlock1(emporaryV, temporaryNeed, temporaryAllocation, MAX, Lock, TEMP);

						for (int i = 0; i < n; i++) {
							deadlock2(emporaryV, temporaryNeed, temporaryAllocation, MAX, Lock);
						}
						bool last = true;
						for (int i = 0; i < n; i++) {
							if (Lock[i] != -1) {
								ready.push(TEMP);
								last = false;
								break;
							}
						}
						if (last) {
							for (int i = 0; i < m; i++) {
								vv[i] -= TEMP.arr[i];
								ALLOCATION[TEMP.process_number][i] += TEMP.arr[i];
								NEED[TEMP.process_number][i] -= TEMP.arr[i];
							}
						}

					}
					else ready.push(TEMP);

				}
				else {
					ready.push(TEMP);

				}
			}
		}
		if (TEMP.odd.compare("release") == 0) {
			for (int i = 0; i < m; i++) {
				vv[i] += TEMP.arr[i];
				ALLOCATION[TEMP.process_number][i] -= TEMP.arr[i];
				NEED[TEMP.process_number][i] += TEMP.arr[i];

			}
		}

		if (!ready.empty()) {

			int size = ready.size();
			int cnt = 0;

			while (1) {

				bool last2 = true;
				if (size == cnt) {
					break;
				}
				Sequence tem = ready.front();
				cnt++;

				bool request_check = request(vv, tem);

				if (request_check) {

					vector <int> emporaryV2 = vv;
					vector<vector<int>> temporaryNeed2 = NEED;
					vector<vector<int>> temporaryAllocation2 = ALLOCATION;

					bool deadlock_check = deadlock(emporaryV2, temporaryNeed2, temporaryAllocation2, MAX, tem);
					if (deadlock_check) {
						vector <int>lock;
						for (int i = 0; i < n; i++)lock.push_back(0);
						for (int i = 0; i < n; i++)deadlock2(emporaryV2, temporaryNeed2, temporaryAllocation2, MAX, lock);

						for (int i = 0; i < n; i++) {
							if (lock[i] != -1) {
								last2 = false;
								break;
							}
						}
						if (last2) {

							for (int i = 0; i < m; i++) {
								vv[i] -= tem.arr[i];
								ALLOCATION[tem.process_number][i] += tem.arr[i];
								NEED[tem.process_number][i] -= tem.arr[i];
							}
							ready.pop();

						}
						else {
							ready.pop();
							ready.push(tem);
						}
					}
					else {
						ready.pop();
						ready.push(tem);
					}
				}
				else {
					ready.pop();
					ready.push(tem);
				}
			}
		}
		for (int i = 0; i < m; i++) {
			out << vv[i] << " ";
		}
		out << "\n";
	}

}

