#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include<menu.h>
#include<registretion.h>


#include <QMainWindow>
#include<QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_admin_button_clicked();
    void on_person_button_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
