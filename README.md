To compile, create a Fedora toolbox container. Enter the container **as root**, and run the following commands:
```sh
yes | dnf install conan gdb
conan profile detect
printf "[conf]\ntools.system.package_manager:mode=install\n" >> /root/.conan2/profiles/default
conan install . --output-folder=<path to cmake build dir> --build=missing
```

To get include files locally. Find the include directory for conan packages by the path `/root/.conan2/p/b/<package hash>/p/include`, and copy them into the project directory.