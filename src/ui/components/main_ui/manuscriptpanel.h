#ifndef MANUSCRIPTPANEL_H
#define MANUSCRIPTPANEL_H

#include "scenedata.h"
#include <QFrame>

class ActSectionHeader;
class QLabel;
class QLineEdit;
class QPushButton;
class QScrollArea;
class QStackedWidget;
class QVBoxLayout;

class ManuscriptPanel : public QFrame
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
    QPushButton*     m_btnNewAct        = nullptr;

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