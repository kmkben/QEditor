#include "mainwindow.hpp"

#include <QCoreApplication>
#include <QApplication>
#include <QLocale>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QApplication::setOrganizationName("Kemke");
    QApplication::setOrganizationDomain("kemke-company.com");
    QApplication::setApplicationName("KemEditor");

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "QEditor_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    MainWindow window(1024, 780, "QEditor");
    window.show();
    return a.exec();
}

