#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std; 

#define N 4
#define TILE_LEN 16
#define BLANK_TILE 0 
#define STEP_LIMIT 100

static const int dx[4] = {0, -1, 0, 1};  
static const int dy[4] = {1, 0, -1, 0};
static const char direction[4] = {'u', 'l', 'd', 'r'};

struct Puzzle
{
    int f[TILE_LEN]; 
    int blank_tile; 
    int md; 
}; 

int manhattan_distance[TILE_LEN][TILE_LEN]; 
Puzzle puz; 
int depth_limit; 
int path[STEP_LIMIT];  

void initMahattantDistance(); 
int getMahattantDistance(Puzzle); 
bool dfs(int, int); 
string iterative_deepening(Puzzle); 

int main()
{
    Puzzle in; 
    
    for (int i = 0; i < TILE_LEN; i++)
    {
        cin >> in.f[i]; 
        if (in.f[i] == BLANK_TILE)
        {
            in.f[i] = TILE_LEN; 
            in.blank_tile = i; 
        }
    }
    initMahattantDistance(); 
    string rs = iterative_deepening(in); 
    cout << rs.size() << endl; 
    return 0; 
}

void initMahattantDistance()
{
    for (int i = 0; i < TILE_LEN; i++)
    {
        for (int j = 0; j < TILE_LEN; j++)
        {
            manhattan_distance[i][j] = abs(i / N - j / N) + abs(i % N - j % N);
        }
    }
}

int getMahattantDistance(Puzzle p)
{
    int cost = 0; 
    for (int i = 0; i < TILE_LEN; i++)
    {
        if (p.f[i] == TILE_LEN)
            continue;
        cost += manhattan_distance[i][p.f[i] - 1]; 
    }

    return cost; 
}

bool dfs(int depth, int prev)
{
    if (puz.md == 0)
        return true; 
    
    // add a heuristic to the current depth 
    // cut a branch if the limit is exceeded
    if (depth + puz.md > depth_limit)
        return false; 

    int sx, sy, tx, ty; 
    Puzzle tmp; 

    sx = puz.blank_tile / N;
    sy = puz.blank_tile % N;

    for (int dir = 0; dir < 4; dir++)
    {
        tx = sx + dx[dir];
        ty = sy + dy[dir]; 
        if (tx < 0 || tx >= N || ty < 0 || ty >= N)
            continue; 
        if (max(prev, dir) - min(prev, dir) == 2)
            continue;
        
        tmp = puz; 

        puz.md -= manhattan_distance[tx * N + ty][puz.f[tx * N + ty] - 1]; 
        puz.md += manhattan_distance[sx * N + sy][puz.f[tx * N + ty] - 1]; 
        swap(puz.f[tx * N + ty], puz.f[sx * N + sy]);
        puz.blank_tile = tx * N + ty;
        if (dfs(depth + 1, dir))
        {
            path[depth] = dir;
            return true;
        }
        puz = tmp;
    }
    return false; 
}

string iterative_deepening(Puzzle in)
{
    in.md = getMahattantDistance(in); 
    for (depth_limit = in.md; depth_limit < STEP_LIMIT; depth_limit++)
    {
        puz = in; 
        if (dfs(0, -100))
        {
            string rs = ""; 
            for (int i = 0; i < depth_limit; i++)
            {
                rs += direction[path[i]]; 
            }
            return rs; 
        }
    }
    return "no answer"; 
}