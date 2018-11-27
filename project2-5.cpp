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
};

vector< vector<int> > Map; // changing element
int row_bound, col_bound;
int battery, step_ans = 0, step_curr; //step_ans -> total steps
stack<position> step;
queue<position> step_back;
stack<position> solution; // final solution
vector< vector<int> > visit; //map_rec -> for visit initialization
bool found;

void DFS(position s, position des_pos, position*** adj)
{
//cout << "OK\n";
    if(found == true || step_curr == battery/2) return;
    if(visit[s.row-1][s.col] != 0 && visit[s.row][s.col-1] != 0 
       && visit[s.row+1][s.col]!=0 && visit[s.row][s.col+1] != 0 && s.row != des_pos.row && s.col != des_pos.col){
           return;
    }

    if(Map[s.row][s.col] != INT_MIN){
        Map[s.row][s.col] += 2;
        visit[s.row][s.col] += 2;
        step_curr++;
        step.push(s);
        step_back.push(s);
cout << s.row << " " << s.col << "  ";
    }
    if(s.row == des_pos.row && s.col == des_pos.col){
        found = true;
    }

    int length = 0, tmp_R, tmp_C;  // adjList sorting

    for(int i=0; adj[s.row][s.col][i].row >0 && adj[s.row][s.col][i].row <1000; i++){ //??
        length++;
    }

    for(int i=0; i<length-1; i++){ 
        for(int j=0; j<length-1-i; j++){
            if(Map[ adj[s.row][s.col][j].row ][ adj[s.row][s.col][j].col ] >
               Map[ adj[s.row][s.col][j+1].row ][ adj[s.row][s.col][j+1].col ] ){
                   tmp_R = adj[s.row][s.col][j].row, tmp_C = adj[s.row][s.col][j].col;
                   adj[s.row][s.col][j].row = adj[s.row][s.col][j+1].row;
                   adj[s.row][s.col][j].col = adj[s.row][s.col][j+1].col;
                   adj[s.row][s.col][j+1].row = tmp_R, adj[s.row][s.col][j+1].col = tmp_C;
               }
        }
    }
    // find adjecent nodes
    for(int i=0; adj[s.row][s.col][i].row != INT_MAX; i++){
        if(visit[adj[s.row][s.col][i].row][adj[s.row][s.col][i].col] == 0){
            DFS(adj[s.row][s.col][i], des_pos, adj);
            if(found == true || step_curr == battery/2) break;
            step.push(s);
            step_back.push(s);
            step_curr++;
cout << s.row << " " << s.col << "  ";
        }
    }
}

void Steps(position s, position *** adj)
{
    int num;
    vector< vector<int> > map_rec;

    for(int i=0; i<row_bound; i++){ // visit? 
        vector<int> Row;
        for(int j=0; j<col_bound; j++){
            num = Map[i][j];
            Row.push_back(num);
        }
        visit.push_back(Row);
        map_rec.push_back(Row);
    }
    for(int i=0; i<row_bound; i++){
        for(int j=0; j<col_bound; j++){

            for(int k=0; k<row_bound; k++){
                for(int l=0; l<col_bound; l++){
                    visit[k][l] = map_rec[k][l];
                }
            }

            if(Map[i][j] == 0){
                found = false;
                position des_pos;
                des_pos.row = i, des_pos.col = j;
                step_curr = 0;
cout << "(" << des_pos.row << "," << des_pos.col << ") ";
                DFS(s, des_pos, adj);
cout << endl;
                //input solution
                solution.push(s);//start_pos
                step_ans ++;
                while(!step_back.empty()){
                    solution.push(step_back.front());
                    step_back.pop();
                    step_ans ++;
                }
                step.pop();
                while(!step.empty()){
                    solution.push(step.top());
                    step.pop();
                    step_ans ++;
                }
            }
            if(Map[i][j] == 0 && j == col_bound-1){
                i--, j--;
            }else if(Map[i][j] == 0 && j != col_bound -1){
                j --;
            }

        }
    }
cout << "done\n";
}

int main(int argc, char* argv[])
{
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
/*for(int k=0; k<4; k++){
    cout << adjList[i][j][k].row << " " << adjList[i][j][k].col << "  ";
}
cout << endl;*/
            }
        }
    }//end of creating an adjcency list

    Steps(start_pos, adjList);

    //output result  
    data_name = "./"+id+"/final.path";
    output.open(data_name,ios::out);
    output << step_ans << "\n";
    if (output.is_open()) {
        while(!solution.empty()){
            output << solution.top().row << " " << solution.top().col << "\n";
            solution.pop();
        }
	}
	else{
        cout << "Unable to open file" << endl;
        return 0;
    } 
	file.close();
	output.close();
    
    return 0;
}