#include "SuffixArray.h"

int main () {
	//string str="abcab bcac cacbcaa";
	string str="abccaa#cbcbcaaabc$bcbcaaaaaaaaaaabcbc&";
	//string str = "her#his$hers&";
	SuffixArray a(str);
	cout << str << endl << endl;
	/*a.search(0,str.size(),"z");
	a.search(0,str.size(),"a");
	a.search(0,str.size(),"br");
	a.search(0,str.size(),"ee");
	a.search(0,str.size(),"bcac");*/
	cout << a.LCS() << endl;
	system("pause");
	return 0;
}