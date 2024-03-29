from fastapi import Body, FastAPI
from pydantic import BaseModel, Field
from typing import Optional

api_app = FastAPI()
class Item(BaseModel):
    name: str
    description: Optional[str] = Field(
        None, title="The description of the item", max_length=300
    )
    price: float = Field(..., gt=0, description="The price must be greater than zero")
    tax: Optional[float] = None


@api_app.put("/post/{item_id}")
async def update_item(item_id: int, item: Item = Body(..., embed=True)):
    results = {"item_id": item_id, "item": item}
    return results


@api_app.get("/hello/{name}")
async def api_hello(name: str):
    return {"hello": f"{name}"}