#ifndef USERSQLTABLEMODEL_H
#define USERSQLTABLEMODEL_H
#include <QSqlTableModel>
class UserSqlTableModel : public QSqlTableModel
{
    Q_OBJECT
public:
    explicit UserSqlTableModel(QObject *parent = 0,QSqlDatabase db = QSqlDatabase() );

    void setStart(int start){this->m_nStart = start;}
    int getStart(){return this->m_nStart;}
public:
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
private:
    int m_nStart;   //记录数据起始id
};

#endif // USERSQLTABLEMODEL_H