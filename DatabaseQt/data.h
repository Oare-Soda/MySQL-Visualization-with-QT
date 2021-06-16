#ifndef DATA_H
#define DATA_H

#include <QWidget>
#include <QSqlTableModel>
#include <add.h>
#include <ui_add.h>
#include "usersqltablemodel.h"
#include <QString>
#include <ui_widget.h>
namespace Ui {
class Data;
}

class Data : public QWidget
{
    Q_OBJECT

public:
    explicit Data(QWidget *parent = 0);
    ~Data();
    Add add;
    QSqlTableModel *model;
    bool isEnableEdit=true;
    void addinfomation();
    void pageSetting();
    int Total;           //总记录数
    int curPage;     //当前页码
    int pageSize=5;      //每页显示条数(limit语句参数)
    int pageStart;       //起始记录数(limit语句参数)


private slots:
    void on_buttonAdd_clicked();
    void on_btn_submit_clicked();
    void on_btn_del_clicked();
    void on_fbtn_reset_clicked();
    void on_fbtn_search_clicked();


    void on_page_first_clicked();

    void on_page_last_clicked();

    void on_page_pre_clicked();

    void on_page_next_clicked();

    void on_jump_to_clicked();

private:
    Ui::Data *ui;

};

#endif // DATA_H
