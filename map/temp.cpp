#include <iostream>
#include <map>

using namespace std;

int	main()
{
	map<int, string>	test1;

	cout <<"size= " << test1.size() << endl;
	cout << test1.empty() << endl;
	map<int, string>::iterator	iter = test1.begin();
	cout << iter->first << endl;
	iter = test1.end();
	cout << iter->first << endl;
	// cout << test1[1] << endl;
	cout << test1[2] << endl;
	cout <<"size= " << test1.size() << endl;
	
	// cout << test1.at(1) << endl;

	cout << "-----after insert----" << endl;
	test1.insert(make_pair(1, (string)"aaaa"));
	cout <<"size= " << test1.size() << endl;
	cout << test1.empty() << endl;
	iter = test1.begin();
	cout << iter->second << endl;
	// iter = test1.end();
	iter++;
	cout << iter->second << endl;
	cout << test1[2] << endl;
	// cout << test1.at(1) << endl;
	


}