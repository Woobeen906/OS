#include <fstream>
#include<vector>
#include<algorithm>
using namespace std;

int main()
{
	ifstream inp("sjf.inp");
	ofstream out("sjf.out");

	vector< pair <int, int> > v;

	int cpu, time, n;

	inp >> n;
	for (int i = 0; i < n; i++)
	{
		inp >> cpu >> time;
		v.push_back(make_pair(time, cpu));
	}

	sort(v.begin(), v.end());

	int sum = 0, waiting = 0;
	int min = 0, temp = 0, index = 0;


	for (int i = 0; i < n; i++)
	{
		min = -1;
		temp = 2147483647 - 1;
		for (int j = 0; j < n; j++)
		{
			if (waiting >= v[j].second)
			{
				min = j; break;
			}

		}
		if (min == -1)
		{
			for (int i = 0; i < n; i++)
			{
				if (v[i].second < temp)
				{
					temp = v[i].second;
					index = i;
				}
			}
			waiting = v[index].second + v[index].first;
			v[index].second = 2147483647;
		}
		else
		{
			if (waiting - v[min].second > 0)
			{
				sum += waiting - v[min].second;
				waiting += v[min].first;
			}
			else waiting = v[min].first + v[min].second;

			v[min].second = 2147483647 - 1;
		}
	}

	out << sum;
}