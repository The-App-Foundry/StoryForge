#ifndef NAVRAIL_H
#define NAVRAIL_H

#include <QFrame>

class QButtonGroup;

class NavRail : public QFrame
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
    bool m_hovered = false;
};

#endif // NAVRAIL_H
