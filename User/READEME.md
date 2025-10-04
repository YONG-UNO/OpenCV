## Ubuntu下安装matlab
### https://matlab.mathworks.com/
### 账号:54703t380@stu.xidian.edu.cn
### 密码:XMDEUk3VVV(假的)
### 勾选 Create symbolic links
### 不勾选 improve....
### 启动:命令提示符 matlab
### matlab缩放:https://ww2.mathworks.cn/matlabcentral/answers/347686-4k-scaling-on-ubuntu


# git使用
| 拉取 pull                          | 提取 fetch                         |
|----------------------------------|----------------------------------|
| git pull = git fetch + git merge | git fetch                        |
| git fetch                        | 从远程仓库获取最新的提交数据                   |
| git merge                        | 将远程仓库的最新代码下载到本地，并且自动合并到当前正在工作的分支 |
| git pull                         |当你想快速让本地分支和远程分支保持一致，并且希望 Git 自动处理合并（如果没有冲突的话）时，就可以使用拉取操作|
| git fetch                        |如果你想先查看远程仓库有哪些更新，再决定是否合并，或者手动选择合并的时机，就可以先执行提取操作。这样能更灵活地控制代码合并的流程，避免自动合并可能带来的冲突处理等问题。|