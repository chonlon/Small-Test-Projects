## 使用sudo会有问题, 主要在于当前用户在使用sudo命令后会变成root, 那么像~就会变成 /root
echo "watchout: sudo needed"
./install_basic.sh
./ssh_config.sh
./install_zsh.sh
./install_vcpkg.sh
./virbox_auto_mount.sh