#include "versionmanager.h"
#include "ui_versionmanager.h"

VersionManager::VersionManager(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::VersionManager)
{
    ui->setupUi(this);

    // Load Java versions and add radio buttons
    loadJavaVersions();

    // Configure button layout
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(ui->verticalLayout);
    mainLayout->addLayout(ui->buttonLayout);
    ui->centralwidget->setLayout(mainLayout);

    connect(ui->btnApply, &QPushButton::clicked, this, &VersionManager::onApplyClicked);
    connect(ui->btnCancel, &QPushButton::clicked, this, &VersionManager::onCancelClicked);
    connect(ui->btnUpdate, &QPushButton::clicked, this, &VersionManager::onUpdateClicked);
}

VersionManager::~VersionManager()
{
    delete ui;
}

void VersionManager::loadJavaVersions()
{
    QStringList versions = detectJavaVersions();

    foreach (QString version, versions) {
        QRadioButton *radioButton = new QRadioButton(version);
        ui->verticalLayout->addWidget(radioButton);
        javaVersions.append(radioButton);

        connect(radioButton, &QRadioButton::clicked, this, &VersionManager::onRadioButtonClicked);
    }
}

QStringList VersionManager::detectJavaVersions()
{
    QStringList javaDirs;
    QStringList javaVersions;

    // Common directories where Java might be installed
    javaDirs << "C:/Program Files/Java" << "C:/Program Files (x86)/Java";

    // Verifica variáveis de ambiente padrão do Java
    QString javaHome = qgetenv("JAVA_HOME");
    if (!javaHome.isEmpty()) {
        javaVersions << javaHome;
    }

    foreach (QString dir, javaDirs) {
        QDir javaDir(dir);
        if (javaDir.exists()) {
            QStringList versions = javaDir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
            foreach (QString version, versions) {
                javaVersions << javaDir.absoluteFilePath(version);
            }
        }
    }

    // Detecta JDK instalados via PATH
    QProcess process;
    process.start("where java");
    process.waitForFinished();
    QString output = process.readAllStandardOutput();
    QStringList paths = output.split("\r\n", Qt::SkipEmptyParts);

    foreach (QString path, paths) {
        QFileInfo fileInfo(path);
        QString javaPath = fileInfo.absolutePath();
        if (!javaVersions.contains(javaPath)) {
            javaVersions << javaPath;
        }
    }

    return javaVersions;
}

void VersionManager::onRadioButtonClicked()
{
    foreach (QRadioButton *radioButton, javaVersions) {
        if (radioButton->isChecked()) {
            selectedJavaVersion = radioButton->text();
            break;
        }
    }
}

void VersionManager::onApplyClicked()
{
    if (!selectedJavaVersion.isEmpty()) {
        // Code to set the selected Java version system-wide
        QProcess::execute("setx JAVA_HOME " + selectedJavaVersion);
        QMessageBox::information(this, "Success", "Java version set to " + selectedJavaVersion);
    }
}

void VersionManager::onCancelClicked()
{
    close();
}

void VersionManager::onUpdateClicked()
{
    // Clear the current list
    qDeleteAll(javaVersions);
    javaVersions.clear();

    // Reload Java versions
    loadJavaVersions();
}
