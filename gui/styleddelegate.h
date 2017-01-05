#ifndef STYLEDDELEGATE_H
#define STYLEDDELEGATE_H

#include <QStyledItemDelegate>
#include <QBrush>
#include <QPainter>
#include "formain.h"

class StyledDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
       explicit StyledDelegate(QObject *parent = 0, AsmCommand *asmCommand = NULL);
       // чтобы управлять отрисовкой нужно переопределить этот метод
       void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
private:
       AsmCommand *asmCommand;
};

#endif // STYLEDDELEGATE_H
