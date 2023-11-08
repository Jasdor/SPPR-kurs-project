#ifndef KP_H
#define KP_H
#include <math.h>
#include <vector>
#include <algorithm>
#include<map>
#include <QString>
using std::vector,std::max_element,std::make_pair, std::map;

class KP
{
private:
    struct schema
    {
        double q=0;
        map<double,int> path;
    };
    double k1,k2,k3;
    int N,W,R;
    double P1,P2;
    double P = 0.5;
    double V;
    double S;
    double etto;
    double n1,n2,n3,n4;
    double N1,N2,N3,N4;
    double Nv,Np;
    double Vb,Vc,Nvb;
    vector <double> p ={0.04, 0.21, 0.25, 0.25, 0.1, 0.05, 0.04, 0.03, 0.02, 0.01};
    int max_d;
    double q1,q2;
    double x0, V_task1;
    vector <vector <double>> phi,psi;
    map <int, vector<double>> f;
    vector <vector<schema>>q;
    vector <int> path;

public:
    KP();
    void base_parametres();
    void recalculate(double,double,double, double,double);
    void calculate();
    double calculate_V(double,double,int);
    double calculate_n(int);
    double calculate_N(double);
    void task1();
    void task2();
    void task3();
    double calculate_phi_or_psi(double);
    void get_phi_or_psi( vector <vector <double>>&, vector <double>);
    vector <vector <double>>get_phi();
    vector <vector <double>>get_psi();
    double calc_Vb(int,double,double);
    vector <double> get_max_V(double, int);
    double get_P();
    double get_P1();
    double get_P2();
    int get_N();
    double get_x();
    double get_V_task1();
    double get_q1();
    double get_q2();
    double get_Vc();
    double get_Vb();
    double get_Nvb();
    double get_Nv();
    double get_V();
    double get_S();
    int get_W();
    void calculate_N(double&,double&);
    QString get_q();
    QString get_f();
    QString get_path();


    static bool compare(vector<double>& lhs, vector<double>& rhs){
        return lhs[0] < rhs[0];
    }



};

#endif // KP_H
