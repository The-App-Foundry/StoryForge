#include "mainwindow.h"
#include "components/sidebar.h"
#include "components/topbar.h"
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

    TopBar* topBar = new TopBar(centralWidget);
    mainLayout->addWidget(topBar);

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
    SideBar* sideBar = new SideBar(mainContentArea);
    contentLayout->addWidget(sideBar);

    // ── Seed manuscript data ─────────────────────────────────
    // Access ManuscriptPanel through SideBar.
    // SideBar exposes the panel via accessor for data seeding.
    // For now we call it here; in a real app the model layer feeds it.
    {
        QList<ActData> manuscript;

        ActData act1;
        act1.title = QStringLiteral("Act I — The Departure");
        act1.scenes = {
                        { 1, QStringLiteral("Cold Open: The Signal Awakens"),  QStringLiteral("Ryland"), 1240, SceneStatus::Final     },
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
        sideBar->manuscriptPanel()->setManuscript(manuscript);
    }

    // ── Wire scene selection to workspace ────────────────────
    connect(sideBar->manuscriptPanel(), &ManuscriptPanel::sceneSelected,
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