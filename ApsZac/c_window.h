#ifndef C_WINDOW_H
#define C_WINDOW_H

#include <Message.h>

#include <QDialog>
#include <QString>

namespace Ui {
class C_window;
}

class C_window : public QDialog
{
    Q_OBJECT

public:
    explicit C_window(QString& num, QWidget *parent = nullptr);
    ~C_window();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

signals:
    void cel_created(Cel& cel);
private:
    Ui::C_window *ui;
    QString &number;

    quint32 seconds_since_epoch(QDateTime &time);

};

#endif // C_WINDOW_H
