#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>
#include <map>
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
    int cost; 
    bool operator<(const Puzzle &p) const
    {
        for (int i = 0; i < TILE_LEN; i++)
        {
            if (f[i] == p.f[i])
                continue;
            return f[i] < p.f[i];
        }
        return false;
    }
}; 

struct State 
{
    Puzzle puzzle; 
    int estimated; 
    bool operator<(const State &s) const 
    {
        return estimated > s.estimated; 
    }
}; 

int manhattan_distance[TILE_LEN][TILE_LEN]; 
priority_queue<State> pqueue;
map<Puzzle, bool> puzzle_map; 

void initMahattantDistance(); 
int getMahattantDistance(Puzzle); 
int astar(Puzzle &);  

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
    cout << astar(in) << endl; 
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

int astar(Puzzle &p_in)
{
    p_in.md = getMahattantDistance(p_in); 
    p_in.cost = 0; 

    State s_in;
    s_in.puzzle = p_in; 
    s_in.estimated = p_in.md; 
    pqueue.push(s_in); 

    while (!pqueue.empty()) 
    {
        State s = pqueue.top(); 
        pqueue.pop(); 

        if (s.puzzle.md == 0)
            return  s.puzzle.cost;

        int sx, sy, tx, ty;

        sx = s.puzzle.blank_tile / N;
        sy = s.puzzle.blank_tile % N;
        
        for (int dir = 0; dir < 4; dir++)
        {
            tx = sx + dx[dir];
            ty = sy + dy[dir]; 
            if (tx < 0 || tx >= N || ty < 0 || ty >= N)
                continue; 
            
            Puzzle puz = s.puzzle; 
            puz.md -= manhattan_distance[tx * N + ty][puz.f[tx * N + ty] - 1]; 
            puz.md += manhattan_distance[sx * N + sy][puz.f[tx * N + ty] - 1]; 
            swap(puz.f[tx * N + ty], puz.f[sx * N + sy]);
            puz.blank_tile = tx * N + ty;

            if (!puzzle_map[puz]) {
                puzzle_map[s.puzzle] = true; 
                puz.cost++; 
                State s_new; 
                s_new.puzzle = puz; 
                s_new.estimated = puz.cost + puz.md; 
                pqueue.push(s_new); 
            }
        }
    }    
    return -1;      
}