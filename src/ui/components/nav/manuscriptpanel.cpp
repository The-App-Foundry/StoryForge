#include "manuscriptpanel.h"
#include "actsectionheader.h"
#include <QFrame>
#include <QHBoxLayout>
#include <QFile>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QLineEdit>
#include <QStackedWidget>

struct SectionMeta {
    const char* name;       // as emitted by NavRail
    int         stackPage;  // index into m_stack
};

static constexpr SectionMeta kSections[] = {
    { "DRAFT",  0 },
    { "CAST",   1 },
    { "SCENES", 2 },
    { "PLACES", 3 },
    { "PROPS",  4 },
    { "NOTES",  5 },
    };

// ── Construction ────────────────────────────────────────────────────────────

ManuscriptPanel::ManuscriptPanel(QWidget* parent)
    : QFrame(parent)
{
    setObjectName(QStringLiteral("manuscriptPanel"));
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);

    setFixedWidth(287);

    QVBoxLayout* rootLay = new QVBoxLayout(this);
    rootLay->setContentsMargins(10, 0, 10, 0);
    rootLay->setSpacing(0);

    // ── Panel header bar ────────────────────────────────────
    QWidget* panelHeader = new QWidget(this);
    panelHeader->setObjectName(QStringLiteral("manuscriptPanelHeader"));
    panelHeader->setFixedHeight(40);

    QHBoxLayout* headerLay = new QHBoxLayout(panelHeader);
    headerLay->setContentsMargins(14, 0, 14, 0);
    headerLay->setSpacing(0);

    m_labelPanelTitle = new QLabel(QStringLiteral("MANUSCRIPT"), panelHeader);
    m_labelPanelTitle->setObjectName(QStringLiteral("manuscriptPanelTitle"));

    m_labelCount = new QLabel(QStringLiteral("0"), panelHeader);
    m_labelCount->setObjectName(QStringLiteral("manuscriptSceneCount"));
    m_labelCount->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

    headerLay->addWidget(m_labelPanelTitle);
    headerLay->addStretch(1);
    headerLay->addWidget(m_labelCount);

    rootLay->addWidget(panelHeader);

    // Separator
    QFrame* sep = new QFrame(this);
    sep->setObjectName(QStringLiteral("manuscriptPanelSep"));
    sep->setFrameShape(QFrame::HLine);
    sep->setFrameShadow(QFrame::Plain);
    sep->setFixedHeight(1);
    rootLay->addWidget(sep);

    // ── Filter bar ──────────────────────────────────────────
    QWidget* filterBar = new QWidget(this);
    filterBar->setObjectName(QStringLiteral("manuscriptFilterBar"));

    QHBoxLayout* filterLay = new QHBoxLayout(filterBar);
    filterLay->setContentsMargins(10, 6, 10, 6);
    filterLay->setSpacing(0);

    m_filterEdit = new QLineEdit(filterBar);
    m_filterEdit->setObjectName(QStringLiteral("manuscriptFilterEdit"));
    m_filterEdit->setPlaceholderText(QStringLiteral("Filter..."));
    m_filterEdit->setClearButtonEnabled(true);
    filterLay->addWidget(m_filterEdit);

    rootLay->addWidget(filterBar);

    // ── Filter chips row ────────────────────────────────────
    QWidget* chipsBar = new QWidget(this);
    chipsBar->setObjectName(QStringLiteral("manuscriptChipsBar"));

    QHBoxLayout* chipsLay = new QHBoxLayout(chipsBar);
    chipsLay->setContentsMargins(10, 0, 10, 8);
    chipsLay->setSpacing(6);

    m_btnAll = new QPushButton(QStringLiteral("ALL"), chipsBar);
    m_btnAll->setObjectName(QStringLiteral("manuscriptBtnAll"));
    m_btnAll->setCursor(Qt::PointingHandCursor);
    m_btnAll->setCheckable(true);
    m_btnAll->setChecked(true);
    chipsLay->addWidget(m_btnAll);
    chipsLay->addStretch(1);

    rootLay->addWidget(chipsBar);

    // ── Stacked widget ──────────────────────────────────────
    m_stack = new QStackedWidget(this);
    m_stack->setObjectName(QStringLiteral("manuscriptStack"));
    rootLay->addWidget(m_stack, 1);

    buildDraftPage();  // page index 0

    // Placeholder pages for future sections (pages 1–5)
    const QStringList placeholders = { "CAST", "SCENES", "PLACES", "PROPS", "NOTES" };
    for (const QString& name : placeholders) {
        QWidget* placeholder = new QWidget(m_stack);
        placeholder->setObjectName(QStringLiteral("manuscriptPlaceholder"));
        QVBoxLayout* pl = new QVBoxLayout(placeholder);
        QLabel* lbl = new QLabel(name + QStringLiteral(" — coming soon"), placeholder);
        lbl->setObjectName(QStringLiteral("manuscriptPlaceholderLabel"));
        lbl->setAlignment(Qt::AlignCenter);
        pl->addWidget(lbl);
        m_stack->addWidget(placeholder);
    }

    // DRAFT page is default
    m_stack->setCurrentIndex(kPageDraft);

    QFile styleFile(":/manuscriptpanelstyles.qss");

    if(styleFile.open(QFile::ReadOnly | QFile::Text)) {
        QString styleSheet = QLatin1String(styleFile.readAll());
        this->setStyleSheet(styleSheet);
        styleFile.close();
    }
}

// ── Public ──────────────────────────────────────────────────────────────────

void ManuscriptPanel::setManuscript(const QList<ActData>& acts)
{
    m_acts = acts;
    buildActWidgets();

    int total = 0;
    for (const ActData& a : std::as_const(m_acts))
        total += static_cast<int>(a.scenes.size());

    m_labelCount->setText(QString::number(total));
}

void ManuscriptPanel::showSection(const QString& section)
{
    for (const SectionMeta& meta : kSections) {
        if (section == QLatin1String(meta.name)) {
            m_stack->setCurrentIndex(meta.stackPage);

            // Title is always "MANUSCRIPT" — count only meaningful for DRAFT
            m_labelCount->setVisible(meta.stackPage == kPageDraft);
            return;
        }
    }

    qWarning("ManuscriptPanel::showSection — unknown section '%s'",
             qPrintable(section));
}

// ── Private ─────────────────────────────────────────────────────────────────

void ManuscriptPanel::buildDraftPage()
{
    QWidget* draftPage = new QWidget(m_stack);
    draftPage->setObjectName(QStringLiteral("manuscriptDraftPage"));

    QVBoxLayout* pageLay = new QVBoxLayout(draftPage);
    pageLay->setContentsMargins(0, 0, 0, 0);
    pageLay->setSpacing(0);

    m_scrollArea = new QScrollArea(draftPage);
    m_scrollArea->setObjectName(QStringLiteral("manuscriptScrollArea"));
    m_scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    m_scrollArea->setWidgetResizable(true);
    m_scrollArea->setFrameShape(QFrame::NoFrame);

    m_scrollContent = new QWidget();
    m_scrollContent->setObjectName(QStringLiteral("manuscriptScrollContent"));

    m_scrollContent->setFixedWidth(267);

    m_contentLayout = new QVBoxLayout(m_scrollContent);
    m_contentLayout->setContentsMargins(6, 4, 15, 16);
    m_contentLayout->setSpacing(0);

    m_btnNewAct = new QPushButton(QStringLiteral("+ NEW ACT"), m_scrollContent);
    m_btnNewAct->setObjectName(QStringLiteral("manuscriptBtnNewAct"));
    m_btnNewAct->setCursor(Qt::PointingHandCursor);
    m_btnNewAct->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    connect(m_btnNewAct, &QPushButton::clicked, this, [this]() {});

    m_contentLayout->addWidget(m_btnNewAct);
    m_contentLayout->addStretch(1);  // trailing stretch — acts insert before this

    m_scrollArea->setWidget(m_scrollContent);
    pageLay->addWidget(m_scrollArea, 1);

    m_stack->addWidget(draftPage);   // becomes index 0


}

void ManuscriptPanel::buildActWidgets()
{
    clearActWidgets();

    for (const ActData& act : std::as_const(m_acts)) {
        auto* header = new ActSectionHeader(act, m_scrollContent);
        connect(header, &ActSectionHeader::sceneClicked,
                this,   &ManuscriptPanel::sceneSelected);

        // Insert before trailing stretch to preserve bottom padding
        const int insertPos = m_contentLayout->count() - 2;
        m_contentLayout->insertWidget(insertPos, header);
        m_actHeaders.append(header);
    }
}

void ManuscriptPanel::clearActWidgets()
{
    // Synchronous delete — GUI thread, no async context.
    // removeWidget() detaches from layout; delete destroys the QObject
    // and all its children (SceneRow instances) in one pass.
    for (ActSectionHeader* h : std::as_const(m_actHeaders)) {
        m_contentLayout->removeWidget(h);
        delete h;
    }
    m_actHeaders.clear();
}