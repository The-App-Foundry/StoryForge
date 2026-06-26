#include "navpillwidget.h"
#include "../../utils/graphicsutils.h"
#include <QPainter>
#include <QSvgRenderer>
#include <QFont>
#include <QStyle>

static constexpr QColor kAccent  { 0x7b, 0xf0, 0xdb };
static constexpr QColor kFaint   { 0x7a, 0x7a, 0x96 };

NavPillWidget::NavPillWidget(const QString& label,
                             const QString& svgPaths,
                             int svgSize,
                             Orientation orientation,
                             QWidget *parent)
    : QAbstractButton(parent),
      m_label(label),
      m_svgSize(svgSize),
      m_orientation(orientation)
{
    setCheckable(true);
    setObjectName("navRailButton");

    m_activeRenderer   = new QSvgRenderer(GraphicsUtils::makeSvg(svgPaths, kAccent), this);
    m_inactiveRenderer = new QSvgRenderer(GraphicsUtils::makeSvg(svgPaths, kFaint),  this);
}

void NavPillWidget::paintEvent(QPaintEvent *) {
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    const bool  active = isChecked() || property("hovered").toBool();
    const QColor& col  = active ? kAccent : kFaint;

    if (m_orientation == Orientation::Vertical) {
        if (active)
            p.fillRect(0, 8, 2, height() - 16, kAccent);

        const int iconX = (width() - m_svgSize) / 2;
        bool shouldUseActive = active;
        QSvgRenderer* rdr = shouldUseActive ? m_activeRenderer : m_inactiveRenderer;
        rdr->render(&p, QRectF(iconX, 10, m_svgSize, m_svgSize));

        QFont font("DM Mono");
        font.setPixelSize(8);
        font.setLetterSpacing(QFont::AbsoluteSpacing, 0.5);
        p.setFont(font);
        p.setPen(col);
        p.drawText(QRect(0, 32, width(), 16),
                   Qt::AlignHCenter | Qt::AlignVCenter, m_label);
    } else {
        if (active)
            p.fillRect(0, height() - 2, width(), 2, kAccent);

        QFont font("DM Mono");
        font.setPixelSize(8);
        font.setLetterSpacing(QFont::AbsoluteSpacing, 0.5);
        QFontMetrics fm(font);
        int textWidth = fm.horizontalAdvance(m_label);
        int totalWidth = m_svgSize + 2 + textWidth;  // icon + gap + text
        int startX = (width() - totalWidth) / 2;    // center in pill
        p.setFont(font);
        p.setPen(col);

        const int iconX = startX;
        const int iconY = (height() - m_svgSize) / 2;
        bool shouldUseActive = active;
        QSvgRenderer* rdr = shouldUseActive ? m_activeRenderer : m_inactiveRenderer;
        rdr->render(&p, QRectF(iconX, iconY, m_svgSize, m_svgSize));

        int x = startX + m_svgSize + 3;
        int y = (height() - 16) / 2;
        int w = textWidth;

        p.drawText(QRect(x, y, w, 16), Qt::AlignHCenter | Qt::AlignVCenter, m_label);
    }

}

void NavPillWidget::enterEvent(QEnterEvent *event) {
    setProperty("hovered", true);
    update();
    QAbstractButton::enterEvent(event);
}

void NavPillWidget::leaveEvent(QEvent *event) {
    setProperty("hovered", false);
    update();
    QAbstractButton::leaveEvent(event);
}