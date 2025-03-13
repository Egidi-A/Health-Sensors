#include "healthdashboard.h"
#include "./controller.h"

void healthDashboard::addMenu(QVBoxLayout* mainLayout)
{
    QMenuBar*  menuBar = new QMenuBar(this);

    menuBar->addMenu(fileBar);
    menuBar->addMenu(sensoriBar);
    menuBar->addMenu(simulazioniBar);

    // menu File
    fileBar->addAction(new QAction("Carica File Simulazione", fileBar));
    fileBar->addAction(new QAction("Salva File Simulazione", fileBar));
    // menu Sensori
    sensoriBar->addMenu(aggiungiSensore);
    aggiungiSensore->addAction(new QAction("BPM", aggiungiSensore));
    aggiungiSensore->addAction(new QAction("Ossigenazione", aggiungiSensore));
    aggiungiSensore->addAction(new QAction("Temperatura", aggiungiSensore));

    sensoriBar->addAction(new QAction("Rimuovi Sensore", sensoriBar));
    // menu Simulazioni
    simulazioniBar->addAction(new QAction("Simulazione Singolo Sensore", simulazioniBar));
    simulazioniBar->addAction(new QAction("Simulazione Completa", simulazioniBar));

    mainLayout->addWidget(menuBar);
}

void healthDashboard::addDashSensori(Modello* model, QHBoxLayout* dashLayout)
{
    dashSensoriWidget = new dashBoardSensoriWidget();
    dashLayout->addWidget(dashSensoriWidget);
}

void healthDashboard::addDashSimulazione(Modello* model, int idSensore, QHBoxLayout* dashLayout)
{
    dashSimulazioneWidget = new dashboardSimulazioneWidget(model, idSensore);
    dashLayout->addWidget(dashSimulazioneWidget);
}

void healthDashboard::addDashDettagli(Modello* model, int idSensore, QHBoxLayout* dashLayout)
{
    dashDetailsWidget = new dashboardDettagliWidget(model, idSensore);
    dashLayout->addWidget(dashDetailsWidget);
}

dashBoardSensoriWidget* healthDashboard::get_dashSensoriWidget() const
{
    return dashSensoriWidget;
}
dashboardDettagliWidget* healthDashboard::get_dashDettagliWidget() const
{
    return dashDetailsWidget;
}
dashboardSimulazioneWidget* healthDashboard::get_dashSimulazioneWidget() const
{
    return dashSimulazioneWidget;
}

QHBoxLayout* healthDashboard::get_dashboardLayout() const{
    return dashboardLayout;
}

void healthDashboard::showErrorDialog(const std::string& errorMessage) {
    QMessageBox::critical(this, tr("Errore"), QString::fromStdString(errorMessage));
}

healthDashboard::healthDashboard(Modello* model, int idSensore, QWidget *parent)
    : QWidget(parent)
{
    modello = model;
    //aggiungere la barra dei menu
    addMenu(mainLayout);

    // DASHBOARD SENSORI
    addDashSensori(modello, dashboardLayout);

    // DASHBOARD SIMULAZIONI
    addDashSimulazione(modello, idSensore, dashboardLayout);

    // DASHBOARD DETTAGLI
    addDashDettagli(modello, idSensore, dashboardLayout);

    mainLayout->addLayout(dashboardLayout);

    //final
    mainLayout->setSpacing(0);
    setLayout(mainLayout);
    resize(QSize(720, 480));
}

healthDashboard::~healthDashboard() {
    delete controller;
    delete modello;
}

void healthDashboard::setController(Controller *c)
{
    controller = c;
    //connettere le azioni dei menu
    connect(fileBar->actions().at(0), SIGNAL(triggered()),controller, SLOT(caricaSimulazione_controller()));
    connect(fileBar->actions().at(1), SIGNAL(triggered()),controller, SLOT(salvaSimulazione_controller()));

    connect(aggiungiSensore->actions().at(0), SIGNAL(triggered()),controller, SLOT(aggiungiSensoreBPM_controller()));
    connect(aggiungiSensore->actions().at(1), SIGNAL(triggered()),controller, SLOT(aggiungiSensoreOssigenazione_controller()));
    connect(aggiungiSensore->actions().at(2), SIGNAL(triggered()),controller, SLOT(aggiungiSensoreTemperatura_controller()));

    connect(sensoriBar->actions().at(1), SIGNAL(triggered()),controller, SLOT(rimuoviSensore_controller()));

    connect(simulazioniBar->actions().at(0), SIGNAL(triggered()),controller, SLOT(nuovaSimulazioneOne_controller()));
    connect(simulazioniBar->actions().at(1), SIGNAL(triggered()),controller, SLOT(nuovaSimulazioneAll_controller()));

    //connettere i controlli
    connect(dashSensoriWidget->addSensoreBPMButton, SIGNAL(clicked()), controller, SLOT(aggiungiSensoreBPM_controller()));
    connect(dashSensoriWidget->addSensoreOssigenazioneButton, SIGNAL(clicked()), controller, SLOT(aggiungiSensoreOssigenazione_controller()));
    connect(dashSensoriWidget->addSensoreTemperaturaButton, SIGNAL(clicked()), controller, SLOT(aggiungiSensoreTemperatura_controller()));
    connect(dashSensoriWidget->removeSensoreButton, SIGNAL(clicked()), controller, SLOT(rimuoviSensore_controller()));
    connect(dashSensoriWidget->searchBar, SIGNAL(textChanged(const QString&)), controller, SLOT(cercaSensore_controller(const QString&)));

    connect(dashSimulazioneWidget->nuovaSimulazione, SIGNAL(clicked()), controller, SLOT(nuovaSimulazioneOne_controller()));
    connect(dashSimulazioneWidget->caricaSimulazione, SIGNAL(clicked()), controller, SLOT(caricaSimulazione_controller()));
    connect(dashSimulazioneWidget->salvaSimulazione, SIGNAL(clicked()), controller, SLOT(salvaSimulazione_controller()));

    connect(dashDetailsWidget->modificaNomeButton, SIGNAL(clicked()), controller, SLOT(modificaNomeSensore_controller()));
    connect(dashSensoriWidget->listaSensori, SIGNAL(itemClicked(QListWidgetItem*)), controller, SLOT(itemListaCliccato_controller(QListWidgetItem*)));
}
