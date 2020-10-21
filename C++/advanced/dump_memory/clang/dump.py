import argparse
import subprocess

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='dump cpp by options.')
    parser.add_argument(
        '-f', '--file', help='switch which file', dest='file_input')
    parser.add_argument('-m', '--mode', default='all',
                        help='switch which mode to exec, can input \'simple\' and \'all\'', dest='mode')

    args = parser.parse_args()
    if args.mode == 'simple':
        mode_arg = '-fdump-record-layouts-simple'
    else:
        if args.mode != 'all':
            print('got an error mode name, regard as all')
        mode_arg = '-fdump-record-layouts'

    clangname = 'clang++-10'
    subprocess.call([clangname, '-cc1', mode_arg, args.file_input])
