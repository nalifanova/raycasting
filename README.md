# Ray Casting

There are some good articles about ray casting like: https://www.redblobgames.com/articles/visibility/
or https://ncase.me/sight-and-light/ So, I've decided to experiment with that a little bit.


### Dependencies
- SFML 2.6.1

### Build && run

```bash
export PATH=$PATH:`dirname $(which cmake)`
mkdir -p build && cd build
if cmake ..; then
    if make; then # Happy case with build
        echo "Build went well."
    else
        echo "Something went wrong with the build process."
    fi
else
    echo "Error: CMake failed."
fi
```

```bash
./build/bin/raycasting 
```