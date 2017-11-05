#include<iostream>
#include<fstream>
#include<time.h>
#include<stdlib.h>
#include<unistd.h>
#include<vector>
#include<algorithm>
#include<stdio.h>
#include<math.h>
using namespace std;
#define MIN 0
#define MAX 10000
#define LOWER_LIMIT 9000
#define UPPER_LIMIT 10000

//generating the example,the data in example is between[0,len]
void example(int len, int lower_limit, int upper_limit)
{
	int *a = new int[len];
	for (int i = 0; i < len; i++)
		a[i] = i + 1;
	int COUNT = 0;
	for (int i = 0; i < len - 2; i++)
		for (int j = i + 1; j < len - 1; j++)
			for (int k = j + 1; k < len; k++)
				if (i != j && i != k && j != k) {
					int sum = a[i] + a[j] + a[k];
					if (sum >= lower_limit
					    && sum <= upper_limit)
						COUNT++,
						    cout << a[i] << ' ' << a[j]
						    << ' ' << a[k] << endl;
				}
	cout << COUNT << endl;
	delete[]a;
}

void example_test()
{
	int len = 6;
	int lower_limit = 10;
	int upper_limit = 13;
	example(len, lower_limit, upper_limit);
}

//generating the random test instance
void generation(int len, int lower_limit, int upper_limit, int COUNT)
{
	int *a = new int[len];
	srand((int)time(0));
	char *buf = new char[10];
	sprintf(buf, "%d", COUNT);
	string s = "in_";
	s += buf;
	s += ".txt";
	ofstream outf(s.c_str());
	if (outf) {
		outf << len << ' ' << lower_limit << ' ' << upper_limit << endl;
		for (int i = 0; i < len; i++) {
			a[i] = MIN + (int)MAX * (double)rand() / (double)(RAND_MAX + 1.0);
			outf << a[i] << endl;
		}
	}
	outf.close();
	delete[]a;
}

void generation_test()
{
	int len = pow(2, 9);
	for (int COUNT = 0; COUNT < 10; COUNT++) {
                cout<<len<<endl;
		sleep(1);
                if (COUNT%2==0)
		    len *= 2;
		generation(len, LOWER_LIMIT + COUNT * 10,
			   UPPER_LIMIT + COUNT * 10, COUNT);
	}
}

//read the test input data and return vector<int>
vector < int >readData(int count)
{
	string s = "in_";
	char *buf = new char[10];
	sprintf(buf, "%d", count);
	s += buf;
	s += ".txt";
	ifstream inf(s.c_str());
	vector < int >vec;
	int num, lower_limit, upper_limit;
	inf >> num >> lower_limit >> upper_limit;
	int idata;
	while (inf >> idata)
		vec.push_back(idata);
	return vec;
}

void writeData(long long int res, int count)
{
	char *buf = new char[10];
	sprintf(buf, "%d", count);
	string s = "out_";
	s += buf;
	s += ".txt";
	ofstream outf(s.c_str());
	if (outf)
		outf << res;
	outf.close();
}

//O(n*n*n)solution to correct the answer
long long int bruteForce(vector < int >vec, int lower_limit, int upper_limit)
{
	size_t len = vec.size();
	long long int COUNT = 0;
	for (size_t i = 0; i < len - 2; i++)
		for (size_t j = i + 1; j < len - 1; j++)
			for (size_t k = j + 1; k < len; k++)
				if (i != j && i != k && j != k) {
					int sum = vec[i] + vec[j] + vec[k];
					if (sum >= lower_limit
					    && sum <= upper_limit)
						COUNT++;
				}
	return COUNT;
}

//O(n*n)solution 
long long int threeSum2(vector < int >vec, int lower_limit, int upper_limit)
{

	long long int len = vec.size();
	long long int sumcount = len * (len - 1) * (len - 2) / 6;
	int j, k, m, n, judge1, judge2;
	for (int i = 0; i < vec.size() - 2; i++) {
		j = i + 1;
		k = len - 1;
		m = j;
		n = k;
		judge1 = lower_limit - vec[i];
		judge2 = upper_limit - vec[i];
		while (j < k) {
			if (vec[j] + vec[k] < judge1) {
				sumcount -= k - j;
				j++;
			} else
				k--;
		}
		while (m < n) {
			if (vec[m] + vec[n] > judge2) {
				sumcount -= n - m;
				n--;
			} else
				m++;
		}
	}
	return sumcount;
}

//O(n*n)solution to test the space
long long int threeSum(int vec[], int leng, int lower_limit, int upper_limit)
{

	long long int len = leng;
	long long int sumcount = len * (len - 1) * (len - 2) / 6;
	int j, k, m, n, judge1, judge2;
	for (int i = 0; i < len - 2; i++) {
		j = i + 1;
		k = len - 1;
		m = j;
		n = k;
		judge1 = lower_limit - vec[i];
		judge2 = upper_limit - vec[i];
		while (j < k) {
			if (vec[j] + vec[k] < judge1) {
				sumcount -= k - j;
				j++;
			} else
				k--;
		}
		while (m < n) {
			if (vec[m] + vec[n] > judge2) {
				sumcount -= n - m;
				n--;
			} else
				m++;
		}
	}
	return sumcount;
}

void writeData_test()
{
	for (int i = 0; i < 10; i++) {
		cout << i << endl;
		vector < int >vec = readData(i);
		//cout<<bruteForce(vec,2000,10000)<<endl;
		sort(vec.begin(), vec.end());
		//cout<<threeSum2(vec,LOWER_LIMIT,UPPER_LIMIT)<<endl;
		writeData(threeSum2
			  (vec, LOWER_LIMIT + i * 10, UPPER_LIMIT + i * 10), i);
	}
}

int main()
{
	//example_test();
	generation_test();
	//writeData_test();
	for(int i=0;i<10;i++)
	   {
	   cout<<i<<endl;
	   vector<int> vec=readData(i);
	   //cout<<bruteForce(vec,2000,10000)<<endl;
	   sort(vec.begin(),vec.end());
	   //cout<<threeSum2(vec,LOWER_LIMIT,UPPER_LIMIT)<<endl;
	   writeData(threeSum2(vec,LOWER_LIMIT+i*10,UPPER_LIMIT+i*10),i);
	   }
	

	//O(n*n)solution for Oj
	/*
	   int len,lt,ut;
	   scanf("%d%d%d",&len,&lt,&ut);
	   vector<int>vec;
	   int data;
	   for(int i=0;i<len;i++)
	   {
	   scanf("%d",&data);
	   vec.push_back(data);
	   }
	   sort(vec.begin(),vec.end());
	   cout<<threeSum2(vec,lt,ut);
	   //printf("%I64d",threeSum2(vec,lt,ut));
	 */

	//O(n*n*n)solution for Oj
	/*
	   int len,lt,ut;
	   scanf("%d%d%d",&len,&lt,&ut);
	   vector<int>vec;
	   int data;
	   for(int i=0;i<len;i++)
	   {
	   scanf("%d",&data);
	   vec.push_back(data);
	   }
	   sort(vec.begin(),vec.end());
	   printf("%I64d",bruteForce(vec,lt,ut));

	 */

	//O(n*n) solution for Oj
	/*
        int len, lt, ut;
	scanf("%d%d%d", &len, &lt, &ut);
	int *vec = new int[len];
	int data;
	for (int i = 0; i < len; i++) {
		scanf("%d", &data);
		vec[i] = data;
	}
	sort(vec, vec + len);
	cout << threeSum(vec, len, lt, ut);
	delete[]vec;
        */
	return 0;
}
