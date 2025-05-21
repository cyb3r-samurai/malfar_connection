#include "c_window.h"
#include "ui_c_window.h"

C_window::C_window(QString& number, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::C_window)
    , number(number)
{
    ui->setupUi(this);

    ui->cb_pol->addItem("прававя круговая", QVariant(1));
    ui->cb_pol->addItem("левая круговая", QVariant(2));
    ui->cb_pol->addItem("вертикальная", QVariant(3));
    ui->cb_pol->addItem("горизонтальная", QVariant(4));
    ui->cb_pol->addItem("линейная +45%", QVariant(5));
    ui->cb_pol->addItem("линейная -45%", QVariant(6));

    ui->dateTimeEdit->setDateTime(QDateTime::currentDateTime());
    ui->dateTimeEdit_2->setDateTime(QDateTime::currentDateTime());

    for(quint64 i = 0; i < number.toInt(); ++i) {
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(QString::number(3600 - (i%3600))));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem("200"));
    }

}

C_window::~C_window()
{
    delete ui;
}

void C_window::on_pushButton_clicked()
{
    QString az = ui->ln_az->text();
    QString angle = ui->ln_angl->text();
    if((az.isEmpty()) || (angle.isEmpty())) {
        return;
    }
    ui->tableWidget->insertRow(ui->tableWidget->rowCount());
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,
                             0,
                             new QTableWidgetItem(ui->ln_az->text()));
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,
                             1,
                             new QTableWidgetItem(ui->ln_angl->text()));
}

void C_window::on_pushButton_2_clicked()
{
    QModelIndexList selection = ui->tableWidget->selectionModel()->selectedRows();
    while(!selection.empty()) {
        ui->tableWidget->removeRow(selection[0].row());
        selection = ui->tableWidget->selectionModel()->selectedRows();
    }
}



void C_window::on_pushButton_3_clicked()
{
    Cel cel_;

    cel_.chanel_number = ui->ln_session->text().toUInt();
    auto data = ui->cb_pol->itemData(ui->cb_pol->currentIndex());
    cel_.polarization = data.toInt();
    cel_.ka_number = ui->lineEdit->text().toInt();
    float a = ui->ln_freq->text().toFloat();
    cel_.frequency = a;
    QDateTime time_start = ui->dateTimeEdit->dateTime();
    QDateTime time_end = ui->dateTimeEdit_2->dateTime();

    cel_.start_time = double(time_start.toSecsSinceEpoch()) / double (86400) + 25569;
    cel_.end_time = double(time_end.toSecsSinceEpoch()) / double(86400) + 25569;
    cel_.m = ui->tableWidget->rowCount();

    cel_.cel = new qint16*[cel_.m] ;
    for(quint16 i = 0; i < cel_.m; i++) {
        cel_.cel[i] = new qint16[2];
    }
    for(quint16 i = 0; i < cel_.m; i++) {
        cel_.cel[i][0] = ui->tableWidget->item(i,0)->text().toUInt();
        cel_.cel[i][1] = ui->tableWidget->item(i,1)->text().toUInt();
    }
    emit cel_created(cel_);
    C_window::close();
}

quint32 C_window::seconds_since_epoch(QDateTime &time)
{
    QDateTime epoch(QDate(2000, 1, 1), QTime(0, 0, 0), Qt::UTC);
    qint64 sec = time.toSecsSinceEpoch();
    qint64 epoch_sec = epoch.toSecsSinceEpoch();
    return sec - epoch_sec;
}

