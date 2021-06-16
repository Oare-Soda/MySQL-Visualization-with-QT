#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QDebug>
#include <QMessageBox>
#include <data.h>
#include <add.h>
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    //Data data;
    //Add add;
private slots:
    void on_btn_sure_clicked();

    void on_btn_clear_clicked();

private:
    Ui::Widget *ui;
};
class auth
{
public:
    static bool isEnableEdit;
};

#endif // WIDGET_H
