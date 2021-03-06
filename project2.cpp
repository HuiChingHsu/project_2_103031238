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

void BFS(position s, int B, vector< vector<int> > map, position *** adj)
{
    list<position> Queue;
    map[s.row][s.col] += 2;
    Queue.push_back(s);

    while(!Queue.empty()){
        
        s.row = Queue.front().row;
        s.col = Queue.front().col;
//cout << s.row << s.col << " " << map[s.row][s.col] <<endl;
        cout << s.row << " " << s.col << endl;  

        Queue.pop_front();

        for(int i=0; adj[s.row][s.col][i].row != INT_MAX; i++){

            if( map[adj[s.row][s.col][i].row][adj[s.row][s.col][i].col] == 0){
                map[adj[s.row][s.col][i].row][adj[s.row][s.col][i].col] += 2;
                Queue.push_back(adj[s.row][s.col][i]);
            }
//cout << adj[s.row][s.col][i].row << adj[s.row][s.col][i].row << endl;
        }
    }
}

int main(int argc, char* argv[])
{
    int row_bound, col_bound, battery;
    position robot, start_pos;
    
    ifstream file;
    ofstream output;
    string data_name = "";
    string id = "";
    int i =0;
    for(;argv[1][i]!='\0'; i++){
        id += argv[1][i];
    }
    data_name = "./" + id + "/floor.data";
	file.open(data_name, ios::in);
    
    vector< vector<int> > Map;
    if(file.is_open()){
        file >> row_bound;
        file >> col_bound;
        file >> battery;
 
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
    } //end of inputting data (Map -> visiting state) R -> INT_MIN

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
            /*for(int k=0; k<4; k++){
                cout << adjList[i][j][k].row << " " << adjList[i][j][k].col << " ";
            }
            cout << endl;*/
        }
    }//end of creating an adjcency list

    BFS(start_pos, battery, Map, adjList);

    //output result
    /*
    data_name = "./"+id+"/floor.peak";
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