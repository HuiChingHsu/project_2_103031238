#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <limits.h>
#include <queue>
#include <stack>

using namespace std;

class position
{
public:
    int row;
    int col;
    int step_rec = 0;
};

vector< vector<int> > Map; // changing element
int battery;
queue<position> step;

int DFS(position s, position des_pos, position*** adj, vector< vector<int> > visit)
{

    stack<position> tmp_solution;

    tmp_solution.push(s);

    int x = 0;
    while(!tmp_solution.empty() && (s.row != des_pos.row && s.col != des_pos.col)){
//cout << "done! ";
        s.row = tmp_solution.top().row;
        s.col = tmp_solution.top().col;

        if(s.row == des_pos.row && s.col == des_pos.col){
            return s.step_rec;
        }

        tmp_solution.pop();

        if(visit[s.row][s.col] == 0){
            visit[s.row][s.col] += 2;
cout << s.row << " " << s.col << "   ";
            Map[s.row][s.col] += 2;
        }

        x++;
        for(int i=0; adj[s.row][s.col][i].row != INT_MAX; i++){
            if(Map[ adj[s.row][s.col][i].row ][ adj[s.row][s.col][i].col ] == 0){
                adj[s.row][s.col][i].step_rec = x;
/*cout << adj[s.row][s.col][i].step_rec 
<< " " << adj[s.row][s.col][i].row << " " << adj[s.row][s.col][i].col << endl;*/
                tmp_solution.push(adj[s.row][s.col][i]);
            }
        }
        
    }
//cout << s.step_rec << endl;
    return s.step_rec;
}

void Steps(int row, int col, position s, position *** adj)
{
    int step_ans = 0;
    int num;
    vector< vector<int> > visit, map_rec; //map_rec -> for visit initialization

    for(int i=0; i<row; i++){ // visit? 
        vector<int> Row;
        for(int j=0; j<col; j++){
            num = Map[i][j];
            Row.push_back(num);
        }
        visit.push_back(Row);
        map_rec.push_back(Row);
    }
    
    for(int i=0; i<row; i++){
        for(int j=0; j<col; j++){

            for(int k=0; k<row; k++){
                for(int l=0; l<col; l++){
                    visit[k][l] = map_rec[k][l];
                }
            }

            if(Map[i][j] == 0){
                position des_pos;
                des_pos.row = i, des_pos.col = j;
//cout << "OK " << des_pos.row << " " << des_pos.col << endl;
                step_ans += DFS(s, des_pos, adj, visit);
            }
        }
    }
cout << step_ans << " ";
}

int main(int argc, char* argv[])
{
    int row_bound, col_bound;
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
                if(j>0 && Map[i][j-1] == 0){
                    adjList[i][j][x].row = i;
                    adjList[i][j][x].col = j-1;
                    x++;
                }
                if(i<row_bound-1 && Map[i+1][j] == 0){
                    adjList[i][j][x].row = i+1;
                    adjList[i][j][x].col = j;
                    x++;
                }
                if(j<col_bound-1 && Map[i][j+1] == 0){
                    adjList[i][j][x].row = i;
                    adjList[i][j][x].col = j+1;
                }
            }
        }
    }//end of creating an adjcency list

    Steps(row_bound, col_bound, start_pos, adjList);

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