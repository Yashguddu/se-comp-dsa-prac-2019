#include <iostream>
#include <queue>
using namespace std;

const int MAX_CITIES = 50;

int adj_mat[MAX_CITIES][MAX_CITIES] = {0};
bool visited[MAX_CITIES] = {false};

void dfs(int s, int n, string arr[]) {
    visited[s] = true;
    cout << arr[s] << " ";

    for (int i = 0; i < n; i++) {
        if (adj_mat[s][i] && !visited[i]) {
            dfs(i, n, arr);
        }
    }
}

void bfs(int s, int n, string arr[]) {
    bool visited[n] = {false};
    int v;
    queue<int> bfsq;

    if (!visited[s]) {
        cout << arr[s] << " ";
        bfsq.push(s);
        visited[s] = true;

        while (!bfsq.empty()) {
            v = bfsq.front();

            for (int i = 0; i < n; i++) {
                if (adj_mat[v][i] && !visited[i]) {
                    cout << arr[i] << " ";
                    visited[i] = true;
                    bfsq.push(i);
                }
            }

            bfsq.pop();
        }
    }
}

int main() {
    cout << "Enter the number of cities: ";
    int n;
    cin >> n;

    string cities[n];

    for (int i = 0; i < n; i++) {
        cout << "Enter city #" << i << " (Airport code): ";
        cin >> cities[i];
    }

    cout << "\nYour cities are:\n";
    for (int i = 0; i < n; i++) {
        cout << "City #" << i << ": " << cities[i] << endl;
    }

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            cout << "Enter distance between " << cities[i] << " and " << cities[j] << ": ";
            cin >> adj_mat[i][j];
            adj_mat[j][i] = adj_mat[i][j];
        }
    }

    cout << endl;

    cout << "\t";
    for (int i = 0; i < n; i++) {
        cout << cities[i] << "\t";
    }

    for (int i = 0; i < n; i++) {
        cout << endl << cities[i] << "\t";
        for (int j = 0; j < n; j++) {
            cout << adj_mat[i][j] << "\t";
        }
    }

    cout << endl;

    cout << "Enter the starting vertex: ";
    int u;
    cin >> u;

    cout << "DFS: ";
    dfs(u, n, cities);
    cout << endl;

    cout << "BFS: ";
    bfs(u, n, cities);

    return 0;
}

