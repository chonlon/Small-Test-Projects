#!/usr/bin/python -O
import argparse

# define preview cli apps will be used
import subprocess

ls_app = 'logo-ls'
cat_app = 'bat'

# define editor apps will be used
editor_apps = ['vim', 'code', 'kate', 'clion', 'pycharm']

# define directory open apps
dir_apps = ['code', 'ranger', 'clion', 'pycharm', 'dolphin',]


# check if the cli app is installed
def check_clis_installed():
    all_apps = [ls_app, cat_app, 'fzf', 'fd']
    for app in editor_apps:
        all_apps.append(app)
    for app in dir_apps:
        if app not in all_apps:
            all_apps.append(app)
    for app in all_apps:
        check_cli_installed(app)


def check_cli_installed(app):
    try:
        subprocess.check_call(['which', app], stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
    except subprocess.CalledProcessError:
        print('{} is not installed'.format(app))
        exit(1)


if __name__ == "__main__":
    check_clis_installed()
    # get args from command line
    argparser = argparse.ArgumentParser()

    # get path from command line, default is current directory, not required
    argparser.add_argument('path', default='.', nargs='?')
    # get if type is file or directory, default is file, not required, can be file or directory
    argparser.add_argument('-t', '--type', default='f', choices=['f', 'd'])
    # get pattern from command line
    argparser.add_argument('-p', "--pattern", default='', help="pattern to search")
    # get if search hidden files
    argparser.add_argument("-a", "--all", help="search hidden files", default=False, action="store_true")    
    # get open cli app
    argparser.add_argument("-o", "--open", help="open cli app")

    args = argparser.parse_args()

    path = args.path
    file_type = args.type
    pattern = args.pattern
    search_all = args.all
    open_cli = args.open

    # fd in path and fzf select item and pipe to fzf
    command = 'fd --type {} --exclude=.git {} {} . {}'.format(file_type, '-H --ignore' if search_all else '', pattern,
                                                              path)

    command += '|'
    command += 'fzf --preview "{} {}" --select-1'.format(cat_app if file_type == 'f' else ls_app, '{}')
    # get command output
    try:
        output = subprocess.check_output(command, shell=True)
    except:
        # got nothing select from fzf
        exit(0)
    # decode output to string
    output = output.decode('utf-8')

    if len(output) == 0:
        exit(0)

    # open file with
    if not open_cli:
        if file_type == 'f':
            apps: str = '\n'.join(editor_apps)
        else:
            apps: str = '\n'.join(dir_apps)

        # get fzf selected item
        try:
            cli = subprocess.check_output('echo "{}" | fzf'.format(apps), shell=True)
        except:
            exit(0)
        cli = cli.decode('utf-8')
    else:
        check_cli_installed(open_cli)
        cli = open_cli

    # open file
    subprocess.run('{} {}'.format(cli, output).replace('\n', ' '), shell=True)
