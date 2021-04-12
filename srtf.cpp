#include<fstream>
#include<algorithm>
#include<vector>

using namespace std;

struct SRTF {
   int PID;
   int arrive;
   int cpu;
   int watting=0;
};

vector<SRTF>v;
ifstream inp("srtf.inp");
ofstream out("srtf.out");


int alltime = 0, wait = 0, number = 0;

void init(int n) {
    for (int i = 0; i < n; i++) {
        SRTF temp;
        temp.PID = i + 1;
        inp >> temp.arrive >> temp.cpu;
        v.push_back(temp);
    }
}

bool compare(const SRTF& a, const SRTF& b) {
   if (a.arrive < b.arrive) return true;
   else if (a.arrive == b.arrive) {
      if (a.cpu < b.cpu) return true;
      else return false;
   }
   else return false;

}

bool arrive_time_same(const SRTF& a, const SRTF& b) {
   if (a.cpu < b.cpu) return true;
   else if (a.cpu == b.cpu) {
      if (a.PID < b.PID) return true;
      else return false;
   }
   else return false;

}

void wait_sum(vector<SRTF>& v) {
    int i;
    for (i = 1; i < v.size(); i++) {
        if (v[i].arrive < alltime) {
            v[i].watting++;
        }
        else if (alltime == v[i].arrive) {
            if (v[i].cpu < v[0].cpu) {
                sort(v.begin(), v.begin() + i + 1, arrive_time_same);
            }
        }
        else break;
    }
}


int main() {
   
   int n;
   inp >> n;

   init(n);
   sort(v.begin(), v.end(), compare);

   if (v[0].arrive != 0) {
      int temp = v[0].arrive;
      for (int i = 0;i < v.size();i++) {
         v[i].arrive -= temp;
      }
   }


      while(true) {
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
            for ( j = 1;j < v.size();j++) {
               if (alltime >= v[j].arrive) {
                  num = j;
               }
               else break;
            }
            sort(v.begin(), v.begin() + j , arrive_time_same);
         }

      }
   out << wait;

}