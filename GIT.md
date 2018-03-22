# 1、安装git
- 用Debian或Ubuntu Linux，通过一条`sudo apt-get install git`就可以直接完成Git的安装，非常简单。

- 老一点的Debian或Ubuntu Linux，要把命令改为`sudo apt-get install git-core`，因为以前有个软件也叫GIT（GNU Interactive Tools），结果Git就只能叫git-core了。由于Git名气实在太大，后来就把GNU Interactive Tools改成gnuit，git-core正式改为git。

- 如果是其他Linux版本，可以直接通过源码安装。先从Git官网下载源码，然后解压，依次输入：./config，make，sudo make install这几个命令安装就好了。

- Windows就忽略了。

# 2、配置git
（这一步意义不大，似乎不设置也没有影响）我想错了，这步还是很重要的，这是身份识别的象征。
$ git config --global user.name "Your Name"
$ git config --global user.email "email@example.com"

# 3、常规操作
$ mkdir learngit
$ cd learngit
$ git init
$ git add .   添加全部文件，也可以添加指定文件，多个用空格隔开
$ git commit -m "备注内容"
$ git status  查看结果，其中有颜色变化
$ git diff readme.txt   如果提示readme.txt文件被修改，命令查看具体修改内容
$ git log  查看提交的历史记录
$ git log --pretty=oneline  如果嫌输出信息太多，看得眼花缭乱的，可以试试加上--pretty=oneline参数
需要友情提示的是，你看到的一大串类似3628164...882e1e0的是commit id（版本号），和SVN不一样，Git的commit id不是1，2，3……递增的数字，而是一个SHA1计算出来的一个非常大的数字，用十六进制表示。

## 4、时光机穿梭
首先，Git必须知道当前版本是哪个版本，在Git中，用HEAD表示当前版本，也就是最新的提交3628164...882e1e0，上一个版本就是HEAD^，上上一个版本就是HEAD^^，当然往上100个版本写100个^比较容易数不过来，所以写成HEAD~100。

>$ git reset --hard HEAD^  把当前版本“append GPL”回退到上一个版本

最新的那个版本append GPL已经看不到了！好比你从21世纪坐时光穿梭机来到了19世纪，想再回去已经回不去了，肿么办？

办法其实还是有的，只要上面的命令行窗口还没有被关掉，你就可以顺着往上找啊找啊，找到那个append GPL的commit id是3628164...，于是就可以指定回到未来的某个版本：

$ git reset --hard 3628164
HEAD is now at 3628164 append GPL
版本号没必要写全，前几位就可以了，Git会自动去找。当然也不能只写前一两位，因为Git可能会找到多个版本号，就无法确定是哪一个了。

Git的版本回退速度非常快，因为Git在内部有个指向当前版本的HEAD指针，当你回退版本的时候，Git仅仅是把HEAD从指向append GPL。

现在，你回退到了某个版本，关掉了电脑，第二天早上就后悔了，想恢复到新版本怎么办？找不到新版本的commit id怎么办？

在Git中，总是有后悔药可以吃的。当你用$ git reset --hard HEAD^回退到add distributed版本时，再想恢复到append GPL，就必须找到append GPL的commit id。Git提供了一个命令git reflog用来记录你的每一次命令。

>$ git reflog  查看命令历史
	
## 5、工作区和暂存区
在电脑里能看到的目录，比如我的github文件夹就是一个工作区。
工作区有一个隐藏目录.git，这个不算工作区，而是Git的版本库。Git的版本库里存了很多东西，其中最重要的就是称为stage（或者叫index）的暂存区，还有Git为我们自动创建的第一个分支master，以及指向master的一个指针叫HEAD。

第一步是用git add把文件添加进去，实际上就是把文件修改添加到暂存区；

第二步是用git commit提交更改，实际上就是把暂存区的所有内容提交到当前分支。

## 6、撤销修改和删除文件
git checkout -- file
git reset HEAD file

删除本地文件 rm test.txt

- 一是确实要从版本库中删除该文件，那就用命令git rm删掉，并且git commit

-  二是误删，轻松恢复  git checkout -- test.txt


## 7、远程仓库配置（重要）
### 创建SSH Key
$ ssh-keygen -t rsa -C "youremail@example.com"
然后一路回车，使用默认值即可，由于这个Key也不是用于军事目的，所以也无需设置密码。

如果一切顺利的话，可以在用户主目录里找到.ssh目录，里面有id_rsa和id_rsa.pub两个文件，这两个就是SSH Key的秘钥对，id_rsa是私钥，不能泄露出去，id_rsa.pub是公钥，可以放心地告诉任何人。

### 登陆GitHub，打开“Account settings”，“SSH Keys”页面

然后，点“Add SSH Key”，填上任意Title，在Key文本框里粘贴id_rsa.pub文件的内容。
Coding同样的道理。





进入数据库，导入sql文件，输入“source sql文件的路径”（注意你的文件路径要是复制来的，要将"\"全部换成“/”）

输入“show tables”，你就会看到你导入的表了。

ova （原创动画录影带） 编辑
原创动画录影带（Original Video Animation）简称。一般指通过DVD，蓝光碟等影碟发行的方式为主的剧集，也指一些相较原著篇幅较小且内容不一的动画剧集，相较于电视动画、剧场版电视或者电影院播放的不同，OVA则是从发行渠道来划分的，一般通过DVD等影碟的形式发行。一般的OVA不见得广为人知，选材一般是应某个特定作品的爱好者的要求而出的，一般是将情节补完，以满足爱好者收藏的需要。也有的OVA是作为实验期的作品，如果反响不错，就很有可能做成电视动画。