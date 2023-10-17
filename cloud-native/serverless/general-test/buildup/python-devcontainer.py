import logging
import sys

import anyio

import dagger
import typer

SCRIPT = """#!/bin/sh
sed -i 's/deb.debian.org/mirrors.ustc.edu.cn/g' /etc/apt/sources.list
pip install poetry
"""


async def main():
    async with dagger.Connection(dagger.Config(log_output=sys.stderr)) as client:
        await build(client)

async def exec():
    async with dagger.Connection(dagger.Config(log_output=sys.stderr)) as client:
        await exec_c(client)


async def build(client: dagger.Client):
  base = await _build(client)
  
  devcontainer = await (
    base.with_directory("/root/src", client.host().directory("."),exclude=["*.lock"]).with_workdir("/root/src").with_exec(["pwd"]).with_exec(["ls"]).with_exec(["poetry", "install"])
  )

async def exec_c(client: dagger.Client):
  base = await _build(client)
  
  exec = await (
    base.with_exec(["python3", "--version"])
  )

async def _build(client: dagger.Client):
    # If any one of these steps fails, it's an unexpected error so we don't
    # need to handle anything here.

    # The result of `sync` is the container, which allows continued chaining.
    ctr = await (client.container()
        .from_("mcr.microsoft.com/devcontainers/python:3.11-bullseye")
        .with_workdir("/root")
        # Add script with execution permission to simulate a testing tool.
        .with_new_file("python-deps", contents=SCRIPT, permissions=0o750)
        # If the exit code isn't needed: "run-tests; true"
        .with_exec(["sh", "-c", "/root/python-deps; echo -n $? > /root/exit_code"])
    )

    return ctr


app = typer.Typer()

@app.command()
def m():
    try:
        anyio.run(main)
    except dagger.DaggerError:
        # DaggerError is the base class for all errors raised by dagger.
        logging.exception("Unexpected dagger error")
        sys.exit(1)

@app.command()
def e():
    try:
        anyio.run(exec)
    except dagger.DaggerError:
        # DaggerError is the base class for all errors raised by dagger.
        logging.exception("Unexpected dagger error")
        sys.exit(1)
        
app()