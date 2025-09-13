# HINA

**HINA** is a C++ software that can divide images in clusters according to their similarity.

You would like to distinguish the holiday photos taken in the evening at the disco from those taken in the morning at the beach, but there are hundreds of them and they come from different sources. This software can do this job for you.

HINA is the acronym for **H**INA **I**s **N**ot an **A**cronym. It means *doll* in Japanese (雛).

> [!IMPORTANT]
> This software doesn't make use of AI, it is based on histogram comparison.

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
unzip alglib-<version>.cpp.gpl.zip -d src
```

### HINA
You can now build HINA using cmake:
```
export OpenCV_DIR=<hina_folder>/opencv_build
cmake .
make hina
```

## Usage
```
./hina -d <directory> -c <clusters> [-n <files> -m <metric> -q]
```
where `directory` is the path to the folder containing your images and `clusters` is the number of groups you want.

You can also limit the analysis to the first N files using the `-n` option. The metric to compare the histogram is an integer between 0 and 5 described [here](https://docs.opencv.org/4.x/d6/dc7/group__imgproc__hist.html#ga994f53817d621e2e4228fc646342d386), default is 0 (correlation). You can obtain a quiet output using the `-q` flag, just the errors and the final clusters will be printed.

## Testing 
To build and run the tests
```
make test
./test
```
The inputs are 8bpp 300x300 grayscale and RGB images taken from the "Sampling" set of The TESTIMAGES archive. See Asuni N., Giachetti A., ["TESTIMAGES: A Large Data Archive For Display and Algorithm Testing"](https://www.tandfonline.com/doi/abs/10.1080/2165347X.2015.1024298?journalCode=ujgt21), Journal of Graphics Tools, Volume 17, Issue 4, 2015, pages 113-125, DOI:10.1080/2165347X.2015.1024298.

## GUI application (Qt)
> [!CAUTION]
> The GUI application is a beta.

You will need [Qt 6](https://www.qt.io/).

```
cd <hina_folder>/qt
export Qt6_DIR=<Qt_folder>
mkdir build && cd build
cmake ..
make
```

## Contributing
Contributions are most welcome by forking the repository and sending a pull request. Errors and new features proposals can be reported opening an issue as well.

