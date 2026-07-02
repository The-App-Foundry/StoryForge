#ifndef PREMISE_H
#define PREMISE_H

#include "premisedata.h"
#include <QFrame>

class QVLayoutBox;
class QPushButton;
class QStackedWidget;
class Form;

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

private slots:
    void onFormSubmitted(const PremiseData& data);

private:
    QVLayoutBox*        m_premiseLayout     = nullptr;
    QPushButton*        m_editBtn           = nullptr;
    QStackedWidget*     m_stack             = nullptr;
    Form*               m_form              = nullptr;
    QWidget*            m_emptyWrapper      = nullptr;
};

#endif // PREMISE_H
