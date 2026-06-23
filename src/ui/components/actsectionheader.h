#ifndef ACTSECTIONHEADER_H
#define ACTSECTIONHEADER_H

#include "scenedata.h"
#include "scenerow.h"

#include <QLabel>
#include <QWidget>

// ============================================================
// ActSectionHeader
//
// Collapsible section header for one Act.  Owns its SceneRow
// children via Qt parent chain (m_scenesContainer is parent).
//
// Collapse/expand is a single setVisible() call on
// m_scenesContainer — layout adjusts automatically, no manual
// height arithmetic required.
// ============================================================
class ActSectionHeader : public QWidget
{
    Q_OBJECT

public:
    explicit ActSectionHeader(const ActData& act, QWidget* parent = nullptr);

    void setExpanded(bool expanded);
    [[nodiscard]] bool isExpanded() const { return m_expanded; }

    void setActData(const ActData& act);

signals:
    void sceneClicked(int sceneNumber);
    void expandedChanged(bool expanded);

protected:
    void mousePressEvent(QMouseEvent* event) override;
    void enterEvent(QEnterEvent* event) override;
    void leaveEvent(QEvent* event) override;

private:
    void buildSceneRows();
    void clearSceneRows();   // uses delete — GUI thread, synchronous
    void updateChevron();
    void setHeaderHovered(bool hovered);

    ActData  m_act;
    bool     m_expanded = true;

    QLabel*  m_labelChevron    = nullptr;
    QLabel*  m_labelTitle      = nullptr;
    QLabel*  m_labelSceneCount = nullptr;

    QWidget* m_headerRow       = nullptr;
    QWidget* m_scenesContainer = nullptr;

    QList<SceneRow*> m_sceneRows;   // non-owning cache for iteration; Qt parent chain owns
};

#endif // ACTSECTIONHEADER_H