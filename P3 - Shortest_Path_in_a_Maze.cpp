#include<bits/stdc++.h>
using namespace std;

typedef pair<int, int> P;
typedef vector<vector<int> > matrix;

int initMap(matrix &maze, P &start, P &end ) {
  int nrow, ncol;

  //input maze size
  cin >> nrow >> ncol;

  //set maze size
  maze.resize(nrow);
  for (int i = 0; i < nrow; i++){
    maze[i].resize(ncol, 1);
  }
  string _s;
  getline(cin, _s);

  //input map information
  for (int i = 0; i < nrow; i++){
    string line, category;
    int col_idx;
    stringstream ss;
    getline(cin, line);
    ss << line;
    while (ss >> col_idx && col_idx != 0) {
     ss >> category;
      if (category == "x") {
        maze[i][col_idx-1] = 0;
      } else if (category == "s") {
        start = P(i, col_idx-1);
      } else if (category == "t") {
        end = P(i, col_idx-1);
      }
    }
  }

  //output the maze that had been set
  cout << endl;
  for (int i = 0; i < maze.size(); i++) {
    for (int j = 0; j < maze[0].size(); j++) {
      cout << maze[i][j] << " ";
    }
    cout << endl;
  }
  return 0;
}

int bfs(matrix &maze, P &start, P &end) {
  //declare variable
  queue<P> q;
  matrix visited;
  const int dx[] = {0, 1, 0, -1};
  const int dy[] = {-1, 0, 1, 0};
  int nrow = maze.size();
  int ncol = maze[0].size();

  //set maze size
  visited.resize(nrow);
  for (int i = 0; i < nrow; i++) {
    visited[i].resize(ncol, 0);
  }

  //set start = 1
  visited[start.first][start.second] = 1;
  q.push(start);

  //bfs count how long is the shortest path
  while (!q.empty()) {
    int r, c;
    r = q.front().first;
    c = q.front().second;

    //get the next point to do from queue
    q.pop();
    for (int i = 0; i < 4; i++) {
      //add dirextions
      int rr = r + dx[i];
      int cc = c + dy[i];

      //check if point valid
      if (rr >= 0 && rr < nrow && cc >= 0 && cc < ncol) {
        if (!visited[rr][cc] && maze[rr][cc] == 1) {
          visited[rr][cc] = visited[r][c] + 1;
          q.push(P(rr, cc));
        }
      }
    }
  }

  //output shortest path's length
  cout << "shortest path length: " << visited[end.first][end.second]-1 << endl;

  //declare variable
  int r = end.first;
  int c = end.second;
  vector<P> path;

  //recording the path coordinate fron the end to start
  while (r != start.first || c != start.second) {
    for (int i = 0; i < 4; i++) {
      int rr = r + dx[i];
      int cc = c + dy[i];
      if (rr >= 0 && rr < nrow && cc >= 0 && cc < ncol) {
        if (visited[rr][cc] +1 == visited[r][c]) {
          path.push_back(P(rr,cc));
          r = rr;
          c = cc;
          break;
        }
      }
    }
  }

  //output shortest path's coordinate
  cout << "path: \n";
  for (vector<P>::const_reverse_iterator i = path.rbegin(); i != path.rend(); i++) {
    cout << "(" << i->first+1 << ", " << i->second+1 << ")" << endl;
  }
  
  return 0;
}

int main() {
  matrix maze;
  P start, end;
  initMap(maze, start, end);
  bfs(maze, start, end);
  return 0;
}
