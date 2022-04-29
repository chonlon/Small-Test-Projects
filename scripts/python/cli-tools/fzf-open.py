#!/usr/bin/python -O
import argparse

# define preview cli apps will be used
import subprocess
import sys

ls_app = 'logo-ls'
cat_app = 'bat'
rg_app = 'rga'

# define editor apps will be used
editor_apps = ['vim', 'code', 'ranger', 'kate', 'clion', 'pycharm']

# define directory open apps
dir_apps = ['cd', 'code', 'ranger', 'clion', 'pycharm', 'dolphin',]


# check if the cli app is installed
def check_clis_installed():
    all_apps = [ls_app, cat_app, 'fzf', 'fd', rg_app]
    for app in editor_apps:
        all_apps.append(app)
    for app in dir_apps:
        if app not in all_apps:
            all_apps.append(app)
    for app in all_apps:
        check_cli_installed(app)


def check_cli_installed(app):
    try:
        subprocess.check_call(
            ['which', app], stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
    except subprocess.CalledProcessError:
        if app != 'cd':
            print('{} is not installed'.format(app), file=sys.stderr)
            exit(1)


if __name__ == "__main__":
    check_clis_installed()
    # get args from command line
    argparser = argparse.ArgumentParser()

    # get path from command line, default is current directory, not required
    argparser.add_argument('path', default='.', nargs='+')
    # get if type is file or directory, default is file, not required, can be file or directory
    argparser.add_argument('-t', '--type', default='f', choices=['f', 'd'])
    # get pattern from command line
    argparser.add_argument('-p', "--pattern", default='.',
                           help="pattern to search")
    # get if search hidden files
    argparser.add_argument(
        "-a", "--all", help="search hidden files", default=False, action="store_true")
    # get open cli app
    argparser.add_argument("-o", "--open", help="open cli app")
    # get if execute command
    argparser.add_argument("-x", "--exec", help="execute command",
                          default=False, action="store_true")

    # get file filter by content
    argparser.add_argument("-c", "--content", help="filter file by content provided")

    args = argparser.parse_args()

    paths = args.path
    file_type = args.type
    pattern = args.pattern
    search_all = args.all
    open_cli = args.open
    if_exec = args.exec
    content_filter = args.content
    if not content_filter:
        cat_app = cat_app
    else:
        cat_app = '{rg_app} --pretty --context 5 {content_filter} {{}}'\
            .format(rg_app=rg_app, content_filter=content_filter)



    # fd in path and fzf select item and pipe to fzf
    command = 'fd --type {file_type} --exclude=.git {ignore} {pattern}  {path}'.\
        format(file_type=file_type,
               ignore='-H --ignore' if search_all else '',
               pattern=pattern,
               path= ' '.join(paths))

    if content_filter and file_type == 'f':
        command = '{command} | xargs rga {content_filter} --files-with-matches '.\
            format(command=command, content_filter=content_filter)

    command += '|'
    command += 'fzf --sort --preview "{} {}" --select-1'.format(
        cat_app if file_type == 'f' else ls_app, '{}')

    # get command output
    try:
        output = subprocess.check_output(command, shell=True)
    except:
        # got nothing select from fzf
        exit(-1)
    # decode output to string
    output = output.decode('utf-8')

    if len(output) == 0:
        exit(-1)

    # open file with
    if not open_cli:
        if file_type == 'f':
            apps: str = '\n'.join(editor_apps)
        else:
            apps: str = '\n'.join(dir_apps)

        # get fzf selected item
        try:
            cli = subprocess.check_output(
                'echo "{}" | fzf'.format(apps), shell=True)
        except:
            exit(-1)
        cli = cli.decode('utf-8')
    else:
        check_cli_installed(open_cli)
        cli = open_cli

    command = '{} {}'.format(cli, output).replace('\n', ' ')
    # open file
    if if_exec:
        if cli == 'cd':
            print('[Warning] cd is not working in python')
        subprocess.run(command, shell=True)
    else:
        print(command)

