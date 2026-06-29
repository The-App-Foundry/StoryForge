#include "conceptrail.h"
#include "navpillwidget.h"
#include <QHBoxLayout>
#include <QFile>

ConceptRail::ConceptRail(QWidget* parent)
    : QFrame{parent}
{
    setObjectName("draftToolBar");
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    setFixedHeight(42);

    auto* layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    buildNavButtons();

    layout->addStretch(1);

    QFile styleFile(":/styles/conceptrailstyles.qss");

    if(styleFile.open(QFile::ReadOnly | QFile::Text)) {
        QString styleSheet = QLatin1String(styleFile.readAll());
        this->setStyleSheet(styleSheet);
        styleFile.close();
    }
}

void ConceptRail::buildNavButtons()
{
    m_navGroup = new QButtonGroup(this);
    m_navGroup->setExclusive(true);

    const QList<QPair<QString, QString>> items = {
        { "MIND MAP",
          "<circle cx='18' cy='5' r='3' />"
          "<circle cx='6' cy='12' r='3' />"
          "<circle cx='18' cy='19' r='3' />"
          "<line x1='8.59' y1='13.51' x2='15.42' y2='17.49' />"
          "<line x1='15.41' y1='6.51' x2='8.59' y2='10.49' />" },

        { "PREMISE",
          "<path d='M4 19.5A2.5 2.5 0 0 1 6.5 17H20' />"
          "<path d='M6.5 2H20v20H6.5A2.5 2.5 0 0 1 4 19.5v-15A2.5 2.5 0 0 1 6.5 2z' />"
          "<line x1='9' y1='6' x2='15' y2='6' />"
          "<line x1='9' y1='10' x2='15' y2='10' />" },

        { "RESEARCH",
          "<circle cx='11' cy='11' r='8' />"
          "<line x1='21' y1='21' x2='16.65' y2='16.65' />" },

        { "CAST SEEDS",
          "<path d='M16 21v-2a4 4 0 0 0-4-4H5a4 4 0 0 0-4 4v2' />"
          "<circle cx='8.5' cy='7' r='4' />"
          "<circle cx='20' cy='8' r='1' fill='#7bf0db' />"
          "<circle cx='17' cy='13' r='1.5' fill='#7bf0db' />"
          "<circle cx='21' cy='16' r='1' fill='#7bf0db' />" },
    };

    for (const auto& [label, svgPaths] : items) {
        const QString sectionName = label;
        auto* pill = new NavPillWidget(sectionName, svgPaths, 12, NavPillWidget::Orientation::Horizontal, this);
        pill->setProperty("navSection", sectionName);
        pill->setFixedSize(115, 42);

        m_navGroup->addButton(pill);
        static_cast<QHBoxLayout*>(layout())->addWidget(pill);

        connect(pill, &QAbstractButton::toggled, pill,
                static_cast<void (QWidget::*)()>(&QWidget::update));
    }
}
