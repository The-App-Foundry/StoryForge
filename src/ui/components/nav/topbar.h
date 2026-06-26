#ifndef TOPBAR_H
#define TOPBAR_H

#include <QWidget>

class TitleBar;
class ConceptRail;
class StageRail;

class TopBar : public QWidget
{
    Q_OBJECT
public:
    explicit TopBar(QWidget *parent = nullptr);
private:
    void onPhaseChanged(const QString& phase);

    ConceptRail* m_conceptRail  = nullptr;
    TitleBar*    m_titleBar     = nullptr;
    StageRail*   m_stageRail    = nullptr;
    QString      m_phaseLabel;
};

#endif // TOPBAR_H
