#include "styleddelegate.h"

StyledDelegate::StyledDelegate(QObject *parent, AsmCommand *asmCommand) :
    QStyledItemDelegate(parent)
{
    this->asmCommand = asmCommand;
}

void StyledDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (asmCommand != NULL && asmCommand[index.row()].breakePointIsSet) {
        //получаем текущую кисть, которой ячейка была бы зарисована, если бы мы не влезли в процесс
        //смешиваем цвета (в миксе еще устанавливается альфа канал)
        QBrush brush = option.backgroundBrush;
        QColor color = QColor(255, 200, 128);

        //устанавливаем новый цвет и обязательно тип кисти (она изначально выставлена в None)
        brush.setColor(color);
        brush.setStyle(Qt::SolidPattern); // Qt::BrushStyle::SolidPattern

        //сохраняем состояние полотна, рисуем фон, восстанавливаем полотно
        painter->save();
        painter->fillRect(option.rect, brush);
        painter->restore();

        //здесь дорисовываются стандартные вещи вроде текста, которые берется из модели
        // ...
        QPen pen(QColor( 170,170,170 ));
        painter->save();
        painter->setPen(pen);
        painter->drawRect(option.rect.x(), option.rect.y(), option.rect.width()-1, option.rect.height()-1);
        painter->restore();
        //Получаем размер области, на которой будет отображаться текст
        //QRect textRect = subElementRect(SE_ItemViewItemText, option, w);
        QRect textRect = option.rect;

        //Сдвигаем немного, чтобы текст не "прилипал" к краям ячейки
        textRect.setX(textRect.x() + 5);
        textRect.setY(textRect.y() + 5);
        if (!index.data().toString().isEmpty()) {
            painter->drawText(textRect, index.data().toString());
        }
    } else {
        QStyledItemDelegate::paint( painter, option, index );
    }
}




