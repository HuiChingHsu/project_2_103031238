#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <limits.h>
#include <queue>
#include <list>

using namespace std;

class position
{
public:
    int row;
    int col;
    position operator = (const position& p){
        position P;
        P.row = p.row;
        P.col = p.col;
        return P;
    }
};

/*void BFS(position s, int * map, position *** adj)
{
    list<position> Queue;
    map[s.row][s.col] += 2;
    Queue.push_back(s);

    while(!Queue.empty()){
        s = Queue.front();
        if(map[s.row][s.col] != INT_MIN+2) cout << s.row << " " << s.col;
        Queue.pop_front();

        int x=0;
        for(int i=0; adj[i][j][x]; )
    }
}*/

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

        position robot, start_pos;
 
        for(int i=0; i<row_bound; i++){  // creating the map
            vector<int> Row;
            for(int j=0; j<col_bound; j++){
                char value;
                int num;
                file >> value;
                if(value == '0') num = 0;
                else if(value == '1') num = 1;
                else if(value == 'R'){
                    robot.row = i, start_pos.row = i;
                    robot.col = j, start_pos.col = j;
                    num = INT_MIN;
                }
                Row.push_back(num);
            }
            Map.push_back(Row);
        }    
        
    }else{
        cout << "Unable to open file" << endl;
        return 0;
    } //end of inputting data (Map -> visiting state)

    position*** adjList = new position** [row_bound];
    int x;
    for(int i=0; i<row_bound; i++){
            adjList[i] = new position* [col_bound];
        for(int j=0; j<col_bound; j++){
            adjList[i][j] = new position [4];
            
            for(int k=0; k<4; k++){
                adjList[i][j][k].row = INT_MAX;
                adjList[i][j][k].col = INT_MAX;
            }  //initializing adjList;
            x = 0;
            if(Map[i][j] == 0 || Map[i][j] == INT_MIN){
                if(i>0 && Map[i-1][j] == 0){
                    adjList[i][j][x].row = i-1;
                    adjList[i][j][x].col = j;
                    x++;
                }
                if(i<row_bound-1 && Map[i+1][j] == 0){
                    adjList[i][j][x].row = i+1;
                    adjList[i][j][x].col = j;
                    x++;
                }
                if(j>0 && Map[i][j-1] == 0){
                    adjList[i][j][x].row = i;
                    adjList[i][j][x].col = j-1;
                    x++;
                }
                if(j<col_bound-1 && Map[i][j+1] == 0){
                    adjList[i][j][x].row = i;
                    adjList[i][j][x].col = j+1;
                }
            }
            
        }
    }//end of creating an adjcency list

    for(int i=0; i<4; i++){
        cout << adjList[1][1][i].row << " " << adjList[1][1][i].col << endl;
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