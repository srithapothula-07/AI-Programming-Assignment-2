#include <stdio.h>
#include <limits.h>
#define V 6

// Cities index:
// 0-Hyderabad,1-Bangalore,2-Chennai,3-Mumbai,4-Delhi,5-Kolkata

int minDistance(int dist[], int visited[]) {
    int min = INT_MAX, min_index;
    for (int v = 0; v < V; v++)
        if (!visited[v] && dist[v] <= min)
            min = dist[v], min_index = v;
    return min_index;
}

void dijkstra(int graph[V][V], int src) {
    int dist[V], visited[V];

    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        visited[i] = 0;
    }

    dist[src] = 0;

    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, visited);
        visited[u] = 1;

        for (int v = 0; v < V; v++)
            if (!visited[v] && graph[u][v] &&
                dist[u] != INT_MAX &&
                dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
    }

    printf("City\tDistance from Source\n");
    for (int i = 0; i < V; i++)
        printf("%d \t %d\n", i, dist[i]);
}

int main() {
    int graph[V][V] = {
    // Hyd  Blr  Che  Mum  Del  Kol
        {  0, 570, 630, 710,   0,   0}, // Hyderabad
        {570,   0, 350, 980,   0,   0}, // Bangalore
        {630, 350,   0,   0,   0,   0}, // Chennai
        {710, 980,   0,   0,1400,2000}, // Mumbai
        {  0,   0,   0,1400,   0,1500}, // Delhi
        {  0,   0,   0,2000,1500,   0}  // Kolkata
    };

    dijkstra(graph, 0); // Source: Hyderabad
    return 0;
}
