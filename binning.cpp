#include<iostream>
#include<fstream>
#include<bits/stdc++.h>
#include<string>
using namespace std;
/* tuple format
<id> <name> <marks> -1
*/


int main(){
	int binSize;
	fstream fin, fout;
	int tmp; vector<int> nos;
	fout.open("binning.txt", ios::out);
	for(int i=0; i<20; i++)
		nos.push_back(rand()%200);
	sort(nos.begin(), nos.end());
	for(int i=0; i<nos.size(); i++)
		fout<<nos[i]<<" ";
	fout.close();
	fin.open("binning.txt", ios::in);
	cout<<"Enter Bin size:"; cin>>binSize;
	float sum=0; int i;
	while(!fin.eof()){
		sum = 0;
		for(i=0; i<binSize&&!fin.eof(); i++){
			fin>>tmp;
			sum += tmp;
		}
		sum /= i;
		for(int j=0; j<i; j++)
		cout<<sum<<" "; 
	}
	fin.close();
	return 0;
}
