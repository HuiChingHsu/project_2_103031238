#include <iostream>
#include <cstring>
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
    int steps;
    int pre;
};

vector< vector<int> > Map; // changing element
int row_bound, col_bound;
int battery, step_ans = 0,step_curr = 0, End; //step_ans -> total steps
stack<position> step;
queue<position> step_back;
stack<position> solution; // final solution
vector< vector<int> > visit; //map_rec -> for visit initialization
position rec[1000000];

void BFS(position s, position des_pos, position*** adj)
{ 
    int front = 0, rear = 1;
    rec[front].row = s.row, rec[front].col = s.col;
    rec[front].pre = 0, rec[front].steps = 0;
    visit[s.row][s.col] += 2;

    while(front < rear){
//cout << "OK ";
        position tmp = rec[front];
        if(tmp.row == des_pos.row && tmp.col == des_pos.col){
            step_curr = tmp.steps;
            End = front;
            break;
        }
        front ++;

        int length = 0, tmp_R, tmp_C;  // adjList sorting

        for(int i=0; adj[tmp.row][tmp.col][i].row >0 && adj[tmp.row][tmp.col][i].row <1000; i++){ //??
            length++;
        }

        for(int i=0; i<length-1; i++){ 
            for(int j=0; j<length-1-i; j++){
                if(Map[ adj[tmp.row][tmp.col][j].row ][ adj[tmp.row][tmp.col][j].col ] >
                Map[ adj[tmp.row][tmp.col][j+1].row ][ adj[tmp.row][tmp.col][j+1].col ] ){
                    tmp_R = adj[tmp.row][tmp.col][j].row, tmp_C = adj[tmp.row][tmp.col][j].col;
                    adj[tmp.row][tmp.col][j].row = adj[tmp.row][tmp.col][j+1].row;
                    adj[tmp.row][tmp.col][j].col = adj[tmp.row][tmp.col][j+1].col;
                    adj[tmp.row][tmp.col][j+1].row = tmp_R, adj[tmp.row][tmp.col][j+1].col = tmp_C;
                }
            }
        }//

        for(int i=0; adj[tmp.row][tmp.col][i].row >-1 && adj[tmp.row][s.col][i].row <1001; i++){
            if(visit[adj[tmp.row][tmp.col][i].row][adj[tmp.row][tmp.col][i].col] == 0){
//cout << " (" << adj[tmp.row][tmp.col][i].row << " " << adj[tmp.row][tmp.col][i].col << ") ";
                visit[adj[tmp.row][tmp.col][i].row][adj[tmp.row][tmp.col][i].col] += 2;
                rec[rear].row = adj[tmp.row][tmp.col][i].row, rec[rear].col = adj[tmp.row][tmp.col][i].col;
                rec[rear].pre = front-1;
                rec[rear++].steps = tmp.steps+1;
            }
        }
    }
if(step_curr > battery/2) cout << "illegal!";
}

void Path(int idx)
{
    if(idx == 0) return;
    Path(rec[idx].pre);
    Map[rec[idx].row][rec[idx].col] ++;
    step.push(rec[idx]);
    step_back.push(rec[idx]);
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
                position des_pos;
                des_pos.row = i, des_pos.col = j;
cout << "(" << des_pos.row << "," << des_pos.col << ") ";
                BFS(s, des_pos, adj);
                //input solution and modify Map matrix
                Path(End);
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
//cout <<row_bound << " " << col_bound << " " << battery << endl;
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
/*for(int i=0; i<row_bound; i++){
    for(int j=0; j<col_bound; j++){
        cout << Map[i][j] << " ";
    }
    cout << endl;
}*/
    position*** adjList = new position** [row_bound];
    int x;
    for(int i=0; i<row_bound; i++){
            adjList[i] = new position* [col_bound];
        for(int j=0; j<col_bound; j++){
            adjList[i][j] = new position [4];
            
            for(int k=0; k<4; k++){
                adjList[i][j][k].row = INT_MIN+5;
                adjList[i][j][k].col = INT_MIN+5;
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
    cout << adjList[i][j][k].row << " " << adjList[i][j][k].col << "   ";
}*/
            }
        }
//cout << endl;
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