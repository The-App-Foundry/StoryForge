#ifndef CONCEPTVIEW_H
#define CONCEPTVIEW_H

#include <QFrame>

class QStackedWidget;
class ConceptRail;

class ConceptView : public QFrame
{
    Q_OBJECT
public:
    explicit ConceptView(QWidget *parent = nullptr);

signals:
    void viewChanged(QWidget* view);

private slots:
    void onNavItemSelected(const QString& section);

private:
    QStackedWidget*     m_stacked   = nullptr;
    ConceptRail*        m_rail      = nullptr;
};

#endif // CONCEPTVIEW_H
