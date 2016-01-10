#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>
using namespace std;

void dijkstra( int srcNode )
{
    // Definitions of constants
    const int GRAPH_DIM = 7;  // Dimension of graph
    const int NUM_VERTICES = GRAPH_DIM - 1;  // Number of waypoints in navigation context
    const int inf = 99999999;

    // Initialize the navigation map
    int graph[GRAPH_DIM][GRAPH_DIM] = {{0}};
    for ( int i = 1; i <= NUM_VERTICES; i++ )
    {
        for ( int j = 1; j <= NUM_VERTICES; j++ )
        {
            if ( i == j )
            {
                graph[i][j] = 0;  // Cost of local to local
            }
            else
            {
                graph[i][j] = inf;  // No traversable path
            }
        }
    }

    // Load map info
    ifstream graph_cost( "../test_pcl/graph.txt" );
    while ( graph_cost.good( ) )
    {
        int row_index, col_index, val;
        graph_cost >> row_index >> col_index >> val;
        graph[row_index][col_index] = val;
    }

    // Display map info
    for ( int i = 1; i <= NUM_VERTICES; i++ )
    {
        for ( int j = 1; j <= NUM_VERTICES; j++ )
        {
            cout << setw( 10 ) << graph[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl << endl;

    // Initialize cost from No.srcNode node to the others
    int dis[GRAPH_DIM] = {0};
    for ( int i = 1; i <= NUM_VERTICES; i++ )
    {
        dis[i] = graph[srcNode][i];
    }

    // Initialize book, which records the CLOSED set and the OPEN set
    // When initialized, all nodes belong to OPEN set, with flag 0
    int book[GRAPH_DIM] = {0};
    for ( int i = 1; i <= NUM_VERTICES; i++ )
    {
        book[i] = 0;
    }

    // Join the source node into CLOSED set
    book[srcNode] = 1;

    // Calculation of Dijkstra
    for ( int i = 1; i <= NUM_VERTICES; i++ )
    {
        // Find the nearest node from No.srcNode node to the node in OPEN set
        int min = inf;
        int minIndex = 1;
        for ( int j = 1; j <= NUM_VERTICES; j++ )
        {
            if ( book[j] == 0 && dis[j] < min )
            {
                min = dis[j];
                minIndex = j;
            }
        }
        book[minIndex] = 1;

        // Update costs with the newly found node,
        // which is put into CLOSED set
        for ( int i = 1; i <= NUM_VERTICES; i++ )
        {
            if ( graph[minIndex][i] < inf )
            {
                if ( dis[i] > dis[minIndex] + graph[minIndex][i] )
                {
                    dis[i] = dis[minIndex] + graph[minIndex][i];
                }
            }
        }

        // Print path costs
        cout << "From node " << srcNode << " :" << endl;
        for ( int i = 1; i <= NUM_VERTICES; i++ )
        {
            cout << dis[i] << " ";
        }
        cout << endl << endl;
    }
}

int main( int argc, char** argv )
{
    int srcNode = atoi( argv[1] );
    dijkstra( srcNode );
    return 0;
}
