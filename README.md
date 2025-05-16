# 🏰 Village Under Attack

**Village Under Attack** est un jeu de stratégie 2D en **C++**. Le joueur construit un village, collecte des ressources, recrute des troupes et défend son **Hôtel de Ville (TownHall)** contre les ennemis **Raiders**.

Deux versions sont disponibles :
- 🖥 **Mode graphique SDL2**
- 💻 **Mode console simple**

---

## 🎮 Fonctionnalités

- 🕹 Déplacement du joueur sur une carte 2D
- 🏗 Construction : TownHall, GoldMine, ElixirCollector, Wall, Barrack
- 💰 Collecte automatique de ressources
- 👾 Apparition de Raiders ennemis
- ⚔️ Entraînement de troupes : Barbarian et Archer
- 🛑 Fin de partie lorsque le TownHall est détruit

---

## 📂 Structure du projet

Village-under-attack/
├── assets/ # Textures PNG pour SDL2
├── include/ # Tous les fichiers .h
├── src/ # Tous les fichiers .cpp
├── main.cpp # Boucle principale SDL2
├── main_console.cpp # Version console
├── Makefile

markdown
Copier
Modifier

---

## 🧭 Organisation des classes

- `Entity` (abstraite)  
  ├── `Player`  
  └── `Npc`  
   ├── `Enemy` → `Raider`  
   └── `Troop` → `Barbarian`, `Archer`

- `Building`  
 ├── `Wall`  
 ├── `TownHall`  
 ├── `Barrack`  
 └── `ResourceGenerator`  
   ├── `GoldMine`  
   └── `ElixirCollector`

- Autres :
  - `Board` → gère la carte, bâtiments et entités
  - `Resources` → gestion de l’or et de l’élixir
  - `Position` → coordonnées (x, y)

---

## 🔁 Diagramme de classes

lua
Copier
Modifier
           Entity
             |
 -------------------------
 |                       |
Player Npc
|
-----------------------------
| |
Enemy Troop
| |
Raider ---------------|---------
| |
Barbarian Archer

markdown
Copier
Modifier
     Building
        |
| | | |
Wall TownHall ResourceGenerator Barrack
|
---------------------
| |
GoldMine ElixirCollector

yaml
Copier
Modifier

---

## 💡 Rôle des principales classes

| Classe           | Description                                               |
|------------------|-----------------------------------------------------------|
| `Entity`         | Base commune (joueur, troupes, ennemis)                   |
| `Player`         | Déplacement, construction, collecte                       |
| `Npc`            | Entités non-jouables                                      |
| `Raider`         | Ennemi attaquant bâtiments                                |
| `Troop`          | Unité alliée (Barbarian, Archer)                          |
| `Building`       | Base de tous les bâtiments                                |
| `GoldMine`       | Génère de l’or                                            |
| `ElixirCollector`| Génère de l’élixir                                        |
| `Wall`           | Barrière défensive                                        |
| `TownHall`       | Cœur du village : le protéger à tout prix                 |
| `Barrack`        | Permet d’entraîner des troupes                            |
| `Board`          | Carte du jeu et gestion globale                           |
| `Resources`      | Suivi de l’or et élixir                                   |
| `Position`       | Structure x/y                                             |

---

## 🎮 Commandes (SDL2)

| Touche            | Action                                |
|-------------------|----------------------------------------|
| Flèches           | Déplacer le joueur                     |
| `C`               | Collecter des ressources               |
| `G`, `E`, `W`     | Construire : GoldMine, Elixir, Wall    |
| `T`, `B`          | Construire : TownHall, Barrack         |
| `1`, `2`          | Entraîner : Barbarian, Archer          |
| `ESC`             | Quitter le jeu                         |

---

## 🎮 Commandes (console)

| Touche            | Action                                |
|-------------------|----------------------------------------|
| `w` `a` `s` `d`   | Déplacer le joueur (haut/gauche/bas/droite) |
| `c`               | Collecter des ressources               |
| `g`               | Construire une GoldMine (100 élixirs)  |
| `e`               | Construire un ElixirCollector (100 ors)|
| `v`               | Construire un Mur (10 ors)             |
| `q`               | Quitter le jeu                         |

---

## 🛠️ Installation (Linux / Ubuntu)

### Prérequis

```bash
sudo apt update
sudo apt install build-essential libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev
Compilation SDL2
bash
Copier
Modifier
make clean && make
./village2
Compilation Console
bash
Copier
Modifier
g++ -std=c++17 main_console.cpp src/*.cpp src/Entities/*.cpp src/Entities/Enemies/*.cpp src/buildings/*.cpp -o build/test_game
./build/test_game
📸 Aperçu



✅ Améliorations possibles
Ajouter un ennemi spécial Bomberman

Ajouter des tirs visuels pour les Archers

Intégrer un menu d’accueil via SDL2/SDL_ttf

Sauvegarde de la progression

