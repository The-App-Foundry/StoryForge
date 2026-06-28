#include "mainwindow.h"
#include "components/nav/topbar.h"
#include "views/concept/conceptview.h"
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

    QWidget* contentPane = new QWidget(mainContentArea);
    contentPane->setObjectName(QStringLiteral("contentPane"));
    contentPane->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    contentLayout->addWidget(contentPane);
    mainLayout->addWidget(mainContentArea);

    QVBoxLayout* contentPaneLayout = new QVBoxLayout(contentPane);
    contentPaneLayout->setContentsMargins(0, 0, 0, 0);
    contentPaneLayout->setSpacing(0);

    ConceptView* conceptView = new ConceptView(contentPane);
    contentPaneLayout->addWidget(conceptView);

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