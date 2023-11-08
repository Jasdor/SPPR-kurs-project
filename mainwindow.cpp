#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtCore>
#include <iostream>
#include <QPropertyAnimation>
#include <string>
#include <QDesktopServices>
#include "kp.h"
#include <QIntValidator>
KP kp;

QList<QList<QLineEdit*>> lineEditList;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    //centralWidget(setGraphicsEffect(shadow));
    this->setWindowTitle("TPR");
    ui->setupUi(this);
    this->ui->Task_frame->hide();
    this->ui->Parameters_frame->hide();
    this->ui->Main_Window_frame->show();
    this->ui->Data_frrame->hide();
    this->ui->Task1_frame->hide();
    this->ui->Task2_frame->hide();
    this->ui->Task3_frame->hide();
    this->ui->k1_line->setValidator(new QIntValidator(0, 9999));
    this->ui->k2_line->setValidator(new QIntValidator(0, 9999));
    this->ui->k3_line->setValidator(new QIntValidator(0, 9999));
    this->ui->N_line->setValidator(new QIntValidator(0, 9999));
    this->ui->etto_line->setValidator(new QIntValidator(0, 9999));




    //his->ui->TSP_frame->hide();
//    this->ui->Header->grabMouse()=this->moveWindow();


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_menu_button_clicked()
{
    auto width = ui->slide_menu_container->width();
    auto newwidth=0;
    if (width==0)
    {
        newwidth=200;
    }
    else
    {
        newwidth=0;
    }
    QPropertyAnimation *animation= new  QPropertyAnimation(ui->slide_menu_container,"maximumWidth",this);
    animation->setDuration(250);
    animation->setStartValue(width);
    animation->setEndValue(newwidth);
    animation->setEasingCurve(QEasingCurve::InOutQuart);
    animation->start();
}

void MainWindow::on_minimize_window_button_clicked()
{
    this->showMinimized();
    this->show();
}

void MainWindow::on_close_window_button_clicked()
{
    this->close();
}

void MainWindow::on_change_size_button_clicked()
{
    if(this->isMaximized())
    {
        this->showNormal();
        //change_size_button.setIcon();
    }
    else
    {
        this->showMaximized();
    }
    this->show();
}



void MainWindow::on_github_site_clicked()
{
    QDesktopServices::openUrl(QUrl("https://github.com/Jasdor/TPR_task"));
}



//void MainWindow::moveWindow(){
//    if (!this->isMaximized()){
//        if (e==Qt::LeftButton){
//            this->move(this->pos()+e->globalpos-this->clickPosition);
//            this->clickPosition = e->globalPos();
//            e->accept();
//        }
//    }


//}

//void MainWindow::mousePressEvent(QMouseEvent* e){
//    this->clickPosition = e->globalPos();


//}



//void MainWindow::on_calculate_button_clicked()
//{
//    kp.recalculate(this->ui->k1_line->text().toInt(),this->ui->k2_line->text().toInt(),this->ui->k3_line->text().toInt(),this->ui->N_line->text().toInt(),this->ui->etto_line->text().toInt());
//}
\
void MainWindow::hide_frame(){
    this->ui->Task_frame->hide();
    this->ui->Parameters_frame->hide();
    this->ui->Main_Window_frame->hide();
    this->ui->Data_frrame->hide();
        this->ui->Task1_frame->hide();
        this->ui->Task2_frame->hide();
        this->ui->Task3_frame->hide();

}


void MainWindow::on_main_menu_button_clicked()
{
    this->hide_frame();
    this->ui->Main_Window_frame->show();

}


void MainWindow::on_Task_button_clicked()
{
    this->hide_frame();
    this->ui->Task_frame->show();
}


void MainWindow::on_Base_task_button_clicked()
{
    this->hide_frame();
    this->ui->Data_frrame->show();
}


void MainWindow::on_Parametre_button_clicked()
{
    this->hide_frame();
    this->ui->Parameters_frame->show();
}
void MainWindow::do_task1(){

    QString text="\tРешение<br>"
                   "P= %1 - вероятность того, что покупатель выберет первый магазин;<br>"
                   "P<sub>1</sub> = %2 - вероятность того, что покупатель предпочтет стационарный компьютер;<br>"
                   "P<sub>2</sub> = %3 - вероятность того, что покупатель предпочтет ноутбук;<br>"
                   "Найдем значение выигрышей для первого игрока:<br>"
                   "φ<sub>11</sub> = %2 * %4 *10<sup>6</sup> =%5*10<sup>6</sup><br>"
                   "φ<sub>12</sub> = %3 * %4*10<sup>6</sup> = %6*10<sup>6</sup><br>"
                   "φ<sub>21</sub> = %1 * %4 *10<sup>6</sup> = %7*10<sup>6</sup><br>"
                   "φ<sub>22</sub> = %1 * %4 *10<sup>6</sup> = %8*10<sup>6</sup><br>"
                   "Найдем значение выигрышей для первого игрока:<br>"
                   "ψ<sub>11</sub> = (1-%2) * %4 *10<sup>6</sup> =%9*10<sup>6</sup><br>"
                   "ψ<sub>12</sub> = (1-%3) * %4*10<sup>6</sup> = %10*10<sup>6</sup><br>"
                   "ψ<sub>21</sub> = (1-%1) * %4 *10<sup>6</sup> = %11*10<sup>6</sup><br>"
                   "ψ<sub>22</sub> = (1-%1) * %4 *10<sup>6</sup> = %12*10<sup>6</sup><br>"
                   "Аналитический метод:<br>"
                   "x<sub>1</sub><sup>0</sup> = (φ<sub>22</sub>-φ<sub>21</sub>)/(φ<sub>11</sub>-φ<sub>12</sub>-φ<sub>21</sub>+φ<sub>22</sub>)"
                   "= (%8-%7)/(%5-%6-%7+%8)=%13<br>"
                   "Цена игры<br>"
                   "V = x<sub>1</sub><sup>0</sup>φ<sub>11</sub> + (1 -x<sub>1</sub><sup>0</sup>)φ<sub>21</sub> = %13 * %5 *10<sup>6</sup> + (1- %13)*%7*10<sup>6</sup>= %14 *10<sup>6</sup><br>"
                   "Таким образом, фирме «X» следует запланировать на текущий год сборку %14 *10<sup>6</sup> компьютеорв, из них стационарных:<br>"
                   "q<sub>1</sub>= x<sub>1</sub><sup>0</sup>*V= %13 * %14 * 10<sup>6</sup> = %15,<br>"
                   "А остальные -переносные, в количестве:<br>"
                   "q<sub>2</sub> = (1-x<sub>1</sub><sup>0</sup>)*V = (1- %13 )* %14 * 10<sup>6</sup> = %16";

    this->ui->Task1_text->setHtml(text.arg(kp.get_P()).arg(kp.get_P1()).arg(kp.get_P2()).arg(kp.get_N()).arg(kp.get_phi()[0][0]).arg(kp.get_phi()[0][1])
                                      .arg(kp.get_phi()[1][0]).arg(kp.get_phi()[1][1]).arg(kp.get_psi()[0][0]).arg(kp.get_psi()[0][1])
                                      .arg(kp.get_psi()[1][0]).arg(kp.get_psi()[1][1]).arg(kp.get_x()).arg(kp.get_V_task1()).arg(kp.get_q1()).arg(kp.get_q2()));
}

void MainWindow::do_task2(){
    int ans= kp.get_Vc()-kp.get_Vb();
    QString text = "Решение<br>"
                   "Определим прибыль от прожажи двуядерных комиьютеров:<br>"
                   "S = 10(k<sub>2</sub>+k<sub>3</sub>+5) = %1<br>"
                   "Определим максимально ожидаемую прибыль, для чего воспользуемся формулой:<br>"
                   "V = S*(N<sub>B</sub> - (d/2) * |N<sub>B</sub> - N<sub>П</sub>|):<br>"

                   "V(B) = %2 <br>"
                   "Разность:<br>"
                   "V(C)-V(B) = %3 - %2 = %4 %5<br>"
                   "V = %6 <br>"
                   "N<sub>B</sub> = %7 ";

    QString text2;
    if (ans<= kp.get_W()){
        text2=" предпочтение сследует отдать стратегии А<sub>1</sub, тогда V=V(B)> ";

    }
    else{
        text2 = "предпочтение сследует отдать стратегии A<sub>2</sub>, тогда N<sub>П</sub> = 0.7 * P<sub>1</sub> * q<sub>1</sub>";
    }
    this->ui->Task2_text->setHtml(text.arg(kp.get_S()).arg(kp.get_Vb()).arg(kp.get_Vc()).arg(ans).arg(text2).arg(kp.get_V()).arg(kp.get_Nv()));

}
void MainWindow::do_task3(){
    QString text ="Решение<br>"
                   "Рещение задачи выбора оптимального маршрута начинается с построения сети, отображающие все возможные состояня производства (уровни запаса) на каждом этапе, и ребра, определяющие переходы из одного состояния в другое:<br>"
                   "Сеть:<br> %1<br>"
                   "Оптимальные маршруты из каждого состояния:<br> %2<br>"
                   "Оптимальный маршрут:<br>%3";

    this->ui->Task3_text->setHtml(text.arg(kp.get_q()).arg(kp.get_f()).arg(kp.get_path()));
}


void MainWindow::on_Task1_button_clicked()
{
    this->hide_frame();
    this->do_task1();
    this->ui->Task1_frame->show();
}



void MainWindow::on_Task2_button_clicked()
{
    this->hide_frame();
    this->do_task2();
    this->ui->Task2_frame->show();
}


void MainWindow::on_Task3_button_clicked()
{
    this->hide_frame();
    this->do_task3();
    this->ui->Task3_frame->show();
}


void MainWindow::on_calculate_button_clicked()
{
    double k1 = this->ui->k1_line->text().toDouble();
    double k2 = this->ui->k2_line->text().toDouble();
    double k3 = this->ui->k3_line->text().toDouble();
    double N = this->ui->N_line->text().toDouble();
    double etto = this->ui->etto_line->text().toDouble();

    kp.recalculate(k1,k2,k3,N,etto);
}

