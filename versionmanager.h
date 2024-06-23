#ifndef VERSIONMANAGER_H
#define VERSIONMANAGER_H

#include <QMainWindow>
#include <QPushButton>
#include <QRadioButton>
#include <QVBoxLayout>
#include <QProcess>
#include <QDir>
#include <QMessageBox>
#include <QSettings>

QT_BEGIN_NAMESPACE
namespace Ui { class VersionManager; }
QT_END_NAMESPACE

class VersionManager : public QMainWindow
{
    Q_OBJECT

public:
    VersionManager(QWidget *parent = nullptr);
    ~VersionManager();

private slots:
    void onApplyClicked();
    void onCancelClicked();
    void onUpdateClicked();
    void onRadioButtonClicked();

private:
    Ui::VersionManager *ui;
    QVBoxLayout *layout;
    QList<QRadioButton*> javaVersions;
    QString selectedJavaVersion;

    void loadJavaVersions();
    QStringList detectJavaVersions();
};

#endif // VERSIONMANAGER_H
