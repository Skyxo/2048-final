# 2048

**Auteurs :** Charles BERGEAT et Aurélien BIDOU
**Encadrant :** S. Derrode

---

## Description

Jeu 2048 développé en C++ avec Qt/QML. Le principe est de déplacer les tuiles avec les flèches directionnelles du clavier, les tuiles identiques fusionnent, et on essaie d'atteindre 2048.

---

## Instructions pour lancer le jeu

Ouvrir le projet dans Qt Creator, configurer un kit Qt 6, et lancer. Ou en ligne de commande :

```bash
mkdir build && cd build
cmake ..
cmake --build .
./2048
```

---

## Contrôles

Flèches directionnelles pour déplacer les tuiles, bouton Rejouer pour recommencer.

---

## Architecture

On a séparé la logique du jeu (classe `Game` en C++) de l'interface (QML). `Game` hérite de `QObject` et est exposée à QML via `setContextProperty`. Les signaux Qt gèrent la mise à jour de l'affichage.

- `game.h` / `game.cpp` : logique du jeu, déplacements, fusions, score, détection victoire/défaite
- `Main.qml` : interface graphique, grille, score, overlay fin de partie
- `main.cpp` : point d'entrée, lien entre C++ et QML

---

## Ce qui fonctionne

Tout ce qu'on avait prévu a été implémenté. Les déplacements dans les 4 directions, fusions, score, apparition de nouvelles tuiles, détection victoire (2048) et défaite (plus aucun mouvement possible), et le bouton rejouer.

Nous avons repris les couleurs du jeu original pour un maximum de réalisme avec "html picker" sur internet.

---

## Difficultés rencontrées

Le problème principal venait du focus clavier où il fallait bien mettre `focus: true` sur le `Rectangle` racine en QML sinon les touches ne sont pas détectées, ce qui nous a bloqués pendant un moment.

Aussi, pour afficher le plateau à QML on retourne un `QVector<int>` aplati, ce qui demande d'être précautionneux pour que la grille s'affiche dans le bon ordre.

---

## Captures d'écran

<img width="633" height="749" alt="image" src="https://github.com/user-attachments/assets/88fc357c-1919-4e82-b947-87cce0d80ed1" />
