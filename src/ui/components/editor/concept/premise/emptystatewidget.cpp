#include "emptystatewidget.h"
#include "../../../../utils/graphicsutils.h"
#include "../../../buttons/iconbutton.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QtSvgWidgets/QtSvgWidgets>
#include <QPixmap>
#include <QIcon>
#include <QSvgRenderer>
#include <QPainter>

EmptyStateWidget::EmptyStateWidget(QWidget *parent)
    : QWidget{parent}
{

    setAttribute(Qt::WA_StyledBackground, true);

    setObjectName("emptyStateWidget");
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    setFixedSize(648, 231);

    QByteArray docSvg = GraphicsUtils::loadSvg(":/icons/document.svg", QString("#67737c"));
    QByteArray editSvg = GraphicsUtils::loadSvg(":/icons/edit.svg", QString("#8b949e"));

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName("mainLayout");
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    mainLayout->addStretch(1);

    m_icon = new QSvgWidget(this);
    m_icon->load(docSvg);
    m_icon->setFixedSize(32, 32);
    m_icon->setObjectName("svgIcon");
    mainLayout->addWidget(m_icon, 0, Qt::AlignCenter);

    m_label = new QLabel(this);
    m_label->setObjectName("mainText");
    m_label->setText(QStringLiteral("NOTHING TO SEE HERE"));
    mainLayout->addWidget(m_label, 0, Qt::AlignCenter);

    m_subtext = new QLabel(this);
    m_subtext->setObjectName("subText");
    m_subtext->setText(QStringLiteral("Click \"START EDITING\" button to fill in the pillars of your story. "));
    mainLayout->addWidget(m_subtext, 0, Qt::AlignCenter);

    m_editBtn = new IconButton(this);
    m_editBtn->setObjectName("startEditingBtn");
    m_editBtn->setIcon(editSvg);
    m_editBtn->setIconSize(QSize(11, 11));
    m_editBtn->setText("START EDITING");
    mainLayout->addWidget(m_editBtn, 0, Qt::AlignCenter);

    connect(m_editBtn, &QPushButton::clicked, this, &EmptyStateWidget::startEditingClicked);

    mainLayout->addStretch(1);
}