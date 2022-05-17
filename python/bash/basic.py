import os
import time

def bash_shell(bash_command):
    """
    python 中执行 bash 命令
    :param bash_command:
    :return: bash 命令执行后的控制台输出
    """
    try:
        return os.popen(bash_command).read().strip()
    except:
        return None


def find_target(target_path="./../", key='.git'):
    """
    查找目标目录所在的目录 ： 如 ／aa/bb/.git --> return /aa/bb/
    :param target_path:
    :param key: target
    :return:
    """
    walk = os.walk(target_path)
    for super_dir, dir_names, file_names in walk:
        for dir_name in dir_names:
            if dir_name == key:
                dir_full_path = os.path.join(super_dir, dir_name)
                # print(dir_full_path, super_dir, dir_name, sep=" ## ")
                yield super_dir


if __name__ == '__main__':
    print("start execute bash ...........")
    st = time.time()
    cwd = os.getcwd()
    # this for repo
    for repo_path in find_target(os.getcwd(), key='.repo'):
        os.chdir(repo_path)
        if repo_path == os.getcwd():
            print('find repo in -->', repo_path)
            print(bash_shell('pwd'))
            print(bash_shell('repo forall -c git config core.fileMode false --replace-all'))

        else:
            print('error in chdir 2 {}'.format(repo_path))
        if os.getcwd() != cwd:
            os.chdir(cwd)
        if os.getcwd() != cwd:
            print('change 2 cwd FAIL !!!  {}'.format(cwd))

    # this for git
    for git_path in find_target(os.getcwd(), key='.git'):
        os.chdir(git_path)
        if git_path == os.getcwd():
            print('find git in -->', git_path)
            print(bash_shell('pwd'))
            print(bash_shell('git config --global core.filemode false'))
        else:
            print('error in chdir 2 {}'.format(git_path))
        if os.getcwd() != cwd:
            os.chdir(cwd)
        if os.getcwd() != cwd:
            print('change 2 cwd FAIL !!!  {}'.format(cwd))

    et = time.time()
    print('\n\n    #### execute finished in {:.3f} seconds ####'.format(et - st))
    print('\n')
    # test for bash_command
    # print(bash_shell('git init'))
    # print(bash_shell('ls -al'))