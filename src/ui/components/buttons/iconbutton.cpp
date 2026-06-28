#include "iconbutton.h"
#include <QSvgRenderer>
#include <QPainter>
#include <QIcon>
#include <QPixmap>
#include <QRectF>

IconButton::IconButton(QWidget *parent)
    : QPushButton(parent), m_iconSize(16, 16), m_iconTextGap(6)
{
}

void IconButton::setIcon(const QByteArray &svgData)
{
    m_svgData = svgData;
    rebuildIcon();
}

void IconButton::setIconSize(const QSize &size)
{
    m_iconSize = size;
    rebuildIcon();
}

void IconButton::setIconTextGap(int px)
{
    m_iconTextGap = px;
    rebuildIcon();
}

void IconButton::rebuildIcon()
{
    if (m_svgData.isEmpty())
        return;

    const int gw = m_iconSize.width();
    const int gh = m_iconSize.height();

    const int scale = 4;
    QPixmap canvas((gw + m_iconTextGap) * scale, gh * scale);
    canvas.fill(Qt::transparent);

    QSvgRenderer renderer(m_svgData);
    QPainter painter(&canvas);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    renderer.render(&painter, QRectF(0, 0, gw * scale, gh * scale));
    painter.end();

    // iconSize matches the padded canvas aspect, so the glyph is not squished.
    QPushButton::setIcon(QIcon(canvas));
    QPushButton::setIconSize(QSize(gw + m_iconTextGap, gh));
}
