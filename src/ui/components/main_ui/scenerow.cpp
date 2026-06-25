#include "scenerow.h"

#include <QHBoxLayout>
#include <QMouseEvent>
#include <QPainter>
#include <QStyle>
#include <QFontMetrics>

static constexpr int kRowHeight  = 36;
static constexpr int kDotSize    = 7;
static constexpr int kDotLeft    = 14;  // px from widget left edge

// static void setLabelTextFitting(QLabel* label, const QString& text, int maxWidth) {
//     QFont font = label->font();
//     font.setPointSize(12); // Reset to base size defined in QSS so it can scale up or down cleanly

//     QFontMetrics fm(font);

//     // Keep shrinking the font size until it fits perfectly within the allocated pixels
//     while (fm.horizontalAdvance(text) > maxWidth && font.pointSize() > 6) {
//         font.setPointSize(font.pointSize() - 1);
//         fm = QFontMetrics(font);
//     }

//     label->setFont(font);
//     label->setText(text);
// }

SceneRow::SceneRow(const SceneData& data, QWidget* parent)
    : QFrame(parent)
    , m_data(data)
{
    setObjectName(QStringLiteral("sceneRow"));
    setFixedHeight(kRowHeight);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    setCursor(Qt::PointingHandCursor);

    const int dotSlotWidth = kDotLeft + kDotSize + 10;

    QHBoxLayout* lay = new QHBoxLayout(this);
    lay->setContentsMargins(dotSlotWidth, 0, 14, 0);
    lay->setSpacing(0);

    m_labelNumber = new QLabel(this);
    m_labelNumber->setObjectName(QStringLiteral("sceneRowNumber"));
    m_labelNumber->setFixedWidth(12);
    lay->addWidget(m_labelNumber);

    lay->addSpacing(8);

    m_labelTitle = new QLabel(this);
    m_labelTitle->setObjectName(QStringLiteral("sceneRowTitle"));
    m_labelTitle->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    m_labelTitle->setFixedWidth(100);
    lay->addWidget(m_labelTitle);

    lay->addSpacing(12);

    m_labelPov = new QLabel(this);
    m_labelPov->setObjectName(QStringLiteral("sceneRowPov"));
    m_labelPov->setFixedWidth(80);
    m_labelPov->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    lay->addWidget(m_labelPov);

    lay->addSpacing(20);

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

    // int totalAllocatedSpace = 235;
    // int calculatedMaxW = this->width() > 0 ? (this->width() - totalAllocatedSpace) : 110;

    // // Ensure we don't pass a crazy negative or ultra-squashed number
    // if (calculatedMaxW < 110) {
    //     calculatedMaxW = 110;
    // }
    // // Zap the old elidedText block and drop the scaling helper in!
    // setLabelTextFitting(m_labelTitle, m_data.title, calculatedMaxW);

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
    applyData();
}

void SceneRow::paintEvent(QPaintEvent* event)
{
    QWidget::paintEvent(event);

    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);
    p.setPen(Qt::NoPen);
    p.setBrush(sceneStatusColor(m_data.status));

    const int dotY = (height() - kDotSize) / 2;
    p.drawRect(kDotLeft, dotY, kDotSize, kDotSize);
}