# 🏰 Village Under Attack

**Village Under Attack** est un jeu de stratégie 2D en **C++**. Le joueur construit un village, collecte des ressources, recrute des troupes et défend son **Hôtel de Ville (TownHall)** contre des ennemis appelés **Raiders**.

Deux versions sont disponibles :

- 🖥️ **Mode graphique SDL2**
- 💻 **Mode console (texte uniquement)**

---

## 🎮 Fonctionnalités

- 🕹️ Déplacement du joueur sur une carte 2D
- 🏗️ Construction de bâtiments : TownHall, GoldMine, ElixirCollector, Wall, Barrack
- 💰 Génération automatique de ressources
- 👾 Apparition automatique de Raiders ennemis
- ⚔️ Entraînement de troupes (Barbarian, Archer)
- 🛑 Fin de partie si le TownHall est détruit

---

## 📁 Structure du projet

Village-under-attack/
├── assets/ # Textures PNG pour SDL2
├── include/ # Fichiers d'en-tête .h
├── src/ # Fichiers source .cpp
├── main.cpp # Boucle principale SDL2
├── main_console.cpp # Version console du jeu
├── Makefile # Script de compilation

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
    - `Board` : Gère la carte, les entités et les bâtiments
    - `Resources` : Gère l’or et l’élixir
    - `Position` : Représente une position (x, y)

---

## 📐 Diagramme de classes (textuel)

mathematica
+----------------+               +------------------+
|    Position    |<--------------|      Entity      |
+----------------+               +------------------+
| int x, y       |               | Position         |
+----------------+               | texturePath      |
                                 | SDL_Texture*     |
                                 +------------------+
                                         ▲
                                         |
                    +--------------------+--------------------+
                    |                                         |
              +-------------+                          +-------------+
              |    Player   |                          |     Npc     |
              +-------------+                          +-------------+
              | Resources   |                          | int health  |
              +-------------+                          +-------------+
                    ▲                                         ▲
                    |                                         |
             +------------+                             +-----------+
             |  Troop     |                             |  Enemy    |
             +------------+                             +-----------+
             | health      |                             | attackDmg |
             | attackDmg   |                             +-----------+
             | attackRange |                                   ▲
             | speed       |                                   |
             +------------+                             +-------------+
                 ▲  ▲                                   |   Raider    |
                 |  |                                   +-------------+
      +----------+  +-----------+                       | moveDelay   |
      |                       |                         +-------------+
+-------------+       +-------------+
|  Barbarian  |       |   Archer    |
+-------------+       +-------------+

+------------------------+
|      Resources         |
+------------------------+
| int gold, elixir       |
+------------------------+

+------------------------+
|        Board           |
+------------------------+
| SizeX, SizeY           |
| vector<Building*>      |
| vector<Entity*>        |
| Player*                |
| TownHall*              |
+------------------------+

+------------------------+
|       Building         |
+------------------------+
| Position, sizeX/Y      |
| texturePath            |
| Resources cost         |
| int maxInstances       |
| int health             |
+------------------------+
            ▲
            |
   +--------+---------+
   |        |         |
+--------+ +------------------+ +----------------+ +-------------+ +------------+
| Wall   | | TownHall         | | ResourceGenerator | |   Barrack   | | GoldMine  |
+--------+ +------------------+ +----------------+ +-------------+ +------------+
                                       ▲                          ▲
                                       |                          |
                            +------------------+        +-------------------+
                            | ElixirCollector  |        |      Train()      |
                            +------------------+        +-------------------+

---

## 🧠 Rôle des principales classes

| Classe | Description |
| --- | --- |
| `Entity` | Base commune (joueur, troupes, ennemis) |
| `Player` | Déplacement, interaction, construction |
| `Npc` | Entités non contrôlées par le joueur |
| `Raider` | Ennemi attaquant les bâtiments |
| `Troop` | Unité alliée (Barbarian ou Archer) |
| `Building` | Classe de base de tout bâtiment |
| `GoldMine` | Génère automatiquement de l’or |
| `ElixirCollector` | Génère automatiquement de l’élixir |
| `Wall` | Défense fixe contre les ennemis |
| `TownHall` | Centre du village, perte si détruit |
| `Barrack` | Permet de produire des troupes |
| `Board` | Gère toute la logique du plateau de jeu |
| `Resources` | Gère l’or et l’élixir du joueur |
| `Position` | Coordonnées (x, y) dans la grille |

---

## 🎮 Commandes du jeu

### 🖥️ Version SDL2 (graphique)

| Touche | Action |
| --- | --- |
| Flèches | Déplacement du joueur |
| `C` | Collecter les ressources |
| `G`, `E`, `W` | Construire : GoldMine, Elixir, Wall |
| `T`, `B` | Construire : TownHall, Barrack |
| `1`, `2` | Entraîner : Barbarian, Archer |
| `ESC` | Quitter le jeu |

### 💻 Version console (texte)

| Touche | Action |
| --- | --- |
| `w`, `a`, `s`, `d` | Déplacement (haut, gauche, bas, droite) |
| `c` | Collecter les ressources |
| `g` | Construire une GoldMine (100 élixirs) |
| `e` | Construire un ElixirCollector (100 or) |
| `v` | Construire un Mur (10 or) |
| `q` | Quitter le jeu |

---

## ⚙️ Installation & Compilation (Linux)

### 1. Installer les dépendances

```bash
sudo apt update
sudo apt install build-essential libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev
2. Compilation SDL2 (graphique)
bash
Copier
Modifier
make clean && make
./village2
3. Compilation console
bash
Copier
Modifier
g++ -std=c++17 main_console.cpp src/*.cpp src/Entities/*.cpp src/Entities/Enemies/*.cpp src/buildings/*.cpp -o build/test_game
./build/test_game
```
