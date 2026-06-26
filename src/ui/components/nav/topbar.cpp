#include "topbar.h"
#include "conceptrail.h"
#include "titlebar.h"
#include "stagerail.h"
#include <QVBoxLayout>
#include <QFile>
#include <QLabel>

TopBar::TopBar(QWidget *parent)
    : QWidget{parent}
{
    setObjectName("topBar");

    auto* layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    m_titleBar      = new TitleBar(this);
    m_stageRail     = new StageRail(this);
    m_conceptRail   = new ConceptRail(this);

    connect(m_stageRail, &StageRail::phaseChanged,
            this, &TopBar::onPhaseChanged);

    layout->addWidget(m_titleBar);
    layout->addWidget(m_stageRail);
    layout->addWidget(m_conceptRail);

    QFile styleFile(":/topbarstyles.qss");

    if(styleFile.open(QFile::ReadOnly | QFile::Text)) {
        QString styleSheet = QLatin1String(styleFile.readAll());
        this->setStyleSheet(styleSheet);
        styleFile.close();
    }
}

void TopBar::onPhaseChanged(const QString& phase)
{
    m_phaseLabel = phase;

    if(phase == "CONCEPT"){
        m_conceptRail->show();
    } else {
        m_conceptRail->hide();
    }
}
