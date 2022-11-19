# Genshin Artifact Manage System

This is a management system for the artifact of Genshin Impact.  
It's a project of my c++ course design which finished with my roommate in July, 2022.  

## Function  
### Import your artifacts from the game  
(Only 1 account and only artifacts in level 20, because I'm lazy...)  
### Import artifacts manually  
### Display all the artifact imported like the game  
### Create your favorite set of artifacts  
### Rate based on the set of artifacts, the character and the weapon selected  

## Before using  
### Install the font  
You can find the font in the .7z or “...\Genshin Impact\Genshin Impact Game\YuanShen_Data\StreamingAssets\MiHoYoSDKRes\HttpServerResources\font\zh_cn.ttf”  
### Use "yas" to scan your artifacts
Link: https://github.com/wormtql/yas  
1. Start your game, and open the interface of artifacts in the backpack.
2. Run yas.exe as administrator。
3. Release the mouse until you have scanned all artifacts in level 20, then click the right mouse button to exit the scan.
4. Press Enter in the yas.exe and you will get a file named "mona.json" in the same path of yas.exe  
(You can also use yas.exe in cmd)  
### Enjoy!

## Attention  
1. In "CMakeLists.txt", I commented out the line of "Resources.qrc" because it can improve the speed of compilation.  
2. Other resources and the program's download link：https://pan.baidu.com/s/1zwJWU4oHAYDJmTBugtFGuA?pwd=3d7j
(Because github can't upload over 100 files at one time. Decompress to the path where the codes are.)
