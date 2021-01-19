
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
