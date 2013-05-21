#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
int min(int a, int b, int c) {
	int result;
	if (a<b)
		result=a;
	else result=b;
	if (result<c)
		return result;
	else return c;
}
bool forSort(pair <string, int> p1, pair <string, int> p2) {
	if (p1.first>p2.first)
		return false;
	else 
		return true;
}
class SuffixArray {
private:
	string str;
	vector <int> myArray;
	vector <int> allEntries;
public:
	SuffixArray (string in) {
		str=in;
		vector <pair <string,int> > temp;
		for (int i=0; i<in.size(); ++i) {
			//long int c = min(str.find_first_of('#'),str.find_first_of('$'),str.find_first_of('&'));
			temp.push_back(pair <string, int> (str.substr(i), i));
		}
		std::sort(temp.begin(), temp.end(), forSort);
		//for (int i=0; i<temp.size(); ++i)
			//cout << temp[i].first << endl;
		for (int i=0; i<temp.size(); ++i)
			myArray.push_back(temp[i].second);
	}
	void print () const{
		cout << '{';
		for (int i=0; i<myArray.size(); ++i)
			if (i!=myArray.size()-1)
				cout << myArray[i] <<", ";
			else
				cout << myArray[i] << "}\n";
	}
	int search (int left, int right, string s) {
		//cout << str.find(s) << endl;
		if (str.find(s)>str.size()) {
			cout << "No entries of \"" << s << "\" in \"" << str << "\"" << endl;
			return -1;
		}
		allEntries.clear();
		int middle;
		if (left==0 && right==1)
			middle=0;
		else
			if (left+1==right)
				middle=right;
			else
				middle = (right+left)/2;
		if (str.substr(myArray[middle]).substr(0,s.size())==s) {
			allEntriesSearch(middle,s);
			return myArray[middle];
		}
		else
			if (str.substr(myArray[middle]).substr(0,s.size())<s)
				return search(middle, right, s);
			else
				return search(left, middle, s);
	}
	void allEntriesSearch  (int index, string s) {
		int min=index;
		int max=index;
		while (str.substr(myArray[--min]).substr(0,s.size())==s);
		while (str.substr(myArray[++max]).substr(0,s.size())==s);
		for (int i=min+1; i<=max-1; ++i)
			allEntries.push_back(myArray[i]);
		cout << "All entries of \"" << s << '\"' <<endl;
		sort(allEntries.begin(), allEntries.end());
		for (int i=0; i<allEntries.size(); ++i)
			cout << allEntries[i] << ' ';
		cout << endl;
	}
	string LCS () {
		int k=0;
		int start=0, end=0;
		string result="";
		while (end!=myArray.size()) {
			bool first=0, second=0, third=0;
			while (!(first && second && third)) {
				if (str.substr(myArray[end]).find('#')<=str.size() && str.substr(myArray[end]).find('$')<=str.size() && str.substr(myArray[end]).find('&')<=str.size())
					first=true;
				else
					if (str.substr(myArray[end]).find('#')>str.size() && str.substr(myArray[end]).find('$')<=str.size() && str.substr(myArray[end]).find('&')<=str.size())
						second=true;
					else
						if (str.substr(myArray[end]).find('&')<=str.size() && str.substr(myArray[end]).find('#')>str.size() && str.substr(myArray[end]).find('$')>str.size())
							third=true;
				end++;
				if (end==myArray.size())
					break;
			}
			end--;
			if (end==start)
				break;
			string temp=LCP(start, end);
			if (temp.size()>result.size())
				result=temp;
			start++;
			end=start;
		}
		return result;
	}
	string LCP (int start, int end) {
		string s1,s2;
		s1=str.substr(myArray[start]);
		s2=str.substr(myArray[end]);
		int k,id;
		if (s1.find('#')<=s1.size() && s1.find('$')<=s1.size() && s1.find('&')<=s1.size()) {
			k=s1.find('#');
			id=1;
		}
		else
			if (s1.find('#')>s1.size() && s1.find('$')<=s1.size() && s1.find('&')<=s1.size()) {
				k=s1.find('$');
				id=2;
			}
			else
				if (s1.find('#')>s1.size() && s1.find('$')>s1.size() && s1.find('&')<=s1.size()) {
					k=s1.find('&');
					id=3;
				}
		s1=s1.substr(0, k);

		if (s2.find('#')<=s2.size() && s2.find('$')<=s2.size() && s2.find('&')<=s2.size()) {
			k=s2.find('#');
			if (id==1)
				return "";
		}
		else
			if (s2.find('#')>s2.size() && s2.find('$')<=s2.size() && s2.find('&')<=s2.size()) {
				k=s2.find('$');
				if (id==2)
					return "";
			}
			else
				if (s2.find('#')>s2.size() && s2.find('$')>s2.size() && s2.find('&')<=s2.size()) {
					k=s2.find('&');
					if (id==3)
						return "";
				}
		s2=s2.substr(0, k);

		int i=0;
		while (i<s1.size() && i<s2.size() && s1[i]==s2[i])
			++i;
		return s1.substr(0,i);
	}
};