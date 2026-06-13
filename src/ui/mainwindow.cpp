#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QFile>
#include <QFrame>
#include <QPushButton>
#include <QButtonGroup>
#include <QMenu>
#include <QWidgetAction>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget* centralWidget = new QWidget(this);
    this->setCentralWidget(centralWidget);

    // ==========================================
    // 1. TOP-LEVEL CENTRAL GRID LAYOUT
    // ==========================================
    // Replicates grid-template-rows: 50px 36px minmax(0,1fr) from your HTML prototype
    QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    // ==========================================
    // 2. ROW 1: TOP BAR CONTAINER (50px)
    // ==========================================
    QWidget* topBarContainer = new QWidget(centralWidget);
    topBarContainer->setObjectName("topBarContainer");
    topBarContainer->setFixedHeight(50);
    topBarContainer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    QHBoxLayout* topBarLayout = new QHBoxLayout(topBarContainer);
    topBarLayout->setContentsMargins(16, 0, 16, 0);
    topBarLayout->setSpacing(18);

    // Brand Label Box
    QWidget* brandBox = new QWidget(topBarContainer);
    QHBoxLayout* brandLayout = new QHBoxLayout(brandBox);
    brandLayout->setContentsMargins(0, 0, 0, 0);
    brandLayout->setSpacing(11);

    // Logo Emblem Box
    QFrame* logoFrame = new QFrame(brandBox);
    logoFrame->setObjectName("logoFrame");
    logoFrame->setFixedSize(26, 26);
    brandLayout->addWidget(logoFrame);

    QLabel* labelAppTitle = new QLabel("THE FOUNDRY / STORY FORGE", brandBox);
    labelAppTitle->setObjectName("labelAppTitle");
    brandLayout->addWidget(labelAppTitle);
    topBarLayout->addWidget(brandBox);

    // Vertical Divider Line
    QFrame* topDivider = new QFrame(topBarContainer);
    topDivider->setObjectName("topDivider");
    topDivider->setFrameShape(QFrame::VLine);
    topDivider->setFrameShadow(QFrame::Plain);
    topDivider->setFixedWidth(1);
    topDivider->setFixedHeight(30);
    topBarLayout->addWidget(topDivider);

    // ==========================================
    // CUSTOM STORY SWITCHER HEADER LINK BUTTON
    // ==========================================
    QPushButton* comboStoryMenu = new QPushButton(topBarContainer);
    comboStoryMenu->setObjectName("comboStoryMenu");

    QVBoxLayout* btnTextLayout = new QVBoxLayout(comboStoryMenu);
    btnTextLayout->setContentsMargins(12, 6, 12, 6);
    btnTextLayout->setSpacing(2);

    QLabel* labelTitleText = new QLabel("Helion Drift", comboStoryMenu);
    labelTitleText->setObjectName("dropdownTitleText");

    QLabel* labelGenreText = new QLabel("SCI-FI · SPACE HORROR", comboStoryMenu);
    labelGenreText->setObjectName("dropdownGenreText");

    btnTextLayout->addWidget(labelTitleText);
    btnTextLayout->addWidget(labelGenreText);

    btnTextLayout->setAlignment(Qt::AlignVCenter);

    // Attach specialized pop-up menu drawer overlay
    QMenu* storyDropdownMenu = new QMenu(comboStoryMenu);
    storyDropdownMenu->setObjectName("storyDropdownMenu");

    // --- POP-UP SECTION 1: HEADER TEXT LABEL ---
    QWidgetAction* headerAction = new QWidgetAction(storyDropdownMenu);
    QLabel* menuHeaderLabel = new QLabel("YOUR STORIES", storyDropdownMenu);
    menuHeaderLabel->setObjectName("menuHeaderLabel");
    headerAction->setDefaultWidget(menuHeaderLabel);
    storyDropdownMenu->addAction(headerAction);

    // --- POP-UP SECTION 2: DYNAMIC STORY LIST ENTRIES ---
    // Story Row Entry 1: Helion Drift (Passive State Row)
    QWidgetAction* story1Action = new QWidgetAction(storyDropdownMenu);
    QWidget* row1Widget = new QWidget(storyDropdownMenu);
    row1Widget->setObjectName("menuStoryRow");

    QHBoxLayout* row1Layout = new QHBoxLayout(row1Widget);
    row1Layout->setContentsMargins(14, 10, 14, 10);
    row1Layout->setSpacing(12); // Slightly wider tracking between variables

    QLabel* r1Dot = new QLabel(" ", row1Widget);
    r1Dot->setObjectName("menuRowDotInactive");
    r1Dot->setFixedWidth(8);

    QLabel* r1Name = new QLabel("Helion Drift", row1Widget);
    r1Name->setObjectName("menuRowNameText");

    QLabel* r1Meta = new QLabel("Sci-Fi · Space Horror", row1Widget);
    r1Meta->setObjectName("menuRowMetaText");
    // STRETCH FIX: Tell the layout engine to let the genre text expand horizontally to prevent clamping
    r1Meta->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    QLabel* r1Badge = new QLabel("FINAL", row1Widget);
    r1Badge->setObjectName("menuRowBadgeFinal");
    r1Badge->setAlignment(Qt::AlignCenter);

    row1Layout->addWidget(r1Dot);
    row1Layout->addWidget(r1Name);
    row1Layout->addWidget(r1Meta);
    row1Layout->addStretch(1); // Flex spacer to actively isolate the badge to the right edge
    row1Layout->addWidget(r1Badge);
    story1Action->setDefaultWidget(row1Widget);
    storyDropdownMenu->addAction(story1Action);

    // Story Row Entry 2: Test (Active/Selected State Match)
    QWidgetAction* story2Action = new QWidgetAction(storyDropdownMenu);
    QWidget* row2Widget = new QWidget(storyDropdownMenu);
    row2Widget->setObjectName("menuStoryRowActive");

    QHBoxLayout* row2Layout = new QHBoxLayout(row2Widget);
    row2Layout->setContentsMargins(14, 10, 14, 10);
    row2Layout->setSpacing(12);

    QFrame* r2Dot = new QFrame(row2Widget);
    r2Dot->setObjectName("menuRowDotActive");
    r2Dot->setFixedSize(7, 7);

    QLabel* r2Name = new QLabel("Test", row2Widget);
    r2Name->setObjectName("menuRowNameTextActive");

    QLabel* r2Meta = new QLabel("Science Fiction", row2Widget);
    r2Meta->setObjectName("menuRowMetaText");
    // STRETCH FIX: Prevent clipping by expanding the tracking envelope
    r2Meta->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    QLabel* r2Badge = new QLabel("EDITING", row2Widget);
    r2Badge->setObjectName("menuRowBadgeEditing");
    r2Badge->setAlignment(Qt::AlignCenter);

    row2Layout->addWidget(r2Dot);
    row2Layout->addWidget(r2Name);
    row2Layout->addWidget(r2Meta);
    row2Layout->addStretch(1); // Flex spacer
    row2Layout->addWidget(r2Badge);
    story2Action->setDefaultWidget(row2Widget);
    storyDropdownMenu->addAction(story2Action);

    // --- POP-UP SECTION 3: REACTIONARY INTERACTION SEPARATOR ---
    QFrame* menuSeparator = new QFrame(storyDropdownMenu);
    menuSeparator->setObjectName("menuSeparator");
    menuSeparator->setFrameShape(QFrame::HLine);
    menuSeparator->setFixedHeight(1);
    QWidgetAction* separatorAction = new QWidgetAction(storyDropdownMenu);
    separatorAction->setDefaultWidget(menuSeparator);
    storyDropdownMenu->addAction(separatorAction);

    // --- POP-UP SECTION 4: STYLED HOVER ACTION FOOTER BUTTON ---
    QWidgetAction* footerAction = new QWidgetAction(storyDropdownMenu);
    QPushButton* btnNewStory = new QPushButton("+ New story from scratch", storyDropdownMenu);
    btnNewStory->setObjectName("menuNewStoryButton");
    btnNewStory->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    footerAction->setDefaultWidget(btnNewStory);
    storyDropdownMenu->addAction(footerAction);

    comboStoryMenu->setMenu(storyDropdownMenu);
    topBarLayout->addWidget(comboStoryMenu);

    topBarLayout->addStretch(1);
    mainLayout->addWidget(topBarContainer);

    // ==========================================
    // 3. ROW 2: STAGE STRIP RAIL (36px)
    // ==========================================
    QWidget* stageStripRail = new QWidget(centralWidget);
    stageStripRail->setObjectName("stageStripRail");
    stageStripRail->setFixedHeight(36);
    stageStripRail->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    QHBoxLayout* stageStripLayout = new QHBoxLayout(stageStripRail);
    stageStripLayout->setContentsMargins(18, 0, 18, 0);
    stageStripLayout->setSpacing(0);

    QLabel* labelStageTag = new QLabel("STAGE", stageStripRail);
    labelStageTag->setObjectName("labelStageTag");
    stageStripLayout->addWidget(labelStageTag);

    QButtonGroup* stageGroup = new QButtonGroup(this);
    stageGroup->setExclusive(true);

    QStringList phases = {"CONCEPT", "DRAFT", "EDITING", "REVISION", "FINAL", "PUBLISH"};
    for (int i = 0; i < phases.size(); ++i) {
        QString phaseName = phases[i];

        QWidget* stageSegmentWidget = new QWidget(stageStripRail);
        stageSegmentWidget->setObjectName("stageSegmentWidget");
        QHBoxLayout* segmentLayout = new QHBoxLayout(stageSegmentWidget);
        segmentLayout->setContentsMargins(0, 0, 0, 0);
        segmentLayout->setSpacing(8);

        QPushButton* btn = new QPushButton(phaseName, stageSegmentWidget);
        btn->setObjectName("stageButton");
        btn->setCheckable(true);
        btn->setFixedHeight(28);

        if (phaseName == "CONCEPT") {
            btn->setChecked(true);
        }
        stageGroup->addButton(btn);
        segmentLayout->addWidget(btn);

        QFrame* stageIndicatorDot = new QFrame(stageSegmentWidget);
        stageIndicatorDot->setObjectName("stageIndicatorDot");
        stageIndicatorDot->setFixedSize(5, 5);
        stageIndicatorDot->setProperty("activePhase", phaseName == "CONCEPT");
        segmentLayout->addWidget(stageIndicatorDot);

        if (i < phases.size() - 1) {
            QFrame* stageTimelineLine = new QFrame(stageSegmentWidget);
            stageTimelineLine->setObjectName("stageTimelineLine");
            stageTimelineLine->setFrameShape(QFrame::HLine);
            stageTimelineLine->setFrameShadow(QFrame::Plain);
            stageTimelineLine->setFixedHeight(1);
            stageTimelineLine->setFixedWidth(18);
            segmentLayout->addWidget(stageTimelineLine);
        }

        stageStripLayout->addWidget(stageSegmentWidget);
    }

    stageStripLayout->addStretch(1);
    mainLayout->addWidget(stageStripRail);

    // ==========================================
    // 4. MAIN WORKSPACE CANVAS HOUSING AREA
    // ==========================================
    QWidget* mainContentArea = new QWidget(centralWidget);
    mainContentArea->setObjectName("mainContentArea");
    mainContentArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    mainLayout->addWidget(mainContentArea);

    // ==========================================
    // 5. QSS
    // ==========================================
    QFile styleFile(":/styles.qss");

    if(styleFile.open(QFile::ReadOnly | QFile::Text)) {
        QString styleSheet = QLatin1String(styleFile.readAll());
        this->setStyleSheet(styleSheet);
        styleFile.close();
    }
}

MainWindow::~MainWindow()
{
}