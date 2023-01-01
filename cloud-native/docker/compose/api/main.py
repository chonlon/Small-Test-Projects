from fastapi import FastAPI

app = FastAPI()
api_app = FastAPI()
app.mount("/api", api_app)


@api_app.get("/hello/{name}")
async def say_hello(name: str):
    return {"message": f"Hello {name}"}


@app.head("/")
async def root():
    return {"message": "Hello World"}


@app.get("/")
async def root():
    return {"message": "Hello World"}