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

# 📐 Diagramme de Classes - Village Under Attack

```mermaid
classDiagram
    %% =============================================
    %% CORE GAME CLASSES
    %% =============================================
    class Position {
        +int x
        +int y
    }

    class Resources {
        +int gold
        +int elixir
        +getGold() int
        +getElixir() int
        +spendGold(int) bool
        +spendElixir(int) bool
    }

    class Board {
        +vector~Building*~ buildings
        +vector~Entity*~ entities
        +addEntity(Entity*)
        +addBuilding(Building*)
        +render(SDL_Renderer*)
        +update()
    }

    %% =============================================
    %% ENTITY HIERARCHY
    %% =============================================
    class Entity {
        <<abstract>>
        #Position position
        #string repr
        +move(int dx, int dy)
        +update(Board&) virtual
        +render(SDL_Renderer*) virtual
    }

    class Player {
        +Resources resources
        +Interact(Board&)
        +collectResources(ResourceGenerator*)
    }

    class Npc {
        <<abstract>>
        +int health
        +int attackDamage
        +moveTowards(Board&, Position)
    }

    Entity <|-- Player
    Entity <|-- Npc

    %% ----------------------------
    %% NPC SUBCLASSES
    %% ----------------------------
    class Enemy {
        <<abstract>>
        +bool targeted
    }

    class Troop {
        <<abstract>>
        +int speed
        +attack(Board&)
    }

    Npc <|-- Enemy
    Npc <|-- Troop

    class Raider {
        +destroyBuilding(Building*)
    }

    class Barbarian {
        +meleeAttack()
    }

    class Archer {
        +rangeAttack()
    }

    Enemy <|-- Raider
    Troop <|-- Barbarian
    Troop <|-- Archer

    %% =============================================
    %% BUILDING HIERARCHY
    %% =============================================
    class Building {
        <<abstract>>
        #Position p
        #int sizeX
        #int sizeY
        #SDL_Texture* texture
        +collidesWith(Position) bool
        +render(SDL_Renderer*) virtual
    }

    %% ----------------------------
    %% BUILDING SUBCLASSES
    %% ----------------------------
    class TownHall {
        +bool destroyed
        +produceResources()
    }

    class Wall {
        +int defense
        +takeDamage(int)
    }

    class ResourceGenerator {
        <<abstract>>
        #int productionRate
        +collect(Resources&) virtual
    }

    class Barrack {
        +queue~Troop*~ trainingQueue
        +train(Troop*)
    }

    Building <|-- TownHall
    Building <|-- Wall
    Building <|-- ResourceGenerator
    Building <|-- Barrack

    class GoldMine {
        +mineGold()
    }

    class ElixirCollector {
        +collectElixir()
    }

    ResourceGenerator <|-- GoldMine
    ResourceGenerator <|-- ElixirCollector

    %% =============================================
    %% KEY RELATIONSHIPS
    %% =============================================
    Board "1" *-- "*" Entity
    Board "1" *-- "*" Building
    Player "1" --> "1" Resources
    Barrack "1" --> "*" Troop
    Raider "1" --> "1" Building : Attacks
    Troop "1" --> "1" Enemy : Attacks

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

