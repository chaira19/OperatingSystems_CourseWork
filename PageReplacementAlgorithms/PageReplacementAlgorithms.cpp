#include<iostream>
#include<vector>
#include<unordered_set>

using namespace std;

// stack implementation of LRU algorithm
int LRUStack(vector<int> arr, int frames)
{
	int faults = 0;
	unordered_set<int> pages;
	vector<int> st;
	
	for(int i = 0;i<arr.size();i++)
	{
		if(pages.find(arr[i]) == pages.end())
		{
			faults++;
			if(pages.size()<frames)
			{
				pages.insert(arr[i]);
				st.push_back(arr[i]);
			}
			else
			{
			    int temp = st.front();
			    
				st.erase(st.begin());
				st.push_back(arr[i]);
				
				pages.erase(temp);
				pages.insert(arr[i]);
			}
		}
		else
		{
			for(int j = 0;j<st.size();j++)
			{
				if(st[j] == arr[i])
				{
					st.erase(st.begin()+j);
					st.push_back(arr[i]);
				}
			}
		}
	}
	
	return faults;
}

// counter implementation of LRU algorithm
int LRUcounter(vector<int> arr, int frames)
{
	int faults = 0;
	
	unordered_map<int, int> m;            // page frames
	int counter = 0;                      // counter variable for time unit
	
	for(int i = 0;i<arr.size();i++)
	{
		counter++;                        // counter update per unit tinme
		if(m.find(arr[i]) == m.end())
		{
			faults++;
			if(m.size()<frames)
			{
				m.insert(arr[i], counter);
			}
			else
			{
				//page replacement
				int leastc = counter;
				int reppage;
				for(auto it = m.begin();it != m.end(); it++)
				{
					if(it->second < leastc)
					{
						leastc = it->second;
						reppage = it->first;
					}
				}
				
				m.erase(reppage);
				m.insert(arr[i], counter);
			}
		}
		else
		{
			//already existing, just update the counter
			m[arr[i]] = counter;
		}
	}
	
	return faults;
}
int main()
{
	int n;
	cin>>n;
	
	vector<int> v(n, 0);
	
	for(int i = 0;i<n;i++)
	{
		cin>>v[i];
	}
	
	cout<<LRUStack(v, 4);
}
