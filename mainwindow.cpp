#include "mainwindow.hpp"

MainWindow::MainWindow(int w, int h, QString t) : m_width(w), m_height(h), m_title(t)
{
    addMenu();

    QWidget *centralWidget = new QWidget();

    setWindowTitle(m_title);
    resize(m_width, m_height);

    QHBoxLayout *mainLayout = new QHBoxLayout();

    QGroupBox *leftSidebarGroupBox = new QGroupBox("Files and Projects");
        QVBoxLayout *m_leftSidebarVerticalBox = new QVBoxLayout();
    leftSidebarGroupBox->setLayout(m_leftSidebarVerticalBox);

    //QGroupBox *editorGroupBox = new QGroupBox();
    QHBoxLayout *editorLayout = new QHBoxLayout();
        m_tabList = new QTabWidget();
        m_tabList->setTabsClosable(true);
        m_tabList->addTab(createTabEditor(), tr("Untitled"));
    editorLayout->addWidget(m_tabList);
    //editorGroupBox->setLayout(editorLayout);

    mainLayout->addWidget(leftSidebarGroupBox);
    mainLayout->addLayout(editorLayout);

    centralWidget->setLayout(mainLayout);

    connect(m_actionExit, SIGNAL(triggered(bool)), qApp, SLOT(quit()));
    connect(m_tabList->tabBar(), &QTabBar::tabCloseRequested, m_tabList->tabBar(), &QTabBar::removeTab);

    setCentralWidget(centralWidget);
}

MainWindow::~MainWindow()
{
}

void MainWindow::addMenu()
{
    //Menu File
    QMenu *menuFile = menuBar()->addMenu("&File");

    m_actionNewProject = new QAction("New Project", this);
    m_actionNewProject->setIcon(QIcon("icons/add-document.png"));
    m_actionNewProject->setShortcut(QKeySequence("Ctrl+Shift+N"));

    m_actionNewFile = new QAction("New File", this);
    m_actionNewFile->setIconVisibleInMenu(true);
    QIcon icon_new = QIcon("icons/add-document.png");
    m_actionNewFile->setIcon(icon_new);
    m_actionNewFile->setShortcut(QKeySequence("Ctrl+N"));
    connect(m_actionNewFile, SIGNAL(triggered()), this, SLOT(createNewFile()));

    m_actionOpen = new QAction("Open", this);
    m_actionOpen->setIcon(QIcon("icons/open-folder.png"));
    m_actionOpen->setShortcut(QKeySequence("Ctrl+O"));
    connect(m_actionOpen, SIGNAL(triggered()), this, SLOT(openFile()));

    m_actionRecent = new QAction("Recent", this);
    m_actionRecent->setIcon(QIcon("icons/recent.png"));

    m_actionSave = new QAction("Save", this);
    m_actionSave->setIcon(QIcon("icons/save.png"));
    m_actionSave->setShortcut(QKeySequence("Ctrl+S"));

    m_actionSaveAs = new QAction("Save as", this);
    m_actionSaveAs->setIcon(QIcon("icons/saveas.png"));
    m_actionSaveAs->setShortcut(QKeySequence("Ctrl+Shift+S"));

    m_actionPrint = new QAction("Print", this);
    m_actionPrint->setIcon(QIcon("icons/printer.png"));
    m_actionPrint->setShortcut(QKeySequence("Ctrl+P"));


    m_actionExit = new QAction("Exit", this);
    m_actionExit->setShortcut(QKeySequence("Ctrl+Q"));
    m_actionExit->setIcon(QIcon("icons/exit.png"));

    menuFile->addAction(m_actionNewProject);
    menuFile->addAction(m_actionNewFile);
    menuFile->addAction(m_actionOpen);
    menuFile->addAction(m_actionRecent);
    menuFile->addSeparator();
    menuFile->addAction(m_actionSave);
    menuFile->addAction(m_actionSaveAs);
    menuFile->addSeparator();
    menuFile->addAction(m_actionPrint);
    menuFile->addSeparator();
    menuFile->addAction(m_actionExit);

    //Menu Edit

    QMenu *menuEdit = menuBar()->addMenu("&Edit");

    m_actionUndo = new QAction("Undo", this);
    m_actionUndo->setIcon(QIcon("icons/undo.png"));
    m_actionUndo->setShortcut(QKeySequence("ctrl+Z"));

    m_actionRedo = new QAction("Redo", this);
    m_actionRedo->setIcon(QIcon("icons/redo.png"));
    m_actionRedo->setShortcut(QKeySequence("ctrl+Shift+Z"));

    m_actionCut = new QAction("Cut", this);
    m_actionCut->setIcon(QIcon("icons/cut.png"));
    m_actionCut->setShortcut(QKeySequence("ctrl+X"));

    m_actionCopy = new QAction("Copy", this);
    m_actionCopy->setIcon(QIcon("icons/copy.png"));
    m_actionCopy->setShortcut(QKeySequence("ctrl+C"));

    m_actionPaste = new QAction("Paste", this);
    m_actionPaste->setIcon(QIcon("icons/paste.png"));
    m_actionPaste->setShortcut(QKeySequence("ctrl+V"));

    m_actionRemove = new QAction("Remove", this);
    m_actionRemove->setShortcut(QKeySequence("Del"));

    m_actionDelete = new QAction("Delete", this);
    m_actionDelete->setShortcut(QKeySequence("ctrl+D"));

    m_actionFindeReplace = new QAction("Find/Replace", this);
    m_actionFindeReplace->setShortcut(QKeySequence("ctrl+F"));

    m_actionPreferences = new QAction("Preferences", this);
    m_actionPreferences->setIcon(QIcon("icons/settings.png"));
    //m_actionPreferences->setShortcut(QKeySequence("ctrl+C"));

    menuEdit->addAction(m_actionUndo);
    menuEdit->addAction(m_actionRedo);
    menuEdit->addSeparator();
    menuEdit->addAction(m_actionCut);
    menuEdit->addAction(m_actionCopy);
    menuEdit->addAction(m_actionPaste);
    menuEdit->addSeparator();
    menuEdit->addAction(m_actionRemove);
    menuEdit->addAction(m_actionDelete);
    menuEdit->addSeparator();
    menuEdit->addAction(m_actionFindeReplace);
    menuEdit->addSeparator();
    menuEdit->addAction(m_actionPreferences);


    //Menu View
    QMenu *menuView = menuBar()->addMenu("&View");

    m_actionLeftSide = new QAction("Show Left Sidebar", this);
    m_actionLeftSide->setShortcut(QKeySequence("Ctrl+O"));
    m_actionLeftSide->setIcon(QIcon("icons/left-sidebar.png"));

    m_actionRightSide = new QAction("Show Right Sidebar", this);
    m_actionRightSide->setShortcut(QKeySequence("Ctrl+Shift+O"));
    m_actionRightSide->setIcon(QIcon("icons/right-sidebar.png"));

    m_actionOutput = new QAction("Output", this);

    m_actionTerminal = new QAction("Terminal", this);
    m_actionTerminal->setShortcut(QKeySequence("Ctrl+`"));
    m_actionTerminal->setIcon(QIcon("icons/terminal.png"));

    m_actionWordWrap = new QAction("Word wrap", this);
    m_actionWordWrap->setShortcut(QKeySequence("Ctrl+B"));

    menuView->addAction(m_actionLeftSide);
    menuView->addAction(m_actionRightSide);
    menuView->addSeparator();
    menuView->addAction(m_actionOutput);
    menuView->addSeparator();
    menuView->addAction(m_actionTerminal);
    menuView->addSeparator();
    menuView->addAction(m_actionWordWrap);

    //Menu Build
    QMenu *menuBuild = menuBar()->addMenu("&Build");

    m_actionBuild = new QAction("Build Project", this);
    m_actionBuild->setShortcut(QKeySequence("Ctrl+Shift+B"));
    m_actionBuild->setIcon(QIcon("icons/build.png"));

    m_actionDeploy = new QAction("Deploy", this);
    //m_actionDeploy->setShortcut(QKeySequence("Ctrl+Shift+B"));
    m_actionDeploy->setIcon(QIcon(":/icons/icons/deploy.png"));

    m_actionDebug = new QAction("Debug", this);
    m_actionDebug->setShortcut(QKeySequence("F5"));
    m_actionDebug->setIcon(QIcon("icons/debug.png"));

    m_actionClean = new QAction("Clean", this);
    //m_actionClean->setShortcut(QKeySequence("Ctrl+Shift+B"));
    m_actionClean->setIcon(QIcon("icons/clean.png"));

    m_actionRun = new QAction("Run", this);
    m_actionRun->setShortcut(QKeySequence("Ctrl+R"));
    m_actionRun->setIcon(QIcon("icons/run.png"));

    m_actionRunConfiguration = new QAction("Run Configuration", this);

    menuBuild->addAction(m_actionBuild);
    menuBuild->addAction(m_actionDeploy);
    menuBuild->addAction(m_actionDebug);
    menuBuild->addAction(m_actionClean);
    menuBuild->addSeparator();
    menuBuild->addAction(m_actionRun);
    menuBuild->addAction(m_actionRunConfiguration);

    //Menu Tools
    QMenu *menuTools = menuBar()->addMenu("&Tools");

    m_actionEncoding = new QAction("Encoding", this);

    m_actionTheme = new QAction("Themes", this);

    m_actionFontPolice = new QAction("Change the police", this);

    m_actionLanguage = new QAction("Language", this);

    menuTools->addAction(m_actionEncoding);
    menuTools->addAction(m_actionTheme);
    menuTools->addAction(m_actionFontPolice);
    menuTools->addAction(m_actionLanguage);

    //Menu Help
    QMenu *menuHelp = menuBar()->addMenu("&Help");

    m_actionFAQ = new QAction("FAQ", this);
    m_actionFAQ->setIcon(QIcon("icons/faq.png"));

    m_actionGuideTour = new QAction("Guide Tour", this);

    m_actionAbout = new QAction("About KemEdit", this);
    m_actionAbout->setIcon(QIcon("icons/about.png"));

    m_actionContact = new QAction("Contact", this);

    menuHelp->addAction(m_actionFAQ);
    menuHelp->addAction(m_actionGuideTour);
    menuHelp->addSeparator();
    menuHelp->addAction(m_actionAbout);
    menuHelp->addSeparator();
    menuHelp->addAction(m_actionContact);

    QToolBar *toolBar = addToolBar("File");

    QFontComboBox *choicePolice = new QFontComboBox;

    toolBar->addAction(m_actionNewFile);
    toolBar->addAction(m_actionOpen);
    toolBar->addAction(m_actionSave);
    toolBar->addAction(m_actionSaveAs);
    toolBar->addSeparator();
    toolBar->addAction(m_actionUndo);
    toolBar->addAction(m_actionRedo);
    toolBar->addAction(m_actionCut);
    toolBar->addAction(m_actionCopy);
    toolBar->addAction(m_actionPaste);
    toolBar->addSeparator();
    toolBar->addWidget(choicePolice);
    toolBar->addSeparator();
    //toolBar->addAction(m_actionExit);

    QStatusBar *statusBar = this->statusBar();

    statusBar->addAction(m_actionLeftSide);
    statusBar->addAction(m_actionOutput);
    statusBar->addAction(m_actionTerminal);
    statusBar->addAction(m_actionRightSide);

    // setStatusBar(statusBar);
}


QWidget *MainWindow::createTabEditor()
{
    QWidget *tabEditor = new QWidget();
    m_editor = new QTextEdit();
    m_editor->setFocus();

    QVBoxLayout *editorLayout = new QVBoxLayout();
    editorLayout->setContentsMargins(0, 0, 0, 0);
    editorLayout->addWidget(m_editor);
    tabEditor->setLayout(editorLayout);

    return tabEditor;
}


/*
 *
 * Public SLOTS
 *
 */

void MainWindow::createNewFile()
{
    int currentIdex = m_tabList->addTab(createTabEditor(), tr("Untitled*"));
    m_tabList->setCurrentIndex(currentIdex);
}

void MainWindow::createNewProject()
{

}

void MainWindow::openFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open a file", QString(), "All files(*.txt *.c *cpp *h *hpp *.html *htm *html.twig *.css *.scss *.php *.qml *.qrc)");

    QFile file(fileName);

    if (file.open(QIODevice::ReadOnly))
    {
        m_editor->setText(file.readAll());
    }
}

void MainWindow::openProject()
{

}

