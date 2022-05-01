FROM tiangolo/uvicorn-gunicorn-fastapi:python3.9

COPY . /app
WORKDIR /app
CMD python3 -m uvicorn main:app --host "0.0.0.0" --port 22224
