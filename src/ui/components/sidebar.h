#ifndef SIDEBAR_H
#define SIDEBAR_H

#include <QWidget>
#include <QVBoxLayout>
#include <QButtonGroup>

class NavRail;
class ManuscriptPanel;

class SideBar : public QWidget
{
    Q_OBJECT

public:
    explicit SideBar(QWidget *parent = nullptr);

private:
    NavRail*         m_navRail         = nullptr;
    ManuscriptPanel* m_manuscriptPanel = nullptr;
};

#endif // SIDEBAR_H
