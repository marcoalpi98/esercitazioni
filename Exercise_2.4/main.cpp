#include <iostream>
#include <Eigen/Eigen>
#include <fstream>
#include <map>
#include <sstream>
#include <vector>


using namespace std;
using namespace Eigen;

struct Cell0D
{
    int id;
    int marker;
    double x;
    double y;
};

struct Cell1D
{
    int id;
    int marker;
    int origin;
    int end;
};

struct Cell2D
{
    int id;
    int marker;
    vector<int> vertices;
    vector<int> edges;
};

struct PolygonalMesh
{
    vector<Cell0D> cell0Ds;
    vector<Cell1D> cell1Ds;
    vector<Cell2D> cell2Ds;
};

///\brief Import the Polygonal mesh and test if the mesh is correct
///\param mesh: a PolygonalMesh struct
///\return the result of the reading, true if is success, false otherwise
bool ImportMesh(PolygonalMesh& mesh);

///\brief Import the Cell0D properties from Cell0Ds.csv file
///\param mesh: a PolygonalMesh struct
///\return the result of the reading, true if is success, false otherwise
bool ImportCell0Ds(PolygonalMesh& mesh);

///\brief Import the Cell1D properties from Cell1Ds.csv file
///\param mesh: a PolygonalMesh struct
///\return the result of the reading, true if is success, false otherwise
bool ImportCell1Ds(PolygonalMesh& mesh);

///\brief Import the Cell2D properties from Cell2Ds.csv file
///\param mesh: a PolygonalMesh struct
///\return the result of the reading, true if is success, false otherwise
bool ImportCell2Ds(PolygonalMesh& mesh);

// ***************************************************************************
int main()
{
    PolygonalMesh mesh;

    if(!ImportMesh(mesh))
    {
        return 1;
    }
    // Test the imported mesh properties

    // Test Cell0Ds
    for (const auto& cell0D : mesh.cell0Ds)
    {
        cout << "Cell0D: Id = " << cell0D.id << ", Marker = " << cell0D.marker << ", X = " << cell0D.x << ", Y = " << cell0D.y << endl;
    }

    // Test Cell1Ds
    for (const auto& cell1D : mesh.cell1Ds)
    {
        cout << "Cell1D: Id = " << cell1D.id << ", Marker = " << cell1D.marker << ", Origin = " << cell1D.origin << ", End = " << cell1D.end << endl;
    }

    // Test Cell2Ds
    for (const auto& cell2D : mesh.cell2Ds)
    {
        cout << "Cell2D: Id = " << cell2D.id << ", Marker = " << cell2D.marker << ", Vertices = ";
        for (const auto& vertex : cell2D.vertices)
        {
            cout << vertex << " ";
        }
        cout << ", Edges = ";
        for (const auto& edge : cell2D.edges)
        {
            cout << edge << " ";
        }
        cout << endl;
    }
    return 0;
}
// ***************************************************************************
bool ImportMesh(PolygonalMesh& mesh)
{

    bool success = true;
    success &= ImportCell0Ds(mesh);
    success &= ImportCell1Ds(mesh);
    success &= ImportCell2Ds(mesh);
    return success;

    return false;

}
// ***************************************************************************
bool ImportCell0Ds(PolygonalMesh& mesh)
{
    ifstream file("Cell0Ds.csv");
    if (!file.is_open())
    {
        cerr << "Error opening Cell0Ds.csv file" << endl;
        return false;
    }

    string line;
    getline(file, line); // Skip the header line

    while (getline(file, line))
    {
        stringstream ss(line);
        string token;

        Cell0D cell0D;

        getline(ss, token, ';');
        cell0D.id = stoi(token);

        getline(ss, token, ';');
        cell0D.marker = stoi(token);

        getline(ss, token, ';');
        cell0D.x = stod(token);

        getline(ss, token, ';');
        cell0D.y = stod(token);

        mesh.cell0Ds.push_back(cell0D);
    }

    file.close();
    return true;
}
// ***************************************************************************
bool ImportCell1Ds(PolygonalMesh& mesh)
{
    ifstream file("Cell1Ds.csv");
    if (!file.is_open())
    {
        cerr << "Error opening Cell1Ds.csv file" << endl;
        return false;
    }

    string line;
    getline(file, line); // Skip the header line

    while (getline(file, line))
    {
        stringstream ss(line);
        string token;

        Cell1D cell1D;

        getline(ss, token, ';');
        cell1D.id = stoi(token);

        getline(ss, token, ';');
        cell1D.marker = stoi(token);

        getline(ss, token, ';');
        cell1D.origin = stoi(token);

        getline(ss, token, ';');
        cell1D.end = stoi(token);

        mesh.cell1Ds.push_back(cell1D);
    }

    file.close();
    return true;
}
// ***************************************************************************
bool ImportCell2Ds(PolygonalMesh& mesh)
{
    ifstream file("Cell2Ds.csv");
    if (!file.is_open())
    {
        cerr << "Error opening Cell2Ds.csv file" << endl;
        return false;
    }

    string line;
    getline(file, line); // Skip the header line

    while (getline(file, line))
    {
        stringstream ss(line);
        string token;

        Cell2D cell2D;

        getline(ss, token, ';');
        cell2D.id = stoi(token);

        getline(ss, token, ';');
        cell2D.marker = stoi(token);

        getline(ss, token, ';');
        int numVertices = stoi(token);
        for (int i = 0; i < numVertices; ++i)
        {
            getline(ss, token, ';');
            cell2D.vertices.push_back(stoi(token));
        }

        getline(ss, token, ';');
        int numEdges = stoi(token);
        for (int i = 0; i < numEdges; ++i)
        {
            getline(ss, token, ';');
            cell2D.edges.push_back(stoi(token));
        }

        mesh.cell2Ds.push_back(cell2D);
    }

    file.close();
    return true;
}
