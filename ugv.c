#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define N 70

typedef struct {
    int x, y;
    int g, h, f;
    int parent_x, parent_y;
} Node;

int grid[N][N];

int isValid(int x, int y) {
    return (x >= 0 && x < N && y >= 0 && y < N);
}

int isBlocked(int x, int y) {
    return grid[x][y] == 1;
}

int heuristic(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2); // Manhattan
}

void generateObstacles(int level) {
    int density = (level == 1) ? 10 : (level == 2) ? 25 : 40;
    for (int i=0;i<N;i++)
        for (int j=0;j<N;j++)
            grid[i][j] = (rand()%100 < density) ? 1 : 0;
}

void tracePath(Node nodes[N][N], int gx, int gy) {
    int x = gx, y = gy, length = 0;
    printf("\nPath:\n");
    while (!(nodes[x][y].parent_x == x && nodes[x][y].parent_y == y)) {
        printf("(%d,%d) <- ", x, y);
        int px = nodes[x][y].parent_x;
        int py = nodes[x][y].parent_y;
        x = px; y = py;
        length++;
    }
    printf("START\n");
    printf("Path Length: %d\n", length);
}

void aStar(int sx, int sy, int gx, int gy) {
    int closed[N][N] = {0};
    Node nodes[N][N];

    for (int i=0;i<N;i++)
        for (int j=0;j<N;j++) {
            nodes[i][j].f = nodes[i][j].g = nodes[i][j].h = 99999;
            nodes[i][j].parent_x = i;
            nodes[i][j].parent_y = j;
        }

    nodes[sx][sy].g = 0;
    nodes[sx][sy].h = heuristic(sx,sy,gx,gy);
    nodes[sx][sy].f = nodes[sx][sy].h;

    int openCount = 1;
    Node openList[N*N];
    openList[0] = nodes[sx][sy];

    int explored = 0;

    while (openCount > 0) {
        int minIdx = 0;
        for (int i=1;i<openCount;i++)
            if (openList[i].f < openList[minIdx].f)
                minIdx = i;

        Node current = openList[minIdx];
        openList[minIdx] = openList[--openCount];

        int x = current.x, y = current.y;
        closed[x][y] = 1;
        explored++;

        if (x == gx && y == gy) {
            printf("Goal reached!\n");
            tracePath(nodes, gx, gy);
            printf("Nodes Explored: %d\n", explored);
            return;
        }

        int dx[] = {-1,1,0,0};
        int dy[] = {0,0,-1,1};

        for (int i=0;i<4;i++) {
            int nx = x + dx[i], ny = y + dy[i];

            if (isValid(nx,ny) && !isBlocked(nx,ny) && !closed[nx][ny]) {
                int gNew = nodes[x][y].g + 1;
                int hNew = heuristic(nx,ny,gx,gy);
                int fNew = gNew + hNew;

                if (nodes[nx][ny].f == 99999 || nodes[nx][ny].f > fNew) {
                    openList[openCount++] = (Node){nx,ny,gNew,hNew,fNew,x,y};
                    nodes[nx][ny] = openList[openCount-1];
                }
            }
        }
    }

    printf("No Path Found!\n");
}

int main() {
    srand(time(0));

    int sx=0, sy=0, gx=69, gy=69;
    int densityLevel;

    printf("Obstacle Density (1-Low,2-Med,3-High): ");
    scanf("%d",&densityLevel);

    generateObstacles(densityLevel);

    grid[sx][sy] = 0;
    grid[gx][gy] = 0;

    aStar(sx,sy,gx,gy);

    return 0;
}
