#include "controller.h"

void Controller::updateVecSensoriRicerca()
{
    vecSensoriRicerca.clear();
    for (const auto& sensore : model->getSensori()) {
        QString detSensore = QString::fromStdString(std::to_string(sensore->getSensoreID())+ " - " + sensore->getSensoreNome());
        vecSensoriRicerca.push_back(detSensore);
    }
}

Controller::Controller(QObject *parent): QObject(parent){}
Controller::~Controller() {
    delete model;
    delete view;
    delete fileHandler_controller;
}

void Controller::setModelView_controller(Modello *m, healthDashboard *v){
    model = m;
    view = v;
    updateVecSensoriRicerca();
    view->get_dashSensoriWidget()->updateListaWidget(vecSensoriRicerca);
}
void Controller::setModel_controller(Modello *m){model = m;}

void Controller::setView_controller(healthDashboard *v){view = v;}

void Controller::set_sensoreAttivo(Sensore *s){ sensoreAttivo = s;}

void Controller::aggiungiSensoreBPM_controller() {
    try {
        QString sensoreNuovo = view->get_dashSensoriWidget()->showAddBPMDialog();
        model->aggiungiSensore(sensoreNuovo.toStdString());
        updateVecSensoriRicerca();
        view->get_dashSensoriWidget()->updateListaWidget(vecSensoriRicerca);

    } catch (std::invalid_argument exc) {
        view->showErrorDialog(exc.what());
    } catch (std::runtime_error exc) {
        view->showErrorDialog(exc.what());
    }

}

void Controller::aggiungiSensoreOssigenazione_controller(){
    try {
        QString sensore = view->get_dashSensoriWidget()->showAddOssigenazioneDialog();
        model->aggiungiSensore(sensore.toStdString());
        updateVecSensoriRicerca();
        view->get_dashSensoriWidget()->updateListaWidget(vecSensoriRicerca);
    } catch (std::invalid_argument exc) {
        view->showErrorDialog(exc.what());
    } catch (std::runtime_error exc) {
        view->showErrorDialog(exc.what());
    }
}

void Controller::aggiungiSensoreTemperatura_controller(){
    try {
        QString sensore = view->get_dashSensoriWidget()->showAddTemperaturaDialog();
        model->aggiungiSensore(sensore.toStdString());
        updateVecSensoriRicerca();
        view->get_dashSensoriWidget()->updateListaWidget(vecSensoriRicerca);
    } catch (std::invalid_argument exc) {
        view->showErrorDialog(exc.what());
    } catch (std::runtime_error exc) {
        view->showErrorDialog(exc.what());
    }
}

void Controller::rimuoviSensore_controller(){
    try {
        int sensore = view->get_dashSensoriWidget()->showRemoveDialog();
        model->rimuoviSensore(sensore);
        if(!model->getSensori().size()) sensoreAttivo = nullptr;
        updateVecSensoriRicerca();
        view->get_dashSensoriWidget()->updateListaWidget(vecSensoriRicerca);
    } catch (std::invalid_argument exc) {
        view->showErrorDialog(exc.what());
    } catch (std::runtime_error exc) {
        view->showErrorDialog(exc.what());
    }
}

void Controller::cercaSensore_controller(const QString& text)
{
    updateVecSensoriRicerca();
    if(text != ""){
        for(auto it = vecSensoriRicerca.begin(); it!=vecSensoriRicerca.end(); it++) {
            if(!it->contains(text)){
                vecSensoriRicerca.erase(it--);
            }
        }
    }

    view->get_dashSensoriWidget()->updateListaWidget(vecSensoriRicerca);
}

void Controller::caricaSimulazione_controller()
{
    try {
        std::string path = view->get_dashSimulazioneWidget()->showLoadFileDialog().toStdString();
        SensoriCollection* nuovaCollection = fileHandler_controller->caricaDati(path);
        model->setCollezioneSensori_modello(nuovaCollection);
        updateVecSensoriRicerca();
        view->get_dashSensoriWidget()->updateListaWidget(vecSensoriRicerca);
    } catch (std::invalid_argument exc) {
        view->showErrorDialog(exc.what());
    } catch (std::runtime_error exc) {
        view->showErrorDialog(exc.what());
    }

}

void Controller::salvaSimulazione_controller() const
{
    try {
        std::string path = view->get_dashSimulazioneWidget()->showSaveFileDialog().toStdString();
        fileHandler_controller->salvaDati(model->getCollezioneSensori_modello(), path);
    } catch (std::invalid_argument exc) {
        view->showErrorDialog(exc.what());
    } catch (std::runtime_error exc) {
        view->showErrorDialog(exc.what());
    }
}

void Controller::modificaNomeSensore_controller(){
    try {
        QString nome = view->get_dashDettagliWidget()->showEditNameDialog();
        if(sensoreAttivo){
            model->setSensoreNome_modello(sensoreAttivo->getSensoreID(), nome.toStdString());
            view->get_dashDettagliWidget()->setNameLabel(QString::fromStdString(sensoreAttivo->getSensoreNome()));
            updateVecSensoriRicerca();
            view->get_dashSensoriWidget()->updateListaWidget(vecSensoriRicerca);
        }
        else throw std::runtime_error("Non sono presenti sensori da modificare");
    } catch (std::invalid_argument exc) {
        view->showErrorDialog(exc.what());
    } catch (std::runtime_error exc) {
        view->showErrorDialog(exc.what());
    }

}

void Controller::itemListaCliccato_controller(QListWidgetItem* item)
{
    try {
        if(item != nullptr)
        {
            QString stringaItem = item->text();
            int idCliccato = stringaItem.split(" ").first().toInt();
            Sensore* sensoreAggiornato = this->model->getSensore(idCliccato);
            set_sensoreAttivo(sensoreAggiornato);
            view->get_dashDettagliWidget()->refreshDettagli(sensoreAttivo->getSensoreID());
            view->get_dashSimulazioneWidget()->refreshSimulazione(sensoreAttivo->getSensoreID());
        } else {
            throw std::runtime_error("Errore alla selezione dell'oggetto!");
        }
    } catch (std::invalid_argument exc) {
        view->showErrorDialog(exc.what());
    } catch (std::runtime_error exc) {
        view->showErrorDialog(exc.what());
    }
}

void Controller::nuovaSimulazioneOne_controller() const{
    try {
        if(sensoreAttivo)
        {
            sensoreAttivo->daySimulazione();
            view->get_dashSimulazioneWidget()->refreshSimulazione(sensoreAttivo->getSensoreID());
        }
        else throw std::runtime_error("Non hai selezionato alcun sensore dalla lista");
    } catch (std::invalid_argument exc) {
        view->showErrorDialog(exc.what());
    } catch (std::runtime_error exc) {
        view->showErrorDialog(exc.what());
    }
}

void Controller::nuovaSimulazioneAll_controller() const{
    try {
        if(model->getSensori().size()) {
            for(auto sensore: model->getSensori()) sensore->daySimulazione();
            view->get_dashSimulazioneWidget()->refreshSimulazione(sensoreAttivo->getSensoreID());
        }
        else throw std::runtime_error("Non ci sono sensori da simulare");
    } catch (std::invalid_argument exc) {
        view->showErrorDialog(exc.what());
    } catch (std::runtime_error exc) {
        view->showErrorDialog(exc.what());
    }
}
