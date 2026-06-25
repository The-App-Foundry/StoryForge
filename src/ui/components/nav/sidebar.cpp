#include "sidebar.h"
#include "navrail.h"
#include "manuscriptpanel.h"
#include <QHBoxLayout>

SideBar::SideBar(QWidget *parent)
    : QWidget{parent}
{
    setObjectName("sideBar");

    auto* layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    m_navRail = new NavRail(this);
    m_manuscriptPanel = new ManuscriptPanel(this);

    layout->addWidget(m_navRail);
    layout->addWidget(m_manuscriptPanel);

    connect(m_navRail, &NavRail::navItemSelected,
            m_manuscriptPanel, &ManuscriptPanel::showSection);
}
