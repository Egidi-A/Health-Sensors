#ifndef DASHBOARDSENSORIWIDGET_H
#define DASHBOARDSENSORIWIDGET_H

#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <QMessageBox>
#include <QMessageBox>
#include <QInputDialog>
#include <./MODELLO/modello.h>

class dashBoardSensoriWidget : public QWidget
{
    Q_OBJECT
public:
    QVBoxLayout* dashSensoriLayout = new QVBoxLayout();
    QLabel* labelSensori = new QLabel("Dashboard Sensori");
    QPushButton* addSensoreBPMButton = new QPushButton("Aggiungi Sensore BPM");
    QPushButton* addSensoreOssigenazioneButton = new QPushButton("Aggiungi Sensore Ossigenazione");
    QPushButton* addSensoreTemperaturaButton = new QPushButton("Aggiungi Sensore Temperatura");
    QPushButton* removeSensoreButton = new QPushButton("Rimuovi Sensore");
    QListWidget* listaSensori = new QListWidget();
    QLineEdit* searchBar = new QLineEdit();

    explicit dashBoardSensoriWidget(QWidget *parent = nullptr);

    int showRemoveDialog();
    QString showAddBPMDialog();
    QString showAddOssigenazioneDialog();
    QString showAddTemperaturaDialog();

    void updateListaWidget(std::vector<QString> newWidgets);
};

#endif // DASHBOARDSENSORIWIDGET_H
