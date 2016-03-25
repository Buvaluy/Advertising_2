#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "func.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    Func *obj;
    bool loadFinished;
    QMessageBox msg;
    QStringList listAlbum;
    QStringList listGroup;
    QString sendText;
    QString url;
    QMovie *movie;
    QString wayToFolder;
    QString blackDor;
    bool blackDorB = false;
    bool withPauseBeforePaste;



private slots:
    void on_actionStart_triggered();

    void on_webView_loadFinished(bool arg1);

    void on_lineEditAddAlbum_returnPressed();

    void on_lineEditAddGroup_returnPressed();

    void on_pushButtonLoadAlbum_clicked();

    void on_pushButtonSaveAlbum_clicked();

    void on_pushButtonClearAlbum_clicked();

    void on_pushButtonLoadGroup_clicked();

    void on_pushButtonSaveGroup_clicked();

    void on_pushButtonClearGroup_clicked();

    void on_webView_loadStarted();

    void waitPause();

    void on_checkBox_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;

protected:
   virtual void keyPressEvent(QKeyEvent *event);
    virtual void keyReleaseEvent();
   virtual void closeEvent(QCloseEvent *);
};

#endif // MAINWINDOW_H
