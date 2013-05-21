#include <iostream>
#include <fstream>
#include <map>
#include <deque>
#include <cstdlib>
#include <vector>
#include <string>
#include <list>

using namespace std;
ifstream in;
fstream out;

bool isBlack (vector <string> color) //возможно к этому придерется, тебе лучше знать
{									//если да, надо придумать чентиь другое
    for (int i=0; i<color.size(); ++i) 
    {
        if (color[i] != "black")
            return false;
    }
    return true;
}
class graph {
private:
    deque < deque <int> > vertex;
public:
    graph (deque <deque <int> > v) 
    {
        vertex = v;
    }
    graph () 
    {
        in.open("input.txt");
        int k;
        in >> k;
        for (int i=0; i<k; ++i) 
        {
            deque <int> links;
            int count,link;
            in >> count;
            for (int j=0; j<count; ++j) 
            {
                in >> link;
                links.push_back(link);
            }
            vertex.push_back(links);
        }
        in.close();
    }
    void print () const 
    {
        system ("touch graph.txt");
        out.open("graph.txt");
        out << "digraph G {" << endl;
        this->DFS(true);
        out << "}";
        out.close();
        system("dot graph.txt -o graph.png -T png");
        system ("rm graph.txt");
        system("ristretto graph.png");
    }
    void BFS (int start=0, bool print=0) const //поиск в ширину
    {
        vector <string> color(vertex.size(), "white");
        vector <int> parent (vertex.size(), -1);
        list <int> Q;
        Q.push_front(start);
        while (!Q.empty()) {
            int current = Q.front();
            for (deque <int>::const_iterator it=vertex[current].begin(); it!=vertex[current].end(); ++it) 
            {
                if (print)
                    out << current+1 << " -> " <<  *it+1 << endl;
                else
                    cout << current+1 << " -> " <<  *it+1 << endl;
                if (color[*it] == "white") 
                {
                    color[*it] = "gray";
                    parent[*it] = current;
                    Q.push_back(*it);
                }
            }
            Q.pop_front();
            color[current] = "black";
            //if (!print)
            //    cout << current+1 << ' ' << "black" << endl;
        }
        if (!isBlack(color)) {
            cout << "There is may be some vertexes are not avaible from " << start + 1 << " vertex." << endl;
        }
    }
    
    void DFS_Visit (vector <string> &color, vector <int> &parent, 
				int current, bool print) const 
	{
        color[current] = "gray";
        for (deque <int>::const_iterator it=vertex[current].begin(); it!=vertex[current].end(); ++it) 
        {
            if (print)
                out << current+1 << " -> " <<  *it+1 << endl;
            else
                cout << current+1 << " -> " <<  *it+1 << endl;
            if (color[*it] == "white") {
                parent[*it] = current;
                this->DFS_Visit(color, parent, *it, print);
            }
        }
        color[current] = "black";
        return;
    }
    
    void DFS (bool print=0) const { //поиск в глубину
        vector <string> color (vertex.size(), "white");
        vector <int> parent (vertex.size(), -1);
        for (int i=0; i<vertex.size(); ++i) 
        {
            if (color[i]=="white")
                this->DFS_Visit(color, parent, i, print);
        }
    }
    int get_count () const 
    {
        return vertex.size();
    }
    deque <deque <int> > get_vertex () const 
    {
        return vertex;
    }
};
int main() {

    graph G;
    G.DFS();
    return 0;
}
