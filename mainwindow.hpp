#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QtWidgets>

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        MainWindow(int, int, QString);
        ~MainWindow();

        void addMenu();

    public slots:
        void createNewFile();
        void createNewProject();
        void openFile();
        void openProject();

    private:

        QWidget *createTabEditor();

        int m_width;
        int m_height;
        QString m_title;


        // Tabs of editor
        QTabWidget *m_tabList;

        QTextEdit *m_editor;

        //MenuBar vars

        //Menu File
        QAction *m_actionNewProject;
        QAction *m_actionNewFile;
        QAction *m_actionOpen;
        QAction *m_actionRecent;
        QAction *m_actionSave;
        QAction *m_actionSaveAs;
        QAction *m_actionPrint;
        QAction *m_actionExit;

        //Menu Edit
        QAction *m_actionUndo;
        QAction *m_actionRedo;
        QAction *m_actionCut;
        QAction *m_actionCopy;
        QAction *m_actionPaste;
        QAction *m_actionSelectAll;
        QAction *m_actionRemove;
        QAction *m_actionDelete;
        QAction *m_actionFindeReplace;
        QAction *m_actionPreferences;

        //Menu View
        QAction *m_actionLeftSide;
        QAction *m_actionRightSide;
        QAction *m_actionOutput;
        QAction *m_actionTerminal;
        QAction *m_actionWordWrap;

        //Menu Build
        QAction *m_actionBuild;
        QAction *m_actionDeploy;
        QAction *m_actionDebug;
        QAction *m_actionClean;
        QAction *m_actionRun;
        QAction *m_actionRunConfiguration;

        //Menu Tools
        QAction *m_actionEncoding;
        QAction *m_actionTheme;
        QAction *m_actionFontPolice;
        QAction *m_actionLanguage;

        //Menu Help
        QAction *m_actionFAQ;
        QAction *m_actionGuideTour;
        QAction *m_actionAbout;
        QAction *m_actionContact;



        QVBoxLayout *m_leftSidebarVerticalBox;
};
#endif // MAINWINDOW_HPP


