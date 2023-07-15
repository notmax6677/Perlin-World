# Perlin-World
Perlin-Noise based OpenGL program that depicts a primitive Minecraft-like world map.

<div align=center>
  <img src="perlin-world.gif" alt="Program Preview" width=500 />

  <i>sorry for bad gif quality lol</i>
</div>

So i've never really worked with perlin noise up until now so i've just wanted to do something small to display my understanding of it.
My end-goal that i hope to getting around to is making an OpenGL based minecraft clone from scratch, like the youtuber JDH did, so you'd figure how this is kind of a step in that direction.

This program uses <a href="https://github.com/Reputeless/PerlinNoise" target="_blank">Reputeless' Perlin Noise Library</a> as a base to actually generate the noise necessary, im pretty much just visualizing it in a pretty way here.

You can build this project with the `Makefile` in `./bin`, the `.exe` format is already there cus i developed this project on Windows.

When running the app, press `space` to generate another "world" and have it render onto the screen instead of the current one.
Also feel free to change the couple of (self-explanatory) values in `./src/headers/settings.hpp`, but then remember to actually build the program once again :)
