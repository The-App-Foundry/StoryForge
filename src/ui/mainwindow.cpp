#include "mainwindow.h"
#include "components/nav/sidebar.h"
#include "components/nav/topbar.h"
#include "components/nav/manuscriptpanel.h"
#include "components/nav/scenedata.h"
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