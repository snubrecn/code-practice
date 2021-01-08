#include <stdio.h>

#include <iostream>
#define MAX 100
#define INF 100000

int adjacent[MAX][MAX];
int dist[MAX];
int parent[MAX];
int unvisited[MAX];

int V, E;

void Init() {
  for (int i = 1; i <= V; i++) {
    dist[i] = INF;
    parent[i] = 0;
    unvisited[i] = 1;
  }
}

void PrintPath(int start, int end) {
  std::cout << end << " ";
  int u = parent[end];

  while (u != start) {
    std::cout << u << " ";
    u = parent[u];
  }
  std::cout << start << std::endl;
}

void Iteration(int start) {
  Init();

  dist[start] = 0;

  for (int i = 1; i <= V; i++) {
    for (int j = 1; j <= V; j++) {
      if (dist[j] > dist[i] + adjacent[i][j]) {
        dist[j] = dist[i] + adjacent[i][j];
        parent[j] = i;
      }
    }
  }
}

void BFS(int start) {
  Init();

  dist[start] = 0;

  int q[MAX];
  int front, rear;
  front = rear = 0;

  q[rear++] = start;
  int u;

  while (front != rear) {
    u = q[front++];

    for (int i = 1; i <= V; i++) {
      if (dist[i] > dist[u] + adjacent[u][i]) {
        dist[i] = dist[u] + adjacent[u][i];
        parent[i] = u;
        q[rear++] = i;
      }
    }
  }
}

void Dijkstra(int start, int end) {
  Init();

  dist[start] = 0;

  int u, min;

  while (1) {
    min = INF;

    for (int i = 1; i <= V; i++) {
      if (unvisited[i] && dist[i] < min) {
        u = i;
        min = dist[i];
      }
    }

    unvisited[u] = 0;
    if (u == end) {
      break;
    }

    for (int i = 1; i <= V; i++) {
      if (dist[i] > dist[u] + adjacent[u][i]) {
        dist[i] = dist[u] + adjacent[u][i];
        parent[i] = u;
      }
    }
  }
}

void DFS(int curr, int end, int sum_dist, int min_dist) {
  if (sum_dist == 0) {
    Init();
    // curr is start
    dist[curr] = 0;
  }

  if (curr == end) {
    if (sum_dist < min_dist) {
      min_dist = sum_dist;
      dist[end] = sum_dist;
    }
    return;
  }

  for (int i = 1; i <= V; i++) {
    if (dist[i] > dist[curr] + adjacent[curr][i]) {
      dist[i] = dist[curr] + adjacent[curr][i];
      parent[i] = curr;
      DFS(i, end, sum_dist + adjacent[curr][i], min_dist);
    }
  }
}

int main(void) {
  for (int i = 0; i < MAX; i++) {
    for (int j = 0; j < MAX; j++) {
      adjacent[i][j] = INF;
    }
    adjacent[i][i] = 0;
  }

  freopen("input.txt", "r", stdin);

  scanf("%d %d", &V, &E);

  for (int i = 0; i < E; i++) {
    int start, end, weight;
    scanf("%d %d %d", &start, &end, &weight);
    adjacent[start][end] = weight;
  }

  int v_start = 1;
  int v_end = 6;

  Iteration(v_start);
  std::cout << "Iteration-based shortest path result: \n";
  std::cout << "Dist from " << v_start << " to " << v_end << ": " << dist[v_end] << std::endl;
  std::cout << "Path: ";
  PrintPath(v_start, v_end);

  BFS(v_start);
  std::cout << "Breadth-First-Search shortest path result: \n";
  std::cout << "Dist from " << v_start << " to " << v_end << ": " << dist[v_end] << std::endl;
  std::cout << "Path: ";
  PrintPath(v_start, v_end);

  Dijkstra(v_start, v_end);
  std::cout << "Dijkstra shortest path result: \n";
  std::cout << "Dist from " << v_start << " to " << v_end << ": " << dist[v_end] << std::endl;
  std::cout << "Path: ";
  PrintPath(v_start, v_end);

  DFS(v_start, v_end, 0, INF);
  std::cout << "Depth-First-Search shortest path result: \n";
  std::cout << "Dist from " << v_start << " to " << v_end << ": " << dist[v_end] << std::endl;
  std::cout << "Path: ";
  PrintPath(v_start, v_end);

  return 0;
}
