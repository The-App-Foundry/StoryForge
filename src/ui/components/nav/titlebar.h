#ifndef TITLEBAR_H
#define TITLEBAR_H

#include <QFrame>

class TitleBar : public QFrame
{
    Q_OBJECT
public:
    explicit TitleBar(QWidget *parent = nullptr);

signals:
};

#endif // TITLEBAR_H
