#include "actsectionheader.h"

#include <QHBoxLayout>
#include <QMouseEvent>
#include <QStyle>
#include <QVBoxLayout>
#include <QPushButton>

static void setLabelTextFitting(QLabel* label, const QString& text, int maxWidth) {
    QFont font = label->font();
    QFontMetrics fm(font);
    QString optimizedText = text;

    // If the text is too wide for our panel allotment, dial back the font size
    int currentWidth = fm.horizontalAdvance(text);
    while (currentWidth > maxWidth && font.pointSize() > 7) { // Don't go smaller than 7pt
        font.setPointSize(font.pointSize() - 1);
        fm = QFontMetrics(font);
        currentWidth = fm.horizontalAdvance(text);
    }

    label->setFont(font);
    label->setText(optimizedText);
}

ActSectionHeader::ActSectionHeader(const ActData& act, QWidget* parent)
    : QFrame(parent)
    , m_act(act)
{
    setObjectName(QStringLiteral("actSectionHeader"));
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    QVBoxLayout* rootLay = new QVBoxLayout(this);
    rootLay->setContentsMargins(0, 0, 0, 0);
    rootLay->setSpacing(0);

    // ── Header row ──────────────────────────────────────────
    m_headerRow = new QWidget(this);
    m_headerRow->setObjectName(QStringLiteral("actHeaderRow"));
    m_headerRow->setFixedHeight(32);
    m_headerRow->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    m_headerRow->setCursor(Qt::PointingHandCursor);

    QHBoxLayout* headerLay = new QHBoxLayout(m_headerRow);
    headerLay->setContentsMargins(12, 0, 14, 0);
    headerLay->setSpacing(8);

    m_labelChevron = new QLabel(m_headerRow);
    m_labelChevron->setObjectName(QStringLiteral("actChevron"));
    m_labelChevron->setFixedWidth(6);
    headerLay->addWidget(m_labelChevron);

    m_labelTitle = new QLabel(m_headerRow);
    m_labelTitle->setObjectName(QStringLiteral("actTitle"));
    m_labelTitle->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    headerLay->addWidget(m_labelTitle);

    headerLay->addStretch(1);

    QPushButton* addSceneBtn = new QPushButton(QStringLiteral("Add scene"), m_headerRow);
    addSceneBtn->setObjectName("addSceneBtn");
    addSceneBtn->setFixedHeight(20);
    addSceneBtn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    headerLay->addWidget(addSceneBtn);

    headerLay->addSpacing(0);

    m_labelSceneCount = new QLabel(m_headerRow);
    m_labelSceneCount->setObjectName(QStringLiteral("actSceneCount"));
    headerLay->addWidget(m_labelSceneCount);

    rootLay->addWidget(m_headerRow);

    // ── Scenes container ────────────────────────────────────
    // SceneRow widgets are children of this container.
    // setVisible(false) hides all children at once — no individual loop needed.
    m_scenesContainer = new QWidget(this);
    m_scenesContainer->setObjectName(QStringLiteral("actScenesContainer"));
    m_scenesContainer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    QVBoxLayout* scenesLay = new QVBoxLayout(m_scenesContainer);
    scenesLay->setContentsMargins(0, 0, 0, 0);
    scenesLay->setSpacing(0);

    rootLay->addWidget(m_scenesContainer);

    setActData(act);
}

// ── Public ─────────────────────────────────────────────────────────────────

void ActSectionHeader::setExpanded(bool expanded)
{
    if (m_expanded == expanded)
        return;
    m_expanded = expanded;
    m_scenesContainer->setVisible(m_expanded);
    updateChevron();
    emit expandedChanged(m_expanded);
}

void ActSectionHeader::setActData(const ActData& act)
{
    m_act = act;

    // Target width calculation: Panel is 287px total.
    // Subtract your margins, chevron width, add button, and scene count.
    // ~120px to 140px is a safe maximum boundary for the title text field.
    int maxTitleWidth = 130;

    // Use our new fitting function instead of raw setText
    setLabelTextFitting(m_labelTitle, act.title.toUpper(), maxTitleWidth);

    m_labelSceneCount->setText(
        QString::number(act.scenes.size()) +
        QLatin1String(act.scenes.size() == 1 ? " scene" : " scenes")
    );

    buildSceneRows();
    updateChevron();
}

// ── Private ────────────────────────────────────────────────────────────────

void ActSectionHeader::buildSceneRows()
{
    clearSceneRows();

    auto* lay = qobject_cast<QVBoxLayout*>(m_scenesContainer->layout());
    Q_ASSERT(lay);

    for (const SceneData& scene : std::as_const(m_act.scenes)) {
        auto* row = new SceneRow(scene, m_scenesContainer);
        connect(row, &SceneRow::clicked, this, &ActSectionHeader::sceneClicked);
        lay->addWidget(row);
        m_sceneRows.append(row);
    }
}

void ActSectionHeader::clearSceneRows()
{
    // Synchronous delete — we are on the GUI thread, no async context.
    // removeWidget() + delete is safe here. deleteLater() would be
    // appropriate only if called from a non-GUI thread or signal handler
    // where immediate destruction could re-enter the event loop.
    for (SceneRow* row : std::as_const(m_sceneRows)) {
        m_scenesContainer->layout()->removeWidget(row);
        delete row;
    }
    m_sceneRows.clear();
}

void ActSectionHeader::updateChevron()
{
    m_labelChevron->setText(m_expanded ? QStringLiteral("▼") : QStringLiteral("▶"));
}

void ActSectionHeader::setHeaderHovered(bool hovered)
{
    m_headerRow->setProperty("hovered", hovered);
    m_headerRow->style()->unpolish(m_headerRow);
    m_headerRow->style()->polish(m_headerRow);
}

// ── Events ─────────────────────────────────────────────────────────────────
// NOTE: mousePressEvent lives on the outer ActSectionHeader widget.
// Header row click = toggle expand. Scene row clicks are handled by
// SceneRow itself and bubble up via sceneClicked() signal.

void ActSectionHeader::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
        setExpanded(!m_expanded);
    QWidget::mousePressEvent(event);
}

void ActSectionHeader::enterEvent(QEnterEvent* event)
{
    setHeaderHovered(true);
    QWidget::enterEvent(event);
}

void ActSectionHeader::leaveEvent(QEvent* event)
{
    setHeaderHovered(false);
    QWidget::leaveEvent(event);
}