#ubuntu 16.04 above.
echo -e '\n[Install]\nWantedBy=multi-user.target\nAlias=rc-local.service\n' >> /lib/systemd/system/rc-local.service
echo -e '#!/bin/bash\n\nmount -t vboxsf 1_code /mnt/1_code\n' >> /etc/rc.local
sudo ln -s /lib/systemd/system/rc-local.service /etc/systemd/system/
sudo chmod+x /etc/rc.local
#reboot