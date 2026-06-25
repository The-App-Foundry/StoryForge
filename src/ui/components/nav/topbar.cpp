#include "topbar.h"
#include "storymenu.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QFile>

TopBar::TopBar(QWidget *parent)
    : QFrame{parent}
{
    setFixedHeight(50);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    setObjectName(QStringLiteral("topBarContainer"));

    QHBoxLayout* topBarLayout = new QHBoxLayout(this);
    topBarLayout->setContentsMargins(16, 0, 16, 0);
    topBarLayout->setSpacing(18);

    // Brand box
    QWidget* brandBox = new QWidget(this);
    QHBoxLayout* brandLayout = new QHBoxLayout(brandBox);
    brandLayout->setContentsMargins(0, 0, 0, 0);
    brandLayout->setSpacing(11);

    QFrame* logoFrame = new QFrame(brandBox);
    logoFrame->setObjectName(QStringLiteral("logoFrame"));
    logoFrame->setFixedSize(26, 26);
    brandLayout->addWidget(logoFrame);

    QLabel* labelAppTitle = new QLabel(QStringLiteral("STORY FORGE"), brandBox);
    labelAppTitle->setObjectName(QStringLiteral("labelAppTitle"));
    brandLayout->addWidget(labelAppTitle);
    topBarLayout->addWidget(brandBox);

    QFrame* topDivider = new QFrame(this);
    topDivider->setObjectName(QStringLiteral("topDivider"));
    topDivider->setFrameShape(QFrame::VLine);
    topDivider->setFrameShadow(QFrame::Plain);
    topDivider->setFixedWidth(1);
    topDivider->setFixedHeight(30);
    topBarLayout->addWidget(topDivider);

    StoryMenu* storyMenu = new StoryMenu(this);
    topBarLayout->addWidget(storyMenu);

    topBarLayout->addStretch(1);

    QFile styleFile(":/topbarstyles.qss");

    if(styleFile.open(QFile::ReadOnly | QFile::Text)) {
        QString styleSheet = QLatin1String(styleFile.readAll());
        this->setStyleSheet(styleSheet);
        styleFile.close();
    }
}
