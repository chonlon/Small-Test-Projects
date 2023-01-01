import pathlib

import docker

docker = docker.from_env()

nginx_network = docker.networks.list(names='bridge')[0]
try:
    list = docker.networks.list(names = 'fastapi-nginx-proxy')
    if len(list) > 0:
        nginx_network = list[0]
    else :
        nginx_network = docker.networks.create('fastapi-nginx-proxy', driver='bridge')
except Exception as e:
    print(e)


# create volumes
# docker.volumes.create('nginx-conf')

# find or build image
local_images = docker.images.list()
fastapi_built = False
# check if image is already built
for image in local_images:
    print(image)
    if len(image.tags) > 0 and image.tags[0] == 'fast-api:local':
        fastapi_built = True
        break

if not fastapi_built:
    print("building image {}".format("fast-api:local"))
    docker.images.build(path='./api', tag='fast-api:local')
else:
    print("image already built, using cached image")

# find or download image
print("pulling image {}".format("nginx:latest"))
docker.images.pull('nginx', tag='latest')

# login to aliyun

# run containers
print("running")

try:
    docker.containers.get('fast-api').remove(force=True)
except:
    pass
try:
    docker.containers.get('nginx').remove(force=True)
except:
    pass

try:
    fastapi_container = docker.containers.run('fast-api:local',
                          name='fast-api',
                          detach=True,
                          )
    nginx_network.connect(fastapi_container, aliases=['fast-api'])

    docker.containers.run('nginx:latest',
                          name='nginx',
                          network=nginx_network.id,
                          detach=True,
                          ports={'80/tcp': 22223},
                          # mounts=[
                          #     docker.types.Mount(
                          #         target='/etc/nginx/conf.d',
                          #         source=pathlib.Path('./nginx/conf/fastapi.conf').absolute(),
                          #         type='bind'
                          #     ),
                          # ],
                          volumes={pathlib.Path('./nginx/conf/fastapi.conf').absolute(): {'bind': '/etc/nginx/conf.d/default.conf', 'mode': 'rw'}})
except Exception as e:
    print(pathlib.Path('./nginx/conf/fastapi.conf').absolute())
    print(e)