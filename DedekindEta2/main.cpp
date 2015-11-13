#include <iostream>
#include <map>
#include <fstream>
#include <vector>

using namespace std;

int MAX_N;

int xx(int m, int n, int a) {
    return (6*m + 1) * (6*m + 1) + a * (6*n + 1) * (6*n + 1);
}

void print_table(ostream &os, const int a, const int b, string h1, string h2) {
    os << "<html><head><style type=\"text/css\">td {text-align:center;}</style></head><body>\n";
    os << "<table border=\"1\" cellspacing=\"0\"><tr><td colspan=\"3\">&eta;(" << h1 << "z)&eta;(" << h2 << "z)</td></tr>\n\n";
    
    map<int, vector<pair<int, int> > > map_vp;
    for (int m = -MAX_N; m <= MAX_N; m++) {
        for (int n = -MAX_N; n <= MAX_N; n++) {
            int x = xx(m, n, a);
            map<int, vector<pair<int, int> > >::iterator it = map_vp.find(x);
            if (it == map_vp.end())
                map_vp[x] = vector<pair<int, int> >();
            map_vp[x].push_back(make_pair(m, n));
        }
    }
    
    map<int, int> map_i;
    for (auto itmap = map_vp.begin(); itmap != map_vp.end(); itmap++) {
        int t = 0;
        for (auto itvec = itmap->second.begin(); itvec != itmap->second.end(); itvec++)
            t += ((itvec->first + itvec->second) % 2 == 0) ? +1 : -1;
        
        map_i[itmap->first] = t;
    }
    
    for (auto itmap = map_vp.begin(); itmap != map_vp.end(); itmap++) {
        vector<pair<int,int> > vec_mns = itmap->second;
        size_t rowspan = vec_mns.size();
        os << "<tr><td rowspan=\"" << rowspan << "\">" << xx(vec_mns[0].first, vec_mns[0].second, a) / b << "</td>\n";
        os << "<td>" << vec_mns[0].first << " " << vec_mns[0].second << "</td>\n";
        os << "<td rowspan=\"" << rowspan << "\">" << map_i[itmap->first] << "</td></tr>\n";
        
        for (auto itvec = 1 + itmap->second.begin(); itvec != itmap->second.end(); itvec++)
            os << "<tr><td>" << itvec->first << " " << itvec->second << "</td></tr>\n\n";
    }
    
    os << "\n</table>\n</body>\n</html>\n\n" << endl;
}

vector<pair<pair<int, int>, pair<string, string> > > desciption = {
    {{23, 24}, {"23", ""}},
    {{11, 12}, {"22", "2"}},
    {{7, 8}, {"21", "3"}},
    {{5, 6}, {"20", "4"}},
    {{3, 4}, {"18", "6"}},
    {{2, 3}, {"16", "8"}},
    {{1, 2}, {"12", "12"}},
};

int main(int argc, const char * argv[]) {
    cout << "MAX_N=";
    cin >> MAX_N;

    for (auto vecit = desciption.begin(); vecit != desciption.end(); vecit++) {
        int a = vecit->first.first;
        int b = vecit->first.second;
        string ha = vecit->second.first;
        string hb = vecit->second.second;
        
        filebuf fb;
        fb.open("index_" + ha + "_" + hb + ".html", ios::out);
        ostream os(&fb);
        
        os.unsetf(ios::floatfield);
        os.setf(ios::fixed, ios::floatfield);
        os.precision(12);
        
        print_table(os, a, b, ha, hb);
        
        fb.close();
    }
}