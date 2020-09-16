# SouthProject

This is a prototype for a visual novel game engine. At least this is
what I intended to do.

It is developed upon SDL2.

The project is developed during the last moths of my undergraduate
period as an attempt to learn programming and developing game. The
framework of the project was mainly learned from \[1\].

The repository is a little bit messy. I was not familiar with the
convention how a program should be organized. So I almost put
everything together, source code, library, image, music, script and
save files. Usually only the source code, library and other text-based
files should be uploaded to github but I could not find a better way
to distribute the assets of the game. Since this is only a little
prototype and there is no munch assets, I just uploaded them in the
repository.

This project is developed using Microsoft Visual Studio and could be
compiled and run using VS 2019. 

Detailed documentation is in `Documentation` directory.

## Compile

Open the solution file in VS 2019 and build the soluiton. Please use
X64 Debug configuration. I have not set up the right include directory
and link input for other configurations.

## Run

Before you run the game, you should copy the dlls required by the
program into the directory where the game program is. It should be
`x64/Debug/`. The dlls requried are provided in the `dll` directory.

## How to play

The program only accept keyboard and mouse input. However, you could
only use mouse to interact with UI and only keyboard to interact with
the options.

| Key     | Description            |
| ESC     | Menu                   |
| UP/Down | Scroll between options |
| Enter   | Confirm                |

## For English Speaker

The text of the game is written in Chinese which is my mother
tongue. Although it is easy to modify the script to translate the
content to English, I decide not to do so yet. It is better we have a
localization solution for this problem.

# 南方Project

这是一个视觉小说游戏引擎的原型。至少这是我曾经想做的东西。

它依赖于SDL2。

该项目是我在大学期间的最后几个月开发的，作为一个学习编程与开发游戏的尝
试。代码的框架主要借鉴自[1]。

这个代码库很混乱。我当初对于如何组织程序代码毫无了解，所以我把几乎所有
东西都放到一起，源代码，库，图片，音乐，脚本以及存档文件。一般来说，
github只用来分享源代码与文档或其他基于文本的文件，但是我并没有更好的分
配游戏需要用的资源的方式。这只是一个小项目，并且使用的资源也很少，为了
方便起见，我也将资源上传了。

该项目是用微软的Visual Studio开发的，请用VS2019来编译。

详细的文档在`Directory`目录下。

## 编译

打开项目解决方案文件即可直接编译。请使用X64 Debug配置方案。其他的配置
方案还未设置正确的头文件包含路径，也没有链接库。

## 运行

运行游戏之前，请将dll文件夹内的dll文件拷贝至可执行文件所在目录，通常应
该是`x64/Debug`

## 操作指南

游戏接受键盘和鼠标输入。但是只能用鼠标与UI互动，只能用键盘和选项互动。

| 按键        | 功能         |
| ESC         | 打开菜单     |
| 方向键上/下 | 在选项间移动 |
| Enter       | 确认         |

# Reference
\[1\] *SDL Game Development* by Shaun Mitchell