#ifndef CONCEPTRAIL_H
#define CONCEPTRAIL_H

#include <QFrame>
#include <QButtonGroup>

class QPushButton;

class ConceptRail : public QFrame
{
    Q_OBJECT
public:
    explicit ConceptRail(QWidget* parent = nullptr);
signals:
    void navItemSelected(const QString& section);
private:
    void buildNavButtons();

    QButtonGroup* m_navGroup = nullptr;
};

#endif // CONCEPTRAIL_H
