#include<iostream>
#include<fstream>
#include<bits/stdc++.h>
using namespace std;
map<set<int>, int> final;

fstream fout;
void print(map<set<int>, int> &m, bool save){
	fstream fout;
	fout.open("apriori_out.txt", ios::out|ios::app);
	if(!save)
	fout<<"Printing global frequent itemset:\n";
	for(map<set<int>, int>::iterator it=m.begin(); it!=m.end(); it++){
		if(save){
			if(final.find(it->first)==final.end())
			final[it->first] = it->second;
			else
			final[it->first] += it->second;
		}
		
		cout<<"{"; fout<<"{";
		for(set<int>::iterator i=it->first.begin(); i!=it->first.end(); i++){
			cout<<*i<<" "; fout<<*i<<" ";
		}
		cout<<"} : "; fout<<"} : ";
		cout<<it->second<<endl; fout<<it->second<<endl;
	}
	fout.close();
}

void join(map<set<int>, int> &m, map<set<int>, int> &next){
	map<set<int>, int>::iterator a=m.begin(), b, tmp; set<int>::iterator i, j;
	//map<set<int>, int> next; 
	int n; bool join, first; set<int> t;
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
	//m = next;
}

void prune(map<set<int>, int> &m, map<set<int>, int> &next){
	map<set<int>, int>::iterator tmp; set<int> curr, t;
	
	/*for(map<set<int>, int>::iterator it=m.begin(); it!=m.end();){
		if(it->second<sup){
			tmp = it;
			tmp++;
			m.erase(it);
			it = tmp;
		}
		else
		it++;
	}*/
	set<int>::iterator tit; bool isPruned;
	for(map<set<int>, int>::iterator it=next.begin(); it!=next.end();){
		curr = it->first; isPruned = false;
		for(set<int>::iterator i=curr.begin(); i!=curr.end(); i++){
			t = curr;
			t.erase(*i);
			if(m.find(t)==m.end()){
				//prune this set
				tmp = it; tmp++;
				m.erase(curr);
				it = tmp; isPruned = true;
				break;
			}
			
		}
		if(!isPruned)
		it++;
	}
	m = next; next.clear();
}

void apriori(set<set<int> > &file, map<set<int>, int> &m, int sup){
	map<set<int>, int>::iterator tit;
	map<set<int>, int> next;
	print(m, true); 
	join(m, next);
	prune(m, next);
	
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
		for(map<set<int>, int>::iterator it=m.begin(); it!=m.end();){
			if(it->second<sup){
				tit = it;
				tit++;
				m.erase(it);
				it = tit;
			}
			else
			it++;
		}
		print(m, true);
		join(m, next);
		prune(m, next); 
	}
}

int main(){
	fstream fin, fout; int tmp, sup;
	bool first=true;
	final.clear();
	fin.open("tid_pid.txt", ios::in);
	fout.open("apriori_out.txt", ios::out|ios::trunc);
	fout.close();
	cout<<"Enter min support: "; cin>>sup;
	map<set<int>, int> m, next; set<int> t; map<set<int>, int>::iterator tit;
	//Bring file to memory
	set<set<int> > file; set<int> f;
	//Make partitions
	while(!fin.eof()){
		for(int i=0; i<100&&!fin.eof(); ){
			if(first){
				//ignore tid
				fin>>tmp; first=false; continue;
			}
			fin>>tmp;
			if(tmp==-999){
				file.insert(f); f.clear();
				i++;
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
			
		for(map<set<int>, int>::iterator it=m.begin(); it!=m.end();){
			if(it->second<sup){
				tit = it;
				tit++;
				m.erase(it);
				it = tit;
			}
			else
			it++;
		}
		cout<<file.size();
		apriori(file, m, sup/2);
		file.clear();
		m.clear();
		fout.open("apriori_out.txt", ios::out|ios::app);
		fout<<"END OF PARTITION\n";
		fout.close();
	}
	//prune(m, sup); 
	
	//Remove infrequents w.r.t original support from final
	for(map<set<int>, int>::iterator it=final.begin(); it!=final.end();){
		if(it->second<sup){
			tit = it;
			tit++;
			final.erase(it);
			it = tit;
		}
		else
		it++;
	}
	
	print(final, false);
	
	fin.close();
	return 0;
}

