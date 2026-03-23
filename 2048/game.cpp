#include "game.h"
#include <QRandomGenerator>
#include <algorithm>

// Constructeur
Game::Game(QObject *parent) : QObject(parent)
{
    recommencer();
}

// Getters
int Game::score() const
{
    return var_score;
}

QVector<int> Game::plateau() const
{
    QVector<int> flat;
    for (int r = 0; r < 4; r++)
        for (int c = 0; c < 4; c++)
            flat.append(mat_plateau[r][c]);
    return flat;
}

// Recommencer
void Game::recommencer()
{
    var_score = 0;
    for (int r = 0; r < 4; r++)
        for (int c = 0; c < 4; c++)
            mat_plateau[r][c] = 0;

    tuileAleatoire();
    tuileAleatoire();

    emit actualisationScore();
    emit actualisationPlateau();
}

// Ajout d'une tuile aléatoire
void Game::tuileAleatoire()
{
    QVector<QPair<int,int>> empty;
    for (int r = 0; r < 4; r++)
        for (int c = 0; c < 4; c++)
            if (mat_plateau[r][c] == 0)
                empty.append({r, c});

    if (empty.isEmpty()) return;

    int idx = QRandomGenerator::global()->bounded(empty.size());
    int value = (QRandomGenerator::global()->bounded(10) < 9) ? 2 : 4;
    mat_plateau[empty[idx].first][empty[idx].second] = value;
}

// Déplacement d'une ligne vers la gauche
bool Game::mouvementLigne(int line[4])
{
    bool changed = false;

    // Tasser les tuiles (supprimer les zéros)
    int temp[4] = {0, 0, 0, 0};
    int pos = 0;
    for (int i = 0; i < 4; i++)
        if (line[i] != 0)
            temp[pos++] = line[i];

    // Fusionner les tuiles identiques adjacentes
    for (int i = 0; i < 3; i++) {
        if (temp[i] != 0 && temp[i] == temp[i+1]) {
            temp[i] *= 2;
            var_score += temp[i];
            temp[i+1] = 0;
        }
    }

    // Retasser après fusion
    int result[4] = {0, 0, 0, 0};
    pos = 0;
    for (int i = 0; i < 4; i++)
        if (temp[i] != 0)
            result[pos++] = temp[i];

    // Vérifier si la ligne a changé
    for (int i = 0; i < 4; i++) {
        if (line[i] != result[i]) changed = true;
        line[i] = result[i];
    }

    return changed;
}

// Déplacements dans les 4 directions
void Game::mouvement(const QString &direction)
{
    bool changed = false;

    if (direction == "left") {
        for (int r = 0; r < 4; r++)
            if (mouvementLigne(mat_plateau[r])) changed = true;
    }
    else if (direction == "right") {
        for (int r = 0; r < 4; r++) {
            int line[4] = { mat_plateau[r][3], mat_plateau[r][2], mat_plateau[r][1], mat_plateau[r][0] };
            if (mouvementLigne(line)) {
                changed = true;
                mat_plateau[r][3] = line[0]; mat_plateau[r][2] = line[1];
                mat_plateau[r][1] = line[2]; mat_plateau[r][0] = line[3];
            }
        }
    }
    else if (direction == "up") {
        for (int c = 0; c < 4; c++) {
            int line[4] = { mat_plateau[0][c], mat_plateau[1][c], mat_plateau[2][c], mat_plateau[3][c] };
            if (mouvementLigne(line)) {
                changed = true;
                mat_plateau[0][c] = line[0]; mat_plateau[1][c] = line[1];
                mat_plateau[2][c] = line[2]; mat_plateau[3][c] = line[3];
            }
        }
    }
    else if (direction == "down") {
        for (int c = 0; c < 4; c++) {
            int line[4] = { mat_plateau[3][c], mat_plateau[2][c], mat_plateau[1][c], mat_plateau[0][c] };
            if (mouvementLigne(line)) {
                changed = true;
                mat_plateau[3][c] = line[0]; mat_plateau[2][c] = line[1];
                mat_plateau[1][c] = line[2]; mat_plateau[0][c] = line[3];
            }
        }
    }

    if (changed) {
        tuileAleatoire();
        emit actualisationPlateau();
        emit actualisationScore();
    }

    if (checkVictoire())  emit victoire();
    if (!mouvementPossible())  emit defaite();
}

// Vérification victoire
bool Game::checkVictoire() const
{
    for (int r = 0; r < 4; r++)
        for (int c = 0; c < 4; c++)
            if (mat_plateau[r][c] == 2048) return true;
    return false;
}

// Vérification défaite
bool Game::mouvementPossible() const
{
    for (int r = 0; r < 4; r++)
        for (int c = 0; c < 4; c++) {
            if (mat_plateau[r][c] == 0) return true;
            if (c < 3 && mat_plateau[r][c] == mat_plateau[r][c+1]) return true;
            if (r < 3 && mat_plateau[r][c] == mat_plateau[r+1][c]) return true;
        }
    return false;
}
