import os
import wget

clash_dir = '{}/.config/clash'.format(os.path.expanduser('~'))
clash_subscribe_link_file = '{}/clashlink'.format(clash_dir)
clash_config_file = '{}/config.yaml'.format(clash_dir)

if os.path.isfile(clash_subscribe_link_file):
    with open(clash_subscribe_link_file) as f:
        url = f.readline()
        print('Downloading {}'.format(url))
        print(clash_subscribe_link_file)
        print(clash_config_file)
        # wget.download(url, clash_dir)
        os.system('wget --no-check-certificate {} -O {}'.format(url, clash_config_file))
else:
    print('File not Exists!')


os.system('{0}/clash-linux-amd64 -d {0}'.format(clash_dir))

