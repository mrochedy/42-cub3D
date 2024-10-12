# 42-cub3D, by Maxime Rochedy and Hélios Daher

Welcome to our repository for **cub3D**, a 3D game engine project we developed as part of our studies at **École 42**. This project earned the perfect score of **125/100**, with all available bonuses. These additional features include **wall collisions**, a **minimap**, **openable and closable doors**, **animations**, and the ability to **move the viewpoint using the mouse**—not just with the keyboard arrows.

This version of **cub3D** is **cross-compatible** between **Linux** and **macOS**, allowing it to run smoothly on both platforms. In this repository, you'll find everything you need to compile and play the game on either system. Even though it was carefully crafted and was evaluated by three different students, errors may still exist. Your feedback is highly appreciated!

<img width="198" alt="125/100 grade" src="https://github.com/user-attachments/assets/708486c1-c045-40d6-ab0c-e5dc3650a50d">

## About the Project

**Cub3D** is an advanced project in the 42 curriculum that introduces students to fundamental 3D rendering techniques using **raycasting**. Inspired by early FPS games like **Wolfenstein 3D**, the game aims to immerse the player in a maze-like environment, where they must navigate and interact with the surroundings.

This project was developed by **Maxime Rochedy** (**mrochedy**) and **Hélios Daher** (**hdaher**), as part of the 42 common core. The objective was to understand the inner workings of a simple 3D engine, using **C** and the **MiniLibX** graphics library to manage rendering, interactions, and game physics. With a cross-compatible design, our **cub3D** can run on both Linux and macOS, ensuring a broader accessibility.

Please note that while this code is provided for **learning purposes**, you should not copy it for your own submissions. Using this repository responsibly will help you deepen your understanding of graphics programming and 3D game development. Please respect the 42 school's policies on plagiarism.

## Getting Started

This project is compatible on Linux and macOS.

> If you are on macOS, make sure you have installed Xcode Command Line Tools.

To try the game, start by cloning the repository as follows:

```bash
git clone https://github.com/mrochedy/42-cub3D.git
cd 42-cub3D
```

Then build and launch the game:

```bash
make
./cub3D [map_file.cub]
```

The map file should be in the `.cub` format, as specified by the **cub3D** requirements. A `maps` folder is provided at the root of the repository, containing a variety of maps for testing and exploration.

### Map Requirements

Maps must conform to the **cub3D** project specifications, which are the following:

- The map must be composed of only **6** possible characters: `0` for an empty space, `1` for a wall, and `N`, `S` ,`E` or `W` for the player’s start position and spawning orientation.
- The map must be **closed/surrounded** by walls.
- Except for the map content, each type of element can be separated by one or more empty line(s).
- Except for the map content which always has to be the last, each type of element can be set in any order in the file.
- Except for the map, each type of information from an element can be separated by one or more space(s).
- The map must be parsed **as it looks** in the file. Spaces are a **valid** part of the map.
- Each element (except the map) first information is the **type identifier** (composed by one or two character(s)), followed by all **specific informations** for each object in a strict order such as :
  - NO ./path_to_the_north_texture
  - SO ./path_to_the_south_texture
  - WE ./path_to_the_west_texture
  - EA ./path_to_the_east_texture
  - F 220,100,0 _(Floor color)_
  - C 225,30,0 _(Ceiling color)_

The `maps` folder also includes some invalid maps for testing purposes. Feel free to create your own maps to enhance the gameplay experience, but make sure they follow the rules of the **cub3D** project.

## Contributing

If you find this version of **cub3D** useful or have any suggestions for improvements, feel free to **⭐️ star ⭐️** the repository or create a pull request. Contributions are always welcome, but please do not submit this code as your own for official 42 project submissions. Let’s keep the learning experience authentic!

Thank you for visiting, and happy coding!
