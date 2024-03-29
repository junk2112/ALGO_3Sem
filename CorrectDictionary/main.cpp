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
struct ver {
    string name;
    deque <string> links;
    int number;
public:
    ver (string n, deque <string> l,int num) {
        name=n;
        links=l;
        number=num;
    }
};

ver find (deque <ver> vertex, string name) {
    for (deque <ver>::const_iterator it=vertex.begin(); it!= vertex.end() ++it) {
        if (it->name==name)
            return *it;
    }

}

bool isBlack (vector <string> color) {
    for (int i=0; i<color.size(); ++i) {
        if (color[i]!="black")
            return false;
    }
    return true;
}

class graph {
private:
    deque <ver> vertex;
public:
    graph () {
        in.open("input.txt");
        int k;
        in >> k;
        for (int i=0; i<k; ++i) {
            string name;
            in >> name;
            int x;
            in >> x;
            deque <string> links;
            string link;
            for (int j=0; j<x; ++j) {
                in >> link;
                links.push_back(link);
            }
            ver v(name,links,i);
            vertex.push_back(v);
        }
        in.close();
    }
    void print () {
        for (int i=0; i<vertex.size(); ++i) {
            cout << vertex[i].name << endl;
            for (int j=0; j<vertex[i].links.size(); ++j) {
                cout << "->" << vertex[i].links[j] << endl;
            }
        }
    }
    /*void draw () const {
        system ("touch graph.txt");
        out.open("graph.txt");
        out << "digraph G {" << endl;
        this->DFS(true);
        out << "}";
        out.close();
        system("dot graph.txt -o graph.png -T png");
        system ("rm graph.txt");
        system("okular graph.png");
    }
    void BFS (int s=vertex[0], bool draw=0) const {
        vector <string> color(vertex.size(), "white");
        vector <int> parent (vertex.size(), -1);
        list <string> Q;
        Q.push_front(s);
        while (!Q.empty()) {
            int current = Q.front();
            for (deque <string>::const_iterator it=vertex[current].begin(); it!=vertex[current].end(); ++it) {
                if (draw)
                    out << current+1 << " -> " <<  it->first+1 << endl;
                else
                    cout << current+1 << " -> " <<  it->first+1 << endl;
                if (color[it->first]=="white") {
                    color[it->first]="gray";
                    parent[it->first]=current;
                    Q.push_back(it->first);
                }
            }
            Q.pop_front();
            color[current]="black";
            if (!draw)
                cout << current+1 << ' ' << "black" << endl;
        }
        if (!isBlack(color)) {
            cout << "There is some vertexes are not avaible from " << s+1 << " vertex." << endl;
        }
    }*/
    void DFS_Visit (vector <string> &color, vector <int> &parent, vector <int> &inTime, vector <int> &outTime,
    int current, int &time, bool draw) const {
        color[current]="gray";
        inTime[current]=++time;
        for (deque <string>::const_iterator it=vertex[current].links.begin(); it!=vertex[current].links.end(); ++it) {
            /*if (draw)
                out << vertex[current].name << " -> " <<  it->name << endl;
            else
                cout << vertex[current].name << " -> " <<  it->name << endl;
                */
            if (color[it->number]=="white") {
                parent[it->number]=current;
                this->DFS_Visit(color, parent, inTime, outTime, it->first, time, draw);
            }
        }
        color[current]="black";
        outTime[current]=++time;
        return;
    }
    void DFS (bool draw=0) const {
        vector <string> color(vertex.size(), "white");
        vector <int> parent(vertex.size(), -1);
        vector <int> inTime(vertex.size()), outTime(vertex.size());
        int time=0;
        for (int i=0; i<vertex.size(); ++i) {
            if (color[i]=="white")
                this->DFS_Visit(color, parent, inTime, outTime, i, time, draw);
        }
    }
    /*
    int get_count () const {
        return vertex.size();
    }
    deque <map <int, int> > get_vertex () const {
        return vertex;
    }*/
};
int main () {
    graph G;
    G.DFS();
    return 0;
}
