#include "../include/Game.h"
#include "../include/ViewMenu.h"
#include "../include/ViewSettings.h"

#include <stdio.h>
#include <stdlib.h>
#include <curses.h>

char ViewSettingsAusgabe = ' '; // Welche Cursortaste wurde gedrueckt (TODO: Spaeter etfernen)
int ViewSettingsIndex = 0; // Das aktuell ausgewaehlte Element in den Einstellungen

int ViewSymbolIndex =  0; //Das aktuell ausgewaehlte Element in den Symbol Einstellungen
char PlayerSymbol = ' '; //Allgemeines Spieler Symbol, was das Symbol an den ausgewaehlten Spieler weitergibt
char Player1Symbol = 'X'; //Spieler 1 Symbol im Spiel, standardmaessig auf X
char Player2Symbol = 'O'; //Spieler 2 Symbol im Spiel, standardmaessig auf O
int CheckSetSymbol = 0; //Ueberprueft, ob ein Symbol festgelegt wurde

int CheckOperatingSettings = 0; //Ueberprueft, ob Einstellungen gespeichert bzw. geladen wurden
FILE *settingsp; //Pointer auf eine Datei zum Speichern der Einstellungen

int ViewDifficultyIndex = 0; //Das aktuell ausgewaehlte Element in den Schwierigkeitsgrad Einstellungen
int Difficulty = 1; //Schwierigkeitsgrad im Spiel, standardmaessig auf 1 (Einfach)
int CheckSetDifficulty = 0; //Ueberprueft, ob ein Schwierigkeitsgrad festgelegt wurde

int ViewPlayerIndex = 0; //Das aktuell ausgewaehlte Element in den Player Einstellungen, die vor den Symbol Einstellungen erscheinen
int CheckSetPlayer = 0; //Ueberprueft, um welchen Spieler es sich handelt (Spieler 1 oder Spieler 2)

void ViewSettingsPressedKeyCall(int pressedKey) { //Nehme die Tasteneingabe fuer die Einstellungen entgegen#
    char array[2]; //Zeichenkette zum Laden der Schwierigkeit
    switch (pressedKey) {
        case KEY_UP:
            ViewSettingsAusgabe = '^';
            ViewSettingsIndex--;
            break;
        case KEY_DOWN:
            ViewSettingsAusgabe = 'v';
            ViewSettingsIndex++;
            break;
        case KEY_LEFT:
            ViewSettingsAusgabe = '<';
            break;
        case KEY_RIGHT:
            ViewSettingsAusgabe = '>';
            break;
        case 'q':
            GameGet()->quit = 1;// Stoppe die Gameloop und beende das Spiel (TODO: Spaeter etfernen)
            break;
        case 'l':
            ViewSettingsIndex = 0; //Zuruecksetzen des Einstellungen Indexes 
            GameGet()->pressedKeyCall = ViewMenuPressedKeyCall;// Setze die Methode ViewMenuPressedKeyCall um das Hauptmenue darzustellen
            GameGet()->paintCall = ViewMenuPaintCall;// Setze die Methode ViewBoardPaintCall um das Hauptmenue darzustellen
            break;
        case KEY_ENTER:
        case ' ':
        case '\n':
            switch (ViewSettingsIndex) {
                case 0: // Einstellungen laden
                    settingsp = fopen(".settings.txt", "r"); //Oeffne die Datei im Lese-Modus
                    if(settingsp != NULL) { //Liest nur die Einstellungen, solange die Datei existiert/es keine Fehler beim Oeffnen der Datei gibt
                        Player1Symbol=fgetc(settingsp); //Das Spielersymbol fuer den 1. Spieler wird auf den ersten Char in der Datei gesetzt
                        fgetc(settingsp); //Verschlucken des Zeilenumbruchs
                        Player2Symbol=fgetc(settingsp); //Spielersymbol fuer den 2. Spieler
                        array[0]=fgetc(settingsp); //Die Schwierigkeit wird an die erste Stelle der Zeichenkette geladen
                        array[1]=0; //Null-Terminierer (Ende der Zeichenkette)
                        Difficulty=atoi(array); //Die Difficulty wird auf die Zeichenkette (Schwierigkeit) gesetzt
                    }
                    fclose(settingsp);
                    CheckOperatingSettings = 1; //Gibt einen Wert aus, der in der Anzeige (ViewSettingsPaintCall) das erfolgreiche Laden der Datei bestaetigt
                    break;
                case 1: // Einstellungen speichern
                    settingsp = fopen("settings.txt", "w+"); //Oeffne die Datei im Lesen-und-Schreiben-Modus
                    if(settingsp != NULL) {
                        fprintf(settingsp, "%c\n", Player1Symbol); //Schreiben des 1. Spielersymbols, danach Zeilenumbruch
                        fprintf(settingsp, "%c", Player2Symbol);
                        fprintf(settingsp, "%d", Difficulty); //Als naechstes wird die Schwierigkeit geschrieben (nur beim zweiten Spieler, da der erste immer ein "echter" Spieler ist)
                    }
                    fclose(settingsp);
                    CheckOperatingSettings = 2; //Bestaetigt das erfolgreiche Speichern der Einstellungen in der Anzeige (ViewSettingsPaintCall)
                    break;
                case 2: // Spieler Symbol festlegen
                    CheckOperatingSettings = 0; //Setzt den Wert des erfolgreichen Speicherns/Laden einer Datei zurueck
                    //Setzt die Anzeige und Tasteneingabe auf die Symbol-Methode bzw. das Symbol Menue
                    GameGet()->pressedKeyCall = ViewPlayerPressedKeyCall; 
                    GameGet()->paintCall = ViewPlayerPaintCall; 
                    break;
                case 3: // Schwierigkeit festlegen
                    CheckOperatingSettings = 0; //Setzt den Wert des erfolgreichen Speicherns/Laden einer Datei zurueck
                    //Setzt die Anzeige und Tasteneingabe auf die Difficulty-Methode bzw. das Schwierigkeitsgrad Menue
                    GameGet()->pressedKeyCall = ViewDifficultyPressedKeyCall;
                    GameGet()->paintCall = ViewDifficultyPaintCall;
                    break;
                case 4: // Back to Main Menu
                    CheckOperatingSettings = 0; //Setzt den Wert des erfolgreichen Speicherns/Laden einer Datei zurueck
                    ViewSettingsIndex = 0; // Zuruecksetzen des Einstellungen Indexes 
                    GameGet()->pressedKeyCall = ViewMenuPressedKeyCall; // Setze die Methode ViewMenuPressedKeyCall um das Hauptmenue darzustellen
                    GameGet()->paintCall = ViewMenuPaintCall;// Setze die Methode ViewMenuPaintCall um das Hauptmenue darzustellen
                    break;
            }
            break;
    }

    if (ViewSettingsIndex < 0) {
        ViewSettingsIndex = 4;// Springe zum letzten Eintrag
    } 
    else if (ViewSettingsIndex > 4) {
        ViewSettingsIndex = 0;// Springe zum ersten Eintrag
    }
}

void ViewSettingsPaintCall() { // Stelle die Einstellungen dar
    mvprintw(0, 0, "Steuern mit Pfeiltasten, Beenden mit 'q'");
    mvprintw(3, 5, "%c", ViewSettingsAusgabe);

    mvprintw(5, 5, "Einstellungen laden");
    mvprintw(6, 5, "Einstellungen speichern");
    mvprintw(7, 5, "Spieler Symbol festlegen");
    mvprintw(8, 5, "Schwierigkeit festlegen");
    mvprintw(9, 5, "Back to Main Menu");

    mvprintw(ViewSettingsIndex + 5, 4, ">");// Zeige das ausgewaehlte Element an
    if(CheckOperatingSettings == 1) { 
        mvprintw(1, 0, "Die Einstellungen wurden erfolgreich geladen!");
        mvprintw(2, 0, "Das Symbol fuer den 1. Spieler wurde auf %c gesetzt", Player1Symbol);
        mvprintw(3, 0, "Das Symbol fuer den 2. Spieler wurde auf %c gesetzt", Player2Symbol);
        mvprintw(3, 53, "Die Schwierigkeit wurde auf %d gesetzt", Difficulty);
    }
    else if(CheckOperatingSettings == 2) { 
        mvprintw(1, 0, "Die Einstellungen wurden erfolgreich gespeichert!");
    }
}

void ViewSymbolPressedKeyCall(int pressedKey) { //Nehme die Tasteneingabe fuer die Symbol-Einstellungen entgegen
    switch (pressedKey) {
        case KEY_UP:
            ViewSettingsAusgabe = '^';
            ViewSymbolIndex--;
            break;
        case KEY_DOWN:
            ViewSettingsAusgabe = 'v';
            ViewSymbolIndex++;
            break;
        case KEY_LEFT:
            ViewSettingsAusgabe = '<';
            break;
        case KEY_RIGHT:
            ViewSettingsAusgabe = '>';
            break;
        case 'q':
            GameGet()->quit = 1;// Stoppe die Gameloop und beende das Spiel (TODO: Spaeter etfernen)
            break;
        case 'l':
            CheckSetSymbol = 0;
            ViewSymbolIndex = 0; //Zuruecksetzen des Symbol Indexes 
            GameGet()->pressedKeyCall = ViewSettingsPressedKeyCall; //Setze die Methode ViewSettingsPressedKeyCall um die Tasteneingabe in den Einstellungen entgegenzunehmen
            GameGet()->paintCall = ViewSettingsPaintCall; //Setze die Methode ViewSettingsPaintCall um die Einstellungen darzustellen
            break;
        case KEY_ENTER:
        case ' ':
        case '\n':
            switch (ViewSymbolIndex) {
                case 0: //'X'
                    PlayerSymbol='X';
                    CheckSetSymbol=1;
                    break;
                case 1: //'O'
                    PlayerSymbol='O';
                    CheckSetSymbol=2;
                    break;
                case 2: //'Z'
                    PlayerSymbol='Z';
                    CheckSetSymbol=3;
                    break;
                case 3: //'~'
                    PlayerSymbol='~';
                    CheckSetSymbol=4;
                    break;
                case 4: //Back To Settings
                    CheckSetSymbol = 0;
                    ViewSymbolIndex = 0; //Zuruecksetzen des Symbol Indexes 
                    GameGet()->pressedKeyCall = ViewSettingsPressedKeyCall; //Setze die Methode ViewSettingsPressedKeyCall um die Tasteneingabe in den Einstellungen entgegenzunehmen
                    GameGet()->paintCall = ViewSettingsPaintCall; //Setze die Methode ViewSettingsPaintCall um die Einstellungen darzustellen
                    break;
            }
            break;
    }
    if (ViewSymbolIndex < 0) {
        ViewSymbolIndex = 4;// Springe zum letzten Eintrag
    } 
    else if (ViewSymbolIndex > 4) {
        ViewSymbolIndex = 0;// Springe zum ersten Eintrag
    }
}

void ViewSymbolPaintCall() { //Stelle die Symbol-Einstellungen dar
    mvprintw(0, 0, "Steuern mit Pfeiltasten, Beenden mit 'q'");
    mvprintw(3, 5, "%c", ViewSettingsAusgabe);

    mvprintw(5, 5, "X");
    mvprintw(6, 5, "O");
    mvprintw(7, 5, "Z");
    mvprintw(8, 5, "~");
    mvprintw(9, 5, "Back To Settings");

    mvprintw(ViewSymbolIndex + 5, 4, ">");// Zeige das ausgewaehlte Element an

    //Anzeigeausgabe zum Erfolgreichen Setzen eines Spielersymbols
    if(CheckSetSymbol == 1) { 
        mvprintw(1, 0, "Das Spielersymbol wurde erfolgreich auf %c gesetzt!", PlayerSymbol);
    }
    else if(CheckSetSymbol == 2) { 
        mvprintw(1, 0, "Das Spielersymbol wurde erfolgreich auf %c gesetzt!", PlayerSymbol);
    }
    else if(CheckSetSymbol == 3) { 
        mvprintw(1, 0, "Das Spielersymbol wurde erfolgreich auf %c gesetzt!", PlayerSymbol);
    }
    else if(CheckSetSymbol == 4) { 
        mvprintw(1, 0, "Das Spielersymbol wurde erfolgreich auf %c gesetzt!", PlayerSymbol);
    }

    //Setzt das Symbol auf den jeweils ausgewaehlten Spieler
    if(CheckSetPlayer == 1) {
        Player1Symbol = PlayerSymbol;
    }
    else if(CheckSetPlayer == 2) {
        Player2Symbol = PlayerSymbol;
    }
}

void ViewDifficultyPressedKeyCall(int pressedKey) { //Nehme die Tasteneingabe fuer die Schwierigkeitsgrad-Einstellungen entgegen
    switch (pressedKey) {
        case KEY_UP:
            ViewSettingsAusgabe = '^';
            ViewDifficultyIndex--;
            break;
        case KEY_DOWN:
            ViewSettingsAusgabe = 'v';
            ViewDifficultyIndex++;
            break;
        case KEY_LEFT:
            ViewSettingsAusgabe = '<';
            break;
        case KEY_RIGHT:
            ViewSettingsAusgabe = '>';
            break;
        case 'q':
            GameGet()->quit = 1;// Stoppe die Gameloop und beende das Spiel (TODO: Spaeter etfernen)
            break;
        case 'l':
            ViewDifficultyIndex = 0; //Zuruecksetzen des Symbol Indexes 
            GameGet()->pressedKeyCall = ViewSettingsPressedKeyCall; //Setze die Methode ViewSettingsPressedKeyCall um die Tasteneingabe in den Einstellungen entgegenzunehmen
            GameGet()->paintCall = ViewSettingsPaintCall; //Setze die Methode ViewSettingsPaintCall um die Einstellungen darzustellen
            break;
        case KEY_ENTER:
        case ' ':
        case '\n':
            switch (ViewDifficultyIndex) {
                case 0: //'Einfach'
                    Difficulty=1; //Schwierigkeit=Einfach
                    CheckSetDifficulty=1; //Wert fuer die Anzeige, bestaetigt das Setzen des Schwierigkeitgrades auf Einfach
                    break;
                case 1: //'Mittel'
                    Difficulty=2; //Schwierigkeit=Mittel
                    CheckSetDifficulty=2; //Wert fuer die Anzeige, bestaetigt das Setzen des Schwierigkeitgrades auf Mittel
                    break;
                case 2: //'Schwer'
                    Difficulty=3; //Schwierigkeit=Schwer
                    CheckSetDifficulty=3; //Wert fuer die Anzeige, bestaetigt das Setzen des Schwierigkeitgrades auf Schwer
                    break;
                case 3: //Back To Settings
                    ViewDifficultyIndex = 0; //Zuruecksetzen des Schwierigkeits Indexes 
                    GameGet()->pressedKeyCall = ViewSettingsPressedKeyCall; //Setze die Methode ViewSettingsPressedKeyCall um die Tasteneingabe in den Einstellungen entgegenzunehmen
                    GameGet()->paintCall = ViewSettingsPaintCall; //Setze die Methode ViewSettingsPaintCall um die Einstellungen darzustellen
                    break;
            }
            break;
    }
    if (ViewDifficultyIndex < 0) {
        ViewDifficultyIndex = 3;// Springe zum letzten Eintrag
    } 
    else if (ViewDifficultyIndex > 3) {
        ViewDifficultyIndex = 0;// Springe zum ersten Eintrag
    }
}

void ViewDifficultyPaintCall() { //Stelle die Schwierigkeitsgrad-Einstellungen dar
    mvprintw(0, 0, "Steuern mit Pfeiltasten, Beenden mit 'q'");
    mvprintw(3, 5, "%c", ViewSettingsAusgabe);

    mvprintw(5, 5, "Einfach");
    mvprintw(6, 5, "Mittel");
    mvprintw(7, 5, "Schwer");
    mvprintw(8, 5, "Back To Settings");

    mvprintw(ViewDifficultyIndex + 5, 4, ">");// Zeige das ausgewaehlte Element an

    //Anzeigeausgabe zum Erfolgreichen Setzen einer Schwierigkeit
    if(CheckSetDifficulty == 1) { 
        mvprintw(1, 0, "Die Schwierigkeit wurde erfolgreich auf Einfach gesetzt!");
    }
    else if(CheckSetDifficulty == 2) { 
        mvprintw(1, 0, "Die Schwierigkeit wurde erfolgreich auf Mittel gesetzt!");
    }
    else if(CheckSetDifficulty == 3) { 
        mvprintw(1, 0, "Die Schwierigkeit wurde erfolgreich auf Schwer gesetzt!");
    }  
}

void ViewPlayerPressedKeyCall(int pressedKey) { //Nehme die Tasteneingabe fuer die Player-Einstellungen (die vor den Symbol Einstellungen erscheint) entgegen
    switch (pressedKey) {
        case KEY_UP:
            ViewSettingsAusgabe = '^';
            ViewPlayerIndex--;
            break;
        case KEY_DOWN:
            ViewSettingsAusgabe = 'v';
            ViewPlayerIndex++;
            break;
        case KEY_LEFT:
            ViewSettingsAusgabe = '<';
            break;
        case KEY_RIGHT:
            ViewSettingsAusgabe = '>';
            break;
        case 'q':
            GameGet()->quit = 1;// Stoppe die Gameloop und beende das Spiel (TODO: Spaeter etfernen)
            break;
        case 'l':
            ViewPlayerIndex = 0; //Zuruecksetzen des Symbol Indexes 
            GameGet()->pressedKeyCall = ViewSettingsPressedKeyCall; //Setze die Methode ViewSettingsPressedKeyCall um die Tasteneingabe in den Einstellungen entgegenzunehmen
            GameGet()->paintCall = ViewSettingsPaintCall; //Setze die Methode ViewSettingsPaintCall um die Einstellungen darzustellen
            break;
        case KEY_ENTER:
        case ' ':
        case '\n':
            switch (ViewPlayerIndex) {
                case 0: //Player 1
                    CheckSetPlayer = 1; //Gibt an die Symbol Methode weiter, dass es sich um den ersten Spieler handelt
                    GameGet()->pressedKeyCall = ViewSymbolPressedKeyCall; //Ruft die Tasteneingabe fuer die Symbol Einstellungen auf
                    GameGet()->paintCall = ViewSymbolPaintCall; //Ruft die Paint Methode fuer die Symbol Einstellungen auf
                    break;
                case 1: //Player 2
                    CheckSetPlayer = 2; //Gibt an die Symbol Methode weiter, dass es sich um den zweiten Spieler handelt
                    GameGet()->pressedKeyCall = ViewSymbolPressedKeyCall; //Ruft die Tasteneingabe fuer die Symbol Einstellungen auf
                    GameGet()->paintCall = ViewSymbolPaintCall; //Ruft die Paint Methode fuer die Symbol Einstellungen auf
                    break;
                case 2: //Back To Settings
                    ViewPlayerIndex = 0; //Zuruecksetzen des Symbol Indexes 
                    GameGet()->pressedKeyCall = ViewSettingsPressedKeyCall; //Setze die Methode ViewSettingsPressedKeyCall um die Tasteneingabe in den Einstellungen entgegenzunehmen
                    GameGet()->paintCall = ViewSettingsPaintCall; //Setze die Methode ViewSettingsPaintCall um die Einstellungen darzustellen
                    break;
            }
            break;
    }
    if (ViewPlayerIndex < 0) {
        ViewPlayerIndex = 2;// Springe zum letzten Eintrag
    } 
    else if (ViewPlayerIndex > 2) {
        ViewPlayerIndex = 0;// Springe zum ersten Eintrag
    }
}

void ViewPlayerPaintCall() { //Stelle die Spieler-Einstellungen dar, die vor den Symbol Einstellungen erscheinen
    mvprintw(0, 0, "Steuern mit Pfeiltasten, Beenden mit 'q'");
    mvprintw(3, 5, "%c", ViewSettingsAusgabe);

    mvprintw(5, 5, "Spieler 1");
    mvprintw(6, 5, "Spieler 2");
    mvprintw(7, 5, "Back To Settings");

    mvprintw(ViewPlayerIndex + 5, 4, ">");// Zeige das ausgewaehlte Element an
}