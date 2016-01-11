/*
 * Based array
*/
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

void table( int numNodes, int numEdges )
{
    const int sizeOfArrForEdges = numEdges + 1;
    vector< int > u( sizeOfArrForEdges );
    vector< int > v( sizeOfArrForEdges );
    vector< int > w( sizeOfArrForEdges );

    const int sizeOfArrForNodes = numNodes + 1;
    vector< int > first( sizeOfArrForNodes );
    vector< int > next( sizeOfArrForNodes );

    // Initialize array first
    for ( int i = 1; i <= numNodes; i++ )
    {
        first[i] = -1;
    }

    // Read edges
    ifstream graph_cost( "../test_pcl/graph.txt" );
    for ( int i = 1; i <= numEdges; i++ )
    {
        int edgeBeginNode, edgeEndNode, edgeVal;
        graph_cost >> edgeBeginNode >> edgeEndNode >> edgeVal;
        u[i] = edgeBeginNode;
        v[i] = edgeEndNode;
        w[i] = edgeVal;
        //cout << edgeBeginNode << " " << edgeEndNode << " " << edgeVal << endl;

        // Key points
        next[i] = first[u[i]];
        first[u[i]] = i;
    }

    // An invalid pointer occurs here.
    int k = first[5];
    while ( k != -1 )
    {
        cout << u[k] << " " << v[k] << " " << w[k] << endl;
        k = next[k];
    }

}

int main( )
{
    table( 5, 9 );
    return 0;
}
