#include "View.h"
#include "Game.h"
#include "controller.h"
#include <iostream>
#include <stdlib.h>

View::View( Controller* c, Game* g) 
    : mainTable( 5, 4, false), playedCardsTable(4,1,false), newGameButton("New Game"),
    endGameButton("End Game"), game_(g), controller_(c) {

        // Sets the border width of the window.
        set_border_width( 10 );

        add(mainTable);

        // Links the startGame method to the New Game button
        newGameButton.signal_clicked().connect( sigc::mem_fun( *this, &View::newGameButtonClicked ) );
        endGameButton.signal_clicked().connect( sigc::mem_fun( *this, &View::endGameButtonClicked ) );

        //TOP BOX
        topHBox.add(newGameButton);
        topHBox.add(endGameButton);
        mainTable.attach(topHBox, 0, 4, 0, 1);

        //PLAYED CARDS
        playedCardsFrame.add(playedCardsTable);
        playedCardsFrame.set_label("Cards on the table");
        for (int j = 0; j < 4; j++) {
            playedCardsTable.attach(tableHBox[j], 0, 1, j, j+1);
            for (int i = 0; i < 13; i++ ) {
                card[0] = new Gtk::Image ( deck.getNullCardImage() );
                tableButton[j * 13 + i].set_image( *card[0] );
                tableHBox[j].add( tableButton[j * 13 + i] );
            }
        }
        mainTable.attach(playedCardsFrame, 0, 4, 1, 2);

        //RAGE, POINTS, DISCARDS
        for (int i = 0; i < 4; i++) {
            std::stringstream sstream;
            sstream << "Player "<< i + 1;
            playerFrame[i].set_label(sstream.str());

            rageButton[i].set_label("Rage!");
            rageVBox[i].add(rageButton[i]);
            rageButton[i].signal_clicked().connect( sigc::bind( sigc::mem_fun( *this, &View::rageButtonClicked), i ));
            rageButton[i].set_sensitive(false);

            pointsLabel[i].set_label("0 points");
            rageVBox[i].add(pointsLabel[i]);

            discardsLabel[i].set_label("0 discards");
            rageVBox[i].add(discardsLabel[i]);

            playerFrame[i].add(rageVBox[i]);

            mainTable.attach(playerFrame[i], i, i + 1, 2, 3);
        }

        //PLAYER HAND, DISCARD BUTTONS
        yourHandFrame.set_label("Player's Hand");
        yourHandFrame.add(playerHBox);
        for (int i = 0; i < 13; i++ ) {
            card[0] = new Gtk::Image ( deck.getNullCardImage() );
            playerCardButton[i].set_image( *card[0] );	
            playerCardButton[i].signal_clicked().connect( sigc::bind( sigc::mem_fun( *this, &View::playerCardButtonClicked ), i ));
            playerHBox.add( playerCardButton[i] );

            discardButton[i].set_label("Discard");
            discardHBox.add(discardButton[i]);
            discardButton[i].signal_clicked().connect( sigc::bind( sigc::mem_fun( *this, &View::discardButtonClicked ), i ));
        }

        mainTable.attach(yourHandFrame, 0, 4, 3, 4);
        mainTable.attach(discardHBox, 0, 4, 4, 5);

        // The final step is to display this newly created widget.
        show_all();

        game_->subscribe(this);

    } 

View::~View() {
    for (int i = 0; i < 52; i++ ) delete card[i];
} 

void View::newGameButtonClicked() {
    if (setPlayerTypes()) {
        controller_->newGameButtonClicked(); 
    }
}

void View::update() {
    GameState currentState = game_->getCurrentState();
    int currentPlayer = controller_->getCurrentPlayer();
    int currentTurn = game_->getCurrentTurn();

    //Disable all rage buttons
    for (int i = 0; i < 4; i++) {
        rageButton[i].set_sensitive(false);
    }

    //Update the player frame 
    std::stringstream sstream;
    sstream << "Player " << currentPlayer << "'s Hand";
    yourHandFrame.set_label(sstream.str());

    updateTable();
    updatePlayerInfo();

    if (currentTurn == 1)
        firstTurnPopup();

    if (currentState == QUITGAME) {
        //Remove all cards from hand display.
        for (int i = 0; i < 13; i++) {
            card[0] = new Gtk::Image( deck.getNullCardImage() );
            playerCardButton[i].set_image( *card[0] );
        }
    }

    else if (currentState == TAKETURN) {
        rageButton[currentPlayer - 1].set_sensitive(true);

        updatePlayerHand();
    }

    else if (currentState == NEXTROUND) {
        recapPopup(); 
        game_->startGame();
    }
    else if (currentState == FINISHEDGAME) {
        recapPopup();

        rageButton[currentPlayer - 1].set_sensitive(false);
        updatePlayerHand();  
        resultPopup();      
    }
}

void View::recapPopup() {
    int const* scores = controller_->getScores();
    int incrementalScores[4] = {0};

    Gtk::Dialog dialog("Results", *this);
    Gtk::VBox* contentArea = dialog.get_vbox();

    std::stringstream resultStream;

    for (int i = 0; i < 4; i++) {
        std::vector<Card> discarded = game_->getDiscarded(i);

        resultStream << "Player " << i + 1 << " discarded:";
        for (unsigned j = 0; j < discarded.size(); j++) {
            resultStream << " " << discarded[j];
            incrementalScores[i] += (int)discarded[j].getRank() + 1;
        }
        resultStream << std::endl;
        resultStream << "Player " << i + 1 << " score: ";
        resultStream << scores[i] - incrementalScores[i] << " + ";
        resultStream << incrementalScores[i] << " = " << scores[i];
        resultStream << std::endl << std::endl;
    }

    Gtk::Label message(resultStream.str());
    message.show();

    contentArea->pack_start(message, true, false);
    dialog.add_button("Next Round", GTK_RESPONSE_CLOSE);

    dialog.run();
}

void View::resultPopup() {
    int winner = 0;
    int const* scores = game_->getScores();

    Gtk::Dialog dialog("Results", *this);
    Gtk::VBox* contentArea = dialog.get_vbox();

    std::stringstream resultStream;

    for (int i = 1; i < 4; i++) {
        if (scores[i] < scores[winner])
            winner = i;
    }
    resultStream << "Player " << winner + 1 << " wins!" << std::endl;

    Gtk::Label message(resultStream.str());
    message.show();
    contentArea->pack_start(message, true, false);
    dialog.add_button("OK", GTK_RESPONSE_CLOSE);

    dialog.run();
}

void View::firstTurnPopup() {
    int currentPlayer = controller_->getCurrentPlayer();
    Gtk::Dialog dialog("First Turn", *this);
    Gtk::VBox* contentArea = dialog.get_vbox();

    std::stringstream resultStream;

    resultStream << "New round.  Player " << currentPlayer << " starts!" << std::endl;

    Gtk::Label message(resultStream.str());
    message.show();
    contentArea->pack_start(message, true, false);
    dialog.add_button("OK", GTK_RESPONSE_CLOSE);

    dialog.run();

}

void View::updatePlayerInfo() {
    updateScores();
    updateDiscards();
}

void View::updateScores() {
    int score;
    for (int i = 0; i < 4; i++) {
        std::stringstream sstream;
        score = game_->getScore(i);
        if (score == 1) {
            sstream << score << " point";
        }
        else {
            sstream << score << " points";
        }
        pointsLabel[i].set_label(sstream.str());
    }
}

void View::updateDiscards() {
    int discards;
    for (int i = 0; i < 4; i++) {
        std::stringstream sstream;
        discards = game_->getDiscard(i);
        if (discards == 1) {
            sstream << discards << " discard";
        }
        else {
            sstream << discards << " discards";
        }
        discardsLabel[i].set_label(sstream.str());

    }
}

void View::updateTable() {
    //Update the displayed cards on the table
    bool const* table = controller_->getTable();
    for (int i = 0; i < 52; i++ ) {
        if (table[i])
            card[0] = new Gtk::Image( deck.getCardImage( (Rank)(i % 13), (Suit)(i / 13) ) );
        else
            card[0] = new Gtk::Image( deck.getNullCardImage() );

        tableButton[i].set_image( *card[0] );	
    } 
}

void View::updatePlayerHand() {
    int currentPlayer = game_->getCurrentPlayer();
    std::vector<Card> hand = game_->getHand(currentPlayer - 1);

    for (int i = 0; (unsigned)i < hand.size(); i++) {
        card[0] = new Gtk::Image( deck.getCardImage( hand[i].getRank(), hand[i].getSuit() ) );
        playerCardButton[i].set_image( *card[0] );
    }
    for (int i = hand.size(); i < 13; i++) {
        card[0] = new Gtk::Image( deck.getNullCardImage() );
        playerCardButton[i].set_image( *card[0] );
    }
}

// Creates dialog boxes to allow the user to choose whether each
// player is human or computer
bool View::setPlayerTypes() {
    enum PlayerType {HUMAN, COMPUTER};

    Gtk::Dialog dialog("Start Game", *this);
    Gtk::VBox* contentArea = dialog.get_vbox();

    Gtk::Label message("Seed Value");
    message.show();
    contentArea->pack_start(message, true, false);

    seedButton.set_digits(0);
    seedButton.set_increments(1, 1);
    seedButton.set_range(0, 999);
    seedButton.set_value(0);
    contentArea->pack_start(seedButton, false, false);
    seedButton.show();

    Gtk::Button* Button1 = dialog.add_button("Next", (int)HUMAN);
    int result = dialog.run();
    int seedValue = 0;

    switch (result) {
        case 0:
            seedValue = (int)seedButton.get_value();
            break;
        default:
            return false;
    }

    contentArea->remove(seedButton);
    Button1->set_label("Human");

    dialog.add_button("Computer", (int)COMPUTER);

    // Stores the value of each player type, as a string.
    std::string playerTypes[4];

    for (int i = 1; i <= 4; i = i + 1) {

        // Sets the dialog box message
        std::stringstream sstream;
        sstream << "Is Player " << i << " a human or a computer?";
        message.set_label(sstream.str());

        // Wait for a response from the dialog box.
        int result = dialog.run();

        // Store the selection type for each player. If the dialog box is closed (Cancel),
        // the function returns with no players set.
        switch (result) {
            case (int)HUMAN:
                playerTypes[i - 1] = "h";
                break;
            case (int)COMPUTER:
                playerTypes[i - 1] = "c";
                break;
            default:
                return false;
                break;
        } // switch
    }

    controller_->setPlayers(playerTypes, seedValue);

    return true;

}

void View::endGameButtonClicked() {
    controller_->endGameButtonClicked();
}

void View::playerCardButtonClicked(unsigned int cardClicked) {
    //int currentPlayer = game_->getCurrentPlayer();
    //std::vector<Card> hand = game_->getHand(currentPlayer - 1);

    //if (cardClicked < hand.size()) 
        controller_->tryPlayingCard(cardClicked);
    
}

void View::discardButtonClicked(unsigned int cardClicked) {
    //int currentPlayer = game_->getCurrentPlayer();
    //std::vector<Card> hand = game_->getHand(currentPlayer - 1);
    //if (cardClicked < hand.size())
        controller_->tryDiscardingCard(cardClicked); 
}

void View::rageButtonClicked( unsigned int buttonClicked ) {
    std::cout<<"RAGE";

    game_->rageQuit(buttonClicked);
}
