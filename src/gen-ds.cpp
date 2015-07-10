#include <iostream>
#include "build-ds.h"

using namespace std;

int main(int argc, char **argv) {
    int i;
    long ds, dp;
    bool debug = false;
    ds = dp = 0;

    for (i = 0; i < argc; i++) {
        string op(argv[i]);
        if (op == "-ds") {
            if (i + 1 < argc) {
                string par(argv[i + 1]);
                ds = std::stol(par);
            }
        } else if (op == "-dp") {
            if (i + 1 < argc) {
                string par(argv[i + 1]);
                dp = std::stol(par);
            }
        } else if (op == "-v") {
            debug = true;
        }
    }

    if (ds >= 0) {
        if (debug)
            cout << "DS = " << ds << endl;
    } else {
        ds = 0;
    }
    if (dp >= 0) {
        if (debug)
            cout << "DP = " << dp << endl;
    } else {
        dp = 0;
    }

    rapidjson::StringBuffer s;
//    getDataSource(s,1,"Andar ");
//    cout << s.GetString() << endl;
    for (i = 1; i <= ds; i++) {
        T_DS ds_gen;
        ds_gen.id = i;
        ds_gen.name = "Andar ";
        getDataSource(s, ds_gen);
        cout << s.GetString() << endl;
        s.Clear();
        if(dp>0){
            getDataPoint(s, ds_gen, dp);
            cout << s.GetString() << endl;
            s.Clear();
        }
    }
    return 0;
}

