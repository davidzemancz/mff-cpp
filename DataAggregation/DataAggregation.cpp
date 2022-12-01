#include <iostream>
#include <fstream>
#include <string>
#include<tuple>
#include <map>

using namespace std;

map<string, char> my_map = {
    { 'A', '1' },
    { 'B', '2' },
    { 'C', '3' }
};

void readinput()
{
    string line;
    while (getline(cin, line))  //input from the file in.txt
    {
        cout << line << endl;   //output to the file out.txt
    }
}

int main()
{
    const string inFile = "C:\\Users\\david\\OneDrive\\MFFUK\\3-1\\C++\\mff-cpp\\Docs\\test.input";
    const string outFile = "C:\\Users\\david\\OneDrive\\MFFUK\\3-1\\C++\\mff-cpp\\Docs\\test1.output";
    
    ifstream in(inFile);
    streambuf* cinbuf = cin.rdbuf(); //save old buf
    cin.rdbuf(in.rdbuf()); //redirect cin to in.txt!

    ofstream out(outFile);
    streambuf* coutbuf = cout.rdbuf(); //save old buf
    cout.rdbuf(out.rdbuf()); //redirect cout to out.txt!

    readinput(); 

    cin.rdbuf(cinbuf);   //reset to standard input again
    cout.rdbuf(coutbuf); //reset to standard output agai

    return 0;
}
