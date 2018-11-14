#include<bits/stdc++.h>

using namespace std;

const int k=4;
vector<int> cluster[k];
float means[k];

int smallestDiff(float diff[k])
{
	float small=diff[0];
	int pos=0;
	
	for(int i=1;i<k;i++)
	if(diff[i]<small)
	{
		small=diff[i];
		pos=i;
	}
	
	return pos;
}

void assignClusters(vector<int> input)
{
	for(int i=0;i<input.size();i++)
	{
		float diff[k];
		for(int j=0;j<k;j++)
		diff[j]=abs((float)input[i]-means[j]);
		
		int pos = smallestDiff(diff);
		
		cluster[pos].push_back(input[i]);
	}
}

int checkMeans(float oldmeans[k])
{
	int flag=0;
	for(int i=0;i<k;i++)
	{
		if(oldmeans[i]!=means[i])
		{
			flag=1;
			break;
		}
	}

	if(flag==1)
	return 1;
	else
	return 0;
}

int updateMeans()
{
	float oldmeans[k];
	for(int i=0;i<k;i++)
	oldmeans[i]=means[i];
	
	for(int i=0;i<k;i++)
	{
		float sum=0;
		for(int j=0;j<cluster[i].size();j++)
		sum+=(float)cluster[i][j];
		
		sum/=(float)cluster[i].size();
		
		means[i]=sum;
	}
	
	return checkMeans(oldmeans);
}

void viewClusters()
{
	for(int i=0;i<k;i++)
	{
		cout<<"The cluster mean is "<<means[i]<<"The elements are ";
		for(int j=0;j<cluster[i].size();j++)
		cout<<cluster[i][j]<<" ";
		cout<<endl;
	}
}

int main()
{
	vector<int> input;
	fstream f;
	f.open("kmeans.txt",ios::in);
	
	while(!f.eof())
	{
		int num;
		f>>num;
		input.push_back(num);
	}
	
	for(int i=0;i<k;i++)
	means[i]=(float)input[i];
	
	int flag=1;

	while(flag)
	{
		cout<<endl;
		
		assignClusters(input);
		flag = updateMeans();	
		viewClusters();

		if(flag)
		for(int i=0;i<k;i++)
		cluster[i].clear();
	}
	
	cout<<"The final clusters and their mean is \n";
	viewClusters();
	
	return 0;
}
