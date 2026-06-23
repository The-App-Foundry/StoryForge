#include "mainwindow.h"
#include "components/sidebar.h"
#include "components/manuscriptpanel.h"
#include "components/scenedata.h"

#include <QButtonGroup>
#include <QFile>
#include <QFrame>
#include <QHBoxLayout>
#include <QLabel>
#include <QMenu>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidgetAction>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // ══════════════════════════════════════════
    // 1. TOP-LEVEL CENTRAL GRID LAYOUT
    //    grid-template-rows: 50px 36px 1fr
    // ══════════════════════════════════════════
    QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    // ══════════════════════════════════════════
    // 2. ROW 1: TOP BAR (50px)
    // ══════════════════════════════════════════
    QWidget* topBarContainer = new QWidget(centralWidget);
    topBarContainer->setObjectName(QStringLiteral("topBarContainer"));
    topBarContainer->setFixedHeight(50);
    topBarContainer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    QHBoxLayout* topBarLayout = new QHBoxLayout(topBarContainer);
    topBarLayout->setContentsMargins(16, 0, 16, 0);
    topBarLayout->setSpacing(18);

    // Brand box
    QWidget* brandBox = new QWidget(topBarContainer);
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

    QFrame* topDivider = new QFrame(topBarContainer);
    topDivider->setObjectName(QStringLiteral("topDivider"));
    topDivider->setFrameShape(QFrame::VLine);
    topDivider->setFrameShadow(QFrame::Plain);
    topDivider->setFixedWidth(1);
    topDivider->setFixedHeight(30);
    topBarLayout->addWidget(topDivider);

    // Story switcher button
    QPushButton* comboStoryMenu = new QPushButton(topBarContainer);
    comboStoryMenu->setObjectName(QStringLiteral("comboStoryMenu"));

    QVBoxLayout* btnTextLayout = new QVBoxLayout(comboStoryMenu);
    btnTextLayout->setContentsMargins(12, 6, 12, 6);
    btnTextLayout->setSpacing(2);

    QLabel* labelTitleText = new QLabel(QStringLiteral("Helion Drift"), comboStoryMenu);
    labelTitleText->setObjectName(QStringLiteral("dropdownTitleText"));
    QLabel* labelGenreText = new QLabel(QStringLiteral("SCI-FI · SPACE HORROR"), comboStoryMenu);
    labelGenreText->setObjectName(QStringLiteral("dropdownGenreText"));
    btnTextLayout->addWidget(labelTitleText);
    btnTextLayout->addWidget(labelGenreText);
    btnTextLayout->setAlignment(Qt::AlignVCenter);

    QMenu* storyDropdownMenu = new QMenu(comboStoryMenu);
    storyDropdownMenu->setObjectName(QStringLiteral("storyDropdownMenu"));

    QWidgetAction* headerAction = new QWidgetAction(storyDropdownMenu);
    QLabel* menuHeaderLabel = new QLabel(QStringLiteral("YOUR STORIES"), storyDropdownMenu);
    menuHeaderLabel->setObjectName(QStringLiteral("menuHeaderLabel"));
    headerAction->setDefaultWidget(menuHeaderLabel);
    storyDropdownMenu->addAction(headerAction);

    // Row 1
    QWidgetAction* story1Action = new QWidgetAction(storyDropdownMenu);
    QWidget* row1Widget = new QWidget(storyDropdownMenu);
    row1Widget->setObjectName(QStringLiteral("menuStoryRow"));
    QHBoxLayout* row1Layout = new QHBoxLayout(row1Widget);
    row1Layout->setContentsMargins(14, 10, 14, 10);
    row1Layout->setSpacing(12);
    QLabel* r1Dot = new QLabel(QStringLiteral(" "), row1Widget);
    r1Dot->setObjectName(QStringLiteral("menuRowDotInactive"));
    r1Dot->setFixedWidth(8);
    QLabel* r1Name = new QLabel(QStringLiteral("Helion Drift"), row1Widget);
    r1Name->setObjectName(QStringLiteral("menuRowNameText"));
    QLabel* r1Meta = new QLabel(QStringLiteral("Sci-Fi · Space Horror"), row1Widget);
    r1Meta->setObjectName(QStringLiteral("menuRowMetaText"));
    r1Meta->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    QLabel* r1Badge = new QLabel(QStringLiteral("FINAL"), row1Widget);
    r1Badge->setObjectName(QStringLiteral("menuRowBadgeFinal"));
    r1Badge->setAlignment(Qt::AlignCenter);
    row1Layout->addWidget(r1Dot);
    row1Layout->addWidget(r1Name);
    row1Layout->addWidget(r1Meta);
    row1Layout->addStretch(1);
    row1Layout->addWidget(r1Badge);
    story1Action->setDefaultWidget(row1Widget);
    storyDropdownMenu->addAction(story1Action);

    // Row 2
    QWidgetAction* story2Action = new QWidgetAction(storyDropdownMenu);
    QWidget* row2Widget = new QWidget(storyDropdownMenu);
    row2Widget->setObjectName(QStringLiteral("menuStoryRowActive"));
    QHBoxLayout* row2Layout = new QHBoxLayout(row2Widget);
    row2Layout->setContentsMargins(14, 10, 14, 10);
    row2Layout->setSpacing(12);
    QFrame* r2Dot = new QFrame(row2Widget);
    r2Dot->setObjectName(QStringLiteral("menuRowDotActive"));
    r2Dot->setFixedSize(7, 7);
    QLabel* r2Name = new QLabel(QStringLiteral("Test"), row2Widget);
    r2Name->setObjectName(QStringLiteral("menuRowNameTextActive"));
    QLabel* r2Meta = new QLabel(QStringLiteral("Science Fiction"), row2Widget);
    r2Meta->setObjectName(QStringLiteral("menuRowMetaText"));
    r2Meta->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    QLabel* r2Badge = new QLabel(QStringLiteral("EDITING"), row2Widget);
    r2Badge->setObjectName(QStringLiteral("menuRowBadgeEditing"));
    r2Badge->setAlignment(Qt::AlignCenter);
    row2Layout->addWidget(r2Dot);
    row2Layout->addWidget(r2Name);
    row2Layout->addWidget(r2Meta);
    row2Layout->addStretch(1);
    row2Layout->addWidget(r2Badge);
    story2Action->setDefaultWidget(row2Widget);
    storyDropdownMenu->addAction(story2Action);

    QFrame* menuSeparator = new QFrame(storyDropdownMenu);
    menuSeparator->setObjectName(QStringLiteral("menuSeparator"));
    menuSeparator->setFrameShape(QFrame::HLine);
    menuSeparator->setFixedHeight(1);
    QWidgetAction* separatorAction = new QWidgetAction(storyDropdownMenu);
    separatorAction->setDefaultWidget(menuSeparator);
    storyDropdownMenu->addAction(separatorAction);

    QWidgetAction* footerAction = new QWidgetAction(storyDropdownMenu);
    QPushButton* btnNewStory = new QPushButton(
        QStringLiteral("+ New story from scratch"), storyDropdownMenu);
    btnNewStory->setObjectName(QStringLiteral("menuNewStoryButton"));
    btnNewStory->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    footerAction->setDefaultWidget(btnNewStory);
    storyDropdownMenu->addAction(footerAction);

    comboStoryMenu->setMenu(storyDropdownMenu);
    topBarLayout->addWidget(comboStoryMenu);
    topBarLayout->addStretch(1);
    mainLayout->addWidget(topBarContainer);

    // ══════════════════════════════════════════
    // 3. ROW 2: STAGE STRIP RAIL (36px)
    // ══════════════════════════════════════════
    QWidget* stageStripRail = new QWidget(centralWidget);
    stageStripRail->setObjectName(QStringLiteral("stageStripRail"));
    stageStripRail->setFixedHeight(36);
    stageStripRail->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    QHBoxLayout* stageStripLayout = new QHBoxLayout(stageStripRail);
    stageStripLayout->setContentsMargins(18, 0, 18, 0);
    stageStripLayout->setSpacing(0);

    QLabel* labelStageTag = new QLabel(QStringLiteral("STAGE"), stageStripRail);
    labelStageTag->setObjectName(QStringLiteral("labelStageTag"));
    stageStripLayout->addWidget(labelStageTag);

    QButtonGroup* stageGroup = new QButtonGroup(this);
    stageGroup->setExclusive(true);

    const QStringList phases = {
        QStringLiteral("CONCEPT"), QStringLiteral("DRAFT"),
        QStringLiteral("EDITING"), QStringLiteral("REVISION"),
        QStringLiteral("FINAL"),   QStringLiteral("PUBLISH")
    };

    for (int i = 0; i < phases.size(); ++i) {
        const QString& phaseName = phases[i];

        QWidget* seg = new QWidget(stageStripRail);
        seg->setObjectName(QStringLiteral("stageSegmentWidget"));
        QHBoxLayout* segLayout = new QHBoxLayout(seg);
        segLayout->setContentsMargins(0, 0, 0, 0);
        segLayout->setSpacing(8);

        QPushButton* btn = new QPushButton(phaseName, seg);
        btn->setObjectName(QStringLiteral("stageButton"));
        btn->setCheckable(true);
        btn->setFixedHeight(28);
        if (phaseName == QLatin1String("CONCEPT"))
            btn->setChecked(true);
        stageGroup->addButton(btn);
        segLayout->addWidget(btn);

        QFrame* dot = new QFrame(seg);
        dot->setObjectName(QStringLiteral("stageIndicatorDot"));
        dot->setFixedSize(5, 5);
        dot->setProperty("activePhase", phaseName == QLatin1String("CONCEPT"));
        segLayout->addWidget(dot);

        if (i < phases.size() - 1) {
            QFrame* line = new QFrame(seg);
            line->setObjectName(QStringLiteral("stageTimelineLine"));
            line->setFrameShape(QFrame::HLine);
            line->setFrameShadow(QFrame::Plain);
            line->setFixedHeight(1);
            line->setFixedWidth(18);
            segLayout->addWidget(line);
        }

        stageStripLayout->addWidget(seg);
    }

    stageStripLayout->addStretch(1);
    mainLayout->addWidget(stageStripRail);

    // ══════════════════════════════════════════
    // 4. MAIN WORKSPACE CANVAS
    // ══════════════════════════════════════════
    QWidget* mainContentArea = new QWidget(centralWidget);
    mainContentArea->setObjectName(QStringLiteral("mainContentArea"));
    mainContentArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QHBoxLayout* contentLayout = new QHBoxLayout(mainContentArea);
    contentLayout->setContentsMargins(0, 0, 0, 0);
    contentLayout->setSpacing(0);

    // SideBar (NavRail + ManuscriptPanel)
    m_sideBar = new SideBar(mainContentArea);
    contentLayout->addWidget(m_sideBar);

    // ── Seed manuscript data ─────────────────────────────────
    // Access ManuscriptPanel through SideBar.
    // SideBar exposes the panel via accessor for data seeding.
    // For now we call it here; in a real app the model layer feeds it.
    {
        QList<ActData> manuscript;

        ActData act1;
        act1.title = QStringLiteral("Act I — The Departure");
        act1.scenes = {
                        { 1, QStringLiteral("Cold Open: The Signal"),  QStringLiteral("Ryland"), 1240, SceneStatus::Final     },
                        { 2, QStringLiteral("The Briefing Room"),       QStringLiteral("Ryland"),  890, SceneStatus::Revised   },
                        { 3, QStringLiteral("Departure Protocol"),      QStringLiteral("Ryland"),    0, SceneStatus::NeedsWork },
                        };

        ActData act2;
        act2.title = QStringLiteral("Act II — The Void");
        act2.scenes = {
                        { 4, QStringLiteral("Waking Up Alone"),          QStringLiteral("Ryland"), 2100, SceneStatus::Drafted    },
                        { 5, QStringLiteral("Rocky"),                    {},                         450, SceneStatus::Drafted    },
                        { 6, QStringLiteral("First Contact Protocol"),   QStringLiteral("Rocky"),     0, SceneStatus::NotStarted },
                        };

        manuscript << act1 << act2;
        m_sideBar->manuscriptPanel()->setManuscript(manuscript);
    }

    // ── Wire scene selection to workspace ────────────────────
    connect(m_sideBar->manuscriptPanel(), &ManuscriptPanel::sceneSelected,
            this, [](int sceneNum) {
                qDebug("MainWindow: open scene %d in editor", sceneNum);
                // TODO: drive editor pane
            });

    // Main content pane (right of sidebar — future editor area)
    QWidget* contentPane = new QWidget(mainContentArea);
    contentPane->setObjectName(QStringLiteral("contentPane"));
    contentPane->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    contentLayout->addWidget(contentPane);

    mainLayout->addWidget(mainContentArea);

    // ══════════════════════════════════════════
    // 5. QSS
    // ══════════════════════════════════════════
    QFile styleFile(QStringLiteral(":/styles.qss"));
    if (styleFile.open(QFile::ReadOnly | QFile::Text)) {
        setStyleSheet(QLatin1String(styleFile.readAll()));
        styleFile.close();
    }
}

MainWindow::~MainWindow() = default;