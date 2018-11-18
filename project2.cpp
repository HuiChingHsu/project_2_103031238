#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class node
{
    public:
    int * adjList
};
int main(int argc, char* argv[])
{
    int row, col;
    
    ifstream file;
    ofstream output;
    string data_name = "";
    string id = "";
    int i =0;
    for(;argv[1][i]!='\0'; i++){
        id += argv[1][i];
    }
    data_name = "./" + id + "/matrix.data";
	file.open(data_name, ios::in);
    if(file.is_open){
        file >> row;
        file >> col;
    }
    
    return 0;
}