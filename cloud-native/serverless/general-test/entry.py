import typer
import os

app = typer.Typer()

@app.command(help="test")
def dagger_startup():
  os.system("poetry run python buildup/dagger-startup.py")

if __name__ == "__main__":
  app()