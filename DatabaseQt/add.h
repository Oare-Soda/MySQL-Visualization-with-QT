#ifndef ADD_H
#define ADD_H

#include <QDialog>
#include <QFileDialog>
namespace Ui {
class Add;
}

class Add : public QDialog
{
    Q_OBJECT

public:
    explicit Add(QWidget *parent = 0);
    ~Add();

    bool isClicked = false;
    //bool isEnabled;
    void on_addbutton_clicked();
    Ui::Add *ui;
private slots:


    void on_qctz_file_clicked();

    void on_swmx_file_2_clicked();

    void on_sjbg_file_clicked();

private:

};

#endif // ADD_H
