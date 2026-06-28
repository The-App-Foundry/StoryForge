#ifndef EMPTYSTATEWIDGET_H
#define EMPTYSTATEWIDGET_H

#include <QWidget>

class QLabel;
class QSvgWidget;
class IconButton;

class EmptyStateWidget : public QWidget
{
    Q_OBJECT
public:
    explicit EmptyStateWidget(QWidget *parent = nullptr);

signals:
    void startEditingClicked();

private:
    QSvgWidget*     m_icon      = nullptr;
    QLabel*         m_label     = nullptr;
    QLabel*         m_subtext   = nullptr;
    IconButton*    m_editBtn   = nullptr;
};

#endif // EMPTYSTATEWIDGET_H
