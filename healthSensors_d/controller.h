#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <./VIEW/healthdashboard.h>
#include <./MODELLO/modello.h>
#include <filehandler.h>

#include <QString>
#include <QMessageBox>
#include <vector>

class Controller : public QObject
{
    Q_OBJECT
private:
    Modello* model;
    healthDashboard* view;
    FileHandler* fileHandler_controller;
    Sensore* sensoreAttivo = nullptr;
    std::vector<QString> vecSensoriRicerca;
    void updateVecSensoriRicerca();

public:
    explicit Controller(QObject *parent = nullptr);
    ~Controller();

    void setModel_controller(Modello* m);
    void setView_controller(healthDashboard* v);

    void setModelView_controller(Modello *m, healthDashboard *v);
    void set_sensoreAttivo(Sensore* s);

public slots:
    void aggiungiSensoreBPM_controller();
    void aggiungiSensoreOssigenazione_controller();
    void aggiungiSensoreTemperatura_controller();

    void rimuoviSensore_controller();
    void cercaSensore_controller(const QString& text);

    void caricaSimulazione_controller();
    void salvaSimulazione_controller() const;
    void nuovaSimulazioneOne_controller() const;
    void nuovaSimulazioneAll_controller() const;

    void modificaNomeSensore_controller();
    void itemListaCliccato_controller(QListWidgetItem* item);

};

#endif // CONTROLLER_H
