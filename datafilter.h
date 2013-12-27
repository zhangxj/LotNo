#ifndef DATAFILTER_H
#define DATAFILTER_H

#include <QObject>
#include <QStringList>
#include <QDebug>
#include <QMap>
#include <QSet>
#include "database.h"

class DataFilter : public QObject
{
    Q_OBJECT
    //Q_PROPERTY(QString inerString READ getString WRITE setString NOTIFY stringChanged)

public:
    explicit DataFilter(QObject *parent = 0);

signals:
    void stringChanged();
    void lotNoListChanged();
    void blockNoListChanged();
    void snListChanged();

public slots:
    QString getString();
    QStringList getLotNoList();
    QStringList getBlockNoList();
    QStringList getSnList();
    void setScan(QString flag, QString no);
    void searchData(QString flag, QString no);
    void selectItem(QString flag, QString no);
    void OnAbout();
    void clearData();

public:
    Database        m_DB;
    QString         m_string;
    QStringList     m_LotNoList;
    QStringList     m_BlockNoList;
    QStringList     m_SnList;

    QString m_CurrentLotNo;
    QString m_CurrentBlockNo;

    QMap< QString, QSet<QString> > m_LotNoMap;
    QMap< QString, QSet<QString> > m_BlockNoMap;

};

#endif // DATAFILTER_H
