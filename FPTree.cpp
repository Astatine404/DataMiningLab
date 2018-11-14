#include<iostream>
#include<fstream>
#include<bits/stdc++.h>

using namespace std;
int sup, itemNos;
vector<pair<int, int> > items;
map<int, int> data;

typedef struct FPNode {
	int item;
	int freq;
	vector<FPNode*> child;
	FPNode* next;
} FPptr;

map<int, FPNode*> header;

bool itemComp(pair<int, int> p, pair<int, int> q){
	if(p.second<q.second)
	return true;
	else
	return false;
}

bool fileComp(int p, int q){
	if(data[p]>data[q])
	return true;
	else
	return false;
}

void readFile(map<int, int> &m, vector<vector<int> > &dat){
	map<int, set<int> > file; int ctr=1;
	fstream fin; bool first=true; int tmp;
	fin.open("textbook.txt", ios::in);
	set<int> f;
	while(!fin.eof()){
			if(first){
				//ignore tid
				fin>>tmp; first=false; continue;
			}
			fin>>tmp; //cout<<tmp;
			if(tmp==-999){
				file[ctr++] = f; f.clear();
				//ignore tid
				fin>>tmp; 
				continue;
			}
			f.insert(tmp);
			if(m.find(tmp)==m.end())
			m[tmp] = 1;
			else
			m[tmp]++;
	}
	//Erase infrequent
	map<int, int>::iterator t;
	set<int> infreq;
	for(map<int, int>::iterator it=m.begin(); it!=m.end();){
		if(it->second<sup){
			//mark infreq
			infreq.insert(it->first);
			
			t = it; t++;
			m.erase(it);
			it = t;
		}
		else
			it++;
	}
	
	//convert set<set> to vector<vector>
	vector<int> tmpVect;
	for(map<int, set<int> >::iterator i=file.begin(); i!=file.end(); i++){
		tmpVect.clear();
 		for(set<int>::iterator j=i->second.begin(); j!=i->second.end(); j++){
 			if(infreq.find(*j)==infreq.end())
			tmpVect.push_back(*j);
 		}
 		dat.push_back(tmpVect);
 	}
 	//cout<<dat.size()<<endl;
	fin.close();
	
}

void preorder(FPptr *root){
	cout<<root->item<<":"<<root->freq<<" ";
	for(int i=0; i<root->child.size(); i++)
		preorder(root->child[i]);
}

void levelorder(FPptr *root){
	FPptr *curr;
	queue<FPNode*> q;
	q.push(root);
	q.push(NULL);
	while(true){
		curr = q.front(); q.pop();
		if(curr==NULL){
			cout<<endl;
			if(q.empty())
			break;
			q.push(NULL);
			continue;
		}
		for(int i=0; i<curr->child.size(); i++)
		q.push(curr->child[i]);
		
		cout<<curr->item<<":"<<curr->freq<<" ";
	}
	
}

void createBranch(vector<int> &tran, FPptr *root, int pos){
	if(pos>=tran.size())
	return;
	//search for tran[pos] in children
	FPptr *foundChild = NULL;
	for(int i=0; i<root->child.size(); i++){
		if(root->child[i]->item == tran[pos]){
			foundChild = root->child[i];
			foundChild->freq++;
			break;
		}
	}
	if(foundChild==NULL){
		foundChild = new FPNode();
		foundChild->item = tran[pos];
		foundChild->freq = 1;
		foundChild->next = NULL;
		vector<FPNode*> tmp;
		foundChild->child = tmp;
		root->child.push_back(foundChild);
	}
	createBranch(tran, foundChild, pos+1);
	
} 

void constHeader(int i, FPptr** prev, FPptr* root){
	if(root->item==i){
		if(*prev)
		(*prev)->next = root;
		else
		header[i] = root;
		
		*prev = root;
	}
	for(int j=0; j<root->child.size(); j++)
		constHeader(i, prev, root->child[j]);
		
}

void printHeader(FPptr* curr){
	if(!curr)
	return;
	cout<<curr->item<<": "<<curr->freq<<"  ";
	printHeader(curr->next);
}

int main(){
	vector<vector<int> > file;
	cout<<"Enter min support: "; cin>>sup;
	cout<<"Enter total no. of items: "; cin>>itemNos;
	readFile(data, file);
	for(map<int, int>::iterator it=data.begin(); it!=data.end(); it++){
		pair<int, int> currPair;
		currPair.first = it->first;
		currPair.second = it->second;
		items.push_back(currPair);
	}
	sort(items.begin(), items.end(), itemComp);
	//sort vector<vector> according to items
	for(int i=0; i<file.size(); i++){
		sort(file[i].begin(), file[i].end(), fileComp);
	}
	FPptr *root = new FPNode();
	root->item = -1;
	root->freq = 0;
	root->next = NULL;
	vector<FPNode*> tmp;
	root->child = tmp;
	
	for(int i=0; i<file.size(); i++){
		for(int j=0; j<file[i].size(); j++)
		cout<<file[i][j];
		cout<<endl;
	}
	cout<<endl;
	for(int i=0; i<file.size(); i++){
		createBranch(file[i], root, 0);
	}
	//construct header
	FPptr* prev;
	for(int i=1; i<=itemNos; i++){
		//preorder search
		prev = NULL;
		constHeader(i, &prev, root);
	}
	//print header
	for(map<int, FPNode*>::iterator it=header.begin(); it!=header.end(); it++){
		printHeader(it->second);
		cout<<endl;
	}
	cout<<endl;
	//levelorder
	levelorder(root);
	return 0;
}

