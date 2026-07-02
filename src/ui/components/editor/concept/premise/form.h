#ifndef FORM_H
#define FORM_H

#include "ui/views/concept/premise/premisedata.h"
#include <QWidget>

class QLabel;
class FormGroup;
class IconButton;

class Form : public QWidget
{
    Q_OBJECT
public:
    explicit Form(QWidget *parent = nullptr);

signals:
    void formSubmitted(const PremiseData& data);

private:
    void onFormSubmit();

    QLabel*         m_header            = nullptr;
    QLabel*         m_subheader         = nullptr;
    FormGroup*      m_formGroups[5];
    IconButton*    m_doneBtn           = nullptr;
};

#endif // FORM_H
