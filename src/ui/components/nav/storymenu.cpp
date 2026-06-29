#include "storymenu.h"
#include "storymenurow.h"

#include <QLabel>
#include <QVBoxLayout>
#include <QWidgetAction>
#include <QMenu>
#include <QFile>

StoryMenu::StoryMenu(QWidget *parent)
    : QPushButton{parent}
{
    this->setObjectName(QStringLiteral("storyMenu"));

    QVBoxLayout* btnTxtLayout = new QVBoxLayout(this);
    btnTxtLayout->setContentsMargins(12, 6, 12, 6);
    btnTxtLayout->setSpacing(2);
    btnTxtLayout->setAlignment(Qt::AlignVCenter);

    m_currentTitleLbl = new QLabel(QStringLiteral("Helion Drift"), this);
    m_currentTitleLbl->setObjectName(QStringLiteral("dropdownTitleText"));

    m_currentGenreLbl = new QLabel(QStringLiteral("SCI-FI · SPACE HORROR"), this);
    m_currentGenreLbl->setObjectName(QStringLiteral("dropdownGenreText"));

    btnTxtLayout->addWidget(m_currentTitleLbl);
    btnTxtLayout->addWidget(m_currentGenreLbl);

    // 3. Instantiate the dropdown menu
    m_dropdown = new QMenu(this);
    m_dropdown->setObjectName(QStringLiteral("storyDropdownMenu"));

    this->setMenu(m_dropdown);

    QFile styleFile(":/styles/storymenustyles.qss");

    if(styleFile.open(QFile::ReadOnly | QFile::Text)) {
        QString styleSheet = QLatin1String(styleFile.readAll());
        this->setStyleSheet(styleSheet);
        styleFile.close();
    }
}

void StoryMenu::populateStories(const QList<StoryData>& stories)
{
    m_dropdown->clear(); // Clear old actions and nested widgets instantly!

    // Add static Header Action
    QWidgetAction* headerAction = new QWidgetAction(m_dropdown);
    QLabel* menuHeaderLabel = new QLabel(QStringLiteral("YOUR STORIES"), m_dropdown);
    menuHeaderLabel->setObjectName(QStringLiteral("menuHeaderLabel"));
    headerAction->setDefaultWidget(menuHeaderLabel);
    m_dropdown->addAction(headerAction);

    // Populate dynamic rows using your StoryMenuRow QWidget class
    for (const auto& story : stories) {
        QWidgetAction* storyAction = new QWidgetAction(m_dropdown);

        // Pass parent down to the row widget
        StoryMenuRow* rowWidget = new StoryMenuRow(m_dropdown);
        rowWidget->setStoryData(story.name, story.meta, story.badge, story.isActive);

        storyAction->setDefaultWidget(rowWidget);
        m_dropdown->addAction(storyAction);
    }

    // Add Separator Line
    QFrame* menuSeparator = new QFrame(m_dropdown);
    menuSeparator->setObjectName(QStringLiteral("menuSeparator"));
    menuSeparator->setFrameShape(QFrame::HLine);
    menuSeparator->setFixedHeight(1);

    QWidgetAction* separatorAction = new QWidgetAction(m_dropdown);
    separatorAction->setDefaultWidget(menuSeparator);
    m_dropdown->addAction(separatorAction);

    // Add Footer Button
    QWidgetAction* footerAction = new QWidgetAction(m_dropdown);
    QPushButton* btnNewStory = new QPushButton(QStringLiteral("+ New story from scratch"), m_dropdown);
    btnNewStory->setObjectName(QStringLiteral("menuNewStoryButton"));
    btnNewStory->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    footerAction->setDefaultWidget(btnNewStory);
    m_dropdown->addAction(footerAction);
}

void StoryMenu::addStoryToMenu(const QString& name, const QString& meta)
{
    QWidgetAction* storyAction = new QWidgetAction(m_dropdown);
    StoryMenuRow* rowWidget = new StoryMenuRow(m_dropdown);
    rowWidget->setStoryData(name, meta, "CONCEPT");

    storyAction->setDefaultWidget(rowWidget);
    m_dropdown->addAction(storyAction);
}