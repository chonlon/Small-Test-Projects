from fastapi.staticfiles import StaticFiles
from fastapi import Body, FastAPI

import api


app = FastAPI()
app.mount("/api", api.api_app)
app.mount("/", StaticFiles(directory="static", html=True), name="static")


