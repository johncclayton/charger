#include <QDebug>
#include "channel_view_model.h"

ChannelViewModel::ChannelViewModel(QObject *parent) : QObject(parent), _cellViewState(CELLS) {
}

void ChannelViewModel::setCellState(CellViewState s) {
    if(s != _cellViewState) {
        _cellViewState = s;
        Q_EMIT cellStateChanged();
        qDebug() << "Cell state changed to:" << _cellViewState;
    }    
}

ChannelViewModel::CellViewState ChannelViewModel::cellState() const { 
    return _cellViewState;
}
          
