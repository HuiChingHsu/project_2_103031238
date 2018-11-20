#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <limits.h>

using namespace std;

class position
{
public:
    int row;
    int col;
};
int main(int argc, char* argv[])
{
    int row_bound, col_bound, battery;
    
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
    
    vector< vector<int> > Map;
    if(file.is_open()){
        file >> row_bound;
        file >> col_bound;
        file >> battery;

//cout << row_bound << " " << col_bound << " " << battery << endl;
 
        for(int i=0; i<row_bound; i++){  // creating the map
            vector<int> Row;
            for(int j=0; j<col_bound; j++){
                char value;
                int num;
                file >> value;
                if(value == '0') num = 0;
                else if(value == '1')num = 1;
                else if(value == 'R') num = INT_MAX;
//cout << num <<" ";
                Row.push_back(num);
            }
//cout << endl;
            Map.push_back(Row);
        }    
        
    }else{
        cout << "Unable to open file" << endl;
        return 0;
    }

    //output result
    /*
    data_name = "./"+id+"./final.peak";
    output.open(data_name,ios::out);

    output << ans_num << "\n";
    if (output.is_open()) {

        while(!result.empty()){
            output << result.front().row << " " << result.front().col << "\n";
            result.pop();
        }

	}
	else{
        cout << "Unable to open file" << endl;
        return 0;
    } 

	file.close();
	output.close();
    */
    return 0;
}