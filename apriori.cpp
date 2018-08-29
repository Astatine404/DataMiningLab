#include<iostream>
#include<fstream>
#include<bits/stdc++.h>

using namespace std;

fstream fout;
void print(map<set<int>, int> &m){
	for(map<set<int>, int>::iterator it=m.begin(); it!=m.end(); it++){
		cout<<"{";
		for(set<int>::iterator i=it->first.begin(); i!=it->first.end(); i++){
			cout<<*i<<" ";
		}
		cout<<"} : ";
		cout<<it->second<<endl;
	}
}

void join(map<set<int>, int> &m){
	map<set<int>, int>::iterator a=m.begin(), b, tmp; set<int>::iterator i, j;
	map<set<int>, int> next; int n; bool join, first; set<int> t;
	for(a=m.begin(); a!=m.end(); a++){
		first = true; tmp = a;
		for(b=++a; b!=m.end(); b++){
			join = true;
			if(first){a--; first=false;}
			for(i=b->first.begin(), j=a->first.begin(), n=0; i!=b->first.end(), j!=a->first.end(), n<b->first.size()-1; i++, j++, n++){
				if(*i!=*j){
					join=false;
					break;
				}
			}
			if(join==false){
				break;
			}
			//Join the set
			t.clear();
			for(i=b->first.begin(), j=a->first.begin(), n=0; i!=b->first.end(), j!=a->first.end(), n<b->first.size()-1; i++, j++, n++){
				t.insert(*i);
			}
			t.insert(*i); t.insert(*j);
			next[t] = 0;
		}
		a = tmp;
	}
	m = next;
}

void prune(map<set<int>, int> &m, int sup){
	map<set<int>, int>::iterator tmp;
	for(map<set<int>, int>::iterator it=m.begin(); it!=m.end();){
		if(it->second<sup){
			tmp = it;
			tmp++;
			m.erase(it);
			it = tmp;
		}
		else
		it++;
	}
}

int main(){
	fstream fin; int tmp, sup;
	bool first=true;
	fin.open("tid_pid.txt", ios::in);
	fout.open("apriori_out.txt", ios::out);
	cout<<"Enter min support: "; cin>>sup;
	map<set<int>, int> m; set<int> t;
	//Bring file to memory
	set<set<int> > file; set<int> f;
	//Make initial sets
	while(!fin.eof()){
			if(first){
				//ignore tid
				fin>>tmp; first=false; continue;
			}
			fin>>tmp;
			if(tmp==-999){
				file.insert(f); f.clear();
				//ignore tid
				fin>>tmp; 
				continue;
			}
			f.insert(tmp);
			t.clear();
			t.insert(tmp);
			if(m.find(t)==m.end())
			m[t] = 1;
			else
			m[t]++;
	}
	prune(m, sup); 
	print(m); 
	join(m);  
	fin.close();
	while(!m.empty()){
		for(set<set<int> >::iterator it=file.begin(); it!=file.end(); it++){
			for(map<set<int>, int>::iterator i=m.begin(); i!=m.end(); i++){
				bool present = true;
				//check if this transaction contains all of current map iterator
				for(set<int>::iterator j=i->first.begin(); j!=i->first.end(); j++){
					if((*it).find(*j)==(*it).end()){
						present = false;
						break;
					}
				}
				if(present)
				i->second++;
			}
		}
		prune(m, sup); 
		print(m); 
		join(m);
	}
	

	return 0;
}

