#ifndef NAVRAIL_H
#define NAVRAIL_H

#include <QWidget>
#include <QButtonGroup>

class QPushButton;

class NavRail : public QWidget
{
    Q_OBJECT

public:
    explicit NavRail(QWidget *parent = nullptr);

signals:
    void navItemSelected(const QString& section);

private:
    void buildNavButtons();
    void buildFooter();

    QButtonGroup* m_navGroup = nullptr;
};

#endif // NAVRAIL_H
