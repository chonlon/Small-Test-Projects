import pathlib
import sys
from fastapi import File
import typer
import pathlib
import subprocess

file_out = None


def dfs(dir: pathlib.Path):
    for filename in dir.iterdir():
        if filename.is_dir():
            yield from dfs(filename)
        else:
            yield filename


def proc_file(file: str):
    typer.echo(f"processing: {file}")
    # split parent dir and file name
    dirname, filename = pathlib.Path(file).parent, pathlib.Path(file).name
    # call system make
    command = f"make r FOLDER='{dirname}' FILE='{filename}'"
    subprocess.run(command, shell=True)
    file_out.write(
        f"{{'filename': '{filename}', 'url': '/models/{filename}.e3dx'}},\n")


def main(dirname: str, count: int = 10):
    typer.echo(f"run in {dirname}")
    # check if dirname is valid
    if not pathlib.Path(dirname).is_dir():
        typer.echo(f"{dirname} is not a valid directory")
        sys.exit(1)
    # dfs find all files in dirname
    for file in dfs(pathlib.Path(dirname)):
        if (file.name.endswith(".SLDPRT") or file.name.endswith(".sldprt")):
            proc_file(file)
            if count == 0:
                break
            count -= 1


if __name__ == "__main__":
    with open("output.txt", "w") as file:
        file_out = file
        typer.run(main)
