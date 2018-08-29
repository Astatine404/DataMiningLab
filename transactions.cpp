#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<bits/stdc++.h>
using namespace std;


typedef struct transaction{
	int tid;
	vector<int> pid;
} tran;

void writeData(){
	fstream fout;
	int pdtsize=0, totaltrn=0, trnsize=0, delim=-999; set<int> tmp; vector<int> pid;
	while(totaltrn<100)
	totaltrn = rand()%1000;
	
	fout.open("tid_pid.txt", ios::in|ios::out);
	
	for(int i=1; i<=totaltrn; i++){
		pid.clear(); tmp.clear();
		trnsize = rand()%20;
		while(pid.size()!=trnsize){
			int curr = rand()%100;
			if(tmp.find(curr)==tmp.end()){
				pid.push_back(curr);
				tmp.insert(curr);
			}
		}
		sort(pid.begin(), pid.end());
		fout<<i<<" ";
		for(int j=0; j<pid.size(); j++)
		fout<<pid[j]<<" ";
		fout<<delim<<endl;
	}
	
}

int main(){
	int tmp=0;
	//writeData();
	fstream fin, fout;
	fin.open("tid_pid.txt", ios::in);
	/*while(!fin.eof()){
		fin>>tmp;
		if(tmp==-999)
		cout<<endl;
		else
		cout<<tmp<<" ";
	}*/
	int choice, tid, pid;
	cout<<"Transaction(0) or product(1):"; cin>>choice;
	if(!choice){
		fout.open("tid.txt", ios::out);
		cout<<"Enter transaction to find:"; cin>>tid;
		while(!fin.eof()){
			fin>>tmp;
			if(tmp==tid){
				fin>>tmp;
				while(tmp!=-999&&!fin.eof()){
					cout<<tmp<<" ";
					fout<<tmp;
					fin>>tmp;
				}
			}
			else{
				while(tmp!=-999&&!fin.eof())
				fin>>tmp;
			}
		}
	}
	else{
		fout.open("pid.txt", ios::out);
		cout<<"Enter product to find:"; cin>>pid;
		int count=0;
		while(!fin.eof()){
			fin>>tmp;
			int curr_tid = tmp;
			fin>>tmp;
			while(tmp!=-999&&!fin.eof()){
				if(tmp==pid){
					cout<<curr_tid<<" ";
					count++;
				}
				fout<<curr_tid;
				fin>>tmp;
			}
			
		}
		cout<<endl<<count;
	}
	return 0;
}
