#ifndef SCENEROW_H
#define SCENEROW_H

#include "scenedata.h"
#include <QWidget>
#include <QLabel>

// ============================================================
// SceneRow
//
// Flat row under an ActSectionHeader.  Manually composed —
// no QTreeWidget so QSS has complete, predictable control.
//
// Layout (left → right, all within a single QHBoxLayout):
//   [status dot — paintEvent]  [##]  [Title — expands]  [POV]  [wc]
//
// Status dot drawn via QPainter in paintEvent.
// NOT via per-instance setStyleSheet() — that triggers a full
// style engine repolish on every row construction.
// ============================================================
class SceneRow : public QWidget
{
    Q_OBJECT

public:
    explicit SceneRow(const SceneData& data, QWidget* parent = nullptr);

    void setData(const SceneData& data);
    [[nodiscard]] int sceneNumber() const { return m_data.number; }

signals:
    void clicked(int sceneNumber);

protected:
    void mousePressEvent(QMouseEvent* event) override;
    void enterEvent(QEnterEvent* event) override;
    void leaveEvent(QEvent* event) override;
    void resizeEvent(QResizeEvent* event) override;
    void paintEvent(QPaintEvent* event) override;

private:
    void applyData();
    void setHovered(bool hovered);

    SceneData m_data;
    bool      m_hovered = false;

    QLabel* m_labelNumber    = nullptr;
    QLabel* m_labelTitle     = nullptr;
    QLabel* m_labelPov       = nullptr;
    QLabel* m_labelWordCount = nullptr;
};

#endif // SCENEROW_H