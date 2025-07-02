# HINA

**HINA** is a c++ software that can divide images in clusters according to their similarity.

You would like to distinguish the holiday photos taken in the evening at the disco from those taken in the morning at the beach, but there are hundreds of them and they come from different sources. This software can do this job for you.

HINA is the acronym for **H**INA **I**s **N**ot an **A**cronym. It means *doll* in Japanese (雛).

## Installation
You will need [OpenCV](https://opencv.org/ "OpenCV") and [ALGLIB](https://www.alglib.net). [CMake](https://cmake.org/) is needed to build.

### OpenCV
OpenCV is a computer vision library. We need it to read the images, compute their histograms and compare them.

Download the compressed sources from [this page](https://github.com/opencv/opencv/releases), unpack them in the `opencv_build` directory and build the library:
```
unzip opencv-<version>.zip
mkdir opencv_build && cd opencv_build
cmake  ../opencv-<version>
make
```
### ALGLIB
ALGLIB is a numerical analysis and data processing library. We need it to perform the hierarchical clustering.

Download the compressed sources from [this page](https://www.alglib.net/download.php#cpp) and unpack them in the `src/alglib-cpp` directory:
```
mkdir src/alglib-cpp
unzip alglib-<version>cpp.gpl.zip -d src/alglib-cpp
```

### HINA
You can now build HINA using cmake:
```
export OpenCV_DIR=<hina_folder>/opencv_build
cmake .
make
```

## Usage
```
./hina -d <directory> -c <clusters> [-n <files>]
```
where `directory` is the path to the folder containing your images and `clusters` is the number of groups you want. You can also limit the analysys to the first N files using the `-n` option.

## Contributing
Contributions are most welcome by forking the repository and sending a pull request. Errors and new features proposals can be reported opening an issue as well.

