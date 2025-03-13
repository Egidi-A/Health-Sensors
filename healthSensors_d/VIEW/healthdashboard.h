#ifndef HEALTHDASHBOARD_H
#define HEALTHDASHBOARD_H

#include <./MODELLO/modello.h>
#include "dashboardsensoriwidget.h"
#include "dashboardsimulazionewidget.h"
#include "dashboarddettagliwidget.h"

#include <QWidget>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QListWidget>
#include <QLineSeries>
#include <QChart>
#include <QChartView>
#include <QDialog>
#include <QInputDialog>
#include <QFileDialog>
#include <QMessageBox>

class Controller;

class healthDashboard : public QWidget
{
    Q_OBJECT
private:
    Controller* controller;

    QVBoxLayout* mainLayout = new QVBoxLayout();
    QMenu* fileBar = new QMenu("File");
    QMenu* sensoriBar = new QMenu("Sensori");
    QMenu* aggiungiSensore = new QMenu("Aggiungi Sensore");

    QMenu* simulazioniBar = new QMenu("Simulazioni");
    dashBoardSensoriWidget* dashSensoriWidget;
    dashboardSimulazioneWidget* dashSimulazioneWidget;
    dashboardDettagliWidget* dashDetailsWidget;
    Modello* modello;
    QHBoxLayout* dashboardLayout = new QHBoxLayout();

public:
    healthDashboard(Modello* model, int idSensore=-1, QWidget *parent = nullptr);
    ~healthDashboard();

    void setController(Controller* c);

    void addMenu(QVBoxLayout* mainLayout);
    void addDashSensori(Modello* model, QHBoxLayout* dashLayout);
    void addDashSimulazione(Modello* model, int idSensore, QHBoxLayout* dashLayout);
    void addDashDettagli(Modello* model, int idSensore, QHBoxLayout* dashLayout);

    dashBoardSensoriWidget* get_dashSensoriWidget() const;
    dashboardDettagliWidget* get_dashDettagliWidget() const;
    dashboardSimulazioneWidget* get_dashSimulazioneWidget() const;
    QHBoxLayout* get_dashboardLayout() const;

    void showErrorDialog(const std::string& errorMessage);
};
#endif // HEALTHDASHBOARD_H
