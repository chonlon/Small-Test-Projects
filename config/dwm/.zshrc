# Personal Zsh configuration file. It is strongly recommended to keep all
# shell customization and configuration (including exported environment
# variables such as PATH) in this file or in files sourced from it.
#
# Documentation: https://github.com/romkatv/zsh4humans/blob/v5/README.md.

# Periodic auto-update on Zsh startup: 'ask' or 'no'.
# You can manually run `z4h update` to update everything.
zstyle ':z4h:' auto-update      'no'
# Ask whether to auto-update this often; has no effect if auto-update is 'no'.
zstyle ':z4h:' auto-update-days '28'

# Keyboard type: 'mac' or 'pc'.
zstyle ':z4h:bindkey' keyboard  'pc'

# Don't start tmux.
zstyle ':z4h:' start-tmux       no

# Mark up shell's output with semantic information.
zstyle ':z4h:' term-shell-integration 'yes'

# Right-arrow key accepts one character ('partial-accept') from
# command autosuggestions or the whole thing ('accept')?
zstyle ':z4h:autosuggestions' forward-char 'accept'

# Recursively traverse directories when TAB-completing files.
zstyle ':z4h:fzf-complete' recurse-dirs 'no'

# Enable direnv to automatically source .envrc files.
zstyle ':z4h:direnv'         enable 'no'
# Show "loading" and "unloading" notifications from direnv.
zstyle ':z4h:direnv:success' notify 'yes'

# Enable ('yes') or disable ('no') automatic teleportation of z4h over
# SSH when connecting to these hosts.
zstyle ':z4h:ssh:example-hostname1'   enable 'yes'
zstyle ':z4h:ssh:*.example-hostname2' enable 'no'
# The default value if none of the overrides above match the hostname.
zstyle ':z4h:ssh:*'                   enable 'no'

# Send these files over to the remote host when connecting over SSH to the
# enabled hosts.
zstyle ':z4h:ssh:*' send-extra-files '~/.nanorc' '~/.env.zsh'

# Clone additional Git repositories from GitHub.
#
# This doesn't do anything apart from cloning the repository and keeping it
# up-to-date. Cloned files can be used after `z4h init`. This is just an
# example. If you don't plan to use Oh My Zsh, delete this line.
z4h install ohmyzsh/ohmyzsh || return

# Install or update core components (fzf, zsh-autosuggestions, etc.) and
# initialize Zsh. After this point console I/O is unavailable until Zsh
# is fully initialized. Everything that requires user interaction or can
# perform network I/O must be done above. Everything else is best done below.
z4h init || return

# Extend PATH.
path=(~/bin $path)

# Export environment variables.
export GPG_TTY=$TTY

# Source additional local files if they exist.
z4h source ~/.env.zsh

# Use additional Git repositories pulled in with `z4h install`.
#
# This is just an example that you should delete. It does nothing useful.
z4h source ohmyzsh/ohmyzsh/lib/diagnostics.zsh  # source an individual file
z4h load   ohmyzsh/ohmyzsh/plugins/emoji-clock  # load a plugin
z4h load   ohmyzsh/ohmyzsh/custom/plugins/zsh-proxy
z4h load   ohmyzsh/ohmyzsh/plugins/extract
# z4h load   ohmyzsh/ohmyzsh/plugins/z
z4h load   ohmyzsh/ohmyzsh/plugins/wd
# z4h load   ohmyzsh/ohmyzsh/plugins/shell-proxy
z4h load   ohmyzsh/ohmyzsh/custom/plugins/git-open


z4h load   zsh-autosuggestions
z4h load   zsh-completions
z4h load   zsh-syntax-highlighting
z4h load   zsh-history-substring-search

# Define key bindings.
z4h bindkey z4h-backward-kill-word  Ctrl+Backspace     Ctrl+H
z4h bindkey z4h-backward-kill-zword Ctrl+Alt+Backspace

z4h bindkey undo Ctrl+/ Shift+Tab  # undo the last command line change
z4h bindkey redo Alt+/             # redo the last undone command line change

z4h bindkey z4h-cd-back    Alt+Left   # cd into the previous directory
z4h bindkey z4h-cd-forward Alt+Right  # cd into the next directory
z4h bindkey z4h-cd-up      Alt+Up     # cd into the parent directory
z4h bindkey z4h-cd-down    Alt+Down   # cd into a child directory

# Autoload functions.
autoload -Uz zmv

# Define functions and completions.
function md() { [[ $# == 1 ]] && mkdir -p -- "$1" && cd -- "$1" }
function cdl() { 
  if [[ $# == 0 ]]; then
    cd $HOME && lsd -- "$HOME"
  else
    z "$1" && lsd -- "$PWD" 
  fi
}
compdef _directories md

# Define named directories: ~w <=> Windows home directory on WSL.
[[ -z $z4h_win_home ]] || hash -d w=$z4h_win_home

# Define aliases.
alias l='exa -lah'
alias ll='exa -lah'
alias c=clear
alias cd=cdl
alias tree='tree -a -I .git'
alias gc='gitmoji -c'
alias dr='docker run --rm -it -v share_data:/root/data/'
compdef dr='docker'
alias db='docker build'
alias lls='logo-ls'
alias ls="exa"
alias vi="nvim"
alias vim="nvim"
alias grep="rg"
alias cat="bat --style=plain"
alias du="dust"
alias grep="rg"
alias find="fd"
alias ra="ranger"
alias rv="EDITOR=vim ranger"
alias clion='f(){ clion $1  1>>/dev/null 2>>/dev/null & }; f'
alias goland='f() { goland $@ 1>>/dev/null 2>>/dev/null & }; f'
alias pycharm='f() { pycharm $1 1>>/dev/null 2>>/dev/null & }; f'
alias webstorm='f() { webstorm $@ 1>>/dev/null 2>>/dev/null & }; f'
alias kate='f() { kate $@ 1>>/dev/null 2>>/dev/null }; f'
alias dolphin='f() { dolphin $@ 1>>/dev/null 2>>/dev/null }; f'
alias fzf-open-alias='f() {eval "$(fzf-open $@)"}; f'
alias fhd='fzf-open-alias "$HOME" -t d'
alias fhf='fzf-open-alias "$HOME"'
alias fhc='f() {eval "$(fzf-open -c $@ $HOME)"}; f'
alias fcc='f() {eval "$(fzf-open -c $@)"}; f'
alias fcf='fzf-open-alias'
alias fcd='fzf-open-alias -t d'
function fcp() {
    local dirnamev="$(fzf-open $@ | awk '{print $2}')"
    if [[ -z "${dirnamev}" ]]; then
        return 0
    fi
    copyq add ${dirnamev}
}

function fwd() {
    local dirnamev="$(wd list | sed '1d' | awk '{print $3}' | tr '\n' ' ')"

    if [[ -z "${dirnamev}" ]]; then
        return 0
    fi
    eval 'fzf-open-alias ${dirnamev} $@ -t d'
}
function fwc() {
    local dirnamev="$(wd list | sed '1d' | awk '{print $3}' | tr '\n' ' ')"
    if [[ -z "${dirnamev}" ]]; then
        return 0
    fi
    eval 'fzf-open-alias ${dirnamev} -c $@'
}
function fwf() {
    local dirnamev="$(wd list | sed '1d' | awk '{print $3}' | tr '\n' ' ')"
    if [[ -z "${dirnamev}" ]]; then
        return 0
    fi
    eval 'fzf-open-alias ${dirnamev} $@'
}

function rga-fzf() {
	RG_PREFIX="rga --files-with-matches"
	local file
	file="$(
		FZF_DEFAULT_COMMAND="$RG_PREFIX '$1'" \
			fzf --sort --preview="[[ ! -z {} ]] && rga --pretty --context 5 {q} {}" \
				--phony -q "$1" \
				--bind "change:reload:$RG_PREFIX {q}" \
				--preview-window="70%:wrap"
	)" &&
	echo "opening $file" &&
	xdg-open "$file"
}


export EDITOR="nvim"

# Set shell options: http://zsh.sourceforge.net/Doc/Release/Options.html.
setopt glob_dots     # no special treatment for file names with a leading dot
setopt no_auto_menu  # require an extra TAB press to open the completion menu
export QT_AUTO_SCREEN_SCALE_FACTOR=1
export QT_SCREEN_SCALE_FACTORS="1.5"


eval "$(zoxide init zsh)"
#eval $(thefuck --alias fu)

#eval $(thefuck --alias)
