#include "formgroup.h"
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>

FormGroup::FormGroup(const QString &label,
                     const QString &placeholder,
                     QWidget *parent)
    : QWidget{parent}
{
    setAttribute(Qt::WA_StyledBackground, true);

    setObjectName("formGroup");

    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName("layout");
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    auto labelBox = new QHBoxLayout();
    labelBox->setContentsMargins(0, 0, 0, 0);
    labelBox->setSpacing(0);

    m_label = new QLabel(this);
    m_label->setObjectName("premiseFormLabel");
    m_label->setText(label);
    labelBox->addWidget(m_label);
    mainLayout->addLayout(labelBox);

    m_data = new QLineEdit(this);
    m_data->setObjectName("premiseEditField");
    m_data->setPlaceholderText(placeholder);
    mainLayout->addWidget(m_data);
}

QString FormGroup::getText() const
{
    return m_data->text();
}
