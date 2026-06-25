#include "navrail.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QAbstractButton>
#include <QFile>
#include <QLabel>
#include <QFrame>
#include <QPainter>
#include <QPainterPath>
#include <QFont>
#include <QFontDatabase>
#include <QSvgRenderer>

// ── Shared helpers ────────────────────────────────────────────────────────────

// Build a complete inline SVG string, substituting the stroke colour so
// QSvgRenderer (which doesn't support CSS `currentColor`) can render it.
static QByteArray makeSvg(const QString& paths, const QColor& stroke)
{
    return QString(
        "<svg xmlns='http://www.w3.org/2000/svg' "
        "width='18' height='18' viewBox='0 0 24 24' "
        "fill='none' stroke='%1' stroke-width='1.6' "
        "stroke-linecap='round' stroke-linejoin='round'>%2</svg>"
    ).arg(stroke.name(), paths).toUtf8();
}

static constexpr QColor kAccent  { 0x7b, 0xf0, 0xdb };
static constexpr QColor kFaint   { 0x7a, 0x7a, 0x96 };

// ── NavPillWidget ─────────────────────────────────────────────────────────────
// Reusable pill for every nav-section button (CAST / SCENES / PLACES / PROPS / NOTES).
// Inherits QAbstractButton so it integrates with QButtonGroup for exclusivity.
class NavPillWidget : public QAbstractButton {
public:
    explicit NavPillWidget(const QString& label,
                           const QString& svgPaths,
                           QWidget *parent = nullptr)
        : QAbstractButton(parent), m_label(label)
    {
        setCheckable(true);
        setFixedSize(53, 56);
        setObjectName("navRailButton");

        // Build both coloured renderers up-front
        m_activeRenderer   = new QSvgRenderer(makeSvg(svgPaths, kAccent), this);
        m_inactiveRenderer = new QSvgRenderer(makeSvg(svgPaths, kFaint),  this);
    }

protected:
    void paintEvent(QPaintEvent *) override {
        QPainter p(this);
        p.setRenderHint(QPainter::Antialiasing);

        const bool  active = isChecked();
        const QColor& col  = active ? kAccent : kFaint;

        // Left indicator bar – visible only when active
        if (active)
            p.fillRect(0, 8, 2, height() - 16, kAccent);

        // Icon
        const int iconX = (width() - 18) / 2;
        QSvgRenderer* rdr = active ? m_activeRenderer : m_inactiveRenderer;
        rdr->render(&p, QRectF(iconX, 10, 18, 18));

        // Label
        QFont font("DM Mono");
        font.setPixelSize(8);
        font.setLetterSpacing(QFont::AbsoluteSpacing, 0.5);
        p.setFont(font);
        p.setPen(col);
        p.drawText(QRect(0, 32, width(), 16),
                   Qt::AlignHCenter | Qt::AlignVCenter, m_label);
    }

private:
    QString        m_label;
    QSvgRenderer*  m_activeRenderer   = nullptr;
    QSvgRenderer*  m_inactiveRenderer = nullptr;
};

// ── FooterButton ──────────────────────────────────────────────────────────────
// Sidebar-toggle at the bottom of the rail. Draws the panel/sidebar icon.
class FooterButton : public QWidget {
public:
    explicit FooterButton(QWidget *parent = nullptr) : QWidget(parent) {
        setFixedSize(53, 48);
        setObjectName("navRailFooterButton");

        // SVG: outer rect + vertical divider (sidebar icon)
        const QString paths =
            "<rect x='3' y='4' width='18' height='16' rx='1'/>"
            "<path d='M9 4v16'/>";
        m_renderer = new QSvgRenderer(makeSvg(paths, kFaint), this);
    }

protected:
    void paintEvent(QPaintEvent *) override {
        // Top border to visually separate from the stretch spacer
        QPainter p(this);
        p.setPen(QColor(0x2a, 0x2a, 0x3a));
        p.drawLine(0, 0, width(), 0);

        // Icon centred (16×16 per the HTML)
        const int iconX = (width()  - 16) / 2;
        const int iconY = (height() - 16) / 2;
        m_renderer->render(&p, QRectF(iconX, iconY, 16, 16));
    }

private:
    QSvgRenderer* m_renderer = nullptr;
};

// ── NavRail ───────────────────────────────────────────────────────────────────

NavRail::NavRail(QWidget *parent)
    : QFrame{parent}
{

    setObjectName("navRail");
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);

    setFixedWidth(53);

    auto* layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    buildNavButtons();

    layout->addStretch(1);

    buildFooter();

    QFile styleFile(":/navrailstyles.qss");

    if(styleFile.open(QFile::ReadOnly | QFile::Text)) {
        QString styleSheet = QLatin1String(styleFile.readAll());
        this->setStyleSheet(styleSheet);
        styleFile.close();
    }
}

void NavRail::buildNavButtons()
{
    m_navGroup = new QButtonGroup(this);
    m_navGroup->setExclusive(true);

    // Each entry: { label, SVG path element(s) }
    // Icon paths mirror the HTML reference exactly.
    const QList<QPair<QString, QString>> items = {
        { "DRAFT",
         "<path d='M4 4h11l5 5v11H4z'/>"
         "<path d='M15 4v5h5M8 13h8M8 17h8'/>" },
        { "CAST",
          "<circle cx='12' cy='8' r='4'/>"
          "<path d='M4 21c0-4 3.6-6 8-6s8 2 8 6'/>" },

        { "SCENES",
          "<rect x='3' y='4' width='18' height='16' rx='1'/>"
          "<path d='M3 9h18M8 4v5M16 4v5M8 20v-5M16 20v-5'/>" },

        { "PLACES",
          "<path d='M12 21s-7-6.2-7-11a7 7 0 0 1 14 0c0 4.8-7 11-7 11z'/>"
          "<circle cx='12' cy='10' r='2.5'/>" },

        { "PROPS",
          "<path d='M12 2 3 7v10l9 5 9-5V7z'/>"
          "<path d='M3 7l9 5 9-5M12 12v10'/>" },

        { "NOTES",
          "<path d='M5 4h11l3 3v13H5z'/>"
          "<path d='M9 9h6M9 13h6M9 17h3'/>" },
    };

    for (const auto& [label, svgPaths] : items) {
        const QString sectionName = label;
        auto* pill = new NavPillWidget(sectionName, svgPaths, this);
        pill->setProperty("navSection", sectionName);

        m_navGroup->addButton(pill);
        static_cast<QVBoxLayout*>(layout())->addWidget(pill);

        connect(pill, &QAbstractButton::clicked, this, [this, sectionName]() {
            emit navItemSelected(sectionName);
        });

        // Repaint on toggle so the indicator bar / colour updates immediately
        connect(pill, &QAbstractButton::toggled, pill,
                static_cast<void (QWidget::*)()>(&QWidget::update));
    }
}

void NavRail::buildFooter()
{
    auto* footer = new FooterButton(this);
    static_cast<QVBoxLayout*>(layout())->addWidget(footer);
}
