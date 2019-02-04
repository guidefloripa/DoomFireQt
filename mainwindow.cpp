#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    qDebug() << "size: " << size() << centralWidget()->size();

    fireWidget = new FireWidget(centralWidget()->width(), centralWidget()->height());

    setCentralWidget(fireWidget);
}

MainWindow::~MainWindow()
{
    delete fireWidget;
    delete ui;
}
