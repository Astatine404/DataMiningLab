#include<iostream>
#include<fstream>
#include<bits/stdc++.h>
using namespace std;
map<set<int>, int> final;
vector<int> item_list;
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

void apriori(set<set<int> > &file, map<set<int>, int> &dc, map<set<int>, int> &ds, map<set<int>, int> &sc, map<set<int>, int> &ss,  int sup){
	map<set<int>, int>::iterator tit;
	set<set<int> >::iterator cit=file.begin();
	while(!ds.empty()&&!dc.empty()){
		//Take 100 transactions at a time
		for(int i=0; cit!=file.end()&&i<100; cit++, i++){
			//Traverse for DC
			for(map<set<int>, int>::iterator i=dc.begin(); i!=dc.end(); i++){
				bool present = true;
				//check if this transaction contains all of current map iterator
				for(set<int>::iterator j=i->first.begin(); j!=i->first.end(); j++){
					if((*cit).find(*j)==(*cit).end()){
						present = false;
						break;
					}
				}
				if(present)
				i->second++;
			}
			//Traverse for DS
			for(map<set<int>, int>::iterator i=ds.begin(); i!=ds.end(); i++){
				bool present = true;
				//check if this transaction contains all of current map iterator
				for(set<int>::iterator j=i->first.begin(); j!=i->first.end(); j++){
					if((*cit).find(*j)==(*cit).end()){
						present = false;
						break;
					}
				}
				if(present)
				i->second++;
			}
			//Check if become frequent in DC
			for(map<set<int>, int>::iterator i=dc.begin(); i!=dc.end();){
				if(i->second>=sup){
					//Move from DC to DS
					ds[i->first] = i->second;
					tit = i; tit++;
					dc.erase(i);
					i = tit; 
					
					//Generate immediate superset of 'i' and check if all subsets there in ss or ds
					for(int item=0; item<item_list.size(); item++){
						if(i->first.find(item_list[item])!=i->first.end())
						continue;
						set<int> curr = i->first;
						curr.insert(item_list[item]);
						//generate power set of curr
						bool valid = true;
						int pow_size = pow(2, curr.size());
						set<int>::iterator sit;
						for(int ctr = 0; ctr<pow_size; ctr++){
							set<int> subset;
							sit = curr.begin();
							for(int j=0; j<curr.size(); j++, sit++){
								// check if jth bit is set
								if(ctr&(1<<j))
								subset.insert(*sit);
							}
							if(subset.empty())
							continue;
							if(ss.find(subset)==ss.end()&&ds.find(subset)==ds.end()){
								valid = false;
								break;
							}
						}
						if(valid)
						dc[curr] = 0;
					}
				}
				else
				i++;
			}
		}
		if(cit==file.end()){
			//Move dc to sc and ds to ss 
			for(map<set<int>, int>::iterator i=dc.begin(); i!=dc.end();){
				sc[i->first] = i->second;
				tit = i; tit++;
				dc.erase(i);
				i = tit;
			}
			for(map<set<int>, int>::iterator i=ds.begin(); i!=ds.end();){
				ss[i->first] = i->second;
				tit = i; tit++;
				ds.erase(i);
				i = tit;
			}
			cit = file.begin();
		}
	}
	print(ss, false);
	
}

int main(){
	fstream fin, fout; int tmp, sup;
	bool first=true;
	final.clear();
	fin.open("tid_pid.txt", ios::in);
	fout.open("apriori_out.txt", ios::out|ios::trunc);
	fout.close();
	cout<<"Enter min support: "; cin>>sup;
	map<set<int>, int> dc, ds, sc, ss; set<int> t; map<set<int>, int>::iterator tit;
	//Bring file to memory
	set<set<int> > file; set<int> f;
	//Collect all 1-itemsets in dc and move transactions to memory
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
		if(dc.find(t)==dc.end())
		dc[t] = 0;
		if(find(item_list.begin(), item_list.end(), tmp)==item_list.end())
		item_list.push_back(tmp);
	
	}
	fin.close();
	
	apriori(file, dc, ds, sc, ss, sup);
	return 0;
}

