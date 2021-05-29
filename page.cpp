#include<fstream>
using namespace std;

ifstream inp("page.inp");
ofstream out("page.out");

#define MAX 20000
typedef struct P {
	int PID[MAX];
	int id;
	int pageNumber[MAX];
	int check[MAX];
	int ref[MAX];
	int pageFrame;
}P;
P FIFO; P LRU; P OPT;

P input;

int fifoCheck(int n) {
	int check_where = -1;
	for (int j = 0; j <= FIFO.id; j++) {
		if (input.PID[n] == FIFO.PID[j] && input.pageNumber[n] == FIFO.pageNumber[j]) {
			check_where = j;
			break;
		}
	}
	return check_where;
}
void fifo(int n) {//FIFO
	for (int i = 0; i < input.id; i++) {
		int same = fifoCheck(i);
		if (same >= 0) {
			continue;
		}
		else {
			FIFO.pageFrame++;
			if (FIFO.check[input.PID[i]] == n) {
				for (int j = 0; j < FIFO.id; j++) {
					if (FIFO.PID[j] == input.PID[i]) {
						if (FIFO.ref[j] != 1) {
							FIFO.ref[j]--;
						}
						else {
							FIFO.pageNumber[j] = input.pageNumber[i];
							FIFO.ref[j] = n;
						}
					}
				}
			}
			else {
				FIFO.PID[FIFO.id] = input.PID[i];
				FIFO.pageNumber[FIFO.id] = input.pageNumber[i];
				FIFO.ref[FIFO.id] = FIFO.check[input.PID[i]] + 1;
				FIFO.check[input.PID[i]]++;
				FIFO.id++;
			}
		}
	}
}




int lruCheck(int n) {
	int check_where = -1;
	for (int j = 0; j <= LRU.id; j++) {
		if (input.PID[n] == LRU.PID[j] && input.pageNumber[n] == LRU.pageNumber[j]) {
			check_where = j;
			break;
		}
	}
	return check_where;
}
void lru(int n) {
	for (int i = 0; i < input.id; i++) {
		int same = lruCheck(i);
		if (same >= 0) {
			continue;
		}
		else {
			LRU.pageFrame++;
			if (LRU.check[input.PID[i]] == n) {
				int cnt = 0;
				for (int x = i - 1; x > -1; x--) {
					if (input.PID[i] == input.PID[x]) {
						for (int y = 0; y < LRU.id; y++) {
							if (LRU.ref[y] != 1 && input.PID[x] == LRU.PID[y] && input.pageNumber[x] == LRU.pageNumber[y]) {
								LRU.ref[y] = 1;
								cnt++;
							}
							if (cnt == n - 1) break;
						}
					}
					if (cnt == n - 1) break;
				}
				for (int x = 0; x < LRU.id; x++) {
					if (LRU.ref[x] == 0 && input.PID[i] == LRU.PID[x]) {
						LRU.PID[x] = input.PID[i];
						LRU.pageNumber[x] = input.pageNumber[i];
						break;
					}
				}
				for (int x = 0; x < LRU.id; x++) {
					LRU.ref[x] = 0;
				}
			}
			else {
				LRU.PID[LRU.id] = input.PID[i];
				LRU.pageNumber[LRU.id] = input.pageNumber[i];
				LRU.check[input.PID[i]]++;
				LRU.id++;
			}
		}
	}
}




int opt_arr[MAX] = { 0 };
int optCheck(int n) {
	int check_where = -1;
	for (int j = 0; j <= OPT.id; j++) {
		if (input.PID[n] == OPT.PID[j] && input.pageNumber[n] == OPT.pageNumber[j]) {
			check_where = j;
			break;
		}
	}
	return check_where;
}
void opt(int n) {
	for (int i = 0; i < input.id; i++) {
		int same = optCheck(i);
		if (same >= 0) {
			continue;
		}
		else {
			OPT.pageFrame++;
			if (OPT.check[input.PID[i]] == n) {
				int cnt = 0;
				for (int x = i + 1; x < input.id; x++) {
					if (input.PID[i] == input.PID[x]) {
						for (int y = 0; y < OPT.id; y++) {
							if (OPT.ref[y] != 1 && input.PID[x] == OPT.PID[y] && input.pageNumber[x] == OPT.pageNumber[y]) {
								OPT.ref[y] = 1;
								cnt++;
							}
							if (cnt == n - 1) break;
						}
					}
					if (cnt == n - 1) break;
				}
				int min = 9999;
				int min_idx = 0;
				for (int x = 0; x < OPT.id; x++) {
					if (OPT.ref[x] == 0 && input.PID[i] == OPT.PID[x]) {
						if (min >= opt_arr[x]) {
							min = opt_arr[x];
							min_idx = x;
						}
					}
				}
				OPT.PID[min_idx] = input.PID[i];
				OPT.pageNumber[min_idx] = input.pageNumber[i];
				opt_arr[min_idx] = OPT.pageFrame;
				for (int x = 0; x < OPT.id; x++) {
					OPT.ref[x] = 0;
				}
			}
			else {
				OPT.PID[OPT.id] = input.PID[i];
				OPT.pageNumber[OPT.id] = input.pageNumber[i];
				OPT.check[input.PID[i]]++;
				OPT.id++;
				opt_arr[OPT.id] = OPT.pageFrame;
			}
		}
	}
}

int main(void) {
	int n;//프레임 넘버
	int input_n = 0;//몇 개 들어왔는가

	inp >> n;

	for (input.id;; input.id++) {
		inp >> input.PID[input.id] >> input.pageNumber[input.id];
		if (input.PID[input.id] == -1) break;
	}

	fifo(n);
	out << "FIFO: " << FIFO.pageFrame<<"\n";

	for (int i = 0; i < FIFO.id; i++) {
		out << i <<" "<< FIFO.PID[i]<< " " << FIFO.pageNumber[i] << "\n";
	}

	lru(n);
	out << "LRU: " << LRU.pageFrame << "\n";


	for (int i = 0; i < LRU.id; i++) {
		out  << i << " " << LRU.PID[i] << " " << LRU.pageNumber[i] << "\n";
	}

	opt(n);
	out << "OPT: " << OPT.pageFrame << "\n";

	for (int i = 0; i < OPT.id; i++) {
		out << i << " " << OPT.PID[i] << " " << OPT.pageNumber[i] << "\n";
	}


	return 0;
}