作为新手，使用 GitHub 进行多人开发其实不难，核心是通过「分支管理」和「协作流程」让多人分工不冲突。下面用简单步骤带你入门：

### 一、准备工作：每个人都需要做的事

1. **注册 GitHub 账号**打开 [GitHub 官网](https://github.com/)，注册账号（免费版足够多人协作）。
2. **安装 Git**多人开发需要用 Git 工具在本地操作代码，然后同步到 GitHub。
    - Linux 系统：直接在终端输入 `sudo apt install git`（Ubuntu/Debian）。
    - Windows/Mac：去 [Git 官网](https://git-scm.com/) 下载安装，一路默认下一步即可。
3. **绑定 Git 与 GitHub**打开终端（Linux/Mac）或 Git Bash（Windows），输入以下命令（替换成你的 GitHub 账号信息），让本地 Git 认识你的 GitHub 账号：

    ```bash
    git config --global user.name "你的GitHub用户名"
    git config --global user.email "你的GitHub注册邮箱"
    ```


### 二、创建共享仓库：项目发起人操作

1. **新建仓库**登录 GitHub 后，点击右上角「+」→「New repository」，填写：

    - 仓库名（如 `team-project`）
    - 勾选「Initialize this repository with a README」（创建一个说明文件）
    - 点击「Create repository」。
2. **邀请合作者**进入仓库页面 → 点击「Settings」→ 左侧「Collaborators」→ 点击「Add people」，输入合作者的 GitHub 用户名或邮箱，邀请他们加入（对方会收到邮件，接受邀请后即可共同开发）。


### 三、多人协作核心流程（重点！）

假设你们团队有 2 人：A（你）和 B（合作者），分工开发不同功能，步骤如下：

#### 步骤 1：每个人先把仓库「克隆」到本地

仓库是放在 GitHub 服务器上的，本地需要一份副本才能修改。

- 打开仓库页面，点击绿色「Code」按钮，复制 HTTPS 链接（如 `https://github.com/你的用户名/team-project.git`）。
- 每个人在本地终端执行（替换链接）：

    ```bash
    git clone https://github.com/你的用户名/team-project.git
    ```
    
    此时本地会出现一个 `team-project` 文件夹，里面就是仓库内容（初始有 README 文件）。

#### 步骤 2：创建「分支」开发，避免直接修改主代码

多人开发时，**绝对不要直接在主分支（默认 `main` 或 `master`）上修改**，否则容易冲突。正确做法是：每个人创建自己的「分支」，在分支上写代码，完成后再合并到主分支。

1. **进入本地仓库文件夹**

    ```bash
    cd team-project  # 进入克隆下来的文件夹
    ```
    
2. **创建并切换到自己的分支**比如你负责登录功能，创建一个 `login-feature` 分支：

```bash
    git checkout -b login-feature  # 新建并切换到该分支
    ```

  合作者 B 负责注册功能，类似创建 `register-feature` 分支。


#### 步骤 3：在自己的分支上写代码，并「提交」到本地

假设你在本地 `team-project` 文件夹里新增了 `login.py` 文件，完成后需要把修改「保存」到本地 Git 记录中：

1. **查看本地修改**
   ```bash
    git status  # 会显示新增的文件（红色）
    ```

2. **将修改加入「暂存区」**

    ```bash
    git add login.py  # 单个文件，或用 git add . 添加所有修改
    ```
    
3. **提交到本地仓库**写一句备注，说明这次改了什么（必填）：

    ```bash
    git commit -m "新增登录功能：实现用户名密码验证"
    ```


#### 步骤 4：把本地分支「推」到 GitHub 服务器

你的代码现在只在自己电脑上，需要推到 GitHub 让其他人看到：

```bash
git push -u origin login-feature  # 第一次推这个分支需要加 -u origin，后续直接 git push 即可
```

此时 GitHub 仓库页面会出现这个分支（点击「main」下拉框可看到）。

#### 步骤 5：发起「Pull Request」（PR），请求合并到主分支

代码完成后，需要让团队确认没问题，再合并到主分支：

1. 打开 GitHub 仓库页面，会看到一个黄色提示「Compare & pull request」，点击它。
2. 填写说明（比如 “登录功能已完成，请求合并”），然后点击「Create pull request」。

#### 步骤 6：团队审核并「合并」代码

- 其他成员（如 B）可以在 PR 页面查看你的代码，提出修改意见（通过评论）。
- 如果你需要修改，在本地 `login-feature` 分支改完后，再次 `git add` → `git commit` → `git push`，PR 会自动更新。
- 确认无误后，由项目负责人点击 PR 页面的「Merge pull request」→「Confirm merge」，你的代码就合并到主分支了。

#### 步骤 7：同步主分支最新代码到自己的分支

当主分支有更新（比如别人的代码合并了），你需要把这些更新同步到自己的分支，避免后续冲突：


```bash
# 1. 切换到主分支
git checkout main

# 2. 拉取最新代码（同步 GitHub 主分支到本地）
git pull

# 3. 切换回自己的分支（如 login-feature）
git checkout login-feature

# 4. 把主分支的更新合并到自己的分支
git merge main
```

### 四、常见问题解决

1. **代码冲突**多人修改同一个文件的同一部分时，合并会出现冲突。此时 Git 会在文件中用 `<<<<<<<` `=======` `>>>>>>>` 标记冲突位置，你需要手动修改（保留正确代码，删除冲突标记），然后重新 `git add` → `git commit` 即可。
    
2. **忘记创建分支，直接在主分支修改了**先把主分支的修改暂存，再创建分支：

    ```bash
    git stash  # 暂存当前修改
    git checkout -b 你的分支名
    git stash pop  # 恢复暂存的修改到新分支
    ```

3. **想放弃本地修改**还没 `commit` 的修改，用：

    ```bash
    git checkout -- 文件名  # 放弃单个文件
    git checkout .  # 放弃所有文件
    ```

### 总结：核心原则

- 「分支开发，主分支只存可运行的代码」。
- 频繁同步：每天开始开发前，先 `git pull` 同步主分支最新代码。
- 小步提交：每次修改尽量小（比如完成一个小功能就提交），方便回溯和审核。

按照这个流程，多人开发就能有序进行啦！刚开始慢一点没关系，多操作几次就熟练了～