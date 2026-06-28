#ifndef PREMISE_H
#define PREMISE_H

#include <QFrame>

class QVLayoutBox;
class QPushButton;
class QStackedWidget;

enum PremiseMode {
    EditMode,
    ViewMode
};

class Premise : public QFrame
{
    Q_OBJECT
public:
    explicit Premise(QWidget *parent = nullptr);

signals:
    void modeChanged(PremiseMode mode);

private:
    QVLayoutBox*        m_premiseLayout     = nullptr;
    QPushButton*        m_editBtn           = nullptr;
    QStackedWidget*     m_stack             = nullptr;
};

#endif // PREMISE_H
