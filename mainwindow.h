#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QPushButton *button;
    QLabel *labelxmin;
    QLabel *labelxmax;
    QLabel *labelymin;
    QLabel *labelymax;
    QLineEdit *xmn;
    QLineEdit *xmx;
    QLineEdit *ymn;
    QLineEdit *ymx;

private slots:
    void buttonClicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
