#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QPainter"
#include "QtMath"
#include "poland.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    resize(800, 600);

    button = new QPushButton(this);
    button->setGeometry(width() * 0.8625, height() * 0.0167, width() * 0.125, height() * 0.067);
    button->setText("Show Graphic");
    button->setStyleSheet("background: rgb(255, 190, 208)");
    connect(button, SIGNAL(clicked()), this, SLOT(buttonClicked()));

    ui->label->setGeometry(width() * 0.0125, height() * 0.0167, width() * 0.125, height() * 0.067);
    ui->label->setText("F(x) = ");

    ui->lineEdit->setGeometry(width() * 0.0125 + width() / 16, height() * 0.0167, width() * 0.8375 - width() / 16, height() * 0.067);
    ui->lineEdit->setStyleSheet("background: rgb(255, 190, 208)");

    ui->label_2->setGeometry(width() * 0.0125, height() * 0.0997, width() * 0.8375, height() * 0.884);

    labelxmin = new QLabel(this);
    labelxmin->setGeometry(width() * 0.8625, height() * 0.1507, width() * 0.125, height() * 0.067);
    labelxmin->setText("xmin =");

    labelxmax = new QLabel(this);
    labelxmax->setGeometry(width() * 0.8625, height() * 0.2277, width() * 0.125, height() * 0.067);
    labelxmax->setText("xmax =");

    labelymin = new QLabel(this);
    labelymin->setGeometry(width() * 0.8625, height() * 0.3047, width() * 0.125, height() * 0.067);
    labelymin->setText("ymin =");

    labelymax = new QLabel(this);
    labelymax->setGeometry(width() * 0.8625, height() * 0.3817, width() * 0.125, height() * 0.067);
    labelymax->setText("ymax =");

    xmn = new QLineEdit(this);
    xmn->setGeometry(width() * 0.8625 + width() * 0.125 / 2, height() * 0.1507, width() * 0.125 / 2, height() * 0.067);
    xmn->setStyleSheet("background: rgb(255, 170, 208)");

    xmx = new QLineEdit(this);
    xmx->setGeometry(width() * 0.8625 + width() * 0.125 / 2, height() * 0.2277, width() * 0.125 / 2, height() * 0.067);
    xmx->setStyleSheet("background: rgb(255, 150, 208)");

    ymn = new QLineEdit(this);
    ymn->setGeometry(width() * 0.8625 + width() * 0.125 / 2, height() * 0.3047, width() * 0.125 / 2, height() * 0.067);
    ymn->setStyleSheet("background: rgb(255, 130, 208)");

    ymx = new QLineEdit(this);
    ymx->setGeometry(width() * 0.8625 + width() * 0.125 / 2, height() * 0.3817, width() * 0.125 / 2, height() * 0.067);
    ymx->setStyleSheet("background: rgb(255, 110, 208)");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::buttonClicked()
{
    QPixmap pm(width() * 0.8375, height() * 0.884);
    pm.fill(Qt::cyan);

    QString func = ui->lineEdit->text();
    QString st = func;

    QPainter painter;
    painter.begin(&pm);

    QPen pen;
    pen.setBrush(Qt::blue);
    //pen.setWidth(2);
    pen.setCapStyle(Qt::RoundCap);
    painter.setPen(pen);

    double x, y;
    double xmin = -10;
    double xmax = 10;
    double ymin = -10;
    double ymax = 10;

    QString mnx = xmn->text();
    QString mxx = xmx->text();
    QString mny = ymn->text();
    QString mxy = ymx->text();

    if (mnx != "")
        xmin = mnx.toDouble();
    if (mxx != "")
        xmax = mxx.toDouble();
    if (mny != "")
        ymin = mny.toDouble();
    if (mxy != "")
        ymax = mxy.toDouble();

    int xgmin = 0;
    int xgmax = pm.width();
    int ygmin = 0;
    int ygmax = pm.height();

    double kx = (xgmax - xgmin) / (xmax - xmin);
    double ky = (ygmin - ygmax) / (ymax - ymin);
    int xg, yg;
    int x0 = xgmin - kx * xmin;
    int y0 = ygmin - ky * ymax;
    double stepx = (xmax - xmin) / (xgmax - xgmin);

    painter.drawLine(x0 - pm.width(), y0, x0 + pm.width(), y0);
    painter.drawLine(x0, y0 - pm.width(), x0, y0 + pm.width());


    QPainterPath path;
    pen.setColor(Qt::red);
    pen.setWidth(2);
    painter.setPen(pen);
    x = xmin;
    st.replace("x", "(" + QString::number(x) + ")");

    double ans = 0;
    int pred = calcc(func.toStdString(), ans);
    int post = pred;
    y = ans;
    xg = x0 + kx * x;
    yg = y0 + ky * y;
    path.moveTo(xg, yg);

    while (x <= xmax) {
        st = func;
        st.replace("x", "(" + QString::number(x) + ")");
        int id = 0;
        id = calcc(st.toStdString(), ans);
        //cout << post << endl;
        if (id == 0)
        {
            y = ans;
            xg = x0 + kx * x;
            yg = y0 + ky * y;
            if (post == -1) {
                path.moveTo(xg, yg);
            }
            if (post == 0) {
                path.lineTo(xg,yg);
                painter.drawPath(path);
            }
        }
        x += stepx;
        post = pred;
        pred = id;
        //cout << "x= " << x << "; y= " << y << "; pred = " << pred << endl;
    }
    ui->label_2->setPixmap(pm);
}
