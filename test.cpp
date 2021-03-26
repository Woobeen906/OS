#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

struct People {
	int number;
	string firstName;
	string lastName;
	string temp;
}; 

bool compare(const People& p1, const People& p2) {
	return (p1.number < p2.number); //사람을 number로 정렬
}

bool compare_LastName( pair<int,string>p1,  pair<int, string>p2) {
	return (p1.second < p2.second); //중복된 이름을 second를 기준으로 정렬
}

int main() {
	ifstream inp("test.inp");
	ofstream out("test.out");
	
	vector<pair<int,string>>overlap; //중복된 이름에 대한 벡터 ( int형은 몇 명 같은 이름인지 카운트 )

	int N;
	vector<People>v; // 사람의 정보가 저장된 벡터
	People people;
	inp >> N;
	for (int i = 0; i < N; i++) {
		inp >> people.number>>people.firstName>>people.lastName;
		v.push_back(people);
	}

	sort(v.begin(), v.end(), compare);

	overlap.push_back(make_pair(1,v[0].lastName)); 

	

	for (int i = 1; i < N; i++) {
		for (int j = 0; j < overlap.size(); j++) {
			if (v[i].lastName == overlap[j].second) {  //현재 v 벡터에서 가르키는 인원과 overlap에 같은 이름이 있다면 그 이름에 수를 1 증가
				overlap[j].first++; 
				break;
			}
			if (j == (overlap.size() - 1)) { //끝까지 찾아도 없다면 현재 v 벡터에 인원을 새로 overlap에 추가
				overlap.push_back(make_pair(1, v[i].lastName));
				break;
			}
		}
	}

	for (int i = 0; i < v.size(); i++){
		string t;

		if (v[i].number < 10000) {
			t = to_string(v[i].number);  //자릿수를 맞추기위해 number를 스트링 문자열 처리해준다.
			while (t.size() < 5)
			{
				t = '0' + t; /* People에 number가 10000보다 작다면 왼쪽에 0을 5자리가 될 때까지 추가해준다.
				                ex) 236에 경우 00236 */
			}
			out << t << " ";
		}
		else out << v[i].number<<" ";
		out << v[i].firstName << "     " << v[i].lastName << "\n";
	}
	sort(overlap.begin(), overlap.end(), compare_LastName);
	out << "\n";
	for (int i = 0; i < overlap.size(); i++) {
		if (overlap[i].first != 1) {
			out << overlap[i].second << " " << overlap[i].first << "\n";
		}
	}
}
