#ifndef ICONBUTTON_H
#define ICONBUTTON_H

#include <QPushButton>
#include <QByteArray>
#include <QSize>

class IconButton : public QPushButton {
    Q_OBJECT

public:
    explicit IconButton(QWidget *parent = nullptr);
    void setIcon(const QByteArray &svgData);
    void setIconSize(const QSize &size);
    void setIconTextGap(int px);

private:
    void rebuildIcon();

    QByteArray m_svgData;
    QSize      m_iconSize;
    int        m_iconTextGap;
};

#endif
