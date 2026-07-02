#ifndef FORMGROUP_H
#define FORMGROUP_H

#include <QWidget>

class QLabel;
class QLineEdit;

class FormGroup : public QWidget
{
    Q_OBJECT
public:
    explicit FormGroup(const QString &label,
                       const QString &placeholder,
                       QWidget *parent = nullptr);
    QString getText() const;

private:
    QLabel*     m_label     = nullptr;
    QLineEdit*  m_data      = nullptr;
};

#endif // FORMGROUP_H
