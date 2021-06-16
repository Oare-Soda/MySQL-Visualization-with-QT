#include "data.h"
#include "ui_data.h"
#include <add.h>
#include "ui_add.h"
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QSqlTableModel>
#include <QMessageBox>
#include <QTextCodec>
#include "widget.h"
UserSqlTableModel::UserSqlTableModel(QObject *parent,QSqlDatabase db) :
    QSqlTableModel(parent,db)
{
    m_nStart = 0;
}
QVariant UserSqlTableModel::headerData(int section, Qt::Orientation orient, int role) const
{
  if (orient == Qt::Vertical && role == Qt::DisplayRole)
    return section + m_nStart;

  return QSqlTableModel::headerData(section,orient,role);
}

Data::Data(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Data)
{
    ui->setupUi(this);
    this->resize(2300,1500);
    //连接数据库
    qDebug()<<QSqlDatabase::drivers();
    QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setUserName("root");
    db.setPassword("root");
    db.setDatabaseName("equipments");
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("GBK"));

    if(!db.open())
    {
        QMessageBox::warning(this,"错误",db.lastError().text());
        return;
    }
    //显示
    //ifEnableEdit=true;
    model=new QSqlTableModel(this);
    model->setTable("equip");
    ui->tableView->setModel(model);
    ui->tableView->setEnabled(true);
    model->select();
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    //connect(ui->buttonAdd,&QPushButton::clicked,this,&Data::addinfomation);
    //qDebug()<<isEnableEdit;

    //修改权限
    //memo:如果使用创建全局变量的方法在登录界面就会运行这个构造函数，无法从登录情况判断权限，如果new一个指针却建在this上那就会随着作用域结束而释放，从而闪退，改成()就ok
    ui->buttonAdd->setEnabled(auth::isEnableEdit);
    ui->btn_del->setEnabled(auth::isEnableEdit);
    ui->btn_submit->setEnabled(auth::isEnableEdit);
    Total=model->rowCount();
    QString totalnum=QString::number(Total);
    ui->totalRecord->setText(totalnum);

}

Data::~Data()
{
    delete ui;
}
//button:增加数据
void Data::addinfomation()
{

    QSqlRecord record=model->record();
    int row=model->rowCount();
    //将主键设置为自增才可以成功submit
    record.setValue(1,add.ui->qcmc_text->text());
    record.setValue(2,add.ui->qcgy_text->text());
    record.setValue(3,add.ui->qctz_text->text());
    record.setValue(4,add.ui->swmx_text->text());
    record.setValue(5,add.ui->sjbg_text->text());
    record.setValue(6,add.ui->bz_text->text());
    model->insertRecord(row,record);

    //修改总计条数
    Total=model->rowCount();
    QString totalnum=QString::number(Total);
    ui->totalRecord->setText(totalnum);

    model->submitAll();
}

void Data::on_buttonAdd_clicked()
{

    add.show();
    //connect是跳出界面再传数据的灵魂
    connect(add.ui->addbutton,&QPushButton::clicked,this,&Data::addinfomation);
}



//button:删除数据
void Data::on_btn_del_clicked()
{
    //1.获取选中的模块
    QItemSelectionModel *sModel = ui->tableView->selectionModel();
    //2.获取选中的行号
    QModelIndexList list=sModel->selectedRows();
    //3.删除所选中的区域
    for(int i=0;i<list.size();i++)
    {
        model->removeRow(list.at(i).row());
    }

}
//button:修改数据
void Data::on_btn_submit_clicked()
{
    model->submitAll();//提交全部修改
    //model->select();
    //修改总计条数
    Total=model->rowCount();
    QString totalnum=QString::number(Total);
    ui->totalRecord->setText(totalnum);
}

//查询——重置
void Data::on_fbtn_reset_clicked()
{
    //清空查询栏
    ui->fline_text->clear();
    ui->currentPage->clear();
    //重新显示完整表
    model=new QSqlTableModel(this);
    model->setTable("equip");
    ui->tableView->setModel(model);
    model->select();
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
}



void Data::on_fbtn_search_clicked()
{
    QString find_text=ui->fline_text->text();
    QString current=ui->comboBox->currentText();
    QString str = QString("%1='%2'").arg(current).arg(find_text);
            model->setFilter(str);
            model->select();
}
void Data::pageSetting()
{
    QString filter=QString("1=1 limit %1,%2;").arg(pageStart).arg(pageSize);
    model->setFilter(filter);
    QString now=QString::number(curPage);
    ui->currentPage->setText(now);
    model->submitAll();
    model->select();
}
void Data::on_page_first_clicked()
{
    pageStart=0;
    curPage=1;
    pageSetting();
}

void Data::on_page_last_clicked()
{
    pageStart=(Total/pageSize)*pageSize;
    curPage=Total/pageSize+1;
    pageSetting();
}

void Data::on_page_pre_clicked()
{
    if(curPage==1) return;
    curPage-=1;
    pageStart=(curPage-1)*pageSize;
    pageSetting();
}

void Data::on_page_next_clicked()
{
    if(curPage==(Total/pageSize+1)) return;
    curPage++;
    pageStart=(curPage-1)*pageSize;
    pageSetting();
}

void Data::on_jump_to_clicked()
{
    curPage=ui->jumpPage->text().toInt();
    pageStart=(curPage-1)*pageSize;
    pageSetting();
}
