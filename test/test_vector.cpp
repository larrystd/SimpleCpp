#include <vector>
#include <cstdlib>
#include <list>
#include <iostream>


using namespace std;

int main() {
    vector<int> authors = {1,2,3 };
	vector<int>articles = { 1,2,3 };
	articles.assign(authors.begin(), authors.end());
 
	for (auto c : articles)
	{
		cout << c << endl;
    }

    for (int i = 0; i < 5; i++) {
        cout << clock() <<endl;
    }
    return 0;
}
