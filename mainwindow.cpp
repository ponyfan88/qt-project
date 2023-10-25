#include <unistd.h>

#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "crack.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    std::string steamGamesLocation;

#ifdef _WIN32 // Windows-specific code

    steamGamesLocation = "c:/Program Files (x86)/steam/steamapps/";

#elif __linux__ // Linux-specific code
        // Linux-specific code here

    if (getenv("HOME") != nullptr) {
        steamGamesLocation = std::string(getenv("HOME")) + "/.steam/steam/steamapps/";
    }
    else {
        // no home environment variable, you freak!
        //askCustomSteamGames();
    }
#else

    //askCustomSteamGames();

#endif

    myGamesFinder.findGames(steamGamesLocation);

    //ui->listWidget->addItem("example");

    ui->gameName->setText("");
    ui->gamePath->setText("");
    ui->openGamePathButton->setVisible(false);
    ui->gameId->setText("");

    for (int i = 0; i < myGamesFinder.games.size(); i++) {
        QString gameName = QString::fromStdString(myGamesFinder.games[i].name);
        ui->listWidget->addItem(gameName);
    }

    int selectedRow = -1;

    // notes for kennedy
    // [this]() {} is like a function in javascript function() {}
    // the third paramer here is where we'd want this to return to, obviously "this"
    // the fourth parameters "capture" is what's inside the brackets. not sure i understand this 100% yet, but it seems to be importing variables.
    // putting "this" in its place just allows it to run the methods that ui has, and selectedRow lets us change selectedRow
    // we use "mutable" to mark that we can change stuff outside of the lambda function
    connect(ui->listWidget,&QListWidget::itemSelectionChanged, this, [this, selectedRow]() mutable {
        ui->openGamePathButton->setVisible(true); // simple and effective, sorry this gets ran multiple times.

        selectedRow = ui->listWidget->currentRow();
        Game myGame = myGamesFinder.games[selectedRow];

        ui->gameName->setText(QString::fromStdString(myGame.name)); // set the games name
        ui->gamePath->setText(QString::fromStdString(myGame.path)); // set the games path
        ui->gameId->setText(QString::fromStdString(std::to_string(myGame.id))); // set the games id

        ui->crackedStatus->setStyleSheet("QLabel { color : red; }"); // BAD color

        crack myCrack = crack(myGame);

    });

    connect(ui->openGamePathButton,&QPushButton::clicked, this, [this]()  {
        //execl("");
        // nothing yes, eventually use xdg-open to do that
    });
}

MainWindow::~MainWindow()
{    
    delete ui;
}

