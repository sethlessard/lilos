# lil os

This is currently only a kernel.. working to be an OS.

```bash
sudo apt-get install -y build-essential gcc make qemu-system nasm xorriso
```

### Build the operating system

```sh
./build.sh
```

### Run the operating system in Qemu

```sh
./build.sh

make run
```

## Run the ISO in Qemu

```sh
./build.sh

make runiso
```

### Clean the project

```sh
./clean.sh
```
