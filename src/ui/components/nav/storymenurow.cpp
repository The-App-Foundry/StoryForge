#include "storymenurow.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QStyle>

StoryMenuRow::StoryMenuRow(QWidget *parent)
    : QWidget{parent}
{
    QHBoxLayout* rowLayout = new QHBoxLayout(this);
    rowLayout->setContentsMargins(14, 10, 14, 10);
    rowLayout->setSpacing(12);

    QLabel* rDot = new QLabel(QStringLiteral(" "), this);
    rDot->setObjectName(QStringLiteral("menuRowDotInactive"));
    rDot->setFixedWidth(8);

    QLabel* rName = new QLabel(this);
    rName->setObjectName(QStringLiteral("menuRowNameText"));

    QLabel* rMeta = new QLabel(this);
    rMeta->setObjectName(QStringLiteral("menuRowMetaText"));
    rMeta->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    QLabel* rBadge = new QLabel(this);
    rBadge->setObjectName(QStringLiteral("menuRowBadgeFinal"));
    rBadge->setAlignment(Qt::AlignCenter);

    rowLayout->addWidget(rDot);
    rowLayout->addWidget(rName);
    rowLayout->addWidget(rMeta);
    rowLayout->addStretch(1);
    rowLayout->addWidget(rBadge);
}

void StoryMenuRow::setStoryData(const QString& name, const QString& meta, const QString& badge, const bool& isActive)
{
    m_nameLabel->setText(name);
    m_metaLabel->setText(meta);
    m_badgeLabel->setText(badge);

    if(isActive) {
        this->setObjectName(QStringLiteral("menuStoryRowActive"));
        m_dotLabel->setObjectName(QStringLiteral("menuRowDotActive"));
        m_dotLabel->setFixedSize(7, 7);
        m_nameLabel->setObjectName(QStringLiteral("menuRowNameTxtActive"));
    } else {
        this->setObjectName(QStringLiteral("menuStoryRow"));
        m_dotLabel->setObjectName(QStringLiteral("menuRowDotInactive"));
        m_dotLabel->setText(QStringLiteral(" "));
        m_dotLabel->setFixedWidth(8);
        m_nameLabel->setObjectName(QStringLiteral("menuRowNameTxt"));
    }

    if (badge == QLatin1String("FINAL")){
        m_badgeLabel->setObjectName(QStringLiteral("menuRowBadgeFinal"));
    } else if (badge == QLatin1String("EDITING")) {
        m_badgeLabel->setObjectName(QStringLiteral("menuRowBadgeEditing"));
    }

    this->style()->unpolish(this);
    this->style()->polish(this);
}
