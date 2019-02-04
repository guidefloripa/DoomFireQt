#ifndef FIREWIDGET_H
#define FIREWIDGET_H

#include <QWidget>
#include <QTimer>

class FireWidget : public QWidget
{
    Q_OBJECT
public:
    explicit FireWidget(int w, int h, QWidget *parent = nullptr);
    ~FireWidget();

protected:
   class Priv;

   Priv *d;
   QTimer *timer;

   void paintEvent(QPaintEvent *event);
   void mouseReleaseEvent(QMouseEvent *event);

signals:

public slots:
   void onTimerUpdate();
};

#endif // FIREWIDGET_H
