#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QVector>

class Game : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int score READ score NOTIFY actualisationScore)
    Q_PROPERTY(QVector<int> plateau READ plateau NOTIFY actualisationPlateau)

public:
    explicit Game(QObject *parent = nullptr);

    int score() const;
    QVector<int> plateau() const;

    Q_INVOKABLE void mouvement(const QString &direction);
    Q_INVOKABLE void recommencer();

signals:
    void actualisationScore();
    void actualisationPlateau();
    void victoire();
    void defaite();

private:
    int var_score;
    int mat_plateau[4][4];

    void tuileAleatoire();
    bool mouvementLigne(int line[4]);
    bool mouvementPossible() const;
    bool checkVictoire() const;
};

#endif // GAME_H
