#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "firewidget.h"

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    FireWidget *fireWidget;

    QPushButton* playPauseButton;
    QPushButton* createDestroyButton;

    QPushButton* DecreaseWindButton;
    QPushButton* IncreaseWindButton;

    QPushButton* DecreaseInvervalButton;
    QPushButton* IncreaseInvervalButton;

    QLabel *WindSpeedLabel;
    QLabel *updateIntervalLabel;

public slots:
    void onStatusUpdated();
};

#endif // MAINWINDOW_H
