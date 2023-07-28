#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>
#include <map>
using namespace std;

// Constants and Definitions
#define N 4
#define TILE_LEN 16
#define BLANK_TILE 0

static const int dx[4] = {0, -1, 0, 1};
static const int dy[4] = {1, 0, -1, 0};
static const char direction[4] = {'u', 'l', 'd', 'r'};

struct Puzzle
{
    int f[TILE_LEN]; // puzzle configuration
    int blank_tile; // index of the blank tile
    int md; // Manhattan distance for the current puzzle state
    int cost; // number of moves to reach this state from the initial state
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
    Puzzle puzzle; // current puzzle state
    int estimated; // estimated cost from the current state to the goal state
    bool operator<(const State &s) const
    {
        return estimated > s.estimated;
    }
};

int manhattan_distance[TILE_LEN][TILE_LEN]; // precomputed Manhattan distances for all tile pairs
priority_queue<State> pqueue; // priority queue for A* search.
map<Puzzle, bool> puzzle_map; // map to keep track of visited puzzle states.

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

    // precompute the Manhattan distances
    initMahattantDistance();

    cout << astar(in) << endl;

    return 0;
}

// precompute the Manhattan distances
void initMahattantDistance()
{
    for (int i = 0; i < TILE_LEN; i++)
    {
        for (int j = 0; j < TILE_LEN; j++)
        {
            // calculate Manhattan distance between tile (i/N, i%N) and (j/N, j%N)
            manhattan_distance[i][j] = abs(i / N - j / N) + abs(i % N - j % N);
        }
    }
}

// calculate the Manhattan distance for a given puzzle state
int getMahattantDistance(Puzzle p)
{
    int cost = 0;
    for (int i = 0; i < TILE_LEN; i++)
    {
        // cost of blank tile = 0
        if (p.f[i] == TILE_LEN)
            continue;
        // i: desired tile value , p.f[i] - 1: current title value
        cost += manhattan_distance[i][p.f[i] - 1];
    }

    return cost;
}

// A* search algorithm
int astar(Puzzle &p_in)
{
    // calculate the md of the initial state
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

        //if puzzle solved, return the number of moves
        if (s.puzzle.md == 0)
            return s.puzzle.cost; 

        int sx, sy, tx, ty;

        // current blank_tile location 
        sx = s.puzzle.blank_tile / N;
        sy = s.puzzle.blank_tile % N;

        for (int dir = 0; dir < 4; dir++)
        {
            // new blank_tile location
            tx = sx + dx[dir];
            ty = sy + dy[dir];

            // prune some paths
            // skip the out of bounds direction
            if (tx < 0 || tx >= N || ty < 0 || ty >= N)
                continue;
            
            Puzzle puz = s.puzzle;

            // update the mahantan distance
            // tx * N + ty: new blank_tile location, cost = 0 
            // f[tx * N + ty]: current value at the new blank_tile location, minus this cost (to 0)
            // sx * N + sy: current blank_tile location, update cost with the new tile value f[tx * N + ty]
            puz.md -= manhattan_distance[tx * N + ty][puz.f[tx * N + ty] - 1];
            puz.md += manhattan_distance[sx * N + sy][puz.f[tx * N + ty] - 1];
            swap(puz.f[tx * N + ty], puz.f[sx * N + sy]);
            puz.blank_tile = tx * N + ty;

            if (!puzzle_map[puz])
            {
                puzzle_map[s.puzzle] = true; // mark the visited state in map
                puz.cost++;
                State s_new;
                s_new.puzzle = puz;
                s_new.estimated = puz.cost + puz.md;
                pqueue.push(s_new); // add the new state to the priority queue
            }
        }
    }
    return -1; // no solution found
}