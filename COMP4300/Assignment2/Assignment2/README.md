# Game Project Documentation

- This project is a game whose goal is to score as many scores as possible and at the same time do not die (collide with enemies). 
  Scores can be obtained by destroying enemies, shooting them, or using special or ultimate abilities. Below is a description of how exactly this happens.

## Player

- **Shape**: Defined in the config file.
- **Spawn**: Appears at the center of the screen at the start and after death (collision with enemy).
- **Movement**: Controlled by **W** (Up), **A** (Left), **S** (Down), **D** (Right) keys, with speed from the config file.
- **Shooting**: Fires bullets toward the mouse pointer on left-click. Bullet speed, size, and lifespan are read from the config.

## Special Ability

- Fired using the right mouse button.
- Spawns a large bullet that does not destroy on collision with enemies, radius, life time and speed are read from a config.
- Includes a cooldown timer.

## Ultimate Ability

- Fired using the **Q** button.
- Spawns multiple entities that do not destroy on collision with enemies.
- A certain number of score points are spent when used (reads the number from the config file). 

## Enemies

- **Spawn**: Appear at random locations every X frames (X from the config). Do not spawn off-screen.
- **Shape**: Random number of vertices (between min and max from the config).
- **Color & Speed**: Randomly assigned, within the config-defined range.
- **Movement**: Bounce off screen edges at the same speed.
- **Collision**: Large enemies split into smaller ones on collision with the player or bullet. Number of smaller enemies equals the original enemy's vertices, and they travel outward at equal angles (360/vertices).

## Pause/Exit game

- Pressing the **P** button pauses the game, all processes except Rendering and userInput are stopped.
- Pressing the **ESC** button exits the game. 

## Score

- Enemies have a score of N * 100, where N is their number of vertices. Smaller enemies are worth double.
- The player's score increases by the value of destroyed enemies.
- Displayed at the top-left corner with a font specified in the config file.

## Rendering & Effects

- Entities rotate slowly for visual appeal.
- Lifespan-based alpha fading: Entities fade out as they approach the end of their lifespan, starting from alpha 255 and ending at 0.


# Configuration File:
- The configuration file will have one line each specifying the window size, 
  font format, player, bullet specification, enemy specifications, 
  special weapon specification and  ultimate abilitiy specificarion. 
  Lines will be given in that order, with the following syntax:


## Window W H FL FS
- This line declares that the SFML Window must be constructed with width W 
  and height H, each of which will be integers. FL is the frame limit that 
  the window should be set to, and FS will be an integer which specifies 
  whether to display the application in full-screen mode (1) or not (0).


## Font F S R G B
| Attribute            | Short Name ---| Type             |
|----------------------|---------------|------------------|
| **File path**         | F             | `std::string`    |
| **Font Size**         | S             | `int`            |
| **Font Color**        | R, G, B       | `int, int, int`  |
- This line defines the font which is to be used to draw text 
  for this program. The format of the line is as follows:


## Player SR CR S FR FG FB OR OG OB OT V
| Attribute            | Short Name ---| Type             |
|----------------------|---------------|------------------|
| **Shape Radius**      | SR            | `int`            |
| **Collision Radius**  | CR            | `int`            |
| **Speed**             | S             | `float`          |
| **Fill Color**        | FR, FG, FB    | `int, int, int`  |
| **Outline Color**     | OR, OG, OB    | `int, int, int`  |
| **Outline Thickness** | OT            | `int`            |
| **Shape Vertices**    | V             | `int`            |


## Enemy SR CR SMIN SMAX OR OG OB OT VMIN VMAX L SI
| Attribute            | Short Name ---| Type             |
|----------------------|---------------|------------------|
| **Shape Radius**      | SR            | `int`            |
| **Collision Radius**  | CR            | `int`            |
| **Min / Max Speed**   | SMIN,SMAX     | `float, float`   |
| **Outline Color**     | OR, OG, OB    | `int, int, int`  |
| **Outline Thickness** | OT            | `int`            |
| **Min/Max Vertices**  | VMIN,VMAX     | `int, int`       |
| **Small Lifespan**    | L             | `int`            |
| **Spawn Interval**    | SI            | `int`            |


## Bullet SR CR S FR FG FB OR OG OB OT V L CD
| Attribute            | Short Name ---| Type             |
|----------------------|---------------|------------------|
| **Shape Radius**      | SR            | `int`            |
| **Collision Radius**  | CR            | `int`            |
| **Speed**             | S             | `float`          |
| **Fill Color**        | FR, FG, FB    | `int, int, int`  |
| **Outline Color**     | OR, OG, OB    | `int, int, int`  |
| **Outline Thickness** | OT            | `int`            |
| **Shape Vertices**    | V             | `int`            |
| **Lifespan**          | L             | `int`            |
| **Cooldown**          | CD            | `int`            |


## SpecialWeapon SR CR S L CD
| Attribute            | Short Name ---| Type             |
|----------------------|---------------|------------------|
| **Shape Radius**      | SR            | `int`            |
| **Collision Radius**  | CR            | `int`            |
| **Speed**             | S             | `float`          |
| **Lifespan**          | L             | `int`            |
| **Cooldown**          | CD            | `int`            |


## UltimateAbilitiy S P L
| Attribute            | Short Name ---| Type             |
|----------------------|---------------|------------------|
| **Speed**             | S             | `float`          |
| **Price**             | P             | `int`            |
| **Lifespan**          | L             | `int`            |


# Game Project Architecture

- This game project is written using the [SFML](https://www.sfml-dev.org/) library and follows the **Entity-Component-System (ECS)** pattern.
  I've added the SFML library to the libraries folder in this repository, so the project should start and run without external installations.

### Main Components

- **Vec2 Class** (`Vec2.h`, `Vec2.cpp`):  
  The `Vec2` class represents a 2D vector used for handling positional and directional data. This class provides essential vector operations, such as addition, subtraction, scaling, and magnitude calculations, which are used to manage entity positions and movement within the game.

- **Components** (`Components.h`):  
  Components store the data required by entities in the game. These data structures can represent various aspects of an entity, such as:
  - **cTransform**: Represents the entity’s position, velocity (movement speed and direction) and angle in the game world.
  - **cShape**: Represents the entity’s shape which is created with the use of the SFML library.
  - **Other Components**: Can include collision, lifespan, input states, and more, depending on the entity. Components are simple and don’t contain behavior, just the data that systems will use.

- **Entity Class** (`Entity.h`, `Entity.cpp`):  
  The `Entity` class acts as a wrapper or container for one or more components. Entities are uniquely identified by IDs but have no inherent behavior. Their role is to aggregate different components, which define their characteristics.

- **EntityManager Class** (`EntityManager.h`, `EntityManager.cpp`):  
  The `EntityManager` is responsible for managing the lifecycle of entities. It allows:
  - Creation and destruction of entities.
  - Adding and removing components from entities.
  - Efficient storage and retrieval of components tied to entities.
  The `EntityManager` plays a key role in keeping track of all active entities and their components within the game world.

- **Game Class** (`Game.h`, `Game.cpp`):  
  The `Game` class serves as the core engine driving the game’s execution. It handles:
  - **Initialization**: Setting up the necessary entities, components, and systems.
  - **Game Loop**: The game loop is the heart of the engine, which runs continuously, updating the game state at regular intervals. It processes input, updates the state of entities, and renders the game.
  - **Input Handling**: It captures and processes player input, allowing interaction with the game world.
  - **System Updates**: The game’s various systems (e.g., movement, rendering, collision) are updated in each frame to reflect the current state of the game world.

- **Main Entry Point** (`main.cpp`):  
  The entry point of the application initializes the game and starts the game loop. This file is responsible for setting up the game instance and invoking the main `Game` class functions to drive the gameplay.

## How it Works

- **Entity-Component System (ECS) Architecture**:  
  This game uses an ECS model to achieve modularity and flexibility. Entities are composed of components, which are simple data containers. Systems, defined within the game’s core, act on entities by manipulating their components. The result is a flexible system where new features can be added by introducing new components and systems without modifying existing code.

- **Entity and Component Interaction**:  
  Entities are created using the `EntityManager`, which also manages their components. Systems are responsible for manipulating these components to produce the desired behavior. For example, a **sMovement** would update the `Position` and `Velocity` components based on calculations.

- **Game Loop**:  
  The `Game` class manages the main game loop, which drives the update-render cycle:
  1. **Input Processing**: Player inputs are captured and passed to the relevant systems.
  2. **Entity Update**: Systems update the state of entities, such as movement.
  3. **Rendering**: Finally, the game renders the current state of the entities to the screen.
  This loop runs continuously at a fixed interval (frames per second), ensuring the game is responsive and visually fluid.

## Summary

- This project’s architecture is designed to be both modular and efficient, leveraging the Entity-Component-System (ECS) pattern to clearly separate data from behavior. By organizing the code into entities, components, and systems, the game can easily scale, allowing for the seamless addition of new features and more complex gameplay without increasing codebase complexity. For instance, this architecture enables us to introduce new components, like `cPhysics`, transforming the game into a platformer. With the EntityManager and components, we can develop a variety of simple 2D games, such as Flappy Bird or Pac-Man."