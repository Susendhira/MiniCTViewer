# 🏥 Mini CT Viewer

A desktop CT image viewer built with **C++ and Qt5** for the SurgeonLabs developer assessment.

## Features
- 📁 Load folders of CT images (PNG, JPG, BMP, TIFF)
- 🖼️ Smooth image viewer with zoom and pan
- 🎚️ Slice navigation with slider and Prev/Next buttons
- 🌗 Real-time brightness and contrast adjustment
- ✏️ Annotation tools with pixel measurements

## Tech Stack
| | |
|--|--|
| Language | C++17 |
| UI Framework | Qt 5.14.1 |
| Build System | qmake |
| OS | Linux Ubuntu 22.04 |

## Build Instructions

### Prerequisites
```bash
sudo apt install qt5-default
```

### Build
```bash
git clone https://github.com/Susendhira/MiniCTViewer.git
cd MiniCTViewer
qmake MiniCTViewer.pro
make
./MiniCTViewer
```

## How to Use
1. Click **Open Folder** to load CT images
2. Use **Prev/Next** buttons or **slider** to navigate slices
3. **Scroll mouse wheel** to zoom, **click and drag** to pan
4. Adjust **Brightness** and **Contrast** in real time
5. Use **Draw Line** or **Draw Rectangle** to annotate with pixel measurements
