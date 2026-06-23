#include "scenerow.h"

#include <QHBoxLayout>
#include <QMouseEvent>
#include <QPainter>
#include <QStyle>

static constexpr int kRowHeight  = 36;
static constexpr int kDotSize    = 7;
static constexpr int kDotLeft    = 14;  // px from widget left edge

SceneRow::SceneRow(const SceneData& data, QWidget* parent)
    : QWidget(parent)
    , m_data(data)
{
    setObjectName(QStringLiteral("sceneRow"));
    setFixedHeight(kRowHeight);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    setCursor(Qt::PointingHandCursor);

    // Left margin = dot slot width so labels never overlap the painted dot
    const int dotSlotWidth = kDotLeft + kDotSize + 10;

    QHBoxLayout* lay = new QHBoxLayout(this);
    lay->setContentsMargins(dotSlotWidth, 0, 14, 0);
    lay->setSpacing(0);

    m_labelNumber = new QLabel(this);
    m_labelNumber->setObjectName(QStringLiteral("sceneRowNumber"));
    m_labelNumber->setFixedWidth(26);
    lay->addWidget(m_labelNumber);

    lay->addSpacing(8);

    m_labelTitle = new QLabel(this);
    m_labelTitle->setObjectName(QStringLiteral("sceneRowTitle"));
    m_labelTitle->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    lay->addWidget(m_labelTitle);

    lay->addSpacing(12);

    m_labelPov = new QLabel(this);
    m_labelPov->setObjectName(QStringLiteral("sceneRowPov"));
    m_labelPov->setFixedWidth(80);
    m_labelPov->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    lay->addWidget(m_labelPov);

    lay->addSpacing(12);

    m_labelWordCount = new QLabel(this);
    m_labelWordCount->setObjectName(QStringLiteral("sceneRowWordCount"));
    m_labelWordCount->setFixedWidth(52);
    m_labelWordCount->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    lay->addWidget(m_labelWordCount);

    applyData();
}

void SceneRow::setData(const SceneData& data)
{
    m_data = data;
    applyData();
}

// ── Private ────────────────────────────────────────────────────────────────

void SceneRow::applyData()
{
    m_labelNumber->setText(
        QString::number(m_data.number).rightJustified(2, QLatin1Char('0')));

    // Elide title to fit available label width (falls back to full string
    // when the widget hasn't been laid out yet — resizeEvent will correct it).
    const int availW = m_labelTitle->width() > 0 ? m_labelTitle->width() : 200;
    const QString elided = m_labelTitle->fontMetrics()
                               .elidedText(m_data.title, Qt::ElideRight, availW);
    m_labelTitle->setText(elided);
    m_labelPov->setText(
        m_data.povCharacter.isEmpty() ? QStringLiteral("—") : m_data.povCharacter);
    m_labelWordCount->setText(
        m_data.wordCount > 0
            ? QStringLiteral("%1w").arg(m_data.wordCount)
            : QStringLiteral("—"));
    update();
}

void SceneRow::setHovered(bool hovered)
{
    if (m_hovered == hovered)
        return;
    m_hovered = hovered;
    // Dynamic property triggers the QSS [hovered="true"] selector.
    // Must unpolish/polish so the style engine re-evaluates the property.
    setProperty("hovered", hovered);
    style()->unpolish(this);
    style()->polish(this);
    update();
}

// ── Events ─────────────────────────────────────────────────────────────────

void SceneRow::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
        emit clicked(m_data.number);
    QWidget::mousePressEvent(event);
}

void SceneRow::enterEvent(QEnterEvent* event)
{
    setHovered(true);
    QWidget::enterEvent(event);
}

void SceneRow::leaveEvent(QEvent* event)
{
    setHovered(false);
    QWidget::leaveEvent(event);
}

void SceneRow::resizeEvent(QResizeEvent* event)
{
    QWidget::resizeEvent(event);
    // Re-elide title now that we know the real label width.
    applyData();
}

void SceneRow::paintEvent(QPaintEvent* event)
{
    // QSS paints background first via base class call
    QWidget::paintEvent(event);

    // Status dot — square, 7×7, color from SceneStatus
    // QPainter here avoids per-instance setStyleSheet() cost
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);
    p.setPen(Qt::NoPen);
    p.setBrush(sceneStatusColor(m_data.status));

    const int dotY = (height() - kDotSize) / 2;
    p.drawRect(kDotLeft, dotY, kDotSize, kDotSize);
}