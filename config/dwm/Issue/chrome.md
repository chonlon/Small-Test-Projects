之前装的KDE，应该是用的KDE wallet存储密码，切换dwm以后存储不了密码

解决方案应该有两个：

1. 开机启动 kde 钱包，但是都不用kde了，就不想这么做

2. 使用gnome-keyring，但是应该是之前装系统的影响所以需要修改一些地方；
   
   1. .config里面的 google-chrome 直接删掉（不知道里面哪个文件有影响，全删掉好了）
   
   2. 按照教程开启 gnome-keyring 开机启动
   
   3. 修改 /usr/share/applications/google-chrome.desktop 的exec 加上 `--password-store=gnome` 即可
