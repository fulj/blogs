
shift+i 行首插入 
shift+a 行尾插入
shift+o 上一行插入
ctrl+r 反撤销
 map s <nop>
 19 map S :w<CR>
 20 map Q :q<CR>
 21 map R :source $MYVIMRC<CR>

set wildmenu

<operation><motion>
dl 删除右边
d3l 往右删3个
dd 剪切
yl
y3l
cw 光标在词前更改词
ciw 光标在词中间
ci" 引号中的词
yi"
di"
df:
yf:
cf:一直删到冒号
退出高亮使用命令，:nohl
zz 当前行中心居中
set ignorecase 大写也能搜到
set smartcase 只搜大写
let mapleader=" " //leader键设置成空格
noremap <LEADER><CR> :nohl<CR>
ranger 文件管理器
vim-fugitive 
airblade/vim-gitgutter 显示+ -
gv.vim 打开提交记录

!command
:62,72 !sort

分屏
split 上下分屏
vsplit 左右分屏
set splitright 光标右边
map sl :set splitright<CR>:vsplit<CR>
map sh :set nosplitright<CR>:vsplit<CR>
map sk :set nosplitbelow<CR>:split<CR>
map sj :set splitbelow<CR>:split<CR>
: e ~/Desktop/a.py 分完屏以后打开新文件 e是edit
ctrl+w + [hjkl] 分屏光标移动 快捷键
visulal模式下多行编辑
map <LEADER>l <C-w>l
map <LEADER>h <C-w>h
map <LEADER>j <C-w>j
map <LEADER>k <C-w>k
更改分屏大小
:res
:vertical resize-5
map <up> :res+5<CR>
map <down> :res-5<CR>
map <left> :vertical resize-5<CR>
map <right> :vertical resize+5<CR>
标签页
tabe
tab往右 +tabnext 往左-tabnext
快捷键
map tt :tabe<CR>
map tj :+tabnext<CR>
map tk :-tabnext<CR>
上下分屏改成左右分屏
map sv <C-w>t<C-w>H
map sh <C-w>t<C-w>K


r !cat setup 从外部复制进来
:%s/old/new/g 搜索整个文件，将所有的old替换为new
:%s/old/new/gc 搜索整个文件，将所有的old替换为new，每次都要你确认是否替换
