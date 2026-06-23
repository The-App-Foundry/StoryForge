#ifndef SIDEBAR_H
#define SIDEBAR_H

#include <QWidget>

class NavRail;
class ManuscriptPanel;

class SideBar : public QWidget
{
    Q_OBJECT

public:
    explicit SideBar(QWidget* parent = nullptr);

    // Accessor for MainWindow to seed manuscript data and wire signals.
    // Raw pointer is correct — ManuscriptPanel lifetime is tied to SideBar
    // via Qt parent chain.
    [[nodiscard]] ManuscriptPanel* manuscriptPanel() const { return m_manuscriptPanel; }

private:
    NavRail*         m_navRail         = nullptr;
    ManuscriptPanel* m_manuscriptPanel = nullptr;
};

#endif // SIDEBAR_H