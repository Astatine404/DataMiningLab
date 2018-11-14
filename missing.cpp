#include<iostream>
#include<fstream>
#include<bits/stdc++.h>
#include<string>
#define globalConst "$$$$"
using namespace std;
/* tuple format
<id> <name> <marks> -1
*/


int main(){
	vector<string> names;
	vector<int> marks; vector<int> id;
	fstream fin;
	string tmp;
	fin.open("missing.txt", ios::in);
	float avg=0; int miss=0;
	while(!fin.eof()){
		//id
		fin>>tmp;
		id.push_back(atoi(&tmp[0]));
		//name
		fin>>tmp;
		if(tmp == "?")
			tmp = globalConst;
		names.push_back(tmp);
		//marks
		fin>>tmp;
		if(tmp == "?"){
			tmp = "-1";
			miss++;
		}
		else
			avg += atoi(&tmp[0]);
		marks.push_back(atoi(&tmp[0]));
	}
	avg /= marks.size() - miss;
	for(int i=0; i<id.size(); i++){
		cout<<id[i]<<" "<<names[i]<<" ";
		if(marks[i] == -1)
			cout<<avg<<endl;
		else
			cout<<marks[i]<<endl;
	}
	fin.close();
	return 0;
}
