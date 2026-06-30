#include "premise.h"
#include "ui/components/editor/concept/premise/emptystatewidget.h"
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
    contentArea->addWidget(m_stack, 1, Qt::AlignCenter);

    EmptyStateWidget* stateWidget = new EmptyStateWidget(m_stack);
    m_stack->addWidget(stateWidget);

    connect(stateWidget, &EmptyStateWidget::startEditingClicked, this, [this]() {
        emit modeChanged(EditMode);
    });

    contentArea->addStretch(1);

    QFile styleFile(QStringLiteral(":/premisestyles.qss"));
    if (styleFile.open(QFile::ReadOnly | QFile::Text)) {
        setStyleSheet(QLatin1String(styleFile.readAll()));
        styleFile.close();
    }
}
