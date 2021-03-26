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
	return (p1.number < p2.number); //����� number�� ����
}

bool compare_LastName( pair<int,string>p1,  pair<int, string>p2) {
	return (p1.second < p2.second); //�ߺ��� �̸��� second�� �������� ����
}

int main() {
	ifstream inp("test.inp");
	ofstream out("test.out");
	
	vector<pair<int,string>>overlap; //�ߺ��� �̸��� ���� ���� ( int���� �� �� ���� �̸����� ī��Ʈ )

	int N;
	vector<People>v; // ����� ������ ����� ����
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
			if (v[i].lastName == overlap[j].second) {  //���� v ���Ϳ��� ����Ű�� �ο��� overlap�� ���� �̸��� �ִٸ� �� �̸��� ���� 1 ����
				overlap[j].first++; 
				break;
			}
			if (j == (overlap.size() - 1)) { //������ ã�Ƶ� ���ٸ� ���� v ���Ϳ� �ο��� ���� overlap�� �߰�
				overlap.push_back(make_pair(1, v[i].lastName));
				break;
			}
		}
	}

	for (int i = 0; i < v.size(); i++){
		string t;

		if (v[i].number < 10000) {
			t = to_string(v[i].number);  //�ڸ����� ���߱����� number�� ��Ʈ�� ���ڿ� ó�����ش�.
			while (t.size() < 5)
			{
				t = '0' + t; /* People�� number�� 10000���� �۴ٸ� ���ʿ� 0�� 5�ڸ��� �� ������ �߰����ش�.
				                ex) 236�� ��� 00236 */
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
