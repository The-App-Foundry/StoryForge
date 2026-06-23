#ifndef MANUSCRIPTPANEL_H
#define MANUSCRIPTPANEL_H

#include "scenedata.h"
#include "actsectionheader.h"

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QScrollArea>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QWidget>

// ============================================================
// ManuscriptPanel
//
// Content panel beside the NavRail inside SideBar's QHBoxLayout.
//
// Internal structure:
//   ManuscriptPanel (QVBoxLayout)
//   ├── panelHeader  [SECTION TITLE]  [count]
//   ├── separator    (1px QFrame)
//   └── QStackedWidget
//       ├── page 0: DRAFT  — QScrollArea → Act/Scene tree
//       ├── page 1: CAST   — placeholder QWidget
//       ├── page 2: SCENES — placeholder QWidget
//       ├── page 3: PLACES — placeholder QWidget
//       ├── page 4: PROPS  — placeholder QWidget
//       └── page 5: NOTES  — placeholder QWidget
//
// showSection(QString) is the slot wired from NavRail via SideBar.
// ============================================================
class ManuscriptPanel : public QWidget
{
    Q_OBJECT

public:
    explicit ManuscriptPanel(QWidget* parent = nullptr);

    // Replace the act/scene data and rebuild the DRAFT page
    void setManuscript(const QList<ActData>& acts);

public slots:
    // Wired from NavRail::navItemSelected via SideBar
    void showSection(const QString& section);

signals:
    void sceneSelected(int sceneNumber);

private:
    void buildDraftPage();
    void buildActWidgets();
    void clearActWidgets();

    QList<ActData>            m_acts;
    QList<ActSectionHeader*>  m_actHeaders;

    // Header bar
    QLabel*          m_labelPanelTitle  = nullptr;
    QLabel*          m_labelCount       = nullptr;

    // Filter controls (always visible, above the stack)
    QLineEdit*       m_filterEdit       = nullptr;
    QPushButton*     m_btnAll           = nullptr;

    // Stack — one page per NavRail section
    QStackedWidget*  m_stack            = nullptr;

    // DRAFT page sub-widgets
    QScrollArea*     m_scrollArea       = nullptr;
    QWidget*         m_scrollContent    = nullptr;
    QVBoxLayout*     m_contentLayout    = nullptr;

    // Section → stack index lookup
    // Matches the NavRail button order (CAST=0, SCENES=1, PLACES=2, PROPS=3, NOTES=4)
    // DRAFT is index 0 in the stack and is the default
    static constexpr int kPageDraft  = 0;
    static constexpr int kPageCast   = 1;
    static constexpr int kPageScenes = 2;
    static constexpr int kPagePlaces = 3;
    static constexpr int kPageProps  = 4;
    static constexpr int kPageNotes  = 5;
};

#endif // MANUSCRIPTPANEL_H