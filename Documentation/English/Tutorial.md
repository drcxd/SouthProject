# Tutorial on how to write script

# General Idea
## Scene

This program split a visual novel game into **scene**s. In other
words, the game consists of scenes. At the final of each scene, the
player will be offered a choice. Accoring to the choice, the player 
will be sent to the next scene.

Each scene is defined by the background image, character image, text
which is going to be displayed and background music.

## Page

A scene consists of several pages. A page is a collection of elements
that are going to be displayed to the player. These elements includes
background image, character image, text and music.

# Technical Specification

The script file using xml to document everything. In the xml file, the
root node is a node called `SCENES`. The children nodes of the root node
corresponds to actual scenes.

For a scene node, you have to specify the following things.

- The ID of this scene, other scene may use the ID to reference it.
- Number of page
- The path to a text file which contains the text of this scene and a
  string of numbers which represents each page will consume how many
  lines of the text file.
- The path to music file(s) which is going to played in this
  scene. Each music file will have properties of a name and how many
  pages it lasts.
- A list of objects which is going to be used as background and
  character. Each object is defined by its position, width, height,
  the image ID it is used to reference an image and the ID for the
  object itself.
- The background list. In the list, you have to specify the object ID
  of the background and how many pages you would like it to last.
- The figure list. In this list, you have to specify the object ID of
  the figure and how many pages you would like it to last.
- Finally you have to add a choice list. Each choice must specify the
  following scene.