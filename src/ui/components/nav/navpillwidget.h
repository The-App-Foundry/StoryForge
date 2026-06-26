#ifndef NAVPILLWIDGET_H
#define NAVPILLWIDGET_H

#include <QAbstractButton>
#include <QString>

class QSvgRenderer;

class NavPillWidget : public QAbstractButton
{
    Q_OBJECT
public:
    enum Orientation { Vertical, Horizontal };
    explicit NavPillWidget(const QString& label,
                           const QString& svgPaths,
                           int svgSize,
                           Orientation orientation,
                           QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    void setHovered(bool hovered);
    void enterEvent(QEnterEvent* event) override;
    void leaveEvent(QEvent* event) override;

    QString         m_label;
    QSvgRenderer*   m_activeRenderer        = nullptr;
    QSvgRenderer*   m_inactiveRenderer      = nullptr;
    bool            m_hovered               = false;
    int             m_svgSize;
    Orientation     m_orientation;
};

#endif // NAVPILLWIDGET_H
