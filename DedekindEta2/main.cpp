#include <iostream>
#include <stdio.h>
#include <complex>
#include <cmath>
#include <map>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

typedef complex<double> dcomp;
int MAX_N;

int xx(int m, int n, int a) {
    return (6*m + 1) * (6*m + 1) + a * (6*n + 1) * (6*n + 1);
}

void print_table(ostream &os, const dcomp q, const int a, const int b, string h1, string h2) {
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
    
    map<int, dcomp> map_vc;
    for (auto itmap = map_vp.begin(); itmap != map_vp.end(); itmap++) {
        dcomp res(0, 0);
        for (auto itvec = itmap->second.begin(); itvec != itmap->second.end(); itvec++) {
            int m = itvec->first;
            int n = itvec->second;
            dcomp t = pow(q, 1.0 * xx(m, n, a) / b);
            if ((m + n) % 2 != 0)
                t *= -1;
            res += t;
        }
        map_vc[itmap->first] = res;
    }
    
    for (auto itmap = map_vp.begin(); itmap != map_vp.end(); itmap++) {
        vector<pair<int,int> > vec_mns = itmap->second;
        size_t rowspan = vec_mns.size();
        os << "<tr><td rowspan=\"" << rowspan << "\">" << xx(vec_mns[0].first, vec_mns[0].second, a) / b << "</td>\n";
        os << "<td>" << vec_mns[0].first << " " << vec_mns[0].second << "</td>\n";
        os << "<td rowspan=\"" << rowspan << "\">" << map_vc[itmap->first].real() << "<br>" << map_vc[itmap->first].imag() << "</td></tr>\n";
        
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
    
    double z_re;
    cout << "Z_re=";
    cin >> z_re;
    
    double z_im;
    cout << "Z_im=";
    cin >> z_im;
    
    const dcomp z(z_re, z_im);
    const double pi = 2*asin(1);
    const dcomp q = exp(z * dcomp(0, 1) * 2.0 * pi);
    
    filebuf fb;
    fb.open("index.html", ios::out);
    ostream os(&fb);
    
    os.unsetf ( std::ios::floatfield );
    os.setf( std::ios::fixed, std:: ios::floatfield );
    os.precision(12);
    
    const int a = 23, b = 24;
    print_table(os, q, a, b, "23", "");
    
    fb.close();
}