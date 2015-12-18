#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//#define IR_FUNC_TEST

QT_BEGIN_NAMESPACE
class QAction;
class QMenu;
class QToolBar;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event) Q_DECL_OVERRIDE;

private:
    // Setting Operating
    void readSettings();
    void writeSettings();

    // Create Window Components
    void createActions();
    void createMenus();
    void createToolBars();
    void createStatusBar();

    // Member Variable
    QMenu   *mainMenu;   // the Main Menu
    QAction *exitAct;       // Exit

    QMenu   *settingMenu;      // the Setting Menu
    QAction *basicSettingAct;   // Basic Setting

    QMenu   *helpMenu;   // the Help Menu
    QAction *helpAct;       // Help

    QToolBar *commToolBar; // the common used toolbar
private slots:
    void exitApp();
    void showBasicSetting();
    void showAbout();
};

#endif // MAINWINDOW_H
