#include "kp.h"
#include <iostream>
#include <QDebug>
#include <sstream>
using std::cout;


KP::KP()
{
    this->base_parametres();

}

void KP::base_parametres(){
    this->N=3;
    this->k1=3;
    this->k2=3;
    this->k3=7;
    this->etto=4;
    calculate();
}

void KP::calculate(){
//    this->P1=round((0.5+((this->k2+1)/(2*(this->k3+11))))*100)/100;
    this->P1=(0.5+((this->k2+1.0)/(2.0*(this->k3+11.0))));

//    this->P2=round((0.5+0.02*(this->k1+this->k2+1))*100)/100;
    this->P2=(0.5+0.02*(this->k1+this->k2+1.0));
    this->S=10.0*(this->k2+this->k3+5.0);
    this->W=(2+this->k1)*10;
    this->n1=calculate_n(this->k1);
    this->n2=calculate_n(this->k2);
    this->n3=calculate_n(this->k3);
//    this->n1=round(calculate_n(this->k1)*100)/100;
//    this->n2=round(calculate_n(this->k2)*100)/100;
//    this->n3=round(calculate_n(this->k3)*100)/100;
//    this->n4=100-round((this->n1+this->n2+this->n3)*100)/100;
    this->n4=100.0-(this->n1+this->n2+this->n3);

    this->R=20+this->k3;
    this->task1();
    this->task2();
    calculate_N(this->N1,this->n1);
    calculate_N(this->N2,this->n2);
    calculate_N(this->N3,this->n3);
    calculate_N(this->N4,this->n4);
    qDebug()<<this->N4;
    this->task3();


}

double KP::calculate_V(double Nv, double Np, int d){
    double V_current= this->S*(Nv-(d/2)*fabs(Nv-Np));
    return V_current;
}

double KP::calculate_n(int k){
//    return round(((80*k)/(this->k1+this->k2+this->k3+2))*100)/100;
    return (80.0*k)/(this->k1+this->k2+this->k3+2.0);


}
double KP::calculate_N(double n){
//    return round((0.01*n*this->Nv)*100)/100;
    return (0.01*n*this->Nv);

}

void KP::task1(){
    this->phi=vector <vector <double>>(2,{0,0});
    this->psi=vector <vector <double>>(2,{0,0});
    vector <double> calc={this->P1,this->P, (1.0-this->P), this->P2 };
    this->get_phi_or_psi(this->phi,calc);
    for (auto& i:calc){
        i=1-i;
    }
    this->get_phi_or_psi(this->psi,calc);
//    this->x0=round(((phi[1][1]-phi[1][0])/(phi[0][0]-phi[0][1]-phi[1][0]+phi[1][1]))*100)/100;
//    this->V_task1=round((this->x0*phi[0][0]+(1-this->x0)*phi[1][0])*100)/100;
//    this->q1=round((this->x0*this->V_task1)*100)/100;
//    this->q2=round(((1-this->x0)*this->V_task1)*100)/100;
    this->x0=(phi[1][1]-phi[1][0])/(phi[0][0]-phi[0][1]-phi[1][0]+phi[1][1]);
    this->V_task1=(this->x0*phi[0][0]+(1-this->x0)*phi[1][0]);
    this->q1=(this->x0*this->V_task1);
    this->q2=((1.0-this->x0)*this->V_task1);

}

void KP::task2(){
    this->max_d=static_cast<int>(ceil(this->q1*100/(4*this->etto)));
    double sum_p=0.0, prom=0.05;

    for (auto i:this->p){
        sum_p+=i*prom;
        prom+=0.1;
    }

//    vector <double> Vb=this->get_max_V(round((sum_p*this->q1)*100)/100,max_d);
    vector <double> Vb=this->get_max_V((sum_p*this->q1),max_d);

    this->Vb =Vb[0];


    this->Nvb= Vb[1];
    vector <vector <vector<double>>> Vc(10);

    double Npc_current=0;
    prom=0.05;
    for (int i=0;i<10;i++){
//        Npc_current=round((prom*this->q1)*100)/100;
        Npc_current=(prom*this->q1);


        Vc[i].push_back(this->get_max_V(Npc_current,max_d));
        prom+=0.1;


    }
    double Vc0=0;

    for (int i=0;i<10;i++){
        Vc0+=(*max_element(Vc[i].begin(),Vc[i].end(),this->compare))[0]*this->p[i];
    }

    this->Vc=Vc0;
    if ((Vc0-Vb[0])<=this->W){
        this->Nv=Vb[1];
        this->V=Vb[0];
    }
    else{
//        this->Np=round((0.7*this->P1*this->q1)*100)/100;
        this->Np=(0.7*this->P1*this->q1);

        vector <double> ans=this->get_max_V(this->Np,this->max_d);
        this->Nv=ans[1];
        this->V=ans[0];
    }

}

void KP::get_phi_or_psi(vector <vector<double>>& vec,vector<double> calc){
    int j=0;
    for (auto& i:vec){
        for (auto& k:i){
            k=this->calculate_phi_or_psi(calc[j]);
            j++;
        }
    }



}
double KP::calculate_phi_or_psi(double P){
//    return round((P*this->N)*100)/100;
    return (P*this->N);

}

void KP::task3(){

    vector <vector<schema>>q(5);
    q[0].push_back(schema());
    q[0][0].path.insert({0,0});
    double q_cur=0;
    double condition=this->N1+this->N2+this->N3;
    qDebug()<<condition;
    qDebug()<<this->max_d;

    vector <double>N={this->N1,this->N2,this->N3,this->N4,0.0};
    for (int i =1;i<5;i++){
        int cur_d=0;
        condition=0;
        for (int k=i;k<N.size();k++)
            condition+=N[k];
        qDebug()<<condition;
        map <double, int> value;
        for (auto& k:q[i-1])
            for (auto& l:k.path){
                if (!value.count(l.first)){
                    value.insert({l.first,0});
                }


            }
        for (auto j:value){

                q[i].push_back( schema());
                q[i][q[i].size()-1].q=j.first;
                q[i][q[i].size()-1].path.clear();
                cur_d=0;
                while (round((this->etto*cur_d)+q[i][q[i].size()-1].q)-round(N[i-1])<0.0){cur_d++;}
                //cur_d=(q[i][q[i].size()-1].q-N[i-1])<0.0?static_cast<int>(ceil(round((fabs(q[i][q[i].size()-1].q-N[i-1])/4.0)*10)/10)):0;


                while (cur_d<=this->max_d) {
//                    q_cur=(round(((this->etto*cur_d)+q[i][q[i].size()-1].q-N[i-1])*100)/100);
                    q_cur=((this->etto*cur_d)+q[i][q[i].size()-1].q-N[i-1]);


                    if ( i==4 ){
                        q[i][q[i].size()-1].path.insert({0,cur_d});
                        break;
                    }
                    if (q_cur>condition ){
                        break;
                    }
                    q[i][q[i].size()-1].path.insert({q_cur,cur_d});
                    cur_d++;
                    if (q_cur-N[i]==0)
                        break;

                };
            }
    }

    vector<double> D(this->max_d+1);
    for (double i=1;i<this->max_d+1;i++){
//            D[i]=round((((200*(i+1.0)/i)+10*this->k3)*i*this->etto)*100)/100/100;
            D[i]=(((200*(i+1.0)/i)+10.0*this->k3)*i*this->etto)/100.0;

    }
    map <int, vector<double>> f;
    int quantity=0;
    for(auto i:q)
            quantity+= static_cast<int>(i.size());
    for (int i=0;i<q.size();i++){
            qDebug()<<i+1<<" квартал";
            for (auto& j:q[i]){
                qDebug()<<j.q;
                for (auto& k:j.path){
                     qDebug()<<k.first<<k.second;
                }

            }
    }


    f[quantity]={0,0};
    int l2=1;

    for (int i=q.size()-1;i>0;i--){
        int l1=q[i].size();
        for (auto& j:q[i]){
            vector<vector <double>> vec;
            int l=j.path.size();
            for (auto& k:j.path){
                    double local=quantity+l2-l;
//                    double C=round((D[k.second]+this->R*k.first/100.0+f.at(static_cast<int>(local))[0])*1000)/1000;
                    double C=(D[k.second]+this->R*k.first/100.0+f.at(static_cast<int>(local))[0]);
                    vec.push_back({C, local});
                    l--;

            }
            f[quantity-l1]=*min_element(vec.begin(),vec.end());

            l1--;
        }
        l2=q[i].size();

        quantity-=l2;

    }

    this->q=q;
    this->f=f;
        qDebug()<<"yes";




}

vector <vector <double>> KP::get_phi(){
    return this->phi;
}

vector <vector <double>> KP::get_psi(){
    return this->psi;
}

double KP::calc_Vb(int d, double Nv, double Np){
    double ans=(this->S*(Nv-((d/2.0)*abs(Nv-Np))));
//    double ans=round((this->S*(Nv-((d/2.0)*abs(Nv-Np))))*1000)/1000;


    return ans;
}

vector <double> KP::get_max_V(double Np, int d_max){
    vector <double> ans;
    double V_cur=0,V_prev=0;
    double NV_cur=0,Nv_prev=0;
    int d=1;
    do{
        NV_cur=(4*d*this->etto)/100.0;
        V_cur=this->calc_Vb(d,NV_cur,Np);

        Nv_prev=V_cur>V_prev?NV_cur: Nv_prev;
        V_prev=V_cur>=V_prev?V_cur:V_prev;


        d++;

    }while(V_cur>V_prev or d<=d_max);
    ans.push_back(V_prev);
    ans.push_back(Nv_prev);

    return ans;

}

void KP::recalculate(double k1,double k2,double k3, double N, double etto){
    this->k1=k1;
    this->k2=k2;
    this->k3=k3;
    this->N=N;
    this->etto=etto;
    qDebug()<<this->k1<<this->k2<<this->k3<<this->N<<this->etto;
    this->calculate();

}
double KP::get_P(){
    return this->P;
}
double KP::get_P1(){
    return this->P1;
}
double KP::get_P2(){
    return this->P2;
}
int KP::get_N(){return this->N;};
double KP::get_x(){return this->x0;};
double KP::get_V_task1(){return this->V_task1;};
double KP::get_q1(){return this->q1;};
double KP::get_q2(){return this->q2;};
double KP::get_S(){return this->S;};
double KP::get_Nvb(){return this->Nvb;};
double KP::get_Nv(){return this->Nv;};
double KP::get_Vc(){return this->Vc;};
double KP::get_Vb(){return this->Vb;};
double KP::get_V(){return this->V;};
int KP::get_W(){return this->W;};

void KP::calculate_N(double& N,double& n){
//    N=round((this->Nv*n)*100)/100;
    N=(this->Nv*n);

}

QString KP::get_q(){
    QString text;
    for (int i=0;i<this->q.size();i++){
        std::ostringstream ss1;
        ss1<<i;
        text.append("<br>"+ ss1.str()+"-квартал:");
        for (auto& j:q[i]){
            std::ostringstream ss2;
            ss2<<(j.q);
            text.append("<br>"+ss2.str()+": ");
            for (auto& k:j.path){
                    std::ostringstream ss3;
                    ss3<<k.first;
                    std::ostringstream ss4;
                    ss4<<k.second;
                    text.append("q = " + ss3.str() + " d = "+  ss4.str()+", ");}
        }
    }
    return text;
}
QString KP::get_f(){
    QString text;
    for (auto& i:this->f){
        std::ostringstream ss1;
        ss1<<i.first;
        std::ostringstream ss2;
        ss2<<i.second[0];
        std::ostringstream ss3;
        ss3<<i.second[1];
        text.append("Состояние: "+ ss1.str() +"<br> Оптимальная стоимость:" +  ss2.str() + "; Следующий переход: " +  ss3.str()+ "<br>");
    }
    return text;

}
QString KP::get_path(){
    int i=this->f.at(1)[1];
    QString text="1";
    while ( i!=16){
        std::ostringstream ss1;

        ss1<<i;

        text.append("->"+ ss1.str());
        i=this->f.at(i)[1];
    }
    std::ostringstream ss2;
    ss2<<f.at(1)[0];
    text.append("<<br>>Оптимальная стоимость: " + ss2.str());
    return text;
}






