#ifndef STAGERAIL_H
#define STAGERAIL_H

#include <QFrame>
#include <QString>
#include <QList>

class QLabel;
class QButtonGroup;
class QPushButton;

class StageRail : public QFrame
{
    Q_OBJECT
public:
    explicit StageRail(QWidget *parent = nullptr);
    QString currentPhase() const;
signals:
    void phaseChanged(QString& phase);
private:
    QButtonGroup*           m_stageGroup        = nullptr;
    QList<QFrame*>          m_dots;
    QList<QFrame*>          m_lines;
    QList<QPushButton*>     m_btns;
    QString                 m_currentPhase;

    int findPhaseIndex(const QString& phaseName) const;
    int findStageLevel(const QString& stageName) const;
};

#endif // STAGERAIL_H
