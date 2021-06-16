#include "widget.h"
#include "ui_widget.h"
#include "data.h"
#include "add.h"
bool auth::isEnableEdit=false;
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->resize(700,500);

}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_btn_sure_clicked()
{

    if(ui->m_username->text()=="admin"&&ui->m_password->text()=="123")
    {

        auth::isEnableEdit=true;
        Data *data=new Data();
        qDebug()<<"管理员登陆成功";
        QMessageBox *ms=new QMessageBox(this);
        ms->about(this,"成功提示","管理员登录成功");
        data->show();
        this->close();

    }
    else if(ui->m_username->text()=="user"&&ui->m_password->text()=="123")
    {

        qDebug()<<"非管理员登陆成功";
        QMessageBox *ms=new QMessageBox(this);
        ms->about(this,"成功提示","非管理员登录成功");
        auth::isEnableEdit=false;
        Data *data=new Data();
        data->show();
        qDebug()<<data->isEnableEdit;
        this->close();
    }
    else
    {
        qDebug()<<"用户名或密码错误";
        QMessageBox *ms=new QMessageBox(this);
        ms->about(this,"失败提示","用户名或密码错误");
    }
}

void Widget::on_btn_clear_clicked()
{
    ui->m_password->clear();
    ui->m_username->clear();
}
