#include "add.h"
#include "ui_add.h"
#include "data.h"
#include <QCloseEvent>
#include <QString>
Add::Add(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Add)
{
    ui->setupUi(this);
    this->resize(800,600);

}

Add::~Add()
{
    delete ui;
}

void Add::on_addbutton_clicked()
{
    isClicked=true;
    close();
}

void Add::on_qctz_file_clicked()
{
    QString filename=QFileDialog::getOpenFileName(this,tr("文件选择"),"",tr("文本文件(*txt);;所有类型(*.*)"));
    ui->qctz_text->setText(filename);
}

void Add::on_swmx_file_2_clicked()
{
    QString filename=QFileDialog::getOpenFileName(this,tr("文件选择"),"",tr("文本文件(*txt);;所有类型(*.*)"));
    ui->swmx_text->setText(filename);
}

void Add::on_sjbg_file_clicked()
{
    QString filename=QFileDialog::getOpenFileName(this,tr("文件选择"),"",tr("文本文件(*txt);;所有类型(*.*)"));
    ui->sjbg_text->setText(filename);
}
