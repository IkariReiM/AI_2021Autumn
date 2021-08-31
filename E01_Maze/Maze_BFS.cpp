#include <iostream>
using namespace std;
#include <fstream>
#include <vector>
#include <queue>
#include <stack>

struct Node{
    int x, y;
    Node(int a=-1, int b=-1) : x(a), y(b){}
    Node(const Node& a) : x(a.x), y(a.y) {}
};

vector<vector<int> > maze;
Node start_node, end_node;
vector<vector<Node> >pre;
vector<vector<bool> > visited;
const int row = 18, col = 36;
const int dir[4][2] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
bool is_find = false;

void Init(){
    maze.resize(row, vector<int>(col, 0));
    pre.resize(row, vector<Node>(col, Node()));
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
                maze[i][j] = 1;
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
    Node node = end_node;
    stack<Node> s;
    while(!(pre[node.x][node.y].x == -1 && pre[node.x][node.y].y == -1)){
        s.push(node);
        node = pre[node.x][node.y];
    }
    s.push(start_node);
    cout << "Path Length: " << s.size() << endl;
    while(!s.empty()){
        node = s.top();
        cout << '(' << node.x << ',' << node.y << ") ";
        s.pop();
    }
}

void BFS(){
    queue<Node> q;
    q.push(start_node);
    visited[start_node.x][start_node.y] = true;
    while(1){
        if(q.empty()) break;
        Node node = q.front();
        q.pop();
        for(int i = 0; i < 4; ++i) {
            Node next(node.x+dir[i][0], node.y+dir[i][1]);

            if(next.x < 0 || next.y < 0 || next.x >= row || next.y >= col) continue;
            if(maze[next.x][next.y] == 1) continue;
            if(visited[next.x][next.y]) continue;

            pre[next.x][next.y] = node;
            visited[next.x][next.y] = true;
            q.push(next);
        }
    }
}

int main(){
    Init();
    ReadFile("MazeData.txt");
    BFS();
    PrintPath();
}