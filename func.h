#ifndef FUNC_H
#define FUNC_H

#include <qdebug.h>
#include <QMessageBox>
#include <QFileDialog>
#include <QApplication>
#include <QtGui>
#include <stdio.h>
#include <stdlib.h>
#include <QListWidget>
#include <QStatusBar>
#include <QFile>
#include <QTimer>
#include <QEventLoop>
#include <QDesktopWidget>
#include <QWebView>
#include <QProgressBar>
#include <QLabel>


#include <opencv2/imgproc/imgproc.hpp>

#include <opencv2/core/core_c.h>

#include <opencv/highgui.h>

#include <opencv/cv.h>

#include <opencv2/nonfree/features2d.hpp>
#include <opencv2/nonfree/nonfree.hpp>

#include <opencv2/highgui/highgui_c.h>

#include <opencv2/highgui/highgui.hpp>


using namespace std;
using namespace cv;

class Func
{
public:
    Func();
    Func(QWidget *objMainWindow, QWebView *webView, QListWidget *widgetAlbum, QListWidget *widgetGroup,
         QStringList *listAlbum ,QStringList *listGroup, QString *sendText,
         QStatusBar *statusBar, bool *loadFin,QProgressBar *progressBar, QLabel *labelPause, QString wayToFolder,
         bool *withPauseBeforePaste);
    ~Func();


    void loadFile(QWidget *objMainWindow, QStringList &list, QStatusBar *bar);
    void saveFile(QWidget *objMainWindow, QStringList &list, QStatusBar *bar);
    void autoLoadFile();
    void showList(QListWidget *widget, QStringList &list);
    bool searchEnter();
    void useArrow();
    void usePaste();
    void startSender();
    void test();
    void mySleep(int time);
    void doSnapShot();
    void setBuffer(QString buff);
    bool searchCaptha();


    QMessageBox msg;
    QEventLoop wait;
    QWebView *webView;
    QWidget *objMainWindow;
    QStatusBar *statusBar;
    QListWidget *widgetGroup;
    QListWidget *widgetAlbum;
    QStringList *listAlbum;
    QStringList *listGroup;
    QProgressBar *progressBar;
    QLabel *labelPause;
    QString *sendText;
    QString wayToFolder;
    int xPosCursor;
    int yPosCursor;
    int xCorectPos;
    int yCorectPos;
    bool *loadFin;
    bool pauseSend;
    bool *withPauseBeforePaste;
    IplImage* templ = 0;
    IplImage* templCaptha = 0;

    bool getPauseSend() const;
    void setPauseSend(bool value);
    void setCorectPos(int x, int y);
};

#endif // FUNC_H
