from fastapi import FastAPI
from fastapi.staticfiles import StaticFiles


app = FastAPI()
# app.mount("/static", StaticFiles(directory="static"), name="static")
app.mount("/", StaticFiles(directory="static", html=True), name="static")


@app.get("/api/hello/{name}")
def api_hello(name: str):
    return {"hello": f"{name}"}


@app.get("/hello/{name}")
async def say_hello(name: str):
    return {"message": f"Hello {name}"}
