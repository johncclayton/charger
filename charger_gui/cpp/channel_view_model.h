#ifndef CHANNEL_VIEWMODEL_H
#define CHANNEL_VIEWMODEL_H

#include <QObject>

class ChannelViewModel : public QObject
{
    Q_OBJECT
public:
    explicit ChannelViewModel(QObject *parent = 0);
    
    enum CellViewState {
        CELLS,
        RESISTANCE,
        INFO
    };
    
    Q_ENUMS(CellViewState)

    Q_PROPERTY(CellViewState cellState READ cellState WRITE setCellState NOTIFY cellStateChanged)    
signals:
    void cellStateChanged();
    
public slots:
    void setCellState(CellViewState s);
    
public:
    CellViewState cellState() const;
    
private:
    CellViewState _cellViewState;
    
};

#endif 
