# cub3D - My First RayCaster with miniLibX

🎮 **Project Repository:** [https://github.com/phlvnhalime/Cub3d.git](https://github.com/phlvnhalime/Cub3d.git)

## 📋 Table of Contents
- [Project Overview](#-project-overview)
- [Goals & Objectives](#-goals--objectives)
- [Technical Requirements](#-technical-requirements)
- [Getting Started](#-getting-started)
- [Implementation Steps](#-implementation-steps)
- [File Structure](#-file-structure)
- [Scene File Format (.cub)](#-scene-file-format-cub)
- [Controls](#-controls)
- [Bonus Features](#-bonus-features)
- [Testing](#-testing)
- [Resources](#-resources)

## 🎯 Project Overview

Create a **"realistic" 3D graphical representation** of a maze from a first-person perspective using **Ray-Casting principles**, inspired by the legendary Wolfenstein 3D (1992) - the first true First Person Shooter in gaming history.

### What is Ray-Casting?
Ray-casting is a rendering technique that creates a 3D perspective by casting rays from the player's position to determine wall distances and heights, creating the illusion of 3D depth on a 2D screen.

## 🎯 Goals & Objectives

### Primary Learning Goals:
- **Rigor and C Programming**: Strengthen C programming skills and algorithmic thinking
- **Graphics Programming**: Master window management, colors, events, and shape rendering
- **Mathematical Applications**: Apply mathematics practically without deep theoretical understanding
- **Algorithm Development**: Create elegant and efficient rendering algorithms

### Core Technical Objectives:
1. ✅ Implement ray-casting algorithm from scratch
2. ✅ Create smooth window management and event handling
3. ✅ Parse and validate scene description files (.cub)
4. ✅ Render textured walls with directional textures
5. ✅ Handle player movement and rotation
6. ✅ Display floor and ceiling with different colors

## ⚙️ Technical Requirements

### Programming Language & Standards
- **Language**: C
- **Coding Standard**: 42 Norm compliance
- **Compilation**: `cc` with flags `-Wall -Wextra -Werror`
- **Memory Management**: No memory leaks, proper heap management

### Required Libraries & Functions

#### External Functions Allowed:
```c
// File operations
open, close, read, write

// Standard functions  
printf, malloc, free, perror, strerror, exit

// Math library (-lm)
All functions from math.h

// miniLibX library
All miniLibX functions
```

#### Graphics Library:
- **miniLibX**: Either system version or compile from sources
- Handle smooth window operations (minimize, switch windows, etc.)

### System Requirements
- **libft**: Authorized for use (copy sources + Makefile to libft/ folder)
- **Makefile**: Must include `$(NAME)`, `all`, `clean`, `fclean`, `re`, `bonus`

## 🚀 Getting Started

### 1. Clone the Repository
```bash
git clone git@github.com:phlvnhalime/Cub3d.git
cd Cub3d
```

### 2. Install Dependencies
```bash
# Install miniLibX (if not already installed)
# On macOS: brew install minilibx
# On Linux: Follow miniLibX installation guide
```

### 3. Test the Original Game
Before starting development, experience the original Wolfenstein 3D:
**URL**: http://users.atw.hu/wolf3d/

## 🛠️ Implementation Steps

### Phase 1: Project Setup
1. **Initialize project structure**
   - Create Makefile with required rules
   - Set up libft integration
   - Configure compilation flags

2. **miniLibX Integration**
   - Include miniLibX headers
   - Test basic window creation
   - Implement event handling framework

### Phase 2: File Parsing System
1. **Scene File Parser (.cub)**
   - Parse texture paths (NO, SO, WE, EA)
   - Parse colors (F, C with RGB values)
   - Validate file format and content

2. **Map Validation**
   - Check map characters (0, 1, N, S, E, W)
   - Ensure map is surrounded by walls
   - Validate player starting position

### Phase 3: Core Ray-Casting Engine
1. **Ray-Casting Algorithm**
   - Cast rays from player position
   - Calculate wall distances
   - Determine wall heights for rendering

2. **Rendering System**
   - Draw walls with correct heights
   - Apply textures based on wall direction
   - Render floor and ceiling colors

### Phase 4: Player Controls & Movement
1. **Input Handling**
   - WASD movement keys
   - Arrow keys for rotation
   - ESC and window close events

2. **Player Physics**
   - Smooth movement calculations
   - Rotation mechanics
   - Boundary collision detection

### Phase 5: Testing & Optimization
1. **Error Handling**
   - Invalid file format detection
   - Memory leak prevention
   - Graceful error messages

2. **Performance Optimization**
   - Smooth frame rendering
   - Efficient ray calculations

## 📁 File Structure

```
Cub3d/
├── Makefile
├── README.md
├── src/
│   ├── main.c
│   ├── parsing/
│   │   ├── file_parser.c
│   │   ├── map_validator.c
│   │   └── scene_loader.c
│   ├── raycasting/
│   │   ├── ray_engine.c
│   │   ├── wall_calculator.c
│   │   └── texture_mapper.c
│   ├── rendering/
│   │   ├── renderer.c
│   │   ├── window_manager.c
│   │   └── image_handler.c
│   ├── player/
│   │   ├── movement.c
│   │   ├── rotation.c
│   │   └── controls.c
│   └── utils/
│       ├── error_handler.c
│       ├── math_utils.c
│       └── cleanup.c
├── includes/
│   ├── cub3d.h
│   └── constants.h
├── libft/
│   └── [libft files]
├── maps/
│   ├── valid_map.cub
│   ├── test_map.cub
│   └── invalid_examples/
├── textures/
│   ├── north_wall.xpm
│   ├── south_wall.xpm
│   ├── east_wall.xpm
│   └── west_wall.xpm
└── bonus/
    └── [bonus implementation files]
```

## 📄 Scene File Format (.cub)

### Required Elements:
```
NO ./path_to_the_north_texture
SO ./path_to_the_south_texture  
WE ./path_to_the_west_texture
EA ./path_to_the_east_texture

F 220,100,0
C 225,30,0

111111111111111111111111
100000000011000000000001
101100000111000000000001
100100000000000000000001
111111111011000001110000000000001
100000000011000001110111111111111
11110111111111011100000010001
11110111111111011101010010001
11000000110101011100000010001
10000000000000001100000010001
10000000000000001101010010001
11000001110101011111011110N0111
11110111 1110101 101111010001
11111111 1111111 111111111111
```

### Format Rules:
- **Textures**: `NO/SO/WE/EA ./path_to_texture`
- **Colors**: `F/C R,G,B` (range 0-255)
- **Map Characters**: 
  - `0` = Empty space
  - `1` = Wall  
  - `N/S/E/W` = Player start position and orientation
- **Map Requirements**: 
  - Must be surrounded by walls
  - Must be the last element in file
  - Only one player position allowed

### Example Valid Map:
```
111111
100101  
101001
1100N1
111111
```

## 🎮 Controls

### Movement:
- **W**: Move forward
- **S**: Move backward  
- **A**: Strafe left
- **D**: Strafe right

### Camera:
- **←**: Look left
- **→**: Look right

### System:
- **ESC**: Exit program
- **Red X**: Close window and exit

## 🏆 Bonus Features

⚠️ **Important**: Bonuses only evaluated if mandatory part is PERFECT (100% score)

### Available Bonuses:
1. **Wall Collisions** - Prevent walking through walls
2. **Minimap System** - Real-time overhead view
3. **Interactive Doors** - Doors that open/close
4. **Animated Sprites** - Moving characters/objects
5. **Mouse Look** - Rotate view with mouse

### Bonus Implementation Notes:
- Use separate `_bonus.{c/h}` files
- Include `bonus` rule in Makefile
- Modify scene file format as needed
- Document bonus features clearly

## 🧪 Testing

### Test Categories:

#### 1. File Parsing Tests:
```bash
./cub3D maps/valid_map.cub          # Should work
./cub3D maps/invalid_chars.cub      # Should show error
./cub3D maps/no_walls.cub           # Should show error
./cub3D maps/multiple_players.cub   # Should show error
```

#### 2. Error Handling Tests:
```bash
./cub3D                             # Missing arguments
./cub3D nonexistent.cub             # File not found
./cub3D maps/invalid_texture.cub    # Invalid texture path
```

#### 3. Gameplay Tests:
- Movement in all directions
- Rotation smoothness
- Wall collision detection
- Window management (minimize/restore)
- Clean exit with ESC

### Recommended Test Maps:
Create various test scenarios:
- Large open spaces
- Narrow corridors  
- Complex maze layouts
- Different starting orientations
- Edge cases (single room, etc.)

## 📚 Resources

### Ray-Casting Tutorials:
- [Ray-Casting Tutorial](https://lodev.org/cgtutor/raycasting.html)
- [Wolfenstein 3D Ray-Casting](https://www.playfuljs.com/a-first-person-engine-in-265-lines/)

### miniLibX Documentation:
- [miniLibX Man Pages](https://harm-smits.github.io/42docs/libs/minilibx)
- [42 Graphics Programming Guide](https://42-cursus.gitbook.io/guide/rank-02/minilibx)

### Mathematical Resources:
- [Trigonometry for Game Programming](https://www.khanacademy.org/math/trigonometry)
- [2D Vector Mathematics](https://www.mathsisfun.com/algebra/vectors.html)

### Original Game:
- **Play Wolfenstein 3D**: http://users.atw.hu/wolf3d/

## 🎮 Expected Output Examples

The program should create a first-person view similar to:
- Textured walls based on direction
- Smooth movement and rotation
- Proper perspective rendering
- Different colored floor and ceiling
- Clean, responsive graphics

---

**Good luck with your ray-casting adventure!** 🚀

Remember: This project combines graphics programming, mathematical algorithms, and game development principles. Take time to understand each component before moving to the next phase.

---
*Created for 42 School cub3D project*
