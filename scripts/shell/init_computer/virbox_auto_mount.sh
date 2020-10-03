#ubuntu 16.04 above.
echo -e '[Install]\nWantedBy=multi-user.target\nAlias=rc-local.service\n' >> /lib/systemd/system/rc-local.service
echo -e '#!/bin/bash\n\nmount -t vboxsf 1_code /mnt/1_code\nmount -t vboxsf 1_code /mnt/1_code' >> /etc/rc.local
#reboot