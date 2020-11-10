### 库依赖

- 项目中使用的cmake脚本如有find_package失败, 需要注意库是否安装, 一般来说常规安装(使cmake能找到库, 包括不限于apt install/ cmake install/自定义find脚本等)就能使用

- 我是使用vcpkg管理库依赖的, 因为所以小实验项目之间是没有关系的, 所以他们之间是松散的分布在不同文件夹下的, 也就是说: 没有一个总的cmakelists.txt来管理所以项目, 目前我在vcpkg下安装的库为:

  ```
  boost
  folly
  gflags
  libgd
  range-v3
  benchmark
  ```

  如果你也使用vcpkg的话, 使用它来查找库需要为cmake指定toolchain路径

  ```
  -DCMAKE_TOOLCHAIN_FILE=${root_prefix}/vcpkg/scripts/buildsystems/vcpkg.cmake
  ```

  另外如果你和我一样使用vscode的话, 一般来说需要指定toolchain路径: 
  在`项目/.vscode/settings.json`中设置;

  