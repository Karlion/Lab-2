#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <textclient.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void assignWebClient(TextClient *ncl);

private slots:
    void on_bConnect_clicked();
public slots:
    void data_changed();
    void data_received();

private:
    Ui::MainWindow *ui;
    TextClient *cl;

};

#endif // MAINWINDOW_H
