#include "premise.h"
#include "ui/components/editor/concept/premise/emptystatewidget.h"
#include "ui/components/editor/concept/premise/form.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QStackedWidget>
#include <QFile>

Premise::Premise(QWidget *parent)
    : QFrame{parent}
{
    setObjectName("premiseView");
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QVBoxLayout* contentArea = new QVBoxLayout(this);
    contentArea->setObjectName(QStringLiteral("mainContentArea"));
    contentArea->setContentsMargins(0, 0, 0, 0);
    contentArea->setSpacing(0);

    m_stack = new QStackedWidget(this);
    contentArea->addWidget(m_stack, 1);

    m_emptyWrapper = new QWidget(m_stack);
    m_emptyWrapper->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    QVBoxLayout* wl = new QVBoxLayout(m_emptyWrapper);
    wl->setContentsMargins(0, 0, 0, 0);

    EmptyStateWidget* stateWidget = new EmptyStateWidget(m_stack);
    wl->addWidget(stateWidget, 0, Qt::AlignCenter);
    m_stack->addWidget(m_emptyWrapper);

    m_form = new Form(m_stack);
    m_stack->addWidget(m_form);
    m_stack->setMaximumWidth(760);

    connect(m_form, &Form::formSubmitted, this, &Premise::onFormSubmitted);

    connect(stateWidget, &EmptyStateWidget::startEditingClicked, this, [this]() {
        m_stack->setCurrentWidget(m_form);
        emit modeChanged(EditMode);
    });

    QFile styleFile(QStringLiteral(":/styles/premisestyles.qss"));
    if (styleFile.open(QFile::ReadOnly | QFile::Text)) {
        setStyleSheet(QLatin1String(styleFile.readAll()));
        styleFile.close();
    }
}

void Premise::onFormSubmitted(const PremiseData& data)
{
    m_stack->setCurrentWidget(m_emptyWrapper);
    emit modeChanged(ViewMode);
}
