# Genshin Artifact Manage System

This is a management system for the artifact of Genshin Impact.  
It's a project of my c++ course design which finished with my roommate in July, 2022.  

## Function  
![image](https://user-images.githubusercontent.com/19246285/202847182-be87947f-da19-4eb1-968b-379aa455ba1a.png)
### Import your artifacts from the game  
(Only 1 account and only artifacts in level 20, because I'm lazy...)  
![image](https://user-images.githubusercontent.com/19246285/202847219-75432c16-b385-423b-87b4-cdb207dd3e20.png)
### Import artifacts manually  
![image](https://user-images.githubusercontent.com/19246285/202847258-58114242-eb58-4a2e-b65e-ca69b66a64a0.png)
### Display all the artifact imported like the game  
![image](https://user-images.githubusercontent.com/19246285/202847280-629f6110-b50b-4e7f-951c-3e66e902187e.png)
### Create your favorite set of artifacts  
![image](https://user-images.githubusercontent.com/19246285/202847297-e888380f-0cab-4705-a95b-5b6c0b08c7ba.png)
### Rate based on the set of artifacts, the character and the weapon selected  
![image](https://user-images.githubusercontent.com/19246285/202847355-d5eebbb0-46ec-463d-8091-f521619f78db.png)

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
