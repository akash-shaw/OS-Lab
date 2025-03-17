#include <iostream>
#include <vector>

using namespace std;

class process{
public:
	string name;
	int r1,r2,r3;
	process(string name){
		this->name = name;
		cout<<"Process "<<name<<" Created\n";
	}
};

int main(){
	int n,m;
	vector<int> available;
	int max[n][m];
	int allocation[n][m];
	int need[n][m];

	string name;
	vector<process> processes;
	while(1){
		cout<<"Enter process name: ";
		cin>>name;
		if(name=="stop") break;
		process p(name);
		processes.push_back(p);

	}


	return 0;
}