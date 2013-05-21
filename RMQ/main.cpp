#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
using namespace std;
ifstream in;
fstream out;
double min (double a, double b) {
    if (a<b) return a;
    else return b;
}
class SegmentTree {
    int sizeArray,n;
    vector <pair <int,int> > request;
    vector <double> array,tree;
public:
    SegmentTree (){ //from file
        in.open("input.txt");
        in >> sizeArray;
        for (int i=0; i<sizeArray; ++i) {
            double tmp;
            in >> tmp;
            array.push_back(tmp);
        }
        int tmp;
        in >> tmp;
        for (int i=0; i<tmp; ++i) {
            pair <int, int> tmp2;
            in >> tmp2.first >> tmp2.second;
            tmp2.second-=1;
            request.push_back(tmp2);
        }
        //делаем sizeTree степенью двойки
        //ceil - round up value
        
        n=pow(2.0,ceil(log(sizeArray)/log(2)));
        //cout<< "size " << n << endl;
        tree.resize(2*n-1);
        //инициализируем листья
        for (int i=n-1; i<tree.size(); ++i) {
            if (i-n+1<sizeArray)
                tree[i]=array[i-n+1];
            else tree[i]=99999999;
        }
        //инициализируем остальные вершины
        for (int i=n-2; i>=0; --i) {
            //cout << tree[2*i+1] << ' ' << tree[2*i+2] << endl;
            if (i!=0)
                tree[i]=min(tree[2*i+1], tree[2*i+2]);
            else 
                tree[i]=min(tree[1], tree[2]);
        }
        in.close();
    }
    /*SegmentTree (){ //from keyboard
        cin >> sizeArray;
        for (int i=0; i<sizeArray; ++i) {
            double tmp;
            cin >> tmp;
            array.push_back(tmp);
        }
        int tmp;
        cin >> tmp;
        for (int i=0; i<tmp; ++i) {
            pair <int, int> tmp2;
            cin >> tmp2.first >> tmp2.second;
            tmp2.second-=1;
            request.push_back(tmp2);
        }
        //делаем sizeTree степенью двойки
        //ceil - round up value
        
        n=pow(2.0,ceil(log(sizeArray)/log(2)));
        //cout<< "size " << n << endl;
        tree.resize(2*n-1);
        //инициализируем листья
        for (int i=n-1; i<tree.size(); ++i) {
            if (i-n+1<sizeArray)
                tree[i]=array[i-n+1];
            else tree[i]=99999999;
        }
        //инициализируем остальные вершины
        for (int i=n-2; i>=0; --i) {
            //cout << tree[2*i+1] << ' ' << tree[2*i+2] << endl;
            if (i!=0)
                tree[i]=min(tree[2*i+1], tree[2*i+2]);
            else 
                tree[i]=min(tree[1], tree[2]);
        }
    }*/
    void printTree () const {
        for (int i=0; i<tree.size(); ++i)
            cout << tree[i] << ' ';
        cout << endl;
    }
    void printArray () const {
        for (int i=0; i<array.size(); ++i)
            cout << array[i] << ' ';
        cout << endl;
    }
    double RMQ (int a, int b) {
        double result=99999999;
        a+=n-1;
        //for acm need b+=n-1, its for minimum on [...)
        //here b+=n for minimum on [...]
        b+=n;
        //cout << tree[a] << ' ' << tree[b] << endl;
        while (a<=b) {
            if (a%2==0) { // если левое поддерево "отпадает"
                result=min(result,tree[a]);
                a=(a)/2;
            }
            else { 
                result=min(result,tree[a]);
                a=(a-1)/2;
            }
            if (b%2==1) {//если правое дерево "отпадает"
                result=min(result,tree[b]);
                b=(b-3)/2;
            }
            else {
                result=min(result,tree[b]);
                b=(b-2)/2;                
            }        
        }
        return result;
    }
    void RMQ_AllRequests () {
        for (int i=0; i<request.size(); ++i) {
            cout << this->RMQ(request[i].first, request[i].second) << endl;
        }
    }
};
int main () {
    SegmentTree t;
    //t.printTree();
    t.RMQ_AllRequests();
    //t.RMQ(0,6);
    return 0;
}