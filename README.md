# Cub3D

> *A 3D maze exploration game inspired by the legendary Wolfenstein 3D*

<div align="center">

![C](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)
![Linux](https://img.shields.io/badge/Linux-FCC624?style=for-the-badge&logo=linux&logoColor=black)

**Part of the 42 School curriculum**

</div>

---

## 📖 About

**Cub3D** is a graphical project that introduces fundamental concepts of raycasting and 3D rendering. The player navigates through a maze in first-person view, with textured walls, floor and ceiling colors, and smooth movement controls.

This project was a fascinating dive into how early 3D games created immersive experiences with limited computational resources. It covers mathematical concepts like trigonometry and vector operations, along with practical graphics programming using the **MiniLibX** library.

## Features

### Mandatory
- **First-person 3D perspective** using raycasting algorithms
- **Textured walls** with different textures for each cardinal direction (North, South, East, West)
- **Customizable floor and ceiling colors**
- **Smooth movement controls** with rotation and walking
- **Map validation** to ensure playable maze configurations
- **`.cub` file parsing** for custom map and texture definitions

### Bonus
- **Minimap** displaying the player's position and surroundings
- **Mouse controls** for camera rotation

## 🚀 Installation

### Prerequisites

- **Linux/macOS** (the project uses MiniLibX which is platform-specific)
- **gcc** compiler
- **make**
- **X11** development libraries (Linux) or **AppKit** (macOS)

### Building
```bash
# Clone the repository with submodules
git clone --recursive https://github.com/carowann/cub3d.git
cd cub3d

# Build mandatory version
make

# Or build with bonus features (minimap + mouse controls)
make bonus
```

> **Note:** The `--recursive` flag ensures the libft submodule is cloned properly.

## Usage

### Running the Game
```bash
./cub3D maps/example.cub
```

You can create your own `.cub` files following the format described below.

### Controls

| Action | Mandatory | Bonus |
|--------|-----------|-------|
| Move forward/backward | `W` / `S` or `↑` / `↓` | ✓ |
| Strafe left/right | `A` / `D` | ✓ |
| Rotate camera | `←` / `→` | ✓ |
| Rotate camera (mouse) | - | `Mouse movement` |
| Exit game | `ESC` or close window | ✓ |
| View minimap | - | Top-left corner |

## Map Configuration

Maps are defined in `.cub` files with the following format:
```
NO ./textures/north_wall.xpm
SO ./textures/south_wall.xpm
WE ./textures/west_wall.xpm
EA ./textures/east_wall.xpm

F 220,100,0
C 135,206,235

        1111111111111111111111111
        1000000000110000000000001
        1011000001110000000000001
        1001000000000000000000001
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

### Configuration Elements

| Element | Description |
|---------|-------------|
| `NO`, `SO`, `WE`, `EA` | Texture paths for North, South, West, East walls |
| `F` | Floor color in RGB format (0-255) |
| `C` | Ceiling color in RGB format (0-255) |
| `0` | Empty space (walkable) |
| `1` | Wall |
| `N/S/E/W` | Player starting position and orientation |

## Technical Highlights

- Implementation of **DDA raycasting algorithm** for efficient wall detection
- **Texture mapping** with proper scaling and alignment
- **Player movement and collision detection**
- Robust **error handling** for invalid maps and configurations
- **Memory-safe** implementation with no leaks

## Learning Outcomes

This project solidified my understanding of:

- Low-level graphics programming
- Mathematical concepts in game development (vectors, trigonometry)
- Event handling and game loops
- Parser implementation for custom file formats
- Working with external graphics libraries
- Collaborative development and task distribution

## 👥 Collaboration

<table>
  <tr>
    <td align="center">
      <a href="https://github.com/carowann">
        <img src="https://github.com/carowann.png" width="100px;" alt="Caroline"/><br />
        <sub><b>Caroline</b></sub>
      </a><br />
      <sub>cwannhed (Intra 42)</sub><br />
      <sub>Raycasting & Rendering</sub>
    </td>
    <td align="center">
      <a href="https://github.com/gimasss">
        <img src="https://github.com/gimasss.png" width="100px;" alt="Giorgia"/><br />
        <sub><b>Giorgia</b></sub>
      </a><br />
      <sub>giomastr (Intra 42)</sub><br />
      <sub>Parsing & Bonus Features</sub>
    </td>
  </tr>
</table>

This collaboration was an excellent opportunity to learn about code integration, communication, and working as a team on a complex technical project.

## Acknowledgments

Built as part of the **42 School curriculum**. The project subject and constraints were designed to teach fundamental computer graphics concepts through hands-on implementation.

---

<div align="center">

*This project represents my growing proficiency in C programming and systems-level development, building on the foundations established in previous 42 projects.*

**[🔗 My 42 Profile](https://profile.intra.42.fr/users/cwannhed)**

</div>
