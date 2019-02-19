#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("Doom Fire Qt");

    playPauseButton = new QPushButton(this);
    createDestroyButton = new QPushButton(this);

    DecreaseWindButton = new QPushButton(this);
    DecreaseWindButton->setText("-");
    DecreaseWindButton->setMaximumWidth(35);

    IncreaseWindButton = new QPushButton(this);
    IncreaseWindButton->setText("+");
    IncreaseWindButton->setMaximumWidth(35);

    DecreaseInvervalButton = new QPushButton(this);
    DecreaseInvervalButton->setText("-");
    DecreaseInvervalButton->setMaximumWidth(35);

    IncreaseInvervalButton = new QPushButton(this);
    IncreaseInvervalButton->setText("+");
    IncreaseInvervalButton->setMaximumWidth(35);

    WindSpeedLabel = new QLabel(this);
    //WindSpeedLabel->setStyleSheet("QLabel { color : white; }");

    updateIntervalLabel = new QLabel(this);
    //updateIntervalLabel->setStyleSheet("QLabel { color : white; }");

    ui->mainToolBar->addWidget(playPauseButton);
    ui->mainToolBar->addWidget(createDestroyButton);

    ui->mainToolBar->addSeparator();
    ui->mainToolBar->addWidget(DecreaseWindButton);
    ui->mainToolBar->addWidget(WindSpeedLabel);
    ui->mainToolBar->addWidget(IncreaseWindButton);

    ui->mainToolBar->addSeparator();
    ui->mainToolBar->addWidget(DecreaseInvervalButton);
    ui->mainToolBar->addWidget(updateIntervalLabel);
    ui->mainToolBar->addWidget(IncreaseInvervalButton);

    fireWidget = new FireWidget(centralWidget()->width(), centralWidget()->height());
    setCentralWidget(fireWidget);

    connect(playPauseButton, &QPushButton::released, fireWidget, &FireWidget::onPlayPausePressed);
    connect(createDestroyButton, &QPushButton::released, fireWidget, &FireWidget::onCreateDestroyPressed);
    connect(DecreaseWindButton, &QPushButton::released, fireWidget, &FireWidget::onDecreaseWindPressed);
    connect(IncreaseWindButton, &QPushButton::released, fireWidget, &FireWidget::onIncreaseWindPressed);
    connect(DecreaseInvervalButton, &QPushButton::released, fireWidget, &FireWidget::onDecreaseIntervalPressed);
    connect(IncreaseInvervalButton, &QPushButton::released, fireWidget, &FireWidget::onIncreaseIntervalPressed);

    connect(fireWidget, &FireWidget::statusUpdated, this, &MainWindow::onStatusUpdated);

    onStatusUpdated();
}

MainWindow::~MainWindow()
{
    delete fireWidget;
    delete ui;
}

void MainWindow::onStatusUpdated()
{
    playPauseButton->setText(fireWidget->playPauseString());
    createDestroyButton->setText(fireWidget->CreateDestroyString());

    WindSpeedLabel->setText(fireWidget->windSpeed());
    updateIntervalLabel->setText(fireWidget->updateInterval());
}
