#include "conceptview.h"
#include "premise/premise.h"
#include "../../components/nav/conceptrail.h"
#include <QStackedWidget>
#include <QVBoxLayout>

ConceptView::ConceptView(QWidget *parent)
    : QFrame{parent}
{
    setObjectName("conceptView");
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName("mainLayout");
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    m_rail = new ConceptRail(this);
    mainLayout->addWidget(m_rail);

    QWidget* mainArea = new QWidget(this);
    mainArea->setObjectName(QStringLiteral("mainContentArea"));
    mainArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    
    QVBoxLayout* contentLayout = new QVBoxLayout(mainArea);
    contentLayout->setContentsMargins(0, 0, 0, 0);
    contentLayout->setSpacing(0);
    
    mainLayout->addWidget(mainArea);

    Premise* premisePane = new Premise(mainArea);
    premisePane->setObjectName("premisePane");
    premisePane->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    m_stacked = new QStackedWidget(mainArea);
    m_stacked->addWidget(premisePane);
    contentLayout->addWidget(m_stacked);
    
    connect(m_rail, &ConceptRail::navItemSelect,
            this, &ConceptView::onNavItemSelected);
}

void ConceptView::onNavItemSelected(const QString& section)
{
    // TODO: Switch stacked widget page based on section
    emit viewChanged(m_stacked->currentWidget());
}
