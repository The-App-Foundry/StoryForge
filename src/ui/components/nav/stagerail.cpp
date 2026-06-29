#include "stagerail.h"
#include "../../meta.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QButtonGroup>
#include <QPushButton>
#include <QFile>
#include <QStyle>

StageRail::StageRail(QWidget *parent)
    : QFrame{parent}
{
    setObjectName("stageRail");

    QHBoxLayout* stageStripLayout = new QHBoxLayout(this);
    stageStripLayout->setContentsMargins(18, 0, 18, 0);
    stageStripLayout->setSpacing(0);

    QLabel* labelStageTag = new QLabel(QStringLiteral("STAGE"), this);
    labelStageTag->setObjectName(QStringLiteral("labelStageTag"));
    stageStripLayout->addWidget(labelStageTag);

    m_stageGroup = new QButtonGroup(this);
    m_stageGroup->setExclusive(true);

    m_currentPhase = QLatin1String("CONCEPT");
    emit phaseChanged(m_currentPhase);

    for (int i = 0; i < phases.size(); ++i) {
        const QString& phaseName = phases[i];

        QWidget* seg = new QWidget(this);
        seg->setObjectName(QStringLiteral("stageSegmentWidget"));

        QHBoxLayout* segLayout = new QHBoxLayout(seg);
        segLayout->setContentsMargins(0, 0, 0, 0);
        segLayout->setSpacing(8);

        if (i > 0) {
            QFrame* dot = new QFrame(seg);
            dot->setObjectName(QStringLiteral("stageIndicatorDot"));
            dot->setFixedSize(5, 5);
            dot->setProperty("phaseIndex", i);
            dot->setProperty("activePhase", false);
            segLayout->addWidget(dot);

            m_dots.append(dot);

            QFrame* line = new QFrame(seg);
            line->setObjectName(QStringLiteral("stageLine"));
            line->setFrameShape(QFrame::HLine);
            line->setFrameShadow(QFrame::Plain);
            line->setFixedHeight(1);
            line->setFixedWidth(18);
            line->setProperty("activePhase", false);
            segLayout->addWidget(line);
            m_lines.append(line);
        }

        QPushButton* btn = new QPushButton(phaseName, seg);
        btn->setObjectName(QStringLiteral("stageButton"));
        btn->setCheckable(true);
        btn->setFixedHeight(28);
        m_btns.append(btn);

        if (phaseName == QLatin1String("CONCEPT"))
            btn->setChecked(true);

        m_stageGroup->addButton(btn);
        segLayout->addWidget(btn);


        stageStripLayout->addWidget(seg);
    }

    stageStripLayout->addStretch(1);

    connect(m_stageGroup, QOverload<QAbstractButton*>::of(&QButtonGroup::buttonClicked),
            this, [this](QAbstractButton* btn) {
        m_currentPhase = btn->text();
        emit phaseChanged(m_currentPhase);

        int currentLevel = findStageLevel(m_currentPhase);

        for (int i = 0; i < m_btns.size(); ++i) {
            bool completed = i < currentLevel;

            m_btns[i]->setProperty("completed", completed);
            m_btns[i]->style()->polish(m_btns[i]);
        }

        for (int i = 0; i < m_dots.size(); ++i) {
            bool completed = i < currentLevel;

            m_dots[i]->setProperty("completed", completed);
            m_lines[i]->setProperty("completed", completed);
            m_lines[i]->style()->polish(m_lines[i]);
            m_dots[i]->style()->polish(m_dots[i]);
        }

    });

    QFile styleFile(":/styles/stagerailstyles.qss");

    if(styleFile.open(QFile::ReadOnly | QFile::Text)) {
        QString styleSheet = QLatin1String(styleFile.readAll());
        this->setStyleSheet(styleSheet);
        styleFile.close();
    }
}

QString StageRail::currentPhase() const
{
    return m_currentPhase;
}

int StageRail::findPhaseIndex(const QString& phaseName) const
{
    return phases.indexOf(phaseName);
}

int StageRail::findStageLevel(const QString& phaseName) const
{
    for (int i = 0; i < (int)std::size(kStages); ++i) {
        if(QString::fromLatin1(kStages[i].stage) == phaseName) {
            return kStages[i].stageLevel;
        }
    }

    return -1;
}
