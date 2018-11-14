#include<iostream>
#include<fstream>
#include<bits/stdc++.h>
using namespace std;

typedef struct tuple row_type;
typedef struct TNode tptr;

struct tuple {
	string outlook;
	string temp;
	string humidity;
	string windy;
	string play;
};

struct TNode {
	string attr;
	map<string, tptr*> child_list;
};

map<string, string*> dict;
string outlook[] = {"sunny", "overcast", "rainy"};
string temp[] = {"hot", "mild", "cool"};
string humidity[] ={"normal", "high"};
string windy[] = {"true", "false"};
float dataEnt;

vector<row_type> readData(set<string> &featureSet){
	fstream fin; string tmp;
	vector<row_type> result;
	fin.open("dataset.txt", ios::in);
	while(!fin.eof()){
		row_type currRow;
		fin>>currRow.outlook;
		fin>>currRow.temp;
		fin>>currRow.humidity;
		fin>>currRow.windy;
		fin>>currRow.play;
		result.push_back(currRow);
	}
	featureSet.insert("outlook");
	featureSet.insert("temp");
	featureSet.insert("humidity");
	featureSet.insert("windy");
	return result;
}

float getDatasetEntropy(vector<row_type> &data){
	float nyes=0, len=data.size();
	for(int i=0; i<data.size(); i++){
		if(data[i].play=="yes")
			nyes++;
	}
	float pyes = -(nyes/len)*log2(nyes/len);
	float pno = -((len-nyes)/len)*log2((len-nyes)/len);
	
	return pyes + pno;
}

tptr* getNode(vector<row_type> &data, set<string> &featureSet){
	//Find max info gain attr in featureSet
	string attr; float maxGain=-999.0, len=data.size();
	if(featureSet.find("outlook")!=featureSet.end()){
		cout<<"Outlook:\n";
		float nSun=0, nOver=0, nRain=0, pSun=0, pOver=0, pRain=0;
		for(int i=0; i<data.size(); i++){
			if(data[i].outlook=="sunny"){
				if(data[i].play=="yes")
					pSun++;
				nSun++;
			}
			else if(data[i].outlook=="overcast"){
				if(data[i].play=="yes")
					pOver++;	
				nOver++;
			}
			else if(data[i].outlook=="rainy"){
				if(data[i].play=="yes")
					pRain++;
				nRain++;
			}
		}
		cout<<pSun<<" "<<pOver<<" "<<pRain<<endl;
		cout<<nSun<<" "<<nOver<<" "<<nRain<<endl;
		float eSun=0, eOver=0, eRain=0;
		if(pSun!=nSun)
		eSun = -(pSun/nSun)*log2(pSun/nSun)-((nSun-pSun)/nSun)*log2((nSun-pSun)/nSun);
		if(pOver!=nOver)
		eOver = -(pOver/nOver)*log2(pOver/nOver)-((nOver-pOver)/nOver)*log2((nOver-pOver)/nOver);
		if(pRain!=nRain)
		eRain = -(pRain/nRain)*log2(pRain/nRain)-((nRain-pRain)/nRain)*log2((nRain-pRain)/nRain);
		cout<<eSun<<" "<<eOver<<" "<<eRain<<endl;
		float outGain = dataEnt - ((nSun/len)*eSun+(nOver/len)*eOver+(nRain/len)*eRain);
		cout<<outGain<<endl;
		if(outGain>maxGain){
			attr = "outlook";
			maxGain = outGain;
		}		
	}
	
	if(featureSet.find("temp")!=featureSet.end()){
		cout<<"Temp:\n";
		float nSun=0, nOver=0, nRain=0, pSun=0, pOver=0, pRain=0;
		for(int i=0; i<data.size(); i++){
			if(data[i].temp=="hot"){
				if(data[i].play=="yes")
					pSun++;
				nSun++;
			}
			else if(data[i].temp=="mild"){
				if(data[i].play=="yes")
					pOver++;	
				nOver++;
			}
			else if(data[i].temp=="cool"){
				if(data[i].play=="yes")
					pRain++;
				nRain++;
			}
		}
		cout<<pSun<<" "<<pOver<<" "<<pRain<<endl;
		cout<<nSun<<" "<<nOver<<" "<<nRain<<endl;
		float eSun=0, eOver=0, eRain=0;
		if(pSun!=nSun&&pSun!=0)
		eSun = -(pSun/nSun)*log2(pSun/nSun)-((nSun-pSun)/nSun)*log2((nSun-pSun)/nSun);
		if(pOver!=nOver&&pOver!=0)
		eOver = -(pOver/nOver)*log2(pOver/nOver)-((nOver-pOver)/nOver)*log2((nOver-pOver)/nOver);
		if(pRain!=nRain&&pRain!=0)
		eRain = -(pRain/nRain)*log2(pRain/nRain)-((nRain-pRain)/nRain)*log2((nRain-pRain)/nRain);
		cout<<eSun<<" "<<eOver<<" "<<eRain<<endl;
		float outGain = dataEnt - ((nSun/len)*eSun+(nOver/len)*eOver+(nRain/len)*eRain);
		cout<<outGain<<endl;
		if(outGain>maxGain){
			attr = "temp";
			maxGain = outGain;
		}				
	}
	
	if(featureSet.find("humidity")!=featureSet.end()){
		cout<<"Humidity:\n";
		float nSun=0, nOver=0, pSun=0, pOver=0;
		for(int i=0; i<data.size(); i++){
			if(data[i].humidity=="normal"){
				if(data[i].play=="yes")
					pSun++;
				nSun++;
			}
			else if(data[i].humidity=="high"){
				if(data[i].play=="yes")
					pOver++;	
				nOver++;
			}
		}
		cout<<pSun<<" "<<pOver<<endl;
		cout<<nSun<<" "<<nOver<<endl;
		float eSun=0, eOver=0;
		if(pSun!=nSun&&pSun!=0)
		eSun = -(pSun/nSun)*log2(pSun/nSun)-((nSun-pSun)/nSun)*log2((nSun-pSun)/nSun);
		if(pOver!=nOver&&pOver!=0)
		eOver = -(pOver/nOver)*log2(pOver/nOver)-((nOver-pOver)/nOver)*log2((nOver-pOver)/nOver);
		cout<<eSun<<" "<<eOver<<endl;
		float outGain = dataEnt - ((nSun/len)*eSun+(nOver/len)*eOver);
		cout<<outGain<<endl;
		if(outGain>maxGain){
			attr = "humidity";
			maxGain = outGain;
		}				
	}
	
	if(featureSet.find("windy")!=featureSet.end()){
		cout<<"Windy:\n";
		float nSun=0, nOver=0, pSun=0, pOver=0;
		for(int i=0; i<data.size(); i++){
			if(data[i].windy=="true"){
				if(data[i].play=="yes")
					pSun++;
				nSun++;
			}
			else if(data[i].windy=="false"){
				if(data[i].play=="yes")
					pOver++;	
				nOver++;
			}
		}
		cout<<pSun<<" "<<pOver<<endl;
		cout<<nSun<<" "<<nOver<<endl;
		float eSun=0, eOver=0, eRain=0;
		if(pSun!=nSun&&pSun!=0)
		eSun = -(pSun/nSun)*log2(pSun/nSun)-((nSun-pSun)/nSun)*log2((nSun-pSun)/nSun);
		if(pOver!=nOver&&pOver!=0)
		eOver = -(pOver/nOver)*log2(pOver/nOver)-((nOver-pOver)/nOver)*log2((nOver-pOver)/nOver);
		cout<<eSun<<" "<<eOver<<endl;
		float outGain = dataEnt - ((nSun/len)*eSun+(nOver/len)*eOver);
		cout<<outGain<<endl;
		if(outGain>maxGain){
			attr = "windy";
			maxGain = outGain;
		}	
	}
	
	//Create attr node
	tptr *root = new tptr;
	root->attr = attr;
	map<string, tptr*> child_list;
	if(featureSet.size()==0)
	return root;
	cout<<"Chosen Attr: "<<attr<<endl;
	featureSet.erase(attr);
	int attrlist_size;
	if(attr=="outlook"||attr=="temp")
		attrlist_size = 3;
	else
		attrlist_size = 2;
	
	for(int i=0; i<attrlist_size; i++){
		vector<row_type> tmpData;
		//find data having attr=dict[attr][i]
		for(int j=0; j<data.size(); j++){
			if(attr=="outlook"){
				if(data[j].outlook==dict[attr][i])
					tmpData.push_back(data[j]);
			}
			else if(attr=="temp"){
				if(data[j].temp==dict[attr][i])
					tmpData.push_back(data[j]);
			}
			else if(attr=="humidity"){
				if(data[j].humidity==dict[attr][i])
					tmpData.push_back(data[j]);
			}
			else if(attr=="windy"){
				if(data[j].windy==dict[attr][i])
					tmpData.push_back(data[j]);
			}
		}
		int nyes= 0 , nno = 0;
		//check if all yes or all no
		for(int k=0; k<tmpData.size(); k++){
			if(tmpData[k].play=="yes")
				nyes++;
			else
				nno++;
		}
		if(nno==0){
			cout<<"yesNode!\n";
			tptr* yesNode = new tptr; yesNode->attr="yes";
			child_list[dict[attr][i]] = yesNode;
		}
		else if(nyes==0){
			cout<<"noNode!\n";
			tptr* noNode = new tptr; noNode->attr="no";
			child_list[dict[attr][i]] = noNode;
		}
		else
			child_list[dict[attr][i]] = getNode(tmpData, featureSet);
	
	}		
	root->child_list = child_list;
	return root;
}

int main(){
	vector<row_type> data;
	set<string> featureSet;
	dict["outlook"] = outlook;
	dict["temp"] = temp;
	dict["humidity"] = humidity;
	dict["windy"] = windy;
	data = readData(featureSet);
	dataEnt = getDatasetEntropy(data);
	cout<<"Data Entropy: "<<dataEnt<<endl;
	tptr *root = getNode(data, featureSet);
	return 0;
}
