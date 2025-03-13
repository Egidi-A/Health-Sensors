#ifndef DASHBOARDDETTAGLIWIDGET_H
#define DASHBOARDDETTAGLIWIDGET_H

#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <QInputDialog>

#include <./MODELLO/modello.h>

class dashboardDettagliWidget : public QWidget
{
    Q_OBJECT
public:
    QVBoxLayout* dashDetailsLayout = new QVBoxLayout();
    QLabel *labelDetails = new QLabel("Dashboard Dettagli Sensore");
    QHBoxLayout* detailsIDLayout = new QHBoxLayout();
    QLabel *idDetails = new QLabel("ID: ");
    QLabel* idLabel = new QLabel();
    QHBoxLayout* detailsNomeLayout = new QHBoxLayout();
    QLabel *nomeDetails = new QLabel("Nome: ");
    QLabel* nomeLabel = new QLabel();
    QHBoxLayout* detailsVMinLayout = new QHBoxLayout();
    QLabel *VMinDetails = new QLabel("Valore Minimo: ");
    QLabel* VMinLabel = new QLabel();
    QHBoxLayout* detailsVMaxLayout = new QHBoxLayout();
    QLabel *VMaxDetails = new QLabel("Valore Massimo: ");
    QLabel* VMaxLabel = new QLabel();
    QHBoxLayout* detailsFrequenzaLayout = new QHBoxLayout();
    QLabel *FrequenzaDetails = new QLabel("Frequenza Campionamento: ");
    QLabel* FrequenzaLabel = new QLabel();
    QHBoxLayout* detailsSportMinLayout = new QHBoxLayout();
    QLabel *sportMinDetails = new QLabel("Valore Minimo Sport: ");
    QLabel* SportMinLabel = new QLabel();
    QHBoxLayout* detailsSportMaxLayout = new QHBoxLayout();
    QLabel *sportMaxDetails = new QLabel("Valore Massimo Sport: ");
    QLabel* SportMaxLabel = new QLabel();
    QHBoxLayout* detailsAlertMinLayout = new QHBoxLayout();
    QLabel *alertDetails = new QLabel("Valore di Alert Minimo: ");
    QLabel* alertLabel = new QLabel();
    QPushButton* modificaNomeButton = new QPushButton("Modifica Nome Sensore");
    Modello* modello;

    explicit dashboardDettagliWidget(Modello* model, int idSensore, QWidget *parent = nullptr);
    ~dashboardDettagliWidget();
    QString showEditNameDialog();
    void setNameLabel(QString nome);
    void refreshDettagli(int idSensore);
signals:
};

#endif // DASHBOARDDETTAGLIWIDGET_H
