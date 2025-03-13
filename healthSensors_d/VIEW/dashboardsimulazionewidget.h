#ifndef DASHBOARDSIMULAZIONEWIDGET_H
#define DASHBOARDSIMULAZIONEWIDGET_H

#include <QWidget>
#include <./MODELLO/modello.h>
#include <QLabel>
#include <QLineSeries>
#include <QVBoxLayout>
#include <QVBoxLayout>
#include <QChart>
#include <QChartView>
#include <QPushButton>
#include <QFileDialog>
#include <QValueAxis>

class dashboardSimulazioneWidget : public QWidget
{
    Q_OBJECT
public:
    QVBoxLayout* dashSimulazioneLayout= new QVBoxLayout();
    QLabel *labelSimulazione = new QLabel("Dashboard Simulazione");
    QHBoxLayout* qualityLayout = new QHBoxLayout();
    QLabel* qualityLabel = new QLabel("Day Quality: ");
    QLabel* valueLabel = new QLabel("valori da aggiornare");
    QFrame* frameGrafico = new QFrame();
    QVBoxLayout* layoutGrafico = new QVBoxLayout(frameGrafico);
    QLineSeries *serieDati = new QLineSeries();
    QChart *chartDati = new QChart();
    QChartView *chartView = new QChartView(chartDati);
    QHBoxLayout* bottoniSimulazioneLayout = new QHBoxLayout();
    QPushButton* nuovaSimulazione = new QPushButton("Nuova Simulazione");
    QPushButton* caricaSimulazione = new QPushButton("Carica Simulazione");
    QPushButton* salvaSimulazione = new QPushButton("Salva Simulazione");

    QHBoxLayout* funzioneBPMLayout = new QHBoxLayout();
    QLabel* sportAvgLabel = new QLabel("Day Sport Average: ");
    QLabel* valueSportLabel = new QLabel("valori da aggiornare");

    QHBoxLayout* funzioneOssigenazioneLayout = new QHBoxLayout();
    QLabel* ossigenazioneLabel = new QLabel("Livelli critici di ossigenazione: ");
    QLabel* criticitaLabel = new QLabel("Nessun valore analizzato criticita");

    QHBoxLayout* funzioneTemperaturaLayout = new QHBoxLayout();
    QLabel* temperaturaLabel = new QLabel("Rilevazione febbre: ");
    QLabel* febbreLabel = new QLabel("Nessun valore analizzato febbre");

    Modello* modello;

    explicit dashboardSimulazioneWidget(Modello* model, int idSensore, QWidget *parent = nullptr);

    QString showLoadFileDialog();
    QString showSaveFileDialog();
    void refreshSimulazione(int idSensore);
};

#endif // DASHBOARDSIMULAZIONEWIDGET_H
