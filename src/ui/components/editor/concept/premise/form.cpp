#include "form.h"
#include "formgroup.h"
#include "ui/components/buttons/iconbutton.h"
#include "ui/utils/graphicsutils.h"
#include <QLabel>
#include <QVBoxLayout>

Form::Form(QWidget *parent)
    : QWidget{parent}
{
    setObjectName("premiseForm");

    const QString labels[5] = {
        "logline",
        "central question",
        "central conflict",
        "tone & register",
        "themes",
    };

    const QString placeholders[5] = {
        "[Protragonist] must [goal] before [stakes] -- but [obstacle].",
        "What does this story ask of the reader?",
        "The core tension driving every scene.",
        "e.g. Melancholic, precise, dark humour",
        "e.g. Grief, memory, what it costs to keep a place alive"
    };

    QByteArray check = GraphicsUtils::loadSvg(":/icons/check.svg");


    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(26, 26, 26, 26);
    mainLayout->setSpacing(26);

    auto headerLayout = new QVBoxLayout();
    headerLayout->setContentsMargins(0, 0, 0, 0);
    headerLayout->setSpacing(0);

    m_header = new QLabel(this);
    m_header->setObjectName("premiseFormHeader");
    m_header->setText(QString("premise builder"));
    headerLayout->addWidget(m_header);

    m_subheader = new QLabel(this);
    m_subheader->setObjectName("premiseSubheader");
    m_subheader->setText(QString("Lock in the pillars of your story before a single scene is written."));
    headerLayout->addWidget(m_subheader);

    mainLayout->addLayout(headerLayout);

    auto formLayout = new QVBoxLayout();
    formLayout->setObjectName("formBox");
    formLayout->setContentsMargins(0, 0, 0, 0);
    formLayout->setSpacing(26);


    for (int i = 0; i < 5; ++i) {
        m_formGroups[i] = new FormGroup(labels[i], placeholders[i], this);
        formLayout->addWidget(m_formGroups[i]);
    }

    mainLayout->addLayout(formLayout);

    m_doneBtn = new IconButton(this);
    m_doneBtn->setObjectName("doneBtn");
    m_doneBtn->setIcon(check);
    m_doneBtn->setIconSize(QSize(11, 11));
    m_doneBtn->setText("DONE");
    mainLayout->addWidget(m_doneBtn, 0, Qt::AlignRight);

    connect(m_doneBtn, &QPushButton::clicked, this, &Form::onFormSubmit);
}

void Form::onFormSubmit()
{
    PremiseData data;
    data.logLine = m_formGroups[0]->getText();
    data.ctlQuestion = m_formGroups[1]->getText();
    data.ctlConflict = m_formGroups[2]->getText();
    data.tone = m_formGroups[3]->getText();
    data.themes = m_formGroups[4]->getText();

    emit formSubmitted(data);
}
