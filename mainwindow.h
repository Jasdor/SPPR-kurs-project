#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
# include <QLineEdit>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_menu_button_clicked();

    void on_minimize_window_button_clicked();

    void on_close_window_button_clicked();

    void on_change_size_button_clicked();

    void on_github_site_clicked();
    void hide_frame();


//    void moveWindow(QMouseEvent*);
//   void mousePressEvent(QMouseEvent*);


//    void on_calculate_button_clicked();

    void on_main_menu_button_clicked();

    void on_Task_button_clicked();

    void on_Base_task_button_clicked();

    void on_Parametre_button_clicked();
    void do_task1();
    void do_task2();
    void do_task3();


    void on_Task1_button_clicked();
    void on_Task2_button_clicked();

    void on_Task3_button_clicked();

    void on_calculate_button_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
