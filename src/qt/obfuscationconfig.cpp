#include "Hodgepodgeconfig.h"
#include "ui_Hodgepodgeconfig.h"

#include "bitcoinunits.h"
#include "guiconstants.h"
#include "init.h"
#include "optionsmodel.h"
#include "walletmodel.h"

#include <QKeyEvent>
#include <QMessageBox>
#include <QPushButton>
#include <QSettings>

HodgepodgeConfig::HodgepodgeConfig(QWidget* parent) : QDialog(parent),
                                                        ui(new Ui::HodgepodgeConfig),
                                                        model(0)
{
    ui->setupUi(this);

    connect(ui->buttonBasic, SIGNAL(clicked()), this, SLOT(clickBasic()));
    connect(ui->buttonHigh, SIGNAL(clicked()), this, SLOT(clickHigh()));
    connect(ui->buttonMax, SIGNAL(clicked()), this, SLOT(clickMax()));
}

HodgepodgeConfig::~HodgepodgeConfig()
{
    delete ui;
}

void HodgepodgeConfig::setModel(WalletModel* model)
{
    this->model = model;
}

void HodgepodgeConfig::clickBasic()
{
    configure(true, 1000, 2);

    QString strAmount(BitcoinUnits::formatWithUnit(
        model->getOptionsModel()->getDisplayUnit(), 1000 * COIN));
    QMessageBox::information(this, tr("Hodgepodge Configuration"),
        tr(
            "Hodgepodge was successfully set to basic (%1 and 2 rounds). You can change this at any time by opening Transend's configuration screen.")
            .arg(strAmount));

    close();
}

void HodgepodgeConfig::clickHigh()
{
    configure(true, 1000, 8);

    QString strAmount(BitcoinUnits::formatWithUnit(
        model->getOptionsModel()->getDisplayUnit(), 1000 * COIN));
    QMessageBox::information(this, tr("Hodgepodge Configuration"),
        tr(
            "Hodgepodge was successfully set to high (%1 and 8 rounds). You can change this at any time by opening Transend's configuration screen.")
            .arg(strAmount));

    close();
}

void HodgepodgeConfig::clickMax()
{
    configure(true, 1000, 16);

    QString strAmount(BitcoinUnits::formatWithUnit(
        model->getOptionsModel()->getDisplayUnit(), 1000 * COIN));
    QMessageBox::information(this, tr("Hodgepodge Configuration"),
        tr(
            "Hodgepodge was successfully set to maximum (%1 and 16 rounds). You can change this at any time by opening Transend's configuration screen.")
            .arg(strAmount));

    close();
}

void HodgepodgeConfig::configure(bool enabled, int coins, int rounds)
{
    QSettings settings;

    settings.setValue("nHodgepodgeRounds", rounds);
    settings.setValue("nAnonymizeTransendAmount", coins);

    nZeromintPercentage = rounds;
    nAnonymizeTransendAmount = coins;
}
