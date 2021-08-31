#include <iostream>
using namespace std;
#include <fstream>
#include <vector>

struct Node{
    int x, y;
    Node(int a=-1, int b=-1) : x(a), y(b){}
    Node(const Node& a) : x(a.x), y(a.y) {}
};

vector<vector<int> > maze;
Node start_node, end_node;
vector<Node> path;
vector<vector<bool> > visited;
const int row = 18, col = 36;
bool is_find = false;

void Init(){
    maze.resize(row, vector<int>(col, 0));
    path.clear();
    visited.resize(row, vector<bool>(col, false));
}

void ReadFile(const char* filename){
    ifstream fin(filename);
    if(!fin.is_open()){
        fprintf(stderr, "Error opening file %s\n", filename);
        return;
    }

    for(int i = 0; i < row; ++i){
        for(int j = 0; j < col; ++j){
            char tmp;
            while(1){
                fin >> tmp;
                if(tmp == '1' || tmp == '0' || tmp == 'S' || tmp == 'E') break;
            }
            if(tmp == '1' || tmp == '0'){
                maze[i][j] = tmp-'0';
            }
            else if(tmp == 'S'){
                start_node = Node(i, j);
                maze[i][j] = 0;
            }
            else if(tmp == 'E'){
                end_node = Node(i, j);
                maze[i][j] = 0;
            }
        }
    }
    fin.close();
}

void PrintPath(){
    cout << "Path Length: " << path.size() << endl;
    for(int i = 0; i < path.size(); i++){
        Node node = path[i];
        cout << '(' << node.x << ',' << node.y << ") ";
    }
}

void DFS(Node node){
    if(is_find) return;
    if(node.x < 0 || node.x >= row || node.y < 0 || node.y >= col) return;
    if(maze[node.x][node.y] == 1) return;
    if(visited[node.x][node.y]) return;
    
    if(node.x == end_node.x && node.y == end_node.y){
        path.push_back(end_node);
        PrintPath();
        is_find = true;
        return;
    }
    path.push_back(node);
    visited[node.x][node.y] = true;
    DFS(Node(node.x, node.y+1));
    DFS(Node(node.x, node.y-1));
    DFS(Node(node.x+1, node.y));
    DFS(Node(node.x-1, node.y));
    path.pop_back();
    visited[node.x][node.y] = false;
}

int main(){
    Init();
    ReadFile("MazeData.txt");
    DFS(start_node);
}