import subprocess
import sys
import argparse

class Initer:
    _is_arch: bool
    def __init__(platform: str):
        pass

    def init_zsh():
        pass

    def init_ssh():
        pass

    def init_home():
        pass

    

if __name__ == "__main__":
    parser = argparse.ArgumentParser("Init", description="init my computer with basic zsh and ssh configed")
    parser.add_argument('--platform', '-p',
        required=False,
        default='Arch')

    parser.parse_args()